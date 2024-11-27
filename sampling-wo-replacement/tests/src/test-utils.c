#include <criterion/criterion.h>
#include <criterion/parameterized.h>

#include "utils.h"



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

    char * test_str = int_array_to_string(params->sample_size, params->test_samples);

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