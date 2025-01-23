#ifndef __MTR_OP_H__
#define __MTR_OP_H__

#include <stddef.h>

/**
 * @brief Выполнение сложения матриц
 * 
 * @param mtr_1 Первая матрица
 * @param rows_1 Кол-во строк в первой матрице
 * @param columns_1 Кол-во столбцов в первой матрице
 * 
 * @param mtr_2 Вторая матрица
 * @param rows_2 Кол-во строк во второй матрице
 * @param columns_2 Кол-во столбцов во второй матрице
 * 
 * @param mtr_res Результирующая матрица
 * @param rows_res Количество строк в результрующей матрице
 * @param columns_res Количество столбцов в результирующей матрице
 * 
 * @return Код ошибки
*/
int matrix_sum(double **mtr_1, size_t rows_1, size_t columns_1, \
double **mtr_2, size_t rows_2, size_t columns_2, \
double ***mtr_res, size_t *rows_res, size_t *columns_res);


/**
 * @brief Выполнение умножения матриц
 * 
 * @param mtr_1 Первая матрица
 * @param rows_1 Кол-во строк в первой матрице
 * @param columns_1 Кол-во столбцов в первой матрице
 * 
 * @param mtr_2 Вторая матрица
 * @param rows_2 Кол-во строк во второй матрице
 * @param columns_2 Кол-во столбцов во второй матрице
 * 
 * @param mtr_res Результирующая матрица
 * @param rows_res Количество строк в результрующей матрице
 * @param columns_res Количество столбцов в результирующей матрице
 * 
 * @return Код ошибки
*/
int matrix_mul(double **mtr_1, size_t rows_1, size_t columns_1, \
double **mtr_2, size_t rows_2, size_t columns_2, \
double ***mtr_res, size_t *rows_res, size_t *columns_res);


/**
 * @brief Нахождение обратной матрицы методом Гаусса
 * 
 * @param mtr_src исходная матрица
 * @param rows_src Кол-во строк в исходной матрице
 * @param columns_src Кол-во столбцов в исходной матрице
 * 
 * @param mtr_res Результирующая матрица
 * @param rows_res Количество строк в результрующей матрице
 * @param columns_res Количество столбцов в результирующей матрице
 * 
 * @return Код ошибки
*/
int matrix_inverse(double **mtr_src, size_t rows_src, size_t columns_src, \
double ***mtr_res, size_t *rows_res, size_t *columns_res);

#endif //__MTR_H__
