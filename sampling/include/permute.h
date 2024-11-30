#ifndef PERMUTE_H
#define PERMUTE_H

#define PERMUTATION_MAX_SIZE \
    (RAND_MAX == INT_MAX ? INT_MAX : RAND_MAX + 1)


int permute(int n, int * array);
int permutation(int n, int * array);
bool is_trivial(int size, int * array);
bool is_permuted(int size, int * test_array, int * ref_array);
bool is_permutation(int size, int * array);

#endif