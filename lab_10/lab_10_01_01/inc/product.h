#ifndef __PRODUCT_H__
#define __PRODUCT_H__

#include <stdio.h>

#include "product.h"

/**
 * @brief Структура для хранения данных о продукте
 * @param name Название продукта
 * @param price Цена продукта
 */
typedef struct products
{
    char *name;
    int price;
} product_t;

/**
 * @brief Инициализирует структуру продукта
 * @param[out] pelem Указатель на структуру продукта
 * @param[in] name Название продукта
 * @param[in] price Цена продукта
 * @return Код ошибки
 */
int product_init(product_t *pelem, char *name, int price);

/**
 * @brief Глубоко копирует содержимое одной структуры продукта в другую
 * @param[out] pdst Указатель на структуру, в которую производится копирование
 * @param[in] psrc Указатель на структуру, из которой производится копирование
 * @return Код ошибки
 */
int product_copy(product_t *pdst, product_t *psrc);

/**
 * @brief Считывает данные о продукте из файла
 * @param[in] file Указатель на открытый файл для чтения
 * @param[out] pelem Указатель на структуру продукта
 * @return Код ошибки
 */
int product_read(FILE *file, product_t *pelem);

/**
 * @brief Освобождает память, выделенную под содержимое структуры продукта
 * @param[out] pelem Указатель на структуру продукта
 */
void product_free_content(product_t *pelem);

/**
 * @brief Выводит данные о продукте в файл или поток вывода
 * @param[in] file Указатель на открытый файл для записи
 * @param[in] elem Указатель на структуру продукта
 * @return Код ошибки
 */
int product_print(FILE *file, const product_t *elem);

/**
 * @brief Сравнивает два продукта по имени в лексикографическом порядке
 * @param[in] pleft Указатель на первый продукт
 * @param[in] pright Указатель на второй продукт
 * @return Результат сравнения
 */
int cmp_products_by_name(const void *pleft, const void *pright);

/**
 * @brief Сравнивает два продукта по цене
 * @param[in] pleft Указатель на первый продукт
 * @param[in] pright Указатель на второй продукт
 * @return Результат сравнения
 */
int cmp_products_by_price(const void *pleft, const void *pright);

#endif // __PRODUCT_H__
