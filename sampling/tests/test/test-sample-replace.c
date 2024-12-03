#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include <criterion/new/assert.h>

#include "sample-replace.h"
#include "utils.h"
#include "error.h"

#define MAX_ARRAY_SIZE 1 << 24  /* 16 MB */


Test(random_ints, n_is_neg, .description =
        "Test that n is nonnegative returns error code ERR_NEG_SIZE.") {
    
    cr_expect(eq(int, random_ints(-1, 0, NULL), ERR_NEG_SIZE));
}


Test(random_ints, max_int_is_neg, .description =
        "Test that n is nonnegative returns error code ERR_NEG_SIZE.") {
    
    cr_expect(eq(int, random_ints(1, -1, NULL), ERR_NEG_SIZE));
}


Test(random_ints, is_null, .description =
        "Test that a null array returns error code ERR_NULL_POINTER.") {

    cr_expect(eq(int, random_ints(0, 0, NULL), ERR_NULL_POINTER));
}


Test(random_ints, max_out_of_range, .description = 
        "Test that max_int > RAND_MAX returns error code ERR_OUT_OF_RANGE.") {

    #if (RAND_MAX < INT_MAX)
    cr_expect(eq(int, random_ints(0, RAND_MAX + 1, NULL), ERR_NEG_SIZE));
    cr_expect(eq(int, random_ints(0, INT_MAX, NULL), ERR_NEG_SIZE));
    #endif
}


Test(random_ints, args_in_range, .description = 
        "Test for success when n and max-int are in-range.") {

    int * test_array;

    test_array = int_array(1);
    cr_assert(eq(int, random_ints(0, RAND_MAX, test_array), ERR_SUCCESS));
    cr_assert(eq(int, random_ints(1, RAND_MAX, test_array), ERR_SUCCESS));
    free(test_array);

    test_array = int_array(MAX_ARRAY_SIZE);
    cr_assert(eq(int, random_ints(MAX_ARRAY_SIZE, RAND_MAX, test_array), ERR_SUCCESS));
    free(test_array);

    test_array = int_array(1);
    cr_assert(eq(int, random_ints(1, 0, test_array), ERR_SUCCESS));
    free(test_array);
}


ParameterizedTestParameters(random_ints, vals_in_range) {

    int fixed_maxes[] = {0, RAND_MAX};
    int fixed_size = sizeof(fixed_maxes) / sizeof(int);

    int max_power = (int) log10((double) RAND_MAX);
    int var_size = max_power + 1;
    int total_size = fixed_size + var_size;
    int * max_ints = int_array(total_size);

    for (int i = 0; i < fixed_size; ++i) {
        max_ints[i] = fixed_maxes[i];
    }

    int curr_max = 1;
    for (int i = fixed_size; i < total_size; ++i) {
        max_ints[i] = curr_max;
        curr_max *= 10;
    }

    return cr_make_param_array(int, max_ints, total_size);
}


ParameterizedTest(int * param, random_ints, vals_in_range, .description =
        "Tests that all values are within range for various values of max_int.") {

    int max_int = *param;
    int n = 10000;
    int * test_array = int_array(n);

    random_ints(n, max_int, test_array);

    bool all_in_range = true;
    for(int i = 0; i < n; ++i) {
        all_in_range = test_array[i] >= 0 && test_array[i] <= max_int;
    }

    cr_assert(all_in_range);
}