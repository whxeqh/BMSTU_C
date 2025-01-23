#ifndef __ARR_IO_H__
#define __ARR_IO_H__

#include <stddef.h>

/**
 * @brief Чтение массива из консоли
 *  
 * @param[out] arr    Указатель на первый элемент массива
 * @param[in] length  Количество элементов в массиве
 * 
 * @return Код ошибки.
 */
int arr_read(int *arr, const size_t length);

/**
 * @brief Вывод массива в консоль
 * 
 * @param[in] arr     Указатель на первый элемент массива
 * @param[in] length  Количество элементов в массиве
 */
void arr_print(const int *arr, const size_t length);

/**
 * @brief Создание массива (чтение размерности, выделение памяти, чтение элементов массива).
 * 
 * @param[out] arr      Указатель на массив, в котором будут храниться элементы
 * @param[out] length   Количество элементов в массиве
 * 
 * @return Код ошибки.
 */
int arr_create(int **arr, size_t *length);


#endif //__ARR_IO_H__
