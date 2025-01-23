#ifndef __CHECK_ARRAY_H__
#define __CHECK_ARRAY_H__

#include "check.h"
#include <stdbool.h>

bool is_arrays_equal(const void *pfirst, const size_t length_first, const void *psecond, const size_t length_second, \
                     const size_t el_size, int (*uni_cmp )(const void *left, const void *right));

int cmp_uni_char(const void *left, const void *right);

int cmp_uni_double(const void *left, const void *right);

Suite* bynary_search_suite(void);
Suite* mysort_int_suite(void);
Suite* mysort_char_suite(void);
Suite* mysort_double_suite(void);
Suite* key_suite(void);

#endif //__CHECK_ARRAY_H__
