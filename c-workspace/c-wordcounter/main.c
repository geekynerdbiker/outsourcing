#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counter.h"
#include "mapreduce.h"

int main (int argc, char **argv)
{
    const char *filename = NULL;
    int nb_threads = 1;
    mapreduce_t *mr;

    filename = "input.txt";
    mr = mr_new(read_line, filename, nb_threads);
    

    mr_map(mr, split_words);
    mr_reduce(mr, sum_counts);
    mr_sorted_results(mr);
    mr_del(&mr);

    return EXIT_SUCCESS;
}
