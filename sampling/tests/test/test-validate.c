#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include <criterion/new/assert.h>

#include "validate.h"
#include "utils.h"
#include "error.h"


int validate_nonneg(int x) {
    VALIDATE_NONNEG(x)
    return ERR_SUCCESS;
}

int validate_not_null(int * x) {
    VALIDATE_NOT_NULL(x)
    return ERR_SUCCESS;
}

int validate_min_le_max(int min, int max) {
    VALIDATE_MIN_LE_MAX(min, max)
    return ERR_SUCCESS;
}

int validate_in_rand_range(int min, int max) {
    VALIDATE_IN_RAND_RANGE(min, max)
    return ERR_SUCCESS;
}

int validate_size_in_rand_range(int x) {
    VALIDATE_SIZE_IN_RAND_RANGE(x)
    return ERR_SUCCESS;
}


Test(validate, is_nonneg, .description =
        "Verify that x is not negative.") {

    cr_expect(eq(int, validate_nonneg(0), ERR_SUCCESS));
    cr_expect(eq(int, validate_nonneg(1), ERR_SUCCESS));
    cr_expect(eq(int, validate_nonneg(INT_MAX), ERR_SUCCESS));

    cr_expect(eq(int, validate_nonneg(-1), ERR_NEG_SIZE));
    cr_expect(eq(int, validate_nonneg(INT_MIN), ERR_NEG_SIZE));
}


Test(validate, not_null, .description = 
        "Verify that x is not a null pointer.") {

    int * ptr = (int *) 1;
    cr_expect(eq(int, validate_not_null(ptr), ERR_SUCCESS));
    cr_expect(eq(int, validate_not_null(NULL), ERR_NULL_POINTER));
}


Test(validate, min_le_max, .description = 
        "Verify that min <= max.") {

    cr_expect(eq(int, validate_min_le_max(0, 0), ERR_SUCCESS));
    cr_expect(eq(int, validate_min_le_max(0, 1), ERR_SUCCESS));
    cr_expect(eq(int, validate_min_le_max(-1, 0), ERR_SUCCESS));
    cr_expect(eq(int, validate_min_le_max(INT_MIN, INT_MIN + 1), ERR_SUCCESS));
    cr_expect(eq(int, validate_min_le_max(INT_MAX - 1, INT_MAX), ERR_SUCCESS));
    cr_expect(eq(int, validate_min_le_max(INT_MIN, INT_MAX), ERR_SUCCESS));

    cr_expect(eq(int, validate_min_le_max(1, 0), ERR_MIN_GT_MAX));
    cr_expect(eq(int, validate_min_le_max(INT_MIN + 1, INT_MIN), ERR_MIN_GT_MAX));
    cr_expect(eq(int, validate_min_le_max(INT_MAX, INT_MAX - 1), ERR_MIN_GT_MAX));
    cr_expect(eq(int, validate_min_le_max(INT_MAX, INT_MIN), ERR_MIN_GT_MAX));
}


Test(validate, in_rand_range, .description = 
        "Verify that range(min, max) is within range of RAND_MAX") {

    cr_expect(eq(int, validate_in_rand_range(0,0), ERR_SUCCESS));
    cr_expect(eq(int, validate_in_rand_range(RAND_MAX, RAND_MAX), ERR_SUCCESS));
    cr_expect(eq(int, validate_in_rand_range(0, RAND_MAX), ERR_SUCCESS));
    cr_expect(eq(int, validate_in_rand_range(-RAND_MAX, 0), ERR_SUCCESS));

    cr_expect(eq(int, validate_in_rand_range(-1, RAND_MAX), ERR_OUT_OF_RANGE));
    cr_expect(eq(int, validate_in_rand_range(-RAND_MAX, 1), ERR_OUT_OF_RANGE));
    cr_expect(eq(int, validate_in_rand_range(-RAND_MAX, RAND_MAX), ERR_OUT_OF_RANGE));
    cr_expect(eq(int, validate_in_rand_range(-1, INT_MAX), ERR_OUT_OF_RANGE));
    cr_expect(eq(int, validate_in_rand_range(INT_MIN, 1), ERR_OUT_OF_RANGE));
    cr_expect(eq(int, validate_in_rand_range(INT_MIN, INT_MAX), ERR_OUT_OF_RANGE));
}


Test(validate, size_in_rand_range, .description =
        "Verify that n isn't too large for random array indexing." ) {

    cr_expect(eq(int, validate_size_in_rand_range(0), ERR_SUCCESS));
    cr_expect(eq(int, validate_size_in_rand_range(RAND_MAX), ERR_SUCCESS));
    #if (RAND_MAX < INT_MAX)
    cr_expect(eq(int, validate_size_in_rand_range(RAND_MAX + 1), ERR_SUCCESS));
    #endif

    #if (RAND_MAX < INT_MAX - 1)
    cr_expect(eq(int, validate_size_in_rand_range(RAND_MAX + 2),
                 ERR_SIZE_TOO_LARGE));
    cr_expect(eq(int, validate_size_in_rand_range(INT_MAX),
                 ERR_SIZE_TOO_LARGE));
    #endif
}