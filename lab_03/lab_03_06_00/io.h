#ifndef IO_H
#define IO_H

#include <stddef.h>
#include "constants.h"
#include "errors.h"

int input_size(size_t *a_n, size_t *a_m);
void print_matrix(const size_t a_n, const size_t a_m, int (*a)[M]);

#endif 

