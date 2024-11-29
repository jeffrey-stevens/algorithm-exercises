#ifndef UTILS_H
#define UTILS_H

void fatal_error(char * message);
int * int_array(int size);
void print_int_array(int size, int * array);
char * int_array_to_string(int size, int * array);
void sort_int_array(int size, int * array);

#endif