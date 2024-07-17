#include <stdio.h>
#include "io.h"

/**
 * @brief Функция обработки ввода размеров матрицы.
 * 
 * @param[out] a_n Указатель на переменную, в которую будет записано количество строк.
 * @param[out] a_m Указатель на переменную, в которую будет записано количество столбцов.
 * 
 * @return Код ошибки
 */
int input_size(size_t *a_n, size_t *a_m)
{
    int size_n, size_m;
    printf("Введите кол-во строк и столбцов матрицы: ");
    if (scanf("%d%d", &size_n, &size_m) != 2)
        return ERR_IO;
    if (size_n <= 0 || size_n > N || size_m <= 0 || size_m > M)
        return ERR_RANGE;
        
    *a_n = size_n;
    *a_m = size_m;
    return OK;
}

/**
 * @brief Функция обработки ввода матрицы
 * 
 * @param[in] a_n
 * @param[in] a_m
 * @param[out] matrix
 * 
 * @return Код ошибки 
*/
int input_matrix(const size_t a_n, const size_t a_m, int (*matrix)[M])
{
    printf("Введите матрицу:\n");
    for (size_t i = 0; i < a_n; i++)
        for (size_t j = 0; j < a_m; j++)
            if (scanf("%d", &matrix[i][j]) != 1)
                return ERR_IO;
    return OK;
}

