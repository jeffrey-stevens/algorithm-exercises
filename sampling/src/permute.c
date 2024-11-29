#include <stdlib.h>

#define PERM_ERR_SUCCESS 0;
#define PERM_ERR_NEG_SIZE 1;
#define PERM_ERR_NULL_ARRAY 2;


// Generates a permutation of 0, .., n - 1.
// Assumes that rand seed has been set...
//
int permutation(int n, int array[]) {

    if (n < 0) {
        return PERM_ERR_NEG_SIZE;
    }

    if (array == NULL) {
        return PERM_ERR_NULL_ARRAY;
    }

    // Initialize the array
    for (int i = 0; i < n; ++i) {
        array[i] = i;
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