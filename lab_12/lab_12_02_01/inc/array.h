#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <stddef.h>

#define FILTER_SUCCESS 0
#define FILTER_NEW_DST_LENGTH 1

/**
 * @brief Циклический сдвиг влево на k позиций
 * @param arr Массив, в котором будет происходить сдвиг
 * @param k Количество смещений 
*/
void cyclic_shift(int *arr, const size_t len, const size_t k);

/**
 * @brief 
 * 
 * При первом запуске (dst_len == 0), сначала определится кол-во подходящих под условие элементов и вернется 1
 * При втором запуске (dst_len != 0) в массив dst будут записаны только полные квадраты из массива src
 * 
 * @param src Исходный массив
 * @param src_len Кол-во элементов в исходном массиве
 * @param dst Результирующий массив
 * @param dst_len Количество элементов в результирующем массива
*/
int filter(const int *src, size_t src_len, int *dst, size_t *dst_len);

#endif //__ARRAY_H__
