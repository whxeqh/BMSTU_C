#include "calculations.h"

/**
 * @brief Функция для нахождения минимального нечетного числа, расположенного под главной диагональю
 * 
 * @param[in] a_n Количество строк и столбцов (так как матрица квадратная)
 * @param[in] matrix Указатель на первый элемент матрицы
 * @param[out] number
 *  
 * @return Код ошибки
*/
int find_number(const size_t a_n, int (*matrix)[M], int *number)
{
    int rc = OK, ans = 0;
    for (size_t i = 0; i < a_n; i++)
    {
        for (size_t j = 0; j < i; j++)
        {
            if (matrix[i][j] % 2 && (ans == 0 || ans > matrix[i][j]))
                ans = matrix[i][j];
        }
    }
    if (ans == 0)
        rc = ERR_NO_ODD_NUMBER;
    else 
        *number = ans;

    return rc;
}
