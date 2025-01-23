#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdio.h>
#include "node.h"

/**
 * @brief Умножает две матрицы
 * @param[out] mtr_mul Указатель на указатель на результат умножения матриц
 * @param[in] mtr1 Указатель на первую матрицу
 * @param[in] mtr2 Указатель на вторую матрицу
 * @return Код ошибки
 */
int matrix_mul(node_t **mtr_mul, node_t *mtr1, node_t *mtr2);

/**
 * @brief Складывает две матрицы
 * @param[out] mtr_sum Указатель на указатель на результат сложения матриц
 * @param[in] mtr1 Указатель на первую матрицу
 * @param[in] mtr2 Указатель на вторую матрицу
 * @return Код ошибки
 */
int matrix_sum(node_t **mtr_sum, node_t *mtr1, node_t *mtr2);

/**
 * @brief Удаление строки с наибольшым элементом в матрице 
 * @param[in,out] mtr Указатель на указатель на матрицу
 */
void matrix_lin(node_t **mtr);

/**
 * @brief Выводит матрицу в файл или поток вывода
 * @param[in] file Указатель на открытый файл для записи
 * @param[in] mtr Указатель на матрицу
 * @return Код ошибки
 */
int matrix_print(FILE *file, node_t *mtr);

/**
 * @brief Считывает матрицу из файла
 * @param[in] file Указатель на открытый файл для чтения
 * @param[out] mtr Указатель на указатель на матрицу
 * @return Код ошибки
 */
int matrix_read(FILE *file, node_t **mtr);

/**
 * @brief Освобождает память, выделенную под матрицу
 * @param[in,out] mtr Указатель на указатель на матрицу
 */
void matrix_free(node_t **mtr);

#endif // __MATRIX_H__
