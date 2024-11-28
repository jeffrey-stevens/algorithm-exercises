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


Test(gen_sample, min_eq_max, .description = 
    "Test that min_int = max_int generates min_int/max_int." ) {

    int min_int = 10;
    int max_int = min_int;
    int sample_size = 1;

    int * samples = int_array(sample_size);

    int retval = gen_sample(sample_size, min_int, max_int, samples);

    cr_assert(eq(int, retval, ERR_SUCCESS));
    cr_expect(eq(int, samples[0], min_int));

    free(samples);
}


Test(gen_sample, min_gt_max, .description = 
    "Test for ERR_MIN_GT_MAX error if min_int > max_int.") {

    int min_int = 10;
    int max_int = min_int - 1;
    int sample_size = 10;

    int * samples = int_array(sample_size);
    int retval = gen_sample(sample_size, min_int, max_int, samples);

    cr_expect(eq(int, retval, ERR_MIN_GT_MAX),
        "Error code: %d.  min_int = %d, max_int = %d.",
        retval, min_int, max_int);

    free(samples);
}


Test(gen_sample, range, .description = 
    "Testing that max_int - min_int > RAND_MAX returns error code "
    "ERR_RANGE_TOO_LARGE.") {

    int min_int = -1;
    int max_int = RAND_MAX;
    int sample_size = 10;

    int * samples = int_array(sample_size);
    int retval = gen_sample(sample_size, min_int, max_int, samples);

    cr_expect(eq(int, retval, ERR_RANGE_TOO_LARGE),
        "Error code: %d.  min_int = %d, max_int = %d, RAND_MAX = %d.",
        ERR_RANGE_TOO_LARGE, min_int, max_int, RAND_MAX);

    free(samples);
}