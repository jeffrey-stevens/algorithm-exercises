#include "sample.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define SAMPLE_SIZE 10
#define MIN_NUM 0
#define MAX_NUM 9


int main(int argc, char * argv[]) {

    int sampling[SAMPLE_SIZE];
    int result = gen_sample(SAMPLE_SIZE, MIN_NUM, MAX_NUM, sampling);

    printf("Return code: %d\n", result);

    if (result == ERR_SUCCESS) {

        printf("Result: [");
        for (int i = 0; i < SAMPLE_SIZE; ++i) {
            printf("%d", sampling[i]);
            if (i < SAMPLE_SIZE - 1) {
                printf(", ");
            }
        }
        printf("]\n");
    }
}