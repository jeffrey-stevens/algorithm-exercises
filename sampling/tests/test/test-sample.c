#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include <criterion/new/assert.h>

#include "sample.h"
#include "utils.h"


Test(gen_sample_tree, basic_usage, .description = 
    "Tests gen_sample_tree() on a limited sample size and range.") {

    int sample_size = 20;
    int array_size = sample_size + 10;
    int min_int = 1;
    int max_int = 100;

    int * samples = int_array(array_size);

    // Initialize the array
    for (int i = 0; i < array_size; ++i) {
        samples[i] = 0;
    }

    int retval = gen_sample_tree(sample_size, min_int, max_int, samples);

    cr_assert(eq(int, retval, ERR_SUCCESS));

    // Test that all samples are in range
    bool all_in_range = true;
    for (int i = 0; i < sample_size && all_in_range; ++i) {
        all_in_range = samples[i] >= min_int && samples[i] <= max_int;
    }

    cr_expect(all_in_range);

    // Test that the gen_sample_trees didn't overwrite the samples range
    bool all_zero = true;
    for (int i = sample_size; i < array_size && all_zero; ++i) {
        all_zero = samples[i] == 0;
    }

    cr_expect(all_zero);

    // Test that there are no duplicated samples
    sort_int_array(sample_size, samples);
    bool no_duplicates = true;
    if (sample_size > 0) {
        for (int i = 0; i < sample_size - 1 && no_duplicates; ++i) {
            no_duplicates = samples[i] < samples[i + 1];
        }
    }

    cr_expect(no_duplicates);

    free(samples);
}


Test(gen_sample_tree, min_eq_max, .description = 
    "Test that min_int = max_int generates min_int/max_int." ) {

    int min_int = 10;
    int max_int = min_int;
    int sample_size = 1;

    int * samples = int_array(sample_size);

    int retval = gen_sample_tree(sample_size, min_int, max_int, samples);

    cr_assert(eq(int, retval, ERR_SUCCESS));
    cr_expect(eq(int, samples[0], min_int));

    free(samples);
}


Test(gen_sample_tree, min_gt_max, .description = 
    "Test for ERR_MIN_GT_MAX error if min_int > max_int.") {

    int min_int = 10;
    int max_int = min_int - 1;
    int sample_size = 10;

    int * samples = int_array(sample_size);
    int retval = gen_sample_tree(sample_size, min_int, max_int, samples);

    cr_expect(eq(int, retval, ERR_MIN_GT_MAX),
        "Error code: %d.  min_int = %d, max_int = %d.",
        retval, min_int, max_int);

    free(samples);
}


Test(gen_sample_tree, range, .description = 
    "Testing that max_int - min_int > RAND_MAX returns error code "
    "ERR_RANGE_TOO_LARGE.") {

    int min_int = -1;
    int max_int = RAND_MAX;
    int sample_size = 10;

    int * samples = int_array(sample_size);
    int retval = gen_sample_tree(sample_size, min_int, max_int, samples);

    cr_expect(eq(int, retval, ERR_RANGE_TOO_LARGE),
        "Error code: %d.  min_int = %d, max_int = %d, RAND_MAX = %d.",
        ERR_RANGE_TOO_LARGE, min_int, max_int, RAND_MAX);

    free(samples);
}


Test(gen_sample_tree, size_eq_range, .description = 
    "Test that sample_size = number range generates all integers "
    "in that range.") {

    int min_int = 0;
    int max_int = 9;
    int range = max_int - min_int + 1;
    int sample_size = range;

    int * samples = int_array(sample_size);
    int retval = gen_sample_tree(sample_size, min_int, max_int, samples);

    cr_assert(eq(int, retval, ERR_SUCCESS));

    sort_int_array(sample_size, samples);

    int i = 0;
    bool all_match = true;
    while (i < sample_size && all_match) {
        all_match = samples[i] == min_int + i;
        ++i;
    }

    cr_expect(all_match);

    free(samples);
}


Test(gen_sample_tree, size_gt_range, .description =
    "Test that the sample_size > number range returns error code "
    "ERR_SAMPLE_SIZE_TOO_LARGE") {

    int min_int = 0;
    int max_int = 9;
    int range = max_int - min_int + 1;
    int sample_size = range + 1;

    int * samples = int_array(sample_size);
    int retval = gen_sample_tree(sample_size, min_int, max_int, samples);

    cr_expect(eq(int, retval, ERR_SAMPLE_SIZE_TOO_LARGE),
        "Error code: %d.  min_int = %d, max_int = %d, sample_size = %d.",
        ERR_SAMPLE_SIZE_TOO_LARGE, min_int, max_int, sample_size);

    free(samples);
    }