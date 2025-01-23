#ifndef FILM_ARRAY_H
#define FILM_ARRAY_H

#include <stdio.h>
#include <stdbool.h>
#include "film.h"
#include "errors.h"

#define MAX_LENGTH 15

//Тип для указателя на функцию сравнения фильмов по возрастанию
typedef int (*comparator_t)(const film_t *first, const film_t *second);


/**
 * @brief Считывает фильмы из файла и добавляет их в массив в упорядоченном порядке
 * @param[in] file Указатель на файл с данными.
 * @param[out] films Массив фильмов
 * @param[out] length Кколичество считанных фильмов
 * @param[in] length_max Максимальная длина массива
 * @param[in] cmp Указатель на функцию сравнения фильмов
 * @return Код ошибки
 */
int films_array_read(FILE *file, film_t *films, size_t *length, const size_t length_max, const comparator_t cmp);


/**
 * @brief Вывод фильмов в открытый на запись файл или поток вывода
 * @param[in] file Открытый файл
 * @param[in] films Массив фильмов
 * @param[in] length Количество элементов в массиве
*/
void films_array_print(FILE *file, const film_t *films, const size_t length);


/**
 * @brief Выполняет бинарный поиск по ключу и функции компаратору
 * 
 * @param[out] pos Позиция найденного по ключу элемента в массиве структур
 * @param[in] films Массив фильмов
 * @param[in] length Количество элементов в массиве фильмов
 * @param[in] key Указатель на фильм с ключем, который нужно найти
 * @param[in] cmp Указатель на функцию сравнения фильмов
 * @return true, если фильм найден и выведен, иначе false
 */

bool binary_search(size_t *pos, film_t *films, const size_t length, const film_t *pkey, const comparator_t cmp);

#endif
