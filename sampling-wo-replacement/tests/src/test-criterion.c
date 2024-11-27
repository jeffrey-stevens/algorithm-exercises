#include "sample.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#include <criterion/criterion.h>
#include <criterion/parameterized.h>

#define SAMPLE_SIZE 10
#define MIN_NUM 0
#define MAX_NUM 9


// void test_sample_string(void) {
//     #define SAMPLES -100, 25, -939, 33, 896, -1252, 94837, -923458
//     int samples[] = {SAMPLES};
//     int sample_size = sizeof(samples) / sizeof(samples[0]);

//     char * str = array_to_string(sample_size, samples);

//     puts(str);

//     free(str);
// }


Test(misc, failing, .description = "Forcing a failure...") {
    cr_assert(false, "Forced failure.");
}

Test(misc, passing) {
    cr_assert(true, "Forced pass.");
}


struct array_to_string_params {
    int test_samples[8];
    int sample_size;
    char expected_str[256];
};


ParameterizedTestParameters(array_to_string, serialize) {

    static struct array_to_string_params params[] = {
        { 
            .test_samples = {0},
            .sample_size = 0,
            .expected_str = "[]"
        },
        {
            .test_samples = {-100, 25, -939, 33, 896, -1252, 94837, -923458},
            .sample_size = 8,
            .expected_str = "[-100, 25, -939, 33, 896, -1252, 94837, -923458]"
        }
    };

    int params_size = sizeof(params) / sizeof(struct array_to_string_params);

    return cr_make_param_array(struct array_to_string_params, params, params_size);
};


ParameterizedTest(struct array_to_string_params * params, array_to_string, serialize) {

    char * test_str = array_to_string(params->sample_size, params->test_samples);

    // There's a bug with the way Criterion handles format strings
    // in the assertions...
    int test_size = strlen(test_str);
    int expected_size = strlen(params->expected_str);
    // cr_assert(test_size == expected_size,
    //     "Expected the length of the serialized test string to equal the length of"
    //     "the expected string:\n"
    //     "Test string: %s\n"
    //     "Expected string: %s\n",
    //     test_size, expected_size);
    cr_assert(test_size == expected_size);

    // cr_expect(strncmp(test_str, params->expected_str, expected_size) == 0,
    //     "Expected serialized array to match expected string:\n"
    //     "Test string: %s\n"
    //     "Expected string: %s\n",
    //     test_str, params->expected_str);
    cr_expect(strncmp(test_str, params->expected_str, expected_size) == 0);

    free(test_str);
}


// Test(array_to_string, serialize) {

//     #define TEST_ARRAY {-100, 25, -939, 33, 896, -1252, 94837, -923458}
//     #define EXPECTED_STR "[-100, 25, -939, 33, 896, -1252, 94837, -923458]"

//     int samples[] = TEST_ARRAY;
//     int sample_size = sizeof(samples) / sizeof(samples[0]);
//     char * test_str = array_to_string(sample_size, samples);
    
//     cr_expect(strncmp(test_str, EXPECTED_STR, sample_size) == 0,
//         "Expected serialized array to match expected string:\n"
//         "Test string: %s\n"
//         "Expected string: %s\n",
//         test_str, EXPECTED_STR);

//     free(test_str);
//     #undef TEST_ARRAY
//     #undef EXPECTED_STR
// }


// Test(array_to_string, empty) {

//     #define TEST_ARRAY {}
//     #define EXPECTED_STR "[]"

//     int samples[] = TEST_ARRAY;
//     int sample_size = sizeof(samples) / sizeof(samples[0]);
//     char * test_str = array_to_string(sample_size, samples);
    
//     cr_expect(strncmp(test_str, EXPECTED_STR, sample_size) == 0,
//         "Expected serialized array to match expected string:\n"
//         "Test string: %s\n"
//         "Expected string: %s\n",
//         test_str, EXPECTED_STR);

//     free(test_str);
//     #undef TEST_ARRAY
//     #undef EXPECTED_STR

// }


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