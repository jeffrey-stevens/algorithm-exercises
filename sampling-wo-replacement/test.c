#include "sample.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define SAMPLE_SIZE 10
#define MIN_NUM 0
#define MAX_NUM 9


static void fatal_error(char * message) {
    perror(message);
    exit(EXIT_FAILURE);
}


int * samples_array(int size) {
    
    if (size < 0) {
        fatal_error("Array size parameter was negative.");
    }

    int * samples = (int *) malloc(size * sizeof(int));

    if (samples == NULL) {
        fatal_error("Unable to allocate memory for samples array.");
    }

    return samples;
}


void print_samples(int sample_size, int * samples) {

    printf("[");
    for (int i = 0; i < sample_size; ++i) {
        printf("%d", samples[i]);
        if (i < sample_size - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    return;
}


bool test_min_eq_max() {

    int min_int = 10;
    int max_int = min_int;
    int sample_size = 1;
    int test_passed = false;

    int * samples = samples_array(sample_size);

    int result = gen_sample(sample_size, min_int, max_int, samples);

    printf("Testing that min_int = max_int does not error and "
            "generates only a single value...\n");

    if (result == ERR_SUCCESS) {
        printf("Test passed: gen_sample() returned code ERR_SUCCESS.\n");

        // Check that the correct value was written
        if (samples[0] == min_int) {
            printf("Test passed: A single value of min_int = max_int = %d was generated.\n", min_int);
            test_passed = true;
        } else {
            printf("Test failed: The generated value of %d is not equal to min_int/max_int value of %d:\n",
                samples[0], min_int);
            print_samples(sample_size, samples);
            test_passed = false;
        }

    } else {
        printf("The function returned error code %d.\n", result);
        test_passed = false;
    }

    free(samples);

    return test_passed;
}


bool test_min_gt_max() {

    int min_int = 10;
    int max_int = min_int - 1;
    int sample_size = 10;
    int test_passed = false;

    printf("Testing that min_int > max_int fails with error code ERR_MIN_GT_MAX.\n");

    int * samples = samples_array(sample_size);
    int result = gen_sample(sample_size, min_int, max_int, samples);

    if (result == ERR_MIN_GT_MAX) {
        printf("Test passed: ERR_MIN_GT_MAX was returned.\n");
        test_passed = true;

    } else {
        printf("Test failed: min_int = %d, max_int = %d failed with error code %d.\n",
            min_int, max_int, result);
        test_passed = false;
    }

    return test_passed;
}


bool test_range() {

    int min_int = -1;
    int max_int = RAND_MAX;
    int sample_size = 10;
    int test_passed = false;

    printf("Testing that max_int - min_int > RAND_MAX fails with error code ERR_RANGE_TOO_LARGE.\n");

    int * samples = samples_array(sample_size);
    int result = gen_sample(sample_size, min_int, max_int, samples);

    if (result == ERR_RANGE_TOO_LARGE) {
        printf("Test passed: ");
        printf("min_int = %d, max_int = %d, RAND_MAX = %d fails with error code ERR_RANGE_TOO_LARGE.\n",
            min_int, max_int, RAND_MAX);
        test_passed = true;

    } else {
        printf("Test failed: ");
        printf("gen_sample() gave return code %d.\n", result);
        test_passed = false;
    }

    return test_passed;
}


bool test_sample_size() {
    return true;
}


bool test_basic_usage() {

    bool test_passed = false;
    int sample_size = 10;
    int * samples = samples_array(sample_size);
    int min_num = 0;
    int max_num = 9;

    printf("Simple test of gen_sample().\n");

    int result = gen_sample(sample_size, min_num, max_num, samples);

    if (result == ERR_SUCCESS) {
        printf("The array of samples was generated successfully:\n");
        print_samples(SAMPLE_SIZE, samples);
        test_passed = true;

    } else {
        printf("The array of samples failed with return code %d.\n", result);
        test_passed = false;
    }

    free(samples);

    return test_passed;
}

int main(int argc, char * argv[]) {

    // TODO: Keep track of whether all tests passed or failed.
    test_basic_usage();
    printf("\n");
    test_min_eq_max();
    printf("\n");
    test_min_gt_max();
    printf("\n");
    test_range();

    return EXIT_SUCCESS;
}