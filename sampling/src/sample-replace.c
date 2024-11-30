#include <stdlib.h>
#include <limits.h>

#include "sample.h"
#include "utils.h"
#include "error.h"


int sample_replace(int sample_size, int * dest_array, int src_size, int * src_array) {

    if (sample_size < 0 || src_size < 0) {
        return ERR_NEG_SIZE;
    }

    // sample_size > src_size is allowed under replacement

    if (dest_array == NULL || src_array == NULL) {
        return ERR_NULL_POINTER;
    }

    if (RAND_MAX + 1 < src_size) {
        return ERR_SIZE_TOO_LARGE;
    }

    int j;
    for (int i = 0; i < sample_size; ++i) {
        j = rand() % src_size; 
        dest_array[i] = src_array[j];
    }

    return ERR_SUCCESS;
}
