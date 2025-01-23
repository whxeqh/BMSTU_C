#ifndef FILM_H
#define FILM_H

#include <stdio.h>
#include "errors.h"

#define MAX_TITLE_LEN 25
#define MAX_NAME_LEN  25

typedef struct
{
    char title[MAX_TITLE_LEN + 1];
    char name[MAX_NAME_LEN + 1];
    int year;
} film_t;


/**
 * @brief Считывает информацию о фильме из файла
 * @param[in] file открытый на чтение файл
 * @param[out] pfilm Указатель на структуру фильма
 * @return Код ошибки
 */
int film_read(FILE *file, film_t *pfilm);


/**
 * @brief Считывает информацию о фильме из файла
 * @param[in] file открытый на чтение файл
 * @param[out] pfilm Указатель на структуру фильма
 * @return Код ошибки
 */
void film_print(FILE *file, const film_t *pfilm);


/**
 * @brief Лексикографически сравнивает два фильма по названию.
 * @param[in] first  Первый фильм
 * @param[in] second Второй фильм
 * @return > 0, если название первого фильма больше
 *         < 0, если название второго фильма больше
 *           0, если названия совпадают
*/
int compare_film_by_title(const film_t *first, const film_t *second);


/**
 * @brief Лексикографически сравнивает два фильма по режиссеру.
 * @param[in] first  Первый фильм
 * @param[in] second Второй фильм
 * @return > 0, если название первого фильма больше
 *         < 0, если название второго фильма больше
 *           0, если названия совпадают
*/
int compare_film_by_name(const film_t *first, const film_t *second);

/**
 * @brief Лексикографически сравнивает два фильма по году.
 * @param[in] first  Первый фильм
 * @param[in] second Второй фильм
 * @return > 0, если год первого фильма больше
 *         < 0, если год второго фильма больше
 *           0, если названия совпадают
*/
int compare_film_by_year(const film_t *first, const film_t *second);

#endif
