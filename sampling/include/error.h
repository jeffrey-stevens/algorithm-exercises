#ifndef ERROR_H
#define ERROR_H

#define ERR_SUCCESS             0
#define ERR_NULL_POINTER        1
#define ERR_NEG_SIZE            2
#define ERR_SIZE_TOO_LARGE      3
#define ERR_MIN_GT_MAX          4
#define ERR_RANGE_TOO_LARGE     5


void fatal_error(char * message);


#endif