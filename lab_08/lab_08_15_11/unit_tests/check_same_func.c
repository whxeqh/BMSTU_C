#include "check_same_func.h"

int my_assert_double_eq_tol(double x, double y, double eps)
{
    return ABS(x - y) <= eps;
}

bool are_double_matrixes_equal(double **left, size_t rows_left, size_t columns_left, double **right, size_t rows_right, size_t columns_right)
{
    if (rows_left != rows_right || columns_left != columns_right)
        return false;

    for (size_t i = 0; i < rows_left; i++)
    {
        for (size_t j = 0; j < columns_left; j++)
        {
            if (!my_assert_double_eq_tol(left[i][j], right[i][j], EPS))
                return false;
        }
    }

    return true;
}
