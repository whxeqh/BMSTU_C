#ifndef __MTR_IO_H__
#define __MTR_IO_H__

#include <stddef.h>
#include <stdio.h>

#include "mtr_io.h"
#include "mtr_alloc.h"
#include "errors.h"

/**
 * @brief Чтение матрицы из файла
 * 
 * @param file Файл для чтения
 * @param matrix Матрица, в которую будут записаны данные из файла
 * @param rows Количесто строк 
 * @param columns Количество столбцов
 * 
 * @return Код ошибки
 */
int mtr_read(FILE *file, double **matrix, const size_t rows, const size_t columns);


/**
 * @brief Выделение памяти под матрицу и её заполнение из файла  
 * 
 * @param matrix Матрица, которая будет заполнена данными из файла и под которую будет выделена память 
 * @param rows Количесто строк
 * @param columns Количество столбцов
 * @param file Файл для чтения
 * 
 * @return Код ошибки
 */
int mtr_create(double ***matrix, size_t *rows, size_t *columns, FILE *file);


/**
 * @brief Открытие файла, и вызов функции mtr_create()  
 * 
 * @param matrix Матрица, которая будет заполнена данными из файла и под которую будет выделена память 
 * @param rows Количесто строк
 * @param columns Количество столбцов
 * @param filename Название файла
 * 
 * @return Код ошибки
 */
int mtr_create_ex(double ***matrix, size_t *rows, size_t *columns, const char *filename);


/**
 * @brief Вывод матрицы в файл
 * 
 * @param file Файл для вывода
 * @param matrix Исходная матрица
 * @param rows Количество строк
 * @param columns Количество столбцов
 * 
 * @return Код ошибки
 */
int mtr_print(FILE *file, double **matrix, const size_t rows, const size_t columns);

/**
 * @brief Открытие файла для вывода и дальнейший вызов функции mtr_print()
 * 
 * @param filename Название файла для вывода
 * @param matrix Исходная матрица
 * @param rows Количество строк
 * @param columns Количество столбцов
 * 
 * @return Код ошибки
 */
int mtr_print_ex(const char *filename, double **matrix, const size_t rows, const size_t columns);

#endif //__MTR_IO_H__
