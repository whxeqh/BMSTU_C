#ifndef __MEASUREMENT_FUNCTIONS_H__
#define __MEASUREMENT_FUNCTIONS_H__

#define _POSIX_C_SOURCE 199309L 

#include <stddef.h>
#include <stdlib.h>
#include <time.h>

// Функция подсчитывает время между двумя моментами (начало и конец замера) в микросекундах
unsigned long long calc_elapsed_time(const struct timespec *beg, const struct timespec *end);

/**
 * @brief Функция заполняет массив случайными числами 
 * @param length Длина массива
 * @param arr Массив для заполнения
*/
void init_random(const size_t length, int *arr);

/**
 * @brief Функция заполняет массив отсортированном числами 
 * @param length Длина массива
 * @param arr Массив для заполнения
*/
void init_sorted(const size_t length, int *arr);

/**
 * @brief Функция заполняет массив в обратном порядке 
 * @param length Длина массива
 * @param arr Массив для заполнения
*/
void init_reversed(const size_t length, int *arr);

/**
 * @brief Функция присивает элемены массива src_arr элементам массива arr 
 * @param length Длина массивов
 * @param arr Массив для присваения
 * @param src_arr Исходный массив 
*/
void appropriate(const size_t length, int *arr, const int *src_arr);

#endif // __MEASUREMENT_FUNCTIONS__
