#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#include "utils.h"
#include "validate.h"
#include "error.h"


int sample_replace(int sample_size, int * dest_array, int src_size, int * src_array) {

    if (sample_size < 0 || src_size < 0) {
        return ERR_NEG_SIZE;
    }

    // sample_size > src_size is allowed under replacement

    if (dest_array == NULL || src_array == NULL) {
        return ERR_NULL_POINTER;
    }

    if (RAND_MAX < src_size - 1) {
        return ERR_SIZE_TOO_LARGE;
    }

    int j;
    for (int i = 0; i < sample_size; ++i) {
        j = rand() % src_size; 
        dest_array[i] = src_array[j];
    }

    return ERR_SUCCESS;
}


// Random ints from 0 to max_int, inclusive
//
int random_ints(int n, int max_int, int * array) {

    VALIDATE_NONNEG(n)
    VALIDATE_NONNEG(max_int)
    VALIDATE_NOT_NULL(array)
    VALIDATE_IN_RAND_RANGE(0, max_int)

    for(int i = 0; i < n; ++i) {
        // Write it this way to avoid overflow
        if (max_int == 0) {
            array[i] = 0;
        } else {
            array[i] = ((rand() - 1) % max_int) + 1;
        }
    }

    return ERR_SUCCESS;
}


// Random ints from min_int to max_int, inclusive
//
int random_ints_ranged(int n, int min_int, int max_int, int * array) {

    VALIDATE_NONNEG(n)
    VALIDATE_MIN_LE_MAX(min_int, max_int)
    VALIDATE_IN_RAND_RANGE(min_int, max_int)
    VALIDATE_NOT_NULL(array)
    
    int max_val = max_int - min_int;
    int err_code = random_ints(n, max_val, array);

    return err_code;
}