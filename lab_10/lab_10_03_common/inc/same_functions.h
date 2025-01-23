#ifndef __SAME_FUNCTIONS_H__
#define __SAME_FUNCTIONS_H__

#include <stddef.h>
#include <stdbool.h>

#include "associative_array.h"
#include "data.h"

assoc_array_error_t fill_arr(assoc_array_t arr, data_t *data, size_t length);

bool assoc_arrays_equal(assoc_array_t first, assoc_array_t second, data_t *data_arr, size_t length);

bool assoc_array_equal(assoc_array_t arr, data_t *data_arr, size_t length);

void mul_value(const char *key, int *num, void *param);

void sqr_value(const char *key, int *num, void *param);

#endif //__SAME_FUNCTIONS_H__