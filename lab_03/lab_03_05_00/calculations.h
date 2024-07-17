#ifndef CALCULCATION_H
#define CALCULCATION_H

#include <stdbool.h>
#include <stddef.h>
#include "constants.h"

bool is_simple(const int x);
void swap_elements(int *a, int *b);
void reverse_array(const size_t arr_size, int *a);
size_t fill_array(const size_t a_n, const size_t a_m, int (*matrix)[M], int *arr);
void fill_matrix(const size_t a_n, const size_t a_m, int (*matrix)[M], const size_t arr_size, const int *arr);

#endif 

