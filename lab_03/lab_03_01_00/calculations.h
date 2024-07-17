#ifndef CALCULCATION_H
#define CALCULCATION_H

#include <stddef.h>
#include <stdbool.h>
#include "constants.h"

void ans_array(int *ans, int (*a)[M], const size_t a_n, const size_t a_m);
bool is_decreasing(int (*matrix)[M], const size_t a_n, const size_t a_m);

#endif 

