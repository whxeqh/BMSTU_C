#ifndef __ARR_ALLOC_H__
#define __ARR_ALLOC_H__

#include <stddef.h>

/**
 * @brief Освобождение памяти из-под массива
 * 
 * @param arr[in] Указатель на первый элемент массива 
*/
void arr_free(int *arr);

/**
 * @brief Выделение памяти под массив
 * 
 * @param[in] length  Кол-во элементов в массиве
 * 
 * @return Указатель на выделенную область памяти
*/
int *arr_alloc(size_t length);

/**
 * @brief Перевыделение памяти для массива
 * 
 * @param[out] arr Указатель на массив
 * @param[in] length Кол-во элементов массива
 * 
 * @return Код ошибки
*/
int arr_realloc(int **arr, size_t length);

#endif //__ARR_ALLOC_H__
