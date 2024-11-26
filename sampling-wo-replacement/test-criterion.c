#include "sample.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#include <criterion/criterion.h>

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


char * samples_string(int sample_size, int * samples) {

    // Get the maximum string width for integers
    char tmp_buffer[50];
    int max_int_width = snprintf(tmp_buffer, sizeof(tmp_buffer) / sizeof(tmp_buffer[0]),
        "%d", INT_MIN);
    
    int buffer_size = 
        1  // "["
        + (max_int_width + 2) * (sample_size - 1)  // "N, " for the first sample_size - 1 integers
        + max_int_width  // "N" for the last integer
        + 1  // "]"
        + 1  // "\0"
        ;
    char * buffer = (char *) malloc(buffer_size * sizeof(char));

    int idx = 0;
    buffer[idx] = '[';
    idx = 1;
    int remaining_size = buffer_size - idx;
    int chars_written;

    for (int i = 0; i < sample_size; ++i) {
        if (i < sample_size - 1) {
            chars_written = snprintf(buffer + idx, remaining_size, "%d, ", samples[i]);
            idx += chars_written;
            remaining_size = buffer_size - idx;
        } else {
            snprintf(buffer + idx, remaining_size, "%d]", samples[i]);
        }
    }

    return buffer;
}


int compare_ints(const void * val1, const void * val2) {
    int * int1 = (int *) val1;
    int * int2 = (int *) val2;
    int result;
    
    if (*int1 < *int2) {
        result = -1;
    } else if (*int1 == *int2) {
        result = 0;
    } else {
        result = 1;
    }

    return result;
}


void sort_samples(int sample_size, int * samples) {
    qsort(samples, sample_size, sizeof(int), compare_ints);
}


// void test_sample_string(void) {
//     #define SAMPLES -100, 25, -939, 33, 896, -1252, 94837, -923458
//     int samples[] = {SAMPLES};
//     int sample_size = sizeof(samples) / sizeof(samples[0]);

//     char * str = samples_string(sample_size, samples);

//     puts(str);

//     free(str);
// }


Test(misc, failing) {
    cr_assert(false, "Forced failure.");
}

Test(misc, passing) {
    cr_assert(true, "Forced pass.");
}


Test(test_utilities, samples_string) {

    #define TEST_ARRAY {-100, 25, -939, 33, 896, -1252, 94837, -923458}
    #define EXPECTED_STR "[-100, 25, -939, 33, 896, -1252, 94837, -923458]"

    int samples[] = TEST_ARRAY;
    int sample_size = sizeof(samples) / sizeof(samples[0]);
    char * test_str = samples_string(sample_size, samples);
    
    cr_expect(strncmp(test_str, EXPECTED_STR, sample_size) == 0,
        "Expected serialized array to match expected string:\n"
        "Test string: %s\n"
        "Expected string: %s\n",
        test_str, EXPECTED_STR);

    free(test_str);
    #undef SAMPLES
}


// Test(gen_sample, min_eq_max) {

//     int min_int = 10;
//     int max_int = min_int;
//     int sample_size = 1;
//     int test_passed = false;

//     int * samples = samples_array(sample_size);

//     int result = gen_sample(sample_size, min_int, max_int, samples);

//     printf("Testing that min_int = max_int does not error and "
//             "generates only a single value...\n");
    
//     cr_assert(result == ERR_SUCCESS, 
//                 "gen_sample() returned error code %d..."
//                 "Expected %d (ERR_SUCCESS).", result, ERR_SUCCESS);
//     cr_expect(samples[0] == min_int,
//             "gen_sample() generated %s..."
//             "Expected a single value of min_int = max_int = %d.",
//             print_samples(sample_size, samples), min_int);

//     // if (result == ERR_SUCCESS) {
//     //     printf("Test passed: gen_sample() returned code ERR_SUCCESS.\n");

//     //     // Check that the correct value was written
//     //     if (samples[0] == min_int) {
//     //         printf("Test passed: A single value of min_int = max_int = %d was generated.\n", min_int);
//     //         test_passed = true;
//     //     } else {
//     //         printf("Test failed: The generated value of %d is not equal to "
//     //             "min_int/max_int value of %d:\n", samples[0], min_int);
//     //         print_samples(sample_size, samples);
//     //         test_passed = false;
//     //     }

//     // } else {
//     //     printf("The function returned error code %d.\n", result);
//     //     test_passed = false;
//     // }

//     free(samples);
// }


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
            printf("Test failed: The generated value of %d is not equal to "
                "min_int/max_int value of %d:\n", samples[0], min_int);
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

    printf("Testing that min_int > max_int fails with error code ERR_MIN_GT_MAX...\n");

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

    free(samples);

    return test_passed;
}


bool test_range() {

    int min_int = -1;
    int max_int = RAND_MAX;
    int sample_size = 10;
    int test_passed = false;

    printf("Testing that max_int - min_int > RAND_MAX fails with "
        "error code ERR_RANGE_TOO_LARGE...\n");

    int * samples = samples_array(sample_size);
    int result = gen_sample(sample_size, min_int, max_int, samples);

    if (result == ERR_RANGE_TOO_LARGE) {
        printf("Test passed: ");
        printf("min_int = %d, max_int = %d, RAND_MAX = %d fails with "
            "error code ERR_RANGE_TOO_LARGE.\n", min_int, max_int, RAND_MAX);
        test_passed = true;

    } else {
        printf("Test failed: ");
        printf("gen_sample() gave return code %d.\n", result);
        test_passed = false;
    }

    free(samples);

    return test_passed;
}


bool test_sample_size_1() {

    int min_int = 0;
    int max_int = 9;
    int range = max_int - min_int + 1;
    int sample_size = range;
    int test_passed = false;

    printf("Testing that having a sample size equal to the number range "
        "succeeds and generates all numbers in the range...\n");

    int * samples = samples_array(sample_size);
    int result = gen_sample(sample_size, min_int, max_int, samples);

    if (result == ERR_SUCCESS) {
        printf("Test passed: ");
        printf("gen_sample() gave return code ERR_SUCCESS.\n");

        // Check the entries
        sort_samples(sample_size, samples);

        int i = 0;
        bool all_match = true;
        while (i < sample_size && all_match) {
            all_match = samples[i] == min_int + i;
            ++i;
        }

        if (all_match) {
            printf("Test passed: ");
            printf("All values between %d and %d are represented in the array.\n",
                min_int, max_int);
            test_passed = true;

        } else {
            printf("Test failed: ");
            printf("Some values in the array were unexpected:\n");
            print_samples(sample_size, samples);
            test_passed = false;
        }

    } else {
        printf("Test failed: ");
        printf("gen_sample gave return code %d.\n", result);
        test_passed = true;
    }
    
    free(samples);

    return test_passed;
}


bool test_sample_size_2() {

    int min_int = 0;
    int max_int = 9;
    int range = max_int - min_int + 1;
    int sample_size = range + 1;
    int test_passed = false;

    printf("Testing that having a sample size larger than the number range "
        "fails with error code ERR_SAMPLE_SIZE_TOO_LARGE...\n");

    int * samples = samples_array(sample_size);
    int result = gen_sample(sample_size, min_int, max_int, samples);

    if (result == ERR_SAMPLE_SIZE_TOO_LARGE) {
        printf("Test passed: ");
        printf("min_int = %d, max_int = %d, sample_size = %d failed "
            "with error code ERR_SAMPLE_SIZE_TOO_LARGE.\n", min_int, max_int, sample_size);
        test_passed = true;

    } else {
        printf("Test failed: ");
        printf("gen_sample() gave return code %d.\n", result);
        test_passed = false;
    }

    free(samples);

    return test_passed;
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


// int main(int argc, char * argv[]) {

//     test_sample_string();
//     printf("\n");

//     // TODO: Keep track of whether all tests passed or failed.
//     test_basic_usage();
//     printf("\n");
//     test_min_eq_max();
//     printf("\n");
//     test_min_gt_max();
//     printf("\n");
//     test_range();
//     printf("\n");
//     test_sample_size_1();
//     printf("\n");
//     test_sample_size_2();
//     printf("\n");

//     return EXIT_SUCCESS;
// }