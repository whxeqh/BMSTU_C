#ifndef __PRODUCTS_ARRAY_H__
#define __PRODUCTS_ARRAY_H__

#include <stdio.h>
#include <stddef.h>

#include "product.h"

/**
 * @brief Открывает файл и вызывает функцию для создания массива продуктов
 * @param[in] filename Название файла для чтения
 * @param[out] arr Указатель на массив структур продуктов
 * @param[out] length Указатель на длину массива (количество продуктов)
 * @return Код ошибки
 */
int products_create_ex(char *filename, product_t **arr, size_t *length);

/**
 * @brief Выделяет память под массив продуктов и считывает их из файла
 * @param[in] file Указатель на открытый файл для чтения
 * @param[out] arr Указатель на массив структур продуктов
 * @param[out] length Указатель на длину массива (количество продуктов)
 * @return Код ошибки
 */
int products_create(FILE *file, product_t **arr, size_t *length);

/**
 * @brief Открывает файл и вызывает функцию для чтения массива продуктов
 * @param[in] filename Название файла для чтения
 * @param[out] arr Массив структур продуктов
 * @param[out] length Указатель на длину массива (количество продуктов)
 * @return Код ошибки
 */
int products_read_ex(char *filename, product_t *arr, size_t *length);

/**
 * @brief Считывает продукты из открытого файла в массив
 * @param[in] file Указатель на открытый файл для чтения
 * @param[out] arr Массив структур продуктов
 * @param[in] length Длина массива (количество продуктов)
 * @return Код ошибки
 */
int products_read(FILE *file, product_t *arr, const size_t length);

/**
 * @brief Освобождает память, выделенную под массив продуктов
 * @param[out] arr Указатель на массив структур продуктов
 * @param[out] length Указатель на длину массива (количество продуктов)
 */
void free_products(product_t **arr, size_t *length);

#endif // __PRODUCTS_ARRAY_H__
