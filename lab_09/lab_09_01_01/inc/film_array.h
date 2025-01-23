#ifndef FILM_ARRAY_H
#define FILM_ARRAY_H

#include <stdio.h>
#include <stdbool.h>

#define _POSIX_C_SOURCE 200809L

#include "film.h"
#include "errors.h"


//Тип для указателя на функцию сравнения фильмов по возрастанию
typedef int (*comparator_t)(const film_t *first, const film_t *second);

/**
 * @brief Открывает файл, затем вызывает функцию films_create
 * @param[in] filename Название файла для чтения
 * @param[out] films Массив структур фильма
 * @param[out] length Длина массива (кол-во фильмов)
 * @return Код ошибки
*/
int films_create_ex(const char *filename, film_t **films, size_t *length, const comparator_t cmp);

/**
 * @brief Выделение память под массив фмльмов и запись фильмов в массив структур 
 * @param[in] file Открытый для чтения файл
 * @param[out] films Массив структур фильма
 * @param[out] length Длина массива (кол-во фильмов)
 * @return 
*/
int films_create(FILE *file, film_t **films, size_t *length, const comparator_t cmp);

/**
 * @brief Очистка памяти из-под массива структур фильма
 * @param[out] films Массив структур фильма
 * @param[out] length Длина массива (кол-во фильмов)
*/
void films_free(film_t *films, const size_t length);

/**
 * @brief Подсчёт фильмов в файле
 * @param file Открытый на чтение файл
 * @param length Кол-во фильмов в файле
 * @return Код ошибки
*/
int films_count(FILE *file_in, size_t *length);

/**
 * @brief Считывает фильмы из файла и добавляет их в массив в упорядоченном порядке
 * @param[in] file Открытый на чтение файл
 * @param[out] films Массив фильмов
 * @param[out] length Количество фильмов в файле
 * @param[in] cmp Указатель на функцию сравнения фильмов
 * @return Код ошибки
 */
int films_array_read(FILE *file, film_t *films, const size_t length, const comparator_t cmp);

/**
 * @brief Вывод фильмов в открытый на запись файл или поток вывода
 * @param[in] file Открытый на запись файл
 * @param[in] films Массив фильмов
 * @param[in] length Количество элементов в массиве
 * @return Кот:) ошибки  
*/
int films_array_print(FILE *file, const film_t *films, const size_t length);


/**
 * @brief Выполняет бинарный поиск по ключу и функции компаратору
 * 
 * @param[out] pos Позиция найденного по ключу элемента в массиве структур
 * @param[in] films Массив фильмов
 * @param[in] length Количество элементов в массиве фильмов
 * @param[in] key Указатель на фильм с ключем, который нужно найти
 * @param[in] cmp Указатель на функцию сравнения фильмов
 * @return true, если фильм найден
 *         false в ином случае
 */

bool binary_search(size_t *pos, film_t *films, const size_t length, const film_t *pkey, const comparator_t cmp);

#endif
