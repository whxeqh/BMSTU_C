#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <stdio.h>
#include <stddef.h>

typedef int (*cmp_t)(const void *left, const void *right);

/**
 * @brief Универсальная функция сравнения двух целых чисел
 * @param left[in] Указатель на первый элемент 
 * @param right[in] Указатель на второй элемент
 * @return -1, если left < right
 *          0, если left == right
 *          1, есле left > right
*/
int cmp_uni_int(const void *left, const void *right);


/** @brief Ищет позицию, в которую нужно вставить элемент key
 * @param pbeg[in] Указатель на начало массива
 * @param pend[in] Указатель на конец массива (за последним элементом)
 * @param key[in] Указатель на элемент для сравнения
 * @param el_size[in] Размер типа данных
 * @param uni_cmp[in] Компаратор
 * @return Указатель на элемент для вставки
*/
void *bynary_search(const void *pbeg, const void *pend, const void *key, const size_t el_size, const cmp_t uni_cmp);

/**
 * @brief Сортировка бинарными вставками
 * @param pbeg[in] Указатель на начало массива
 * @param length[in] Количество элементов в массиве
 * @param el_size[in] Размер элементов в массиве
 * @param uni_cmp[in] Компаратор
*/
void mysort(void *pbeg, const size_t length, const size_t el_size, const cmp_t uni_cmp);

/** 
 * @brief Находит количество элементов, которые останутся после фильтрации массива
 * @param pb_src Указатель на начало массива
 * @param pe_src Указатель на за последний элемент массива
 * @return 
*/
int filter_arr_size(const int *pb_src, const int *pe_src);

/**
 * @brief Фильтр.  
 * @param pb_src[in] Указатель на начало массива
 * @param pe_src[in] Указатель на конец массива
 * @param pb_dst[out] Указатель на начало нового массива
 * @param pe_dst[out] Указатель на конец нового массива
 * @return Код ошибки
*/
int key(const int *pb_src, const int *pe_src, int *pb_dst, int **pe_dst);

void destroy_array(int **arr);

#endif //__ARRAY_H__
