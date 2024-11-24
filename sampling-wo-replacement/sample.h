#ifndef SAMPLE_H
#define SAMPLE_H

#define ERR_SUCCESS                 0
#define ERR_MIN_GT_MAX              1
#define ERR_RANGE_TOO_LARGE         2
#define ERR_SAMPLE_SIZE_TOO_LARGE   3


int gen_sample(int sample_size, int min_int, int max_int, int * sample);

#endif