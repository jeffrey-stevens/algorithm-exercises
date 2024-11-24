#ifndef SAMPLE_H
#define SAMPLE_H

#define ERR_SUCCESS                 0
#define ERR_NULL_ARRAY_POINTER      1
#define ERR_NEG_SAMPLE_SIZE         2
#define ERR_MIN_GT_MAX              3
#define ERR_RANGE_TOO_LARGE         4
#define ERR_SAMPLE_SIZE_TOO_LARGE   5


int gen_sample(int sample_size, int min_int, int max_int, int * sample);

#endif