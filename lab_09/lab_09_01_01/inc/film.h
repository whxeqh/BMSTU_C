#ifndef FILM_H
#define FILM_H

#include <stdio.h>
#include "errors.h"

typedef struct
{
    char *title;
    char *name;
    int year;
} film_t;

/**
 * @brief Записывает данные о фильме в `pfilm`. Вся динамически выделенная до входа в функцию память в `pfilm` будет освобождена,
 * @param[out] pfilm Структура для заполнения данными
 * @param[in] title Название фильма
 * @param[in] name Режиссёр
 * @return Код ошибки
 *         OK - Запись прошла успешно
 *         ERR_MEMORY - Ошибка выделения памяти. Данные в pfilm не изменятся
*/
int film_init(film_t *pfilm, char *title, char *name, int year);

int film_copy(film_t *dst, film_t *src);

/**
 * @brief Освобождение памяти из-под динамически выделенных частей структуры 
 * @param[out] pfilm Указатель на структуру
 * @return Код ошибки
*/
void film_free_content(film_t *pfilm);

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
int film_print(FILE *file, const film_t *pfilm);


/**
 * @brief Лексикографически сравнивает два фильма по названию.
 * @param[in] first  Первый фильм
 * @param[in] second Второй фильм
 * @return > 0, если название первого фильма больше
 *         < 0, если название второго фильма больше
 *           0, если названия совпадают
*/
int film_cmp_by_name(const film_t *first, const film_t *second);


/**
 * @brief Лексикографически сравнивает два фильма по режиссеру.
 * @param[in] first  Первый фильм
 * @param[in] second Второй фильм
 * @return > 0, если название первого фильма больше
 *         < 0, если название второго фильма больше
 *           0, если названия совпадают
*/
int film_cmp_by_year(const film_t *first, const film_t *second);

/**
 * @brief Лексикографически сравнивает два фильма по году.
 * @param[in] first  Первый фильм
 * @param[in] second Второй фильм
 * @return > 0, если год первого фильма больше
 *         < 0, если год второго фильма больше
 *           0, если названия совпадают
*/
int film_cmp_by_title(const film_t *first, const film_t *second);

#endif
