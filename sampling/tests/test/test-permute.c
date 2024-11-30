#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include <criterion/new/assert.h>

#include "permute.h"
#include "utils.h"

// Is there a better way of doing this?
#define TEST_PERM_MAX_BITS 20   /* 1 MB */
#define TEST_PERM_MAX_SIZE \
        (PERMUTATION_MAX_SIZE >> TEST_PERM_MAX_BITS > 0) \
        ? 1 << TEST_PERM_MAX_BITS : PERMUTATION_MAX_SIZE


static void free_params(struct criterion_test_params * ctp) {
    cr_free(ctp->params);
}


static bool is_trivial(int size, int * array) {

    bool is_sequential = false;
    for (int i = 0; i < size && is_sequential; ++i) {
        is_sequential = array[i] == i;
    }

    return is_sequential;
}


static bool is_permutation(int size, int * array) {

    int * acopy = (int *) malloc(sizeof(int) * size);
    memcpy(acopy, array, sizeof(int) * size);

    sort_int_array(size, acopy);
    
    bool all_equal = true;
    for (int i = 0; i < size && all_equal; ++i) {
        all_equal = acopy[i] == i;
    }

    free(acopy);

    return all_equal;
}


Test(permutation, n_neg, .description = 
        "Test that n < 0 returns error code PERM_ERR_NEG_SIZE.") {

    int n = -1;
    int err_code = permutation(n, NULL);

    cr_assert(eq(int, err_code, PERM_ERR_NEG_SIZE));
}


Test(permutation, n_too_large, .description = 
        "Test that n > RAND_MAX + 1 returns error code PERM_ERR_TOO_LARGE.") {

#if (RAND_MAX < INT_MAX - 1)
    int n = RAND_MAX + 2;
    int err_code = permutation(n, NULL);

    cr_expect(eq(int, err_code, PERM_ERR_TOO_LARGE));

#else
    cr_log_warn("RAND_MAX is too close to INT_MAX on this machine "
        "to test permutation::n_too_large.");
#endif
}


Test(permutation, array_null, .description =
        "Test that array = NULL returns PERM_ERR_NULL_ARRAY.") {
    int n = 1;
    int err_code = permutation(n, NULL);

    cr_assert(eq(int, err_code, PERM_ERR_NULL_ARRAY));
}


ParameterizedTestParameters(permutation, is_permutation) {

    static int edge_ns[] = {0, TEST_PERM_MAX_SIZE};
    int edge_size = sizeof(edge_ns) / sizeof(int);

    int max_log = (int) log10((double) TEST_PERM_MAX_SIZE);
    int internal_size = max_log + 1;
    int total_size = edge_size + internal_size;

    int * ns = (int *) cr_malloc(sizeof(int) * total_size);

    memcpy(ns, edge_ns, sizeof(int) * edge_size);

    // Test powers of 10 up to TEST_PERM_MAX_SIZE
    int n = 1;
    for (int i = edge_size; i < total_size; ++i) {
        ns[i] = n;
        // Doesn't matter if this overflows...
        n *= 10;
    }

   return cr_make_param_array(int, ns, total_size, free_params);
}


ParameterizedTest(int * np, permutation, is_permutation, .description =
        "Verifies that permutation() is indeed a permutation of 0, ..., n - 1.") {

    int n = *np;
    int * test_array = int_array(n);

    int err_code = permutation(n, test_array);

    cr_assert(eq(int, err_code, PERM_ERR_SUCCESS));

    // Warn if the permutation is not a proper (i.e. nontrivial) permutation
    if (n > 1) {
        if (is_trivial(n, test_array)) {
            cr_log_warn("Generated the trivial permutation.");
        } else {
            cr_log_info("Generated a nontrivial permutation.");
        }
    }
    
    cr_expect(is_permutation(n, test_array));

    free(test_array);
}


// Test(permutation, n_eq_zero, .description =
//         "Test that n = 0 returns PERM_ERR_SUCCESS and doesn't change the array.") {

//     int n = 0;
//     int ref_array[] = {6, 2, 7, 9, 4, 8, 0, 3, 1, 5};
//     int size = sizeof(ref_array) / sizeof(int);

//     int * test_array = int_array(size);
//     for (int i = 0; i < size; ++i) {
//         test_array[i] = ref_array[i];
//     }

//     int err_code = permutation(n, test_array);

//     cr_assert(eq(int, err_code, PERM_ERR_SUCCESS));
//     cr_expect(eq(int[size], test_array, ref_array));

//     free(test_array);
// }


// Test(permutation, is_permutation, .description =
//         "Verifies that permutation() contains all integers 0, ..., n - 1.") {

//     int n = 100;

//     int * test_array = int_array(n);
//     int err_code = permutation(n, test_array);

//     cr_assert(eq(int, err_code, PERM_ERR_SUCCESS));

//     // Warn if the permutation is not a proper (i.e. nontrivial) permutation
//     if (is_trivial(n, test_array)) {
//         cr_log_warn("Generated the trivial permutation.");
//     } else {
//         cr_log_info("Generated a nontrivial permutation.");
//     }
    
//     cr_expect(is_permutation(n, test_array));

//     free(test_array);
// }


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