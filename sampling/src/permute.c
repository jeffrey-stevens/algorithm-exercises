#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#include "permute.h"


static int validate_inputs(int n, int * array) {

    int err_code = PERM_ERR_SUCCESS;

    if (n < 0) {
        err_code = PERM_ERR_NEG_SIZE;

    } else if (n > PERMUTATION_MAX_SIZE) {
        err_code = PERM_ERR_SIZE_TOO_LARGE;

    } else if (array == NULL) {
        err_code = PERM_ERR_NULL_ARRAY;

    } else {
        err_code = PERM_ERR_SUCCESS;
    }

    return err_code;
}


// Permutes an array of n elements
// Assumes that rand seed has been set...
//
int permute(int n, int * array) {

    int err_code = validate_inputs(n, array);
    if (err_code != PERM_ERR_SUCCESS) {
        return err_code;
    }

    // Iterate through each position, performing one random transposition
    // for each.
    int j;  // The random index to swap
    int tmp;
    for (int i = 0; i < n; ++i) {
        j = rand() % n;
        // Swap i and j
        tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }

    // Once all positions have been swapped at least once, this guarantees
    // that each integer has an equal chance of being at any given position.

    return PERM_ERR_SUCCESS;
}


// Generates a permutation of 0, .., n - 1.
// Assumes that rand seed has been set...
//
int permutation(int n, int * array) {

    int err_code = validate_inputs(n, array);
    if (err_code != PERM_ERR_SUCCESS) {
        return err_code;
    }

    // Initialize the array
    for (int i = 0; i < n; ++i) {
        array[i] = i;
    }

    err_code = permute(n, array);

    return err_code;
}