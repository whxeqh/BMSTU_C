#include "calculations.h"

/**
 * @brief Функция, заполняющая матрицу "ходом быка".
 * @param a_n[in] Количество строк
 * @param a_m[in] Количество столбцов
 * @param matrix[out] Указатель на первый элемент матрицы
*/
void fiil_matrix(const size_t a_n, const size_t a_m, int (*matrix)[M])
{
    int num = 1, sign;
    size_t i, k;
    for (size_t j = 0; j < a_m; j++)
    {
        if (j % 2 == 0)
        {
            sign = 1;
            i = 0;
            k = a_n;
        }
        else 
        {
            sign = -1;
            i = a_n - 1;
            k = -1;
        }

        while (i != k)
        {
            matrix[i][j] = num++;
            i += sign;
        }
    }
}
