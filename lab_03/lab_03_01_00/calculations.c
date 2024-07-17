#include "calculations.h"

/**
 * @brief Функция проверки упорядоченности элементов в столбце матрицы.
 *
 * Если элементы столбца k матрицы упорядочены по убыванию, то ans[k] = 1, иначе ans[k] = 0.
 *
 * @param[out] ans Указатель на массив, который будет заполнен результатами проверки.
 * @param[in] matrix Исходная матрица
 * @param[in] a_n Количество строк в матрице.
 * @param[in] a_m Количество столбцов в матрице.
 */
void ans_array(int *ans, int (*matrix)[M], const size_t a_n, const size_t a_m)
{
    for (size_t j = 0; j < a_m; j++)
    {   
        if (is_decreasing(matrix, a_n, j))
            ans[j] = 1;
        else
            ans[j] = 0;
    }
}


/**
 * @brief Функция проверки убыванию элементов в столбце матрицы.
 *
 * Функция проверяет, упорядочены ли элементы столбца матрицы по убыванию.
 *
 * @param[in] matrix Матрица, в которой производится проверка.
 * @param[in] a_n Количество строк в матрице.
 * @param[in] a_m Номер столбца, который проверяется на упорядоченность.
 * @return true, если элементы столбца упорядочены по убыванию, иначе false.
 */
bool is_decreasing(int (*matrix)[M], const size_t a_n, const size_t a_m)
{
    if (a_n <= 1)
        return false;
    for (size_t i = 0; i < a_n - 1; i++)
        if (matrix[i][a_m] <= matrix[i + 1][a_m])
            return false;
    return true;
}
