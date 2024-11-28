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
    int test_passed = false;

    int * samples = int_array(sample_size);

    int result = gen_sample(sample_size, min_int, max_int, samples);

    cr_assert(eq(int, result, ERR_SUCCESS));
    cr_expect(eq(int, samples[0], min_int));

    free(samples);
}