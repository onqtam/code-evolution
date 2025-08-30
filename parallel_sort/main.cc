/*
== HIGH-LEVEL DESCRIPTION:

The program accepts the in/out filenames but has also 2 additional (and optional) parameters:
- the max number of records allowed to be stored in RAM at any point
- number of records to create as the 'in' file (as a convenience to create the data)

Here is how the input is sorted:
- First we open the file and based on the number of records in it we divide work for the cores as start/end positions from the original file to sort. Then we submit the work to all cores.
- If the range for a core is larger than the memory it's allowed to use (max_memory / num_cores) then that core will split it's range into multiple sub-ranges and sort them one after another, storing the results in consecutively named temp files.
- While sorting the assigned ranges (and possibly dividing them into sub-ranges and separate temp files) each core loads the data from the input file into separate chunks with size 'max_pages_in_allocation * 4096' in order to avoid std::bad_alloc and constructs a contiguous array of pointers to all the records from all chunks. Then instead of sorting each chunk and moving entire records around, the cores sort the pointers based on the memory they point to - that way each core sorts multiple buffers (chunks) at the same time, and then based on the sorted pointers a temp file is written with the records from all the chunks.
- When all temp files are sorted and written to disk comes the <num_temp_files>-way merge. For that first we re-open all temp files and pre-load a buffer of size of up to 'max_pages_in_allocation' from each temp file. Then we loop until all records from all temp files have been merged. Each time we get the next smallest element from all buffers from all temp files that are left - using a priority queue (min-heap). Whenever a buffer from a temp file is emptied we refill it (if the temp file hasn't been exhausted).

== EXAMPLE USAGE & ANALYSIS:

Here are my measurements (machine: i7 3770k (4 physical, 8 hyper), 16GB of RAM, 250GB SSD):
- "./main 10gb out 1000000 2500000"
  This creates a 10GB file with 2.5 million 4KB records (ignore the '1000000' thing).
  Each created record is just the same random number repeated about 4094 times (and the first char is '=' and the last is '\n' for easier reading).
  It takes a minute or two to create the file, after which I kill the process when it starts sorting because I want to time only the sorting. Sorry for the confusing interface for using the program...
- "time ./main 10gb out 1000000"
  This starts sorting the file without creating it - using up to 4GB of RAM (1 million 4KB records).
  On an 8 core machine this ends up creating 20 temp files 500MB each.
  It takes 150 seconds to sort the file.
  The first 90 seconds are for the sorting of the temp files where CPU utilization is about 80% across the board and read/write speed is about 120MB/s (each). During this time there will be multiple messages that reactors have stalled for more than 500ms - that's because of the sorting of the pointers to the 300k records of 4KB (500MB) - perhaps there should be a limit to the size of the temp files so that cores are accessible to other cooperative operations as well... Or better yet - sort each temp file in small-enough chunks and then do a merge with occasional preemptive yields - perhaps in a seastar::repeat() loop.
  The second half of the time is for the merging - that's when only 1 CPU core is being used at almost 100% and the read/write speeds are about 140MB/s.

Doubling the dedicated RAM to sorting halves the number of temp files and the number of reads per temp file, reducing the number of required seeks. Using less RAM (and/or reducing the 'max_pages_in_allocation' constant) leads to less read/write/merge throughput.

Valid examples on an 8 core machine:
- "./main in out 23 37" - 148KB input (37 * 4KB), 92KB of RAM (23 * 4KB), 19 temp files (2.375 per core) - 8KB each
- "./main in out 1000 100000" - 400MB input, 4MB of RAM, 800 temp files (100 per core) - 500KB each
- "./main in out 10000 1000000" - 4GB input, 40MB of RAM, 800 temp files (100 per core) - 5MB each
- "./main in out 100000 1000000" - 4GB input, 400MB of RAM, 80 temp files (10 per core) - 50MB each
- "./main in out 1000000 1000000" - 4GB input, 4GB of RAM, 8 temp files (1 per core) - 500MB each

Problematic examples on an 8 core machine:
- "./main in out 8 80" - 320KB input, 32KB of RAM, 80 temp files (10 per core) - 4KB each
  ERROR: not enough RAM to fit 80 records for the 80-way merge - can fit only 8
- "./main in out 100 10000" - 40MB input, 400KB of RAM, 834 temp files (104 per core) - 48KB each
  ERROR: not enough RAM to fit 834 records for the 834-way merge - can fit only 100

Currently there are 2 unpleasant restrictions:
- we need to have enough RAM to hold at least 1 record from each of all the temp files because of the final <num_temp_files>-way merge
- <num_temp_files> cannot be bigger than 'ulimit -n' because of the final <num_temp_files>-way merge

Both would go away if we implemented a multi-pass merge instead of the current <num_temp_files>-way. That way we could utilize more cores for the merges - the passes need not be sequential.

Currently for a 20TB file on an 8 core machine:
- for num_temp_files == 1000 we would need 160GB of RAM
- for num_temp_files == 10000 we would need 16GB of RAM
- for num_temp_files == 100000 we would need 1.6GB of RAM (and having just 4 records per temp file in memory while merging)

= system utilization:
- the sorting of the temp files utilizes the system to the fullest extent possible - I/O, Memory and CPU.
= bottlenecks:
- some cores could finish their work faster than others
- merging is sequential on a single core - a multi-pass merge would make that more parallel but there will be more I/O - it's a tradeoff.
- perhaps too much small writes at the same time could be a burden to the system - limit parallelism?
= improvements for speed:
- for many temp files a multi-pass merge might be beneficial even if there is more I/O - because of the better CPU utilization
- I would think how to avoid issuing separate write requests for pages (not sure if that is a problem though) - but to achieve that, memory would need to be copied into contiguous buffers so that writes are batched - perhaps it's not worth it.

== TODO:

The 2 important ones:
- make it possible to do multi-pass merges so that the 2 biggest problems go away (the open file limit and amount of RAM necessary for at least 1 record from all the temp files). This however will mean more disk reads & writes but the merges will be a bit faster since the heap in the priority queue will be shallower.
- do an in-memory merge-sort with occasional preemptions instead of sorting the pointers for the entire temp files with 1 sort() call in order to avoid reactor stalls (OR reimplement qsort with the ability to yield and resume later on)
- use a tournament tree instead of a heap for the merge because they make twice as less comparisons: https://en.wikipedia.org/wiki/K-way_merge_algorithm#Tournament_Tree

Less important ones:
- Some temp files might get sorted much faster than others. Because work is divided up-front we might end up having some cores waiting for others to finish. Consider using a task queue.
- think about batched/buffered writes instead of these single page ones
- think about being careful not to issue too much write requests - limiting parallelism?
- for high number of temp files - separate them in directories (no more than 1k files per directory)
- check that the input is indeed comprised of only valid ASCII symbols
- switch from asserts to exceptions for preconditions & think about exception safety
- don't write temp files in the cwd - should go in some temp directory
- clean up temp files using seastar::remove_file when done sorting (or if any error occurred)
- switch to using boost::program_options
- answer question: "why don't I need to explicitly close the temp files after the merge phase?"
- feel intense shame because of the use of std::endl
*/

#include <seastar/core/app-template.hh>
#include <seastar/core/reactor.hh>
#include <seastar/core/thread.hh>
#include <seastar/core/print.hh>
#include <seastar/core/distributed.hh>
#include <seastar/core/future-util.hh>

#include <sys/resource.h>

#include <iostream>

using namespace seastar; // is this bad practice?

// returns the ceil of "x / y" - https://stackoverflow.com/a/2745086
size_t ceil_div(size_t x, size_t y) { return (x + y - 1) / y; }

// shows the progress of a process in %
void show_progress(size_t curr, size_t max, const char* msg) {
    if(curr % (max / 10) == 0)
        std::cout << 10 * curr / (max / 10) << "% " << msg << std::endl;
}

constexpr size_t page_size = 4096;
constexpr size_t max_pages_in_allocation = 10000; // CONFIG POINT! A realistic value would be perhaps 10000 - that would be 40MB which should be a reasonable upper boundry for single allocation sizes, but this works even with values as low as 1 (using a low value is highly discouraged)

// Sorts a bunch of ranges from the original file and stores the results into separate temp files.
// This class should perhaps be a private subclass of 'sorter'
struct core_sorter {
    struct range {
        size_t start_pos; // position in file for which this core should start sorting
        size_t end_pos;   // end of the range of the file the core should sort
    };

    core_sorter(std::vector<range> ranges, size_t max_records_per_core, seastar::file_handle&& fh)
            : _p(ranges[engine().cpu_id()]) // get the appropriate range for this core
            , _max_records_per_core(max_records_per_core)
            , _f(std::move(fh)) {}

    future<> do_sort();

private:
    range _p; // core-specific range
    const size_t _max_records_per_core; // this much records at most will go into a temp file
    file _f; // the main file we are sorting - same for all cores

    semaphore _sem{0}; // used to wait for all the reads/writes
    std::vector<temporary_buffer<char>> _chunks; // Used to split the entire memory for a temp file
                                                 // into multiple chunks - to avoid std::bad_alloc.
    std::vector<char*> _pointers; // We sort pointers to records instead of the actual records.
                                  // These pointers can point to separate chunks - no problem.
};

future<> core_sorter::do_sort() {
    // do not proceed if there is no work to do - happens when there are fewer temp files than cores
    if(_p.end_pos == _p.start_pos)
        return now();
    return repeat([this] {
        // Determine how much bytes (and in turn records) we should process.
        // We shouldn't always process the maximum: handle the case if (when) the
        // last core has less than the maximum number of records for a temp file
        const size_t bytes_to_process = std::min(_max_records_per_core * page_size, _p.end_pos - _p.start_pos);
        const size_t num_records_in_temp = bytes_to_process / page_size;

        // if too much records at once - split into multiple to avoid std::bad_alloc
        const size_t records_in_chunk = std::min(num_records_in_temp, max_pages_in_allocation);
        const size_t num_chunks = ceil_div(num_records_in_temp, records_in_chunk);

        _chunks.resize(num_chunks);
        _pointers.resize(num_records_in_temp);

        // pointers to the data in the chunks are used for sorting
        for(size_t c = 0; c < num_chunks; ++c) {
            auto num_to_read = records_in_chunk;
            // handle the last chunk - when "num_records_in_temp % records_in_chunk != 0"
            if(num_to_read * (c + 1) > num_records_in_temp)
                num_to_read -= num_to_read * (c + 1) - num_records_in_temp;

            // issue a bunch of reads
            _chunks[c] = temporary_buffer<char>::aligned(_f.memory_dma_alignment(), num_to_read * page_size);
            (void)_f.dma_read(_p.start_pos + c * records_in_chunk * page_size,
                              _chunks[c].get_write(), num_to_read * page_size).then(
                    [this, num_to_read] (size_t bytes_read) {
                assert(bytes_read == num_to_read * page_size);
                _sem.signal(1);
            });

            // initialize the pointers container which we will be sorting
            // later on with pointers to the records in the current chunk
            for(size_t i = 0; i < num_to_read; ++i)
                _pointers[c * records_in_chunk + i] = &_chunks[c].get_write()[i * page_size];
        }
        return _sem.wait(num_chunks).then([this, num_records_in_temp] {
            // sort the pointers in the container based on whatever they point to
            std::sort(_pointers.begin(), _pointers.end(), [] (const char* lhs, const char* rhs) {
                return memcmp(lhs, rhs, page_size) < 0;
            });

            // temp files - named consecutively based on the offset from the start of the main file
            size_t temp_file_idx = _p.start_pos / (_max_records_per_core * page_size);
            return open_file_dma(sstring("temp_") + std::to_string(temp_file_idx), 
                                 open_flags::create | open_flags::truncate | open_flags::wo).then(
                    [this, num_records_in_temp] (file f_temp) {
                // write the records to disk based on the sorted pointers order
                for(size_t i = 0; i < num_records_in_temp; ++i) {
                    (void)f_temp.dma_write(i * page_size, _pointers[i], page_size).then(
                            [this] (size_t ret) {
                        assert(ret == page_size);
                        _sem.signal(1);
                    });
                }
                return _sem.wait(num_records_in_temp).then([f_temp] () mutable {
                    return f_temp.close().then([f_temp] {
                        // extending the lifetime of the file so the dtor runs after the close() call
                    });
                });
            });
        }).then([this, bytes_to_process] {
            // advance position and determine if we should quit the loop
            _p.start_pos += bytes_to_process;
            return (_p.start_pos < _p.end_pos) ? stop_iteration::no : stop_iteration::yes;
        });
    });
}

struct sorter {
    sorter(const sstring& filename_in, const sstring& filename_out, size_t max_records_in_memory)
        : _filename_in(filename_in)
        , _filename_out(filename_out)
        , _max_records_in_memory(max_records_in_memory)
    {}

    future<> create_file(size_t num);
    future<> sort_file();
    future<> check_sorted();

private:
    // returns a pointer to 1 record from the buffered in-memory parts of a temp file (while merging)
    const char* get_next_temp_record(size_t i) const {
        return &(_temp_files[i].buffer.get()[_temp_files[i].buffer_idx * page_size]);
    }
    // compares the next-in-line in-memory buffered records from 2 temp files
    struct temp_cmp_functor {
        const sorter& _s;
        temp_cmp_functor(sorter& s) : _s(s) {}

        bool operator()(size_t l, size_t r) const {
            return memcmp(_s.get_next_temp_record(l), _s.get_next_temp_record(r), page_size) > 0;
        }
    };
    // used to determine how many records to read from a temp file into an in-memory buffer
    size_t how_many_to_read(size_t temp_file_idx) const;
    // used to refill the in-memory buffer for a temp file
    void refill_buffer(size_t temp_file_idx);

    const sstring _filename_in;
    const sstring _filename_out;
    const size_t _max_records_in_memory;

    file _f;

    semaphore _sem_r{0}; // read semaphore
    semaphore _sem_w{0}; // write semaphore

    size_t _num_records;
    size_t _num_temp_files;

    size_t _records_merged;
    size_t _merged_since_last_refill;

    // A priority queue for the next-in-line temp file index to merge a record from.
    // Using a pointer because we need to construct the comparator object later, because it takes
    // a reference to the parent sorter class, but when the parent sorter class is copied/moved
    // we will end up with a broken reference to the parent class in the comparator object => crash.
    // We also DO need a comparator type for the template here and cannot simply use a lambda later.
    std::unique_ptr<std::priority_queue<size_t, std::vector<size_t>,
                    temp_cmp_functor>> _next_record_idx_queue;

    struct temp_file {
        file f;
        size_t file_pos;
        size_t file_end;

        temporary_buffer<char> buffer; // an in-memory buffer containing part of the temp file
        size_t buffer_idx; // determines how far along the buffer we have gone
        size_t num_left_in_buffer; // how many entries are left unread in the buffer
    };

    std::vector<temp_file> _temp_files;
};

size_t sorter::how_many_to_read(size_t temp_file_idx) const {
    auto& curr = _temp_files[temp_file_idx];
    // start with the entire file
    size_t num_to_read = (curr.file_end - curr.file_pos) / page_size;
    // for 19 temp files and 23 max records in memory we would get buffers of size 1
    // for 19 temp files and 60 max records in memory we would get buffers of size 3
    num_to_read = std::min(num_to_read, _max_records_in_memory / _num_temp_files);
    // take into account the max single allocation size
    return std::min(num_to_read, max_pages_in_allocation);
}

void sorter::refill_buffer(size_t temp_file_idx) {
    size_t size_to_read = how_many_to_read(temp_file_idx) * page_size;
    auto& curr = _temp_files[temp_file_idx];
    (void)curr.f.dma_read(curr.file_pos, curr.buffer.get_write(), size_to_read).then(
            [this, size_to_read] (auto ret) {
        assert(ret == size_to_read);
        _sem_r.signal(1);
    });
    curr.file_pos += size_to_read;
    curr.num_left_in_buffer = size_to_read / page_size;
    curr.buffer_idx = 0;
};

future<> sorter::sort_file() {
    return open_file_dma(_filename_in, open_flags::ro).then([this] (file f_in) {
        _f = f_in;
        _num_records = _f.size().get0() / page_size;
        // if we can't fit smp::count records in RAM we have other issues...
        assert(_max_records_in_memory >= smp::count);
        // the input should be a multiple of the record size
        assert(_f.size().get0() % page_size == 0);

        // == EXAMPLE - GIVEN THE FOLLOWING STARTING CONDITIONS:
        // 
        // num_records: 37
        // smp::count: 8
        // max_records_in_memory: 23            (we have 4096 * 23 bytes (94KB) of RAM in the system)
        // 
        // == WE GET THE FOLLOWING DISTRIBUTION OF RECORDS TO THE CORES:
        // 
        // max_records_per_core: 23 / 8 = 2     (max_records_in_memory / smp::count)
        // records_at_a_time: 2 * 8 = 16        (max_records_per_core * smp::count)
        // min_temp_files_per_core: 37 / 16 = 2 (num_records / records_at_a_time)
        // records_left: 37 - 16 * 2 = 5        (num_records - records_at_a_time * min_temp_files_per_core)
        // records_left_for_last: 5 % 2 = 1     (records_left % max_records_per_core)
        // extra_temp_files: 5 / 2 = 2          (records_left / max_records_per_core)
        // num_temp_files: ceil(37 / 2) = 19    (ceil(num_records / max_records_per_core))
        // 
        // |fff|fff|ff |ff |ff |ff |ff |ffp|    <<< the work distribution for the <smp::count> cores
        // 
        // f = FULL temp file with <max_records_per_core> records in it
        // p = PARTIAL temp file with <records_left_for_last> records in it - only one p could exist
        // 18 * f = 18 * <max_records_per_core> = 36
        // 36 + <records_left_for_last> = 37

        const size_t max_records_per_core    = _max_records_in_memory / smp::count;
        const size_t records_at_a_time       = max_records_per_core * smp::count;
        const size_t min_temp_files_per_core = _num_records / records_at_a_time;
        const size_t records_left            = _num_records - records_at_a_time * min_temp_files_per_core;
        const size_t records_left_for_last   = records_left % max_records_per_core;
        size_t extra_temp_files              = records_left / max_records_per_core;
        _num_temp_files                      = ceil_div(_num_records, max_records_per_core);

        rlimit lim;
        getrlimit(RLIMIT_NOFILE, &lim);

        std::cout << "== CONFIG =================================================" << std::endl;
        std::cout << "num_records " << _num_records << std::endl;
        std::cout << "max_records_in_memory " << _max_records_in_memory << std::endl;
        std::cout << "num_temp_files " << _num_temp_files << std::endl;
        std::cout << "'ulimit -n' " << lim.rlim_cur << std::endl;
        std::cout << "===========================================================" << std::endl;

        // we cannot have more than 'ulimit -n' opened files at the same - during
        // the final merge phase all temp files are opened at the same time.
        // However this value might be bigger by default on some machines and can be changed...
        assert(_num_temp_files < lim.rlim_cur);
        // we should be able to hold more records in memory than the number of temp files because
        // of the final merge step - we should have at least 1 record in memory from each file
        assert(_max_records_in_memory >= _num_temp_files);

        // initialize the sort ranges for the cores with the right start/end positions
        // from the main file (from which we can determine how many records to process)
        std::vector<core_sorter::range> core_ranges {smp::count};
        for(size_t curr_pos = 0, i = 0; i < smp::count; ++i) {
            // determine the number of full temp files
            size_t num_temp_files = min_temp_files_per_core;
            if(extra_temp_files > 0) {
                // the first cores might get 1 extra - depending on the distribution
                ++num_temp_files;
                --extra_temp_files;
            }
            // determine the start/end positions from the main file for each core based on the number
            // of temp files each core should handle (+ any leftovers (if any) for the last core)
            core_ranges[i].start_pos = curr_pos;
            curr_pos += max_records_per_core * num_temp_files * page_size;
            // if this is the last core - add to it any records which have been left
            // undistributed (if any) - they will end up in a smaller temp file (the last one)
            if(i == smp::count - 1)
                curr_pos += records_left_for_last * page_size;
            core_ranges[i].end_pos = curr_pos;
        }

        _temp_files.resize(_num_temp_files);
        // determine the curr/end positions in each temp file
        for(size_t i = 0; i < _num_temp_files; ++i) {
            _temp_files[i].file_pos = 0;
            _temp_files[i].file_end = max_records_per_core * page_size;
        }
        // if the last temp file is partial - update it accordingly
        if(records_left_for_last > 0)
            _temp_files[_num_temp_files - 1].file_end = records_left_for_last * page_size;

        // time to invoke the sorting of the temp files on all cores
        return do_with(sharded<core_sorter>(),
                [this, core_ranges = std::move(core_ranges), max_records_per_core] (auto& sorter) {
            return sorter.start(core_ranges, max_records_per_core, _f.dup()).then([this, &sorter] {
                return sorter.invoke_on_all(&core_sorter::do_sort);
            }).then([&sorter] {
                std::cout << "sorting the temp files is done!" << std::endl;
                return sorter.stop();
            });
        });
    }).then([this] {
        // Now it's time to merge all the temp files - done serially on 1 core
        // First open the output file and all temp files
        return open_file_dma(_filename_out, open_flags::create | open_flags::truncate | open_flags::wo).then([this] (file f_in) {
            _f = f_in;
            for(size_t i = 0; i < _num_temp_files; ++i) {
                (void)open_file_dma("temp_" + std::to_string(i), open_flags::ro).then(
                        [this, i] (file f_in) {
                    _temp_files[i].f = f_in;
                    _sem_w.signal(1);
                });
            }
            // wait for all the temp files to be opened
            return _sem_w.wait(_num_temp_files);
        }).then([this] {
            // load initial buffers from each temp file
            for(size_t i = 0; i < _num_temp_files; ++i) {
                auto& curr = _temp_files[i];
                curr.num_left_in_buffer = how_many_to_read(i);
                curr.buffer = temporary_buffer<char>::aligned(_f.memory_dma_alignment(), curr.num_left_in_buffer * page_size);
                refill_buffer(i);
            }
            // wait for all reads and continue merging the partial buffers
            return _sem_r.wait(_num_temp_files);
        }).then([this] {
            // time to loop until all temp files have been exhausted and everything is merged
            _records_merged = 0;
            _merged_since_last_refill = 0;

            // init the heap with <num_temp_files> indexes (starting from 0) - the top element is
            // always the index of the temp file we should next write to the merged output file
            _next_record_idx_queue = std::make_unique<decltype(_next_record_idx_queue)::element_type>(
                    boost::counting_iterator<int>(0),
                    boost::counting_iterator<int>(_num_temp_files),
                    temp_cmp_functor(*this));

            // 2 nested loops doing the same thing because the inner one might issue an operation
            // for which we might need to wait - a future might have to be resolved occasionally.
            return do_until([this] { return _records_merged == _num_records; }, [this] {
                while(_records_merged != _num_records) {
                    show_progress(_records_merged, _num_records, "merged");

                    size_t idx = _next_record_idx_queue->top();
                    _next_record_idx_queue->pop();

                    (void)_f.dma_write(_records_merged++ * page_size,
                                       get_next_temp_record(idx), page_size).then(
                            [this] (size_t ret) {
                        assert(ret == page_size);
                        _sem_w.signal(1);
                    });

                    auto& curr = _temp_files[idx];
                    ++curr.buffer_idx;
                    ++_merged_since_last_refill;
                    // if we have emptied the buffer
                    if(--curr.num_left_in_buffer == 0) {
                        // but if there is more in the temp file
                        if(curr.file_pos < curr.file_end) {
                            // We need to wait for all writes because if we queue the refill read
                            // immediately we might end up reading from a newer version of the buffer
                            // when doing the previously scheduled writes - order is not guaranteed.
                            // The outer loop will not continue until this future resolves.
                            return _sem_w.wait(_merged_since_last_refill).then([this, idx] {
                                refill_buffer(idx);
                                // wait for the refill before updating the queue
                                return _sem_r.wait(1).then([this, idx] {
                                    _merged_since_last_refill = 0; // we just refilled...
                                    _next_record_idx_queue->push(idx); //re-insert the refilled idx
                                });
                            });
                        }
                    } else {
                        _next_record_idx_queue->push(idx); //re-insert the non-empty buffer idx
                    }
                }
                return _sem_w.wait(_merged_since_last_refill); // wait for the last batch of writes
            });
        });
    }).then([this] {
        std::cout << "merging done!" << std::endl;
        return _f.close();
    });
}

future<> sorter::create_file(size_t num) {
    if(num == 0)
        return now();
    // NOT OPTIMIZED! sequentially creates all records without any asynchronicity
    return async([this, num] {
        _f = open_file_dma(_filename_in, open_flags::create | open_flags::truncate | open_flags::wo).get0();
        auto wbuf = temporary_buffer<char>::aligned(_f.memory_dma_alignment(), page_size);
        for(size_t i = 0; i < num; ++i) {
            show_progress(i, num, "created");
            // create a record (using the very bad rand() because here it's easy and unimportant)
            std::fill(wbuf.get_write(), wbuf.get_write() + page_size, '0' + rand() % 10);
            wbuf.get_write()[0] = '='; // same prefix for all records to test if I erroneously check somewhere only the first byte
            wbuf.get_write()[page_size - 1] = '\n'; // new line after each record - make stuff readable when debugging
            _f.dma_write(i * page_size, wbuf.get_write(), page_size).get0();
        }
        _f.close().get0();
    });
}

future<> sorter::check_sorted() {
    // NOT OPTIMIZED! sequentially checks all records if they are sorted without any asynchronicity
    return async([this] {
        _f = open_file_dma(_filename_out, open_flags::ro).get0();
        _num_records = _f.size().get0() / page_size;
        // will sequentially read into one of the buffers in an alternating fashion
        temporary_buffer<char> buffs[2];
        buffs[0] = temporary_buffer<char>::aligned(_f.memory_dma_alignment(), page_size);
        buffs[1] = temporary_buffer<char>::aligned(_f.memory_dma_alignment(), page_size);
        for(size_t i = 0; i < _num_records; ++i) {
            show_progress(i, _num_records, "checked");
            _f.dma_read(i * page_size, buffs[i % 2].get_write(), page_size).get0();
            // if there has been a previous record - compare with it
            if(i != 0 && memcmp(buffs[(i - 1) % 2].get(), buffs[i % 2].get(), page_size) > 0)
                throw std::runtime_error(format("record {} is out of order!", i));
        }
        _f.close().get0();
        std::cout << "successfully checked if file is sorted!" << std::endl;
    });
}

int main(int argc, char** argv) {
    if(argc < 3) {
        std::cerr << "program accepts 2 parameters - input and output file!" << std::endl;
        return 1;
    }

    sstring in = argv[1];
    sstring out = argv[2];
    size_t max_in_ram = (argc > 3) ? std::stoul(argv[3]) : 100000; // 400 MB
    size_t num_to_create = (argc > 4) ? std::stoul(argv[4]) : 0;

    try {
        app_template app;
        // not using boost::program_options because... no good reason.
        // But now we need to pass '1' as argc to make it work...
        app.run(1, argv, [&] {
            return do_with(sorter(in, out, max_in_ram), [num_to_create] (auto& srt) {
                return srt.create_file(num_to_create).then([&srt] {
                    return srt.sort_file();
                }); //.then([&srt] { return srt.check_sorted(); });
            });
        });
    } catch(...) {
        std::cerr << "Failed to start application: " << std::current_exception() << std::endl;
        return 1;
    }
    return 0;
}
