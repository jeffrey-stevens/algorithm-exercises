#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#include "permute.h"
#include "error.h"
#include "testing.h"


STATIC int validate_inputs(int n, int * array) {

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


STATIC void permute_(int n, int * array) {

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


bool is_permuted(int size, int * test_array, int * ref_array) {

    int * test_copy = copy_int_array(size, test_array);
    int * ref_copy = copy_int_array(size, ref_array);

    // This isn't the most efficient...
    // Better to implement quicksort directly, and then compare
    // the positioning of the pivots

    sort_int_array(size, test_copy);
    sort_int_array(size, ref_copy);

    bool are_equal = int_arrays_equal(size, test_copy, ref_copy);

    free(test_copy);
    free(ref_copy);

    return are_equal;
}


bool is_trivial(int size, int * array) {

    bool is_sequential = false;
    for (int i = 0; i < size && is_sequential; ++i) {
        is_sequential = array[i] == i;
    }

    return is_sequential;
}


bool is_permutation(int size, int * array) {

    int * acopy = copy_int_array(size, array);

    sort_int_array(size, acopy);
    
    bool all_equal = true;
    for (int i = 0; i < size && all_equal; ++i) {
        all_equal = acopy[i] == i;
    }

    free(acopy);

    return all_equal;
}