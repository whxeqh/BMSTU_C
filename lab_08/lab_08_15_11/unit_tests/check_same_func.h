#ifndef __CHECK_SAME_FUNC_H__
#define __CHECK_SAME_FUNC_H__

#include <stdbool.h>
#include <stddef.h>

#define EPS 1e-8

#define ABS(A) ((A) < 0 ? -(A) : (A))

int my_assert_double_eq_tol(double x, double y, double eps);

bool are_double_matrixes_equal(double **left, size_t rows_left, size_t columns_left, double **right, size_t rows_right, size_t columns_right);

#endif //__CHECK_SAME_FUNC_H__