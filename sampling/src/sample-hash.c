
#include "sample.h"
#include "utils.h"
#include "testing.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


int gen_sample_hash(int sample_size, int min_int, int max_int, int * sample) {

    int err_code = validate_inputs(sample_size, min_int, max_int, sample);

    return ERR_SUCCESS;
}