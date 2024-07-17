#ifndef CALCULCATION_H
#define CALCULCATION_H

#include <stddef.h>
#include <stdbool.h>
#include "constants.h"

int first_digit(int num);
int last_digit(int num);
//void insert_string(const size_t a_n, const size_t a_m, int (*matrix)[M], const size_t pos);
bool is_equal_count(const size_t arr_size, int *array, const short digit);
//size_t edit_matrix(size_t a_n, const size_t a_m, int (*matrix)[M], const short digit);

void fill_string(const size_t a_m, int *arr, const int num);
void assign_arrays(int *first_arr, const int *second_arr, const size_t size);
int new_insert_string(size_t *a_n, const size_t a_m, int (*matrix)[M], const int *arr, const size_t pos);
int new_edit_matrix(size_t *a_n, const size_t a_m, int (*matrix)[M], const short digit);

#endif 

