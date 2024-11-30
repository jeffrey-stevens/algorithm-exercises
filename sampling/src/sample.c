
#include <stdlib.h>

#include "sample.h"
#include "error.h"


int validate_inputs(int sample_size, int min_int, int max_int,
        int * sample) {

    int err_code = -1;

    if (sample == NULL) {
        err_code = ERR_NULL_POINTER;

    } else if (sample_size < 0) {
        err_code = ERR_NEG_SIZE;

    } else if (min_int > max_int) {
        err_code = ERR_MIN_GT_MAX;

    } else if (min_int < 0 && max_int > RAND_MAX + min_int - 1) {
        // Want max_int - min_int + 1 <= RAND_MAX.
        // Must rewrite this to avoid overflow...
        err_code = ERR_RANGE_TOO_LARGE;

    } else if (max_int - min_int + 1 < sample_size) {
        // The range is less than the sample size
        // Not possible to have distinct elements
        err_code = ERR_SIZE_TOO_LARGE;

    } else {
        err_code = ERR_SUCCESS;
    }

    return err_code;
}
