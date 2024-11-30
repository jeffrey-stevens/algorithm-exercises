#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#include "permute.h"
#include "error.h"


static int validate_inputs(int n, int * array) {

    int err_code = ERR_SUCCESS;

    if (n < 0) {
        err_code = ERR_NEG_SIZE;

    } else if (n > PERMUTATION_MAX_SIZE) {
        err_code = ERR_SIZE_TOO_LARGE;

    } else if (array == NULL) {
        err_code = ERR_NULL_POINTER;

    } else {
        err_code = ERR_SUCCESS;
    }

    return err_code;
}


static void permute_(int n, int * array) {

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
}


// Permutes an array of n elements
// Assumes that rand seed has been set...
//
int permute(int n, int * array) {

    int err_code = validate_inputs(n, array);
    if (err_code != ERR_SUCCESS) {
        return err_code;
    }

    permute_(n, array);

    // Once all positions have been swapped at least once, this guarantees
    // that each integer has an equal chance of being at any given position.

    return ERR_SUCCESS;
}


// Generates a permutation of 0, .., n - 1.
// Assumes that rand seed has been set...
//
int permutation(int n, int * array) {

    int err_code = validate_inputs(n, array);
    if (err_code != ERR_SUCCESS) {
        return err_code;
    }

    // Initialize the array
    for (int i = 0; i < n; ++i) {
        array[i] = i;
    }

    permute_(n, array);

    return ERR_SUCCESS;
}