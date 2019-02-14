External Merge Sort
=======

An implementation of an external sort algorithm (using helper temporary files) for files which cannot fit into the main RAM. Basically this: https://en.wikipedia.org/wiki/External_sorting#External_merge_sort

The solution uses the seastar framework for asynchronous programming:
- https://github.com/scylladb/seastar
- https://github.com/scylladb/seastar/blob/master/doc/tutorial.md

First we process the file in batches of the size of the RAM - each such batch is divided into <num_cores> chunks which are sorted in parallel with ```std::sort``` (actually sorting pointers to the data so there is less data shuffling) and then the chunks for that batch are merged sequentially to disk.

We do this until the entire file is sorted into separate batch files each with the size of the max RAM to use.

Then comes the final <num_batches>-way merge which is also sequential. For it we have opened all the <num_batches> files and we buffer a few records (as much as possible) from each in memory. Then we proceed to check which is the smallest record from all the buffers (checking only the front records since the data in the buffers is sorted already) and then we take that record and write it in the final sorted version of the file (overwriting it). When a buffer is emptied we preload another one from one of the <num_batches> files, and we do this until we have processed all records.

This algorithm uses extra disk space as much as the original file to sort.

## Usage

The program creates the file it will be sorting by default, and that is controlled with the --count <NUM> parameter, where <NUM> is the number of 4kb records to write. Use '0' to skip creating it.

The --file <FILENAME> argument is required to specify the file to sort.

The --max <NUM> argument tells the algorithm how many records to store in the RAM at most.

Example:

./a.out --file temp --create 128 --max 64

This will create a ~500kb file which will be sorted using 2 ~250kb files.

## Notes about the solution

There are some restrictions for the sizes, and the most important ones are:
- the numbers passed should be powers of 2
- if we can hold X records in ram - we cannot sort a file larger than X*X

The second of these restrictions is imposed by the final merging of all helper files. This could be avoided if there are a few passes and if we don't have to open all of them at once.

- there are 2 places with a ```TODO:``` - problems I couldn't solve quickly...
- sorts records of 4kb size
- no cleanup of helper files from the filesystem
