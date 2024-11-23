/*
 * Make a random sampling of integers such that no two integers are equal.
 * 
*/

#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <assert.h>


struct NumNode {
    int num;
    struct NumNode * left;
    struct NumNode * right;
};


void gen_sample(int sample_size, int min_int, int max_int, int * sample) {

    // This assumes that the caller has set the random seed.

    struct NumNode * root = NULL;



}