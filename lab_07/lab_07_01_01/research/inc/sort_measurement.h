#ifndef __SORT_MEASUREMENT_H__
#define __SORT_MEASUREMENT_H__

#include "array.h"
#include <stddef.h>

typedef void (*uni_sort_t)(void *pbeg, const size_t length, const size_t el_size, const cmp_t uni_cmp);
typedef void (*init_array_t)(const size_t length, int *arr);

unsigned long long sort_measurement(const size_t length, const size_t reps, const char *filename_in, const char *filename_out, init_array_t init_array, uni_sort_t sort);

#endif // __ERRORS_H__
