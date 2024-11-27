#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#include "utils.h"


void fatal_error(char * message) {
    perror(message);
    exit(EXIT_FAILURE);
}


int * int_array(int size) {
    
    if (size < 0) {
        fatal_error("Array size parameter was negative.");
    }

    int * samples = (int *) malloc(size * sizeof(int));

    if (samples == NULL) {
        fatal_error("Unable to allocate memory for the array.");
    }

    return samples;
}


void print_int_array(int size, int * array) {

    printf("[");
    for (int i = 0; i < size; ++i) {
        printf("%d", array[i]);
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    return;
}


char * int_array_to_string(int size, int * array) {

    // Get the maximum string width for integers
    char tmp_buffer[50];
    int max_int_width = snprintf(tmp_buffer,
        sizeof(tmp_buffer) / sizeof(tmp_buffer[0]), "%d", INT_MIN);
    
    // Calculate the maximum buffer size
    int fixed_chars = 3;  // '[', ']', and '\0'
    int total_digits = max_int_width * size;  // The maximum width of all digits
    int total_seps = (size <= 0) ? 0 : 2 * (size - 1);
    int buffer_size = fixed_chars + total_digits + total_seps;

    char * buffer = (char *) malloc(buffer_size * sizeof(char));

    int idx = 0;
    buffer[idx] = '[';
    int chars_written = 1;
    idx += chars_written;
    int remaining_size = buffer_size - idx;

    for (int i = 0; i < size; ++i) {
        // Add the integer to the buffer
        chars_written = snprintf(buffer + idx, remaining_size, "%d", array[i]);
        idx += chars_written;
        remaining_size = buffer_size - idx;

        if (i < size - 1) {
            // Add the separator
            chars_written = snprintf(buffer + idx, remaining_size, ", ");
            idx += chars_written;
            remaining_size = buffer_size - idx;
        }
    }

    buffer[idx] = ']';
    buffer[idx + 1] = '\0';

    return buffer;
}


static int compare_ints(const void * val1, const void * val2) {
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


void sort_int_array(int size, int * array) {
    qsort(array, size, sizeof(int), compare_ints);
}