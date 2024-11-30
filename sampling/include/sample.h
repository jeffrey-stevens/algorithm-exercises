#ifndef SAMPLE_H
#define SAMPLE_H

int validate_inputs(int sample_size, int min_int, int max_int, int * sample);
int gen_sample_tree(int sample_size, int min_int, int max_int, int * sample);
int gen_sample_hash(int sample_size, int min_int, int max_int, int * sample);

#endif