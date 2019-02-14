#include <seastar/core/app-template.hh>
#include <seastar/core/reactor.hh>
#include <seastar/core/future-util.hh>

#include <boost/range/algorithm/sort.hpp>
#include <boost/range/irange.hpp>

#include <iostream>

using namespace seastar;

using aligned_buffer = std::unique_ptr<char[], free_deleter>;

constexpr size_t page_size = 4096;

template<typename I, typename addrFunc>
size_t get_smallest_idx(const I& indexes, size_t numBuffers, size_t maxRecords, addrFunc addr) {
    size_t idx = numBuffers; // invalid
    for(size_t i = 0; i < numBuffers; ++i) {
        // continue with the loop body only if the current chunk isn't finished
        if(indexes[i] >= maxRecords)
            continue;
        // if not initialized yet or is indeed an index to a smaller record
        if(idx == numBuffers || (memcmp(addr(i), addr(idx), page_size) < 0))
            idx = i;
    }
    assert(idx != numBuffers);
    return idx;
};

struct context {
    sstring filename;
    size_t num_to_create = 0;
    size_t max_in_ram_count = 0;
    size_t max_in_ram = 0;
    size_t file_size = 0;
    size_t num_runs = 0;
    size_t chunk_size = 0;
    size_t records_in_chunk = 0;
    size_t records_in_run = 0;

    file f;
    std::vector<file> runs;

    future<> create_file();
    future<> sort_file();
};

future<> context::sort_file() {
    return open_file_dma(filename, open_flags::rw).then([this] (file f_in) {
        f = std::move(f_in);
        // should be a multiple of the cores
        assert(max_in_ram_count % smp::count == 0);
        max_in_ram = max_in_ram_count * page_size;

        file_size = f.size().get0();
        // file size should be a multiple of the number of records to process at once
        assert(file_size % max_in_ram == 0);

        // the total number of records cannot be more than the square of the number of records we can keep in RAM
        assert(pow(max_in_ram_count, 2) >= file_size / page_size);

        num_runs = file_size / max_in_ram;
        chunk_size = max_in_ram / smp::count;
        records_in_chunk = chunk_size / page_size;
        records_in_run = max_in_ram / page_size;
        std::cout << "file_size is " << file_size << "\n";
        std::cout << "max_in_ram is " << max_in_ram << "\n";
        std::cout << "num_runs to sort and merge is " << num_runs << "\n";
        std::cout << "chunk_size is " << chunk_size << "\n";
        std::cout << "records_in_chunk is " << records_in_chunk << "\n";
        std::cout << "records_in_run is " << records_in_run << "\n";

        runs.resize(num_runs);

        auto run_range = boost::irange<size_t>(0, num_runs);
        return do_for_each(run_range, [this] (auto run) {
            std::cout << "run is " << run << "\n";

            struct chunks_struct {
                // the chunks in memory
                std::vector<aligned_buffer> data;
                // pointers to the data in the chunks (for sorting)
                std::vector<std::vector<char*>> pointers;

                chunks_struct() : data(smp::count), pointers(smp::count) {}

                chunks_struct(const chunks_struct&) = delete;
                chunks_struct(chunks_struct&&) = default;
            };

            // this chunks struct could have been moved to the context class...
            return do_with(chunks_struct(), [this, run] (auto& chunks) {
                return smp::invoke_on_all([this, &chunks, run] {
                    auto core = engine().cpu_id();
                    // TODO: not sure why It crashes if I comment this std::cout statement...
                    // perhaps the delay from the output and the flushing hides a race/bug?
                    // also with big-enough loads the crash gets triggered even if this std::cout is here
                    std::cout << "core is " << core << std::endl;
                    auto& chunk = chunks.data[core];
                    auto& sorted_chunk = chunks.pointers[core];

                    chunk = allocate_aligned_buffer<char>(chunk_size, f.memory_dma_alignment());
                    auto read_f = f.dma_read(run * max_in_ram + core * chunk_size, chunk.get(), chunk_size);

                    // we can do this allocation and pointer filling here instead of in the continuation
                    // since it isn't dependent on the actual values of the records in memory
                    sorted_chunk.resize(records_in_chunk);
                    for(auto i = 0u; i < records_in_chunk; ++i)
                        sorted_chunk[i] = &(chunk[i * page_size]);

                    // sort the pointers when the chunk is read
                    return read_f.then([this, &sorted_chunk] (size_t bytes_read) {
                        assert(bytes_read == chunk_size);

                        boost::range::sort(sorted_chunk, [] (const char* lhs, const char* rhs) {
                            return memcmp(lhs, rhs, page_size) < 0;
                        });

                        return now();
                    });
                }).then([this, &chunks, run] {
                    return open_file_dma(filename + std::to_string(run), open_flags::create | open_flags::truncate | open_flags::rw).then(
                            [this, &chunks, run] (file f_in) {
                        // save the file - will be using it later for the <num_runs>-way merge
                        runs[run] = f_in;

                        return do_with(semaphore(0), std::vector<size_t> (smp::count, 0),
                                [this, &chunks, run] (semaphore& sem, auto& indexes) {
                            for(size_t record = 0; record < records_in_run; ++record) {
                                auto idx = get_smallest_idx(indexes, smp::count, records_in_chunk,
                                    [&pointers = chunks.pointers, &indexes] (size_t i) { return pointers[i][indexes[i]]; });

                                runs[run].dma_write(record * page_size, chunks.pointers[idx][indexes[idx]], page_size).then([&sem] (size_t ret) {
                                    assert(ret == page_size);
                                    sem.signal(1);
                                });

                                ++indexes[idx];
                            }
                            return sem.wait(records_in_run);
                        }).then([this, run] {
                            return runs[run].flush();
                        });
                    });
                });
            });
        }).then([this] {
            struct merge_data {
                semaphore sem_r;
                semaphore sem_w;
                const size_t buffered_size;
                const size_t num_buffered;
                std::vector<aligned_buffer> buffered;
                std::vector<size_t> buffered_idx;
                std::vector<size_t> records_read;
            };

            // this is weird - not sure why I did it this way... perhaps should be in the context...
            auto md = merge_data {0, 0,
                                  max_in_ram / num_runs,
                                  max_in_ram / num_runs / page_size,
                                  std::vector<aligned_buffer>(num_runs),
                                  std::vector<size_t>(num_runs),
                                  std::vector<size_t>(num_runs)
            };
            assert(md.buffered_size % page_size == 0);

            std::cout << "ABOUT TO DO THE <NUM_RUNS> way merge of the final file\n";
            std::cout << "buffered_size is " << md.buffered_size << "\n";
            std::cout << "num_buffered is " << md.num_buffered << "\n";

            return do_with(std::move(md), [this] (auto& md) {
                // this lambda should be captured by value because it goes out of scope but stores pointers internally
                auto refill_buffer = [this, &md] (size_t idx) {
                    md.buffered_idx[idx] = 0;
                    runs[idx].dma_read(md.records_read[idx] * page_size, md.buffered[idx].get(), md.buffered_size).then(
                            [&md] (auto ret) {
                        assert(ret == md.buffered_size);
                        md.sem_r.signal(1);
                    });
                };

                for(size_t run = 0; run < num_runs; ++run) {
                    md.buffered[run] = allocate_aligned_buffer<char>(md.buffered_size, page_size);
                    md.records_read[run] = 0;
                    refill_buffer(run);
                }
                // wait for all reads and continue merging the partial buffers
                return md.sem_r.wait(num_runs).then([this, &md, refill_buffer] {
                    auto records_range = boost::irange<size_t>(0, file_size / page_size);
                    // not using a simple loop because we will need to wait on refilling a buffer occasionally
                    return do_for_each(records_range, [this, &md, refill_buffer] (auto record) {
                        auto get_data = [&md] (size_t i) { return &(md.buffered[i][md.buffered_idx[i] * page_size]); };
                        // determine which is the next index of a run to read from
                        auto idx = get_smallest_idx(md.records_read, num_runs, records_in_run, get_data);

                        f.dma_write(record * page_size, get_data(idx), page_size).then([&md] (size_t ret) {
                            assert(ret == page_size);
                            md.sem_w.signal(1);
                        });

                        ++md.buffered_idx[idx];
                        ++md.records_read[idx];

                        // refill a buffer
                        if(md.records_read[idx] % md.num_buffered == 0 && md.records_read[idx] < records_in_run) {
                            refill_buffer(idx);
                            // the loop will not continue until this future (for a single write) resolves
                            return md.sem_r.wait(1);
                        }
                        // nothing to wait for - continue with next iteration
                        return now();
                    });
                }).then([this, &md] {
                    // wait for all the writes to finish
                    return md.sem_w.wait(records_in_run);
                });
            });
        }).then([this, run_range] {
            return do_for_each(run_range, [this] (auto run) {
                return runs[run].close();
            });
        }).then([this] {
            return f.flush();
        }).then([this] {
            // TODO: why does it stall when I try to close the file here?
            // return f.close();
            return now();
        });
    });
}

future<> context::create_file() {
    if(num_to_create == 0)
        return now();

    // the total number of records cannot be more than the square of the number of records we can keep in RAM
    assert(pow(max_in_ram_count, 2) >= num_to_create);

    // create the file
    return do_with(semaphore(0), [this] (semaphore& sem) {
        return open_file_dma(filename, open_flags::create | open_flags::truncate | open_flags::wo).then(
                [this, &sem] (file f_in) {
            f = f_in;
            for (size_t i = 0; i < num_to_create; ++i) {
                do_with(temporary_buffer<char>::aligned(f.memory_dma_alignment(), page_size),
                        [this, i, &sem] (auto& wbuf) {
                    // create a record
                    std::fill(wbuf.get_write(), wbuf.get_write() + page_size, '0' + rand() % 10);
                    wbuf.get_write()[0] = '='; // same prefix to test if I erroneously check somewhere only the first byte
                    wbuf.get_write()[page_size - 1] = '\n'; // new line after each record - make stuff readable when debugging
                    return f.dma_write(i * page_size, wbuf.get_write(), page_size).then([&sem] (size_t ret) {
                        assert(ret == page_size);
                        sem.signal(1);
                    });
                });
            }
            // wait for all the records to be written
            return sem.wait(num_to_create).then([this] {
                return f.flush();
            }).then([this] {
                return f.close();
            });
        });
    });
}

int main(int argc, char** argv) {
    namespace bpo = boost::program_options;

    app_template app;
    app.add_options()
        ("create", bpo::value<size_t>()->default_value(32), "create file to sort with X records")
        ("file", bpo::value<sstring>()->required(), "file to sort")
        ("max", bpo::value<size_t>()->default_value(8), "max records to store in RAM");

    try {
        app.run(argc, argv, [&app] {
            return do_with(context(), [&app] (context& ctx) {
                ctx.num_to_create = app.configuration()["create"].as<size_t>();
                ctx.filename = app.configuration()["file"].as<sstring>();
                ctx.max_in_ram_count = app.configuration()["max"].as<size_t>();
                return ctx.create_file().then([&ctx] {
                    return ctx.sort_file();
                });
            });
        });
    } catch(...) {
        std::cerr << "Failed to start application: "
                  << std::current_exception() << "\n";
        return 1;
    }
    return 0;
}