#ifndef CALCULCATION_H
#define CALCULCATION_H

#include <stddef.h>
#include "constants.h"

int summ_array(const size_t a_m, const int *a);
void swap_elements(int *a, int *b);
void swap_arrays(int *arr_first, int *arr_second, const size_t a_m);
void sort(const size_t a_n, const size_t a_m, int (*matrix)[M], int *keys);
void form_key_array(const size_t a_n, const size_t a_m, int (*matrix)[M], int *kyes);

#endif 

