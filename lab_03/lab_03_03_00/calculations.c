#include "calculations.h"

/**
 * @brief Функция для подсчёта суммы элементов в массиве 
 *
 * @param[in] a_m Размерность массива
 * @param[in] a Указатель на первый элемент массива
 * 
 * @return Сумма элементов массива
*/
int summ_array(const size_t a_m, const int *a)
{
    int ans = 0;
    for (size_t i = 0; i < a_m; i++)
        ans += a[i];
    return ans;
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
 * @brief Функция обмена двух строк (одномерных массивов) матрицы 
 * 
 * @param[out] arr_first Указатель на первый элемент массиа 
 * @param[out] arr_second Указатель на первый элемент массива
 * 
 * @param a_m Размерность этих массивов
*/
void swap_arrays(int *arr_first, int *arr_second, const size_t a_m)
{
    for (size_t i = 0; i < a_m; i++)
        swap_elements(&arr_first[i], &arr_second[i]);
}

//Функция формирует массив keys, каждый элемент которого это сумма элементов соответствующей строки
void form_key_array(const size_t a_n, const size_t a_m, int (*matrix)[M], int *keys)
{
    for (size_t i = 0; i < a_n; i++)
        keys[i] = summ_array(a_m, matrix[i]);
}

/**
 * @brief Функция сортировки матрицы пузырьком по возрастанию суммы элементов в её строках (одномерных массивов)
 * 
 * @param a_n[in] Количество строк
 * @param a_m[in] Количество столбцов
 * @param[out] matrix[out] Указатель на её первый элемент
 * @param[out] keys - массив со згначениями суммы элементов соответствующей строки
*/
void sort(const size_t a_n, const size_t a_m, int (*matrix)[M], int *keys)
{
    for (size_t i = 0; i < a_n; i++)
        for (size_t j = i + 1; j < a_n; j++)
            if (keys[i] > keys[j])
            {
                swap_elements(&keys[i], &keys[j]);       //меняем местами суммы по строкам
                swap_arrays(matrix[i], matrix[j], a_m);  //меняем местами строки 
            }
}
