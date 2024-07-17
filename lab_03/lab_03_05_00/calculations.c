#include "calculations.h"

/**
 * @brief Функция проверки числа на простоту
 * @param[in] x Целое число
 * @return true, если число простое, false, если составное 
*/
bool is_simple(const int x)
{
    if (x < 2)
        return false;
    for (int i = 2; i * i <= x; i++)
        if (x % i == 0)
            return false;

    return true;
}

/** 
 * @brief Функция обмены значений двух переменных
 * @param[out] a Указатель на целое
 * @param[out] b Указатель на целое
*/
void swap_elements(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @brief Функция разворота одномерного массива
 * @param[in] arr_size Размерность массива
 * @param[out] arr Указатель на первый элемент массива
*/
void reverse_array(const size_t arr_size, int *arr)
{
    for (size_t i = 0; i < arr_size / 2; i++)
        swap_elements(&arr[i], &arr[arr_size - i - 1]);
}

/**
 * @brief Функция заполнения одномерного массива простыми числами из матрицы.
 * 
 * @param[in] a_n Количество строк
 * @param[in] a_m Количество столбцов
 * @param[in] matrix Указатель на первый элемент матрицы
 * @param[out] arr Указатель на первый элемент массива
 *  
 * @return Длина заполненного массива
*/
size_t fill_array(const size_t a_n, const size_t a_m, int (*matrix)[M], int *arr)
{
    size_t arr_size = 0;
    for (size_t i = 0; i < a_n; i++)
        for (size_t j = 0; j < a_m; j++)
            if (is_simple(matrix[i][j]))
            {
                arr[arr_size] = matrix[i][j];
                arr_size++;
            }
    return arr_size;
}

/**
 * @brief Функция заполнения матрицы простыми числами из массива 
 * 
 * @param[in] a_n Количество строк
 * @param[in] a_m Количество столбцов
 * @param[out] matrix Указатель на первый элемент матрицы
 * @param[in] arr_size Размерность массива
 * @param[in] arr Указатель на первый элемент массива
*/
void fill_matrix(const size_t a_n, const size_t a_m, int (*matrix)[M], const size_t arr_size, const int *arr)
{
    size_t cnt = 0;
    for (size_t i = 0; i < a_n; i++)
        for (size_t j = 0; j < a_m; j++)
            if (cnt < arr_size && is_simple(matrix[i][j]))
            {
                matrix[i][j] = arr[cnt];
                cnt++;
            }
}
