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

Test(permutation, n_zero, .description =
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