#ifndef PERMUTE_H
#define PERMUTE_H

#define PERMUTATION_MAX_SIZE \
    (RAND_MAX == INT_MAX ? INT_MAX : RAND_MAX + 1)


int permute(int n, int * array);
int permutation(int n, int * array);

#endif