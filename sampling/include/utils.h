#ifndef UTILS_H
#define UTILS_H

int * int_array(int size);
void print_int_array(int size, int * array);
char * int_array_to_string(int size, int * array);
bool int_arrays_equal(int size, int * array1, int * array2);
int * copy_int_array(int n, int * array);
void sort_int_array(int size, int * array);

#endif