#ifndef __PAIR_ARRAY_H__
#define __PAIR_ARRAY_H__

#include <stddef.h>
#include "associative_array.h"

#define DA_INIT_SIZE 1 // Начальный размер массива пар.
#define DA_STEP 2      // Шаг увеличения размера массива.

/**
 * @brief Структура, представляющая пару "ключ-значение".
 */
typedef struct pair
{
    char *key; 
    int value; 
} pair_t;

/**
 * @brief Структура динамически расширяемого массива пар.
 */
typedef struct pair_array
{
    pair_t *data;     // Указатель на массив пар.
    size_t length;    // Количество элементов в массиве.
    size_t allocated; // Выделенный размер массива.
} pair_array_t;

/**
 * @brief Освобождает динамически выделенные ресурсы в паре "ключ-значение".
 * @param[in] elem Указатель на элемент пары.
 */
void pair_free_content(pair_t *elem);

/**
 * @brief Создаёт копию данных для элемента пары.
 * @param[in,out] elem Указатель на элемент пары.
 * @param[in] key Ключ для копирования.
 * @param[in] value Значение для копирования.
 * @return Код ошибки типа.
 */
assoc_array_error_t pair_dup_data(pair_t *elem, const char *key, int value);

/**
 * @brief Создаёт динамический массив пар.
 * @return Указатель на созданный массив пар.
 */
pair_array_t *pair_array_create(void);

/**
 * @brief Инициализирует структуру массива пар.
 * @param[in,out] parr Указатель на массив пар.
 */
void pair_array_init(pair_array_t *parr);

/**
 * @brief Добавляет элемент в конец массива пар.
 * @param[in,out] parr Указатель на массив пар.
 * @param[in] elem Указатель на добавляемую пару.
 * @return Код ошибки типа.
 */
assoc_array_error_t pair_array_push_back(pair_array_t *parr, pair_t *elem);

/**
 * @brief Удаляет элемент массива пар по индексу.
 * @param[in,out] parr Указатель на массив пар.
 * @param[in] index Индекс удаляемого элемента.
 */
void pair_array_delete(pair_array_t *parr, int index);

/**
 * @brief Поиск элемента массива пар по ключу.
 * @param[in] parr Указатель на массив пар.
 * @param[in] key Ключ для поиска.
 * @return Индекс найденного элемента или -1, если элемент не найден.
 */
int pair_array_search(pair_array_t *parr, const char *key);

/**
 * @brief Уничтожает массив пар и освобождает память.
 * @param[in,out] parr Указатель на указатель массива пар.
 */
void pair_array_destroy(pair_array_t **parr);

/**
 * @brief Очищает массив пар, освобождая ресурсы из-под элементов.
 * @param[in,out] parr Указатель на массив пар.
 */
void pair_array_clear(pair_array_t *parr);

/**
 * @brief Применяет функцию к каждому элементу массива пар.
 * @param[in] parr Указатель на массив пар.
 * @param[in] action Функция, применяемая к элементу.
 * @param[in] param Дополнительный параметр для функции.
 */
void pair_array_apply(pair_array_t *parr, void (*action)(const char *key, int *num, void *param), void *param);

/**
 * @brief Поиск элемента массива пар с минимальным значением.
 * @param[in] parr Указатель на массив пар.
 * @return Указатель на элемент с минимальным значением.
 */
pair_t *pair_array_search_min(pair_array_t *parr);

/**
 * @brief Поиск элемента массива пар с максимальным значением.
 * @param[in] parr Указатель на массив пар.
 * @return Указатель на элемент с максимальным значением.
 */
pair_t *pair_array_search_max(pair_array_t *parr);

#endif //__PAIR_ARRAY_H__
