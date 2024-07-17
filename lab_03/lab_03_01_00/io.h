#ifndef IO_H
#define IO_H

#include <stddef.h>
#include "constants.h"
#include "errors.h"

int input_size(size_t *a_n, size_t *a_m);
int input_matrix(const size_t a_n, const size_t a_m, int (*matrix)[M]);
void print_arr(const size_t arr_size, int *ans);

#endif 

