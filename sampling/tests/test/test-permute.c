#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include <criterion/new/assert.h>

#include "permute.h"
#include "utils.h"


Test(permutation, n_neg, .description = 
        "Test that n < 0 returns error code PERM_ERR_NEG_SIZE." ) {

    int n = -1;
    int err_code = permutation(n, NULL);

    cr_assert(eq(int, err_code, PERM_ERR_NEG_SIZE));
}

Test(permutation, array_null, .description =
        "Test that array = NULL returns PERM_ERR_NULL_ARRAY.") {
    int n = 1;
    int err_code = permutation(n, NULL);

    cr_assert(eq(int, err_code, PERM_ERR_NULL_ARRAY));
}


Test(permutation, n_eq_zero, .description =
        "Test that n = 0 returns PERM_ERR_SUCCESS and doesn't change the array.") {

    int n = 0;
    int ref_array[] = {6, 2, 7, 9, 4, 8, 0, 3, 1, 5};
    int size = sizeof(ref_array) / sizeof(int);

    int * test_array = int_array(size);
    for (int i = 0; i < size; ++i) {
        test_array[i] = ref_array[i];
    }

    int err_code = permutation(n, test_array);

    cr_assert(eq(int, err_code, PERM_ERR_SUCCESS));
    cr_expect(eq(int[size], test_array, ref_array));

    free(test_array);
}


Test(permutation, is_permutation, .description =
        "Verifies that permutation() contains all integers 0, ..., n - 1.") {

    int n = 100;

    int * test_array = int_array(n);
    int err_code = permutation(n, test_array);

    cr_assert(eq(int, err_code, PERM_ERR_SUCCESS));

    // Warn if the permutation is not a proper (i.e. nontrivial) permutation
    bool is_permuted = false;
    for (int i = 0; i < n && !is_permuted; ++i) {
        is_permuted = test_array[i] != i;
    }

    if (is_permuted) {
        cr_log_info("Generated a nontrivial permutation.");
    } else {
        cr_log_warn("Generated the trivial permutation.");
    }

    // Sort the array and verify that it is equal to [0, ..., n - 1].
    sort_int_array(n, test_array);
    
    bool all_equal = true;
    for (int i = 0; i < n && all_equal; ++i) {
        all_equal = test_array[i] == i;
    }
    
    cr_expect(all_equal);

    free(test_array);
}


Test(permutation, does_not_overwrite, .description =
        "Verifies that permutation() does not overwrite elements past index n - 1.") {

    int n = 100;
    int size = n + 10;

    // Initialize the end of the test array
    int * test_array = int_array(size);
    for (int i = n; i < size; ++i) {
        test_array[i] = -1;
    }

    int err_code = permutation(n, test_array);

    cr_assert(eq(int, err_code, PERM_ERR_SUCCESS));
    
    bool any_changed = false;
    for (int i = n; i < size && !any_changed; ++i) {
        any_changed = test_array[i] != -1;
    }
    
    cr_expect(not(any_changed));

    free(test_array);
}