#include <limits.h>

#include "error.h"


#define VALIDATE_NONNEG(x) \
    if ((x) < 0) { \
        return ERR_NEG_SIZE; \
    }

#define VALIDATE_NOT_NULL(x) \
    if ((x) == NULL) { \
        return ERR_NULL_POINTER; \
    }

#define VALIDATE_MIN_LE_MAX(min, max) \
    if ((min) > (max)) { \
        return ERR_MIN_GT_MAX; \
    }

#define VALIDATE_IN_RAND_RANGE(min, max) \
    if ( ((min) >= 0 && (max) - (min) > RAND_MAX) || \
            ((min) < 0 && (max) > RAND_MAX + (min)) ) { \
        return ERR_OUT_OF_RANGE; \
    }

#define VALIDATE_SIZE_IN_RAND_RANGE(x) \
    if (RAND_MAX < (x) - 1) { \
        return ERR_SIZE_TOO_LARGE; \
    }