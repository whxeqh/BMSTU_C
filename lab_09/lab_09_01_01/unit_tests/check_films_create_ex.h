#ifndef __CHECK_FILMS_CREATE_EX_H__
#define __CHECK_FILMS_CREATE_EX_H__

#include <check.h>
#include <stdbool.h>

#include "film.h"

/**
 * @brief Сравнение фильмов по полям
 * @param pleft Указатель на первый фильм
 * @param pright Указатель на второй фильм
 * @return true, если фильмы одинаковые
 *         true, в ином случае
*/
bool is_films_equal(const film_t *pleft, const film_t *pright);

/**
 * @brief Функция сравнивает два массива структур на равенство
 * @param left_arr Первый массив стуктур
 * @param left_length Длина первого массива структур
 * @param right_arr Второй массив структур
 * @param right_length Длина второго массива структур
 * @return true, если массивы одинаковы
 *         false в ином случае
 */
bool is_films_arrays_equal(const film_t *left_arr, const size_t left_length, \
                     const film_t *right_arr, const size_t right_length);

Suite* test_films_create_ex_suite(void);

#endif //__CHECK_FILMS_CREATE_EX_H__
