#include <stdlib.h>
#include <stdio.h>

#include "error.h"


void fatal_error(char * message) {
    perror(message);
    exit(EXIT_FAILURE);
}