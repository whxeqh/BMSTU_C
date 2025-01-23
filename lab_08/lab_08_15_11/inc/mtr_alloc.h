#ifndef __MTR_ALLOC_H__
#define __MTR_ALLOC_H__

#include <stddef.h>

/**
 * @brief Освобождение памяти из-под матрицы
 * 
 * @param matrix Исходная матрица
 * @param rows Количество строк
*/
void mtr_free(double **matrix, const size_t rows);

/**
 * @brief Выделение памяти под матрицы
 * 
 * @param rows Количество строк
 * @param rows Количество столбцов
 * 
 * @return Указатель на первую строку матрицы
*/
double **mtr_alloc(const size_t rows, const size_t columns);

/**
 * @brief Выделение памяти под матрицу и заполенние её единицами по главной диагонали
 * 
 * @param rows Количество строк
 * @param rows Количество столбцов
 * 
 * @return Указатель на первую строку матрицы
*/
double **make_identity_matrix(const size_t rows, const size_t columns);

#endif //__MTR_ALLOC_H__
