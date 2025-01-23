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
 * @brief Филтер.  
 * @param pb_src[in] Указатель на начало массива
 * @param pe_src[in] Указатель на конец массива
 * @param pb_dst[out] Указатель на начало нового массива
 * @param pe_dst[out] Указатель на конец нового массива
 * @return Код ошибки
*/
int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);

/**
 * @brief Создает и заполняет массив из файла
 * @param pbeg[out] Указатель на указатель на начало массива 
 * @param pend[out] Указатель на указатель на конец массива 
 * @param file_in[in] Файловая переменная
 * @return Код ошибки
*/
int create_array(int **pbeg, int **pend, FILE *file_in);

/**
 * @brief Открывает файл и вызывает функцию создания и заполнения массива из файла
 * @param pbeg[out] Указатель на указатель на начало массива 
 * @param pend[out] Указатель на указатель на конец массива 
 * @param file_name[in] Название файла
 * @return Код ошибки
*/
int create_array_ex(int **pbeg, int **pend, const char *file_name);

/**
 * @brief Открывает файл и вызывает функцию печати массива в файл
 * @param pbeg[out] Указатель на указатель на начало массива 
 * @param pend[out] Указатель на указатель на конец массива 
 * @param file_name[in] Название файла
 * @return Код ошибки
*/
int print_array_int_ex(const int *pbeg, const int *pend, const char *file_name);

/**
 * @brief Печатает массив в файл
 * @param pbeg[out] Указатель на указатель на начало массива 
 * @param pend[out] Указатель на указатель на конец массива 
 * @param file_in[in] Файловая переменная
 * @return Код ошибки
*/
int print_array_int(const int *pbeg, const int *pend, FILE *file_out);

/**
 * @brief Очистка памяти из под динамического массива
 * @param arr[out] Указатель на выделенную память 
 */
void free_array(int *arr);

#endif //__ARRAY_H__
