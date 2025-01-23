#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "mtr_op.h"
#include "errors.h"
#include "mtr_alloc.h"
#include "mtr_io.h"

#define EPS 1e-8

int matrix_sum(double **mtr_1, size_t rows_1, size_t columns_1, \
double **mtr_2, size_t rows_2, size_t columns_2, \
double ***mtr_res, size_t *rows_res, size_t *columns_res)
{
    assert(mtr_1);
    assert(mtr_2);

    double **tmp_mtr_res;

    if (rows_1 != rows_2 || columns_1 != columns_2 || rows_1 == 0 || columns_1 == 0)
        return  ERR_RANGE;

    tmp_mtr_res = mtr_alloc(rows_1, columns_2);
    if (!tmp_mtr_res)
        return ERR_MEMORY;

    for (size_t i = 0; i < rows_1; i++)
        for (size_t j = 0; j < columns_2; j++)
            tmp_mtr_res[i][j] = mtr_1[i][j] + mtr_2[i][j];
    
    *mtr_res = tmp_mtr_res;
    *rows_res = rows_1;
    *columns_res = columns_2;

    return OK;
}

int matrix_mul(double **mtr_1, size_t rows_1, size_t columns_1, \
double **mtr_2, size_t rows_2, size_t columns_2, \
double ***mtr_res, size_t *rows_res, size_t *columns_res)
{
    assert(mtr_1);
    assert(mtr_2);

    double **tmp_mtr_res;

    if (columns_1 != rows_2 || columns_1 == 0 || rows_2 == 0)
        return ERR_RANGE;

    tmp_mtr_res = mtr_alloc(rows_1, columns_2);
    if (!tmp_mtr_res)
        return ERR_MEMORY;

    for (size_t i = 0; i < rows_1; i++)
        for (size_t j = 0; j < columns_2; j++)
        {
            double sum = 0.0;
            for (size_t k = 0; k < columns_1; k++)
                sum += mtr_1[i][k] * mtr_2[k][j];

            tmp_mtr_res[i][j] = sum;
        }

    *mtr_res = tmp_mtr_res;
    *rows_res = rows_1;
    *columns_res = columns_2;
    return OK;
}

/**
 * @brief Обмен двух указателей на строки матрицы
 * @param left Указатель на первую строку
 * @param right Указатель на вторую строку
*/
static void swap_double_pointers(double **left, double **right)
{
    double *tmp = *left;
    *left = *right;
    *right = tmp;
}

/**
 * @brief Делит все элементы строки на делитель (divider)
 * @param row указатель на первый элемент массива строк
 * @param divider делитель
 * @param length длина строки
*/
static void divide_row(double *row, size_t length, double divider)
{
    assert(row);

    for (size_t i = 0; i < length; i++)
        row[i] /= divider;
}


/**
 * @brief Вычитает из каждого элемента строки rows_left соответствующий ему элемент строки rows_right, умноженный на factor
 * @param row_left Строка "уменьшаемое"
 * @param rows_right Строка "вычитаемое"
 * @param columns Количество столбцов (элементов в строке)
 * @param factor Коэфицент
*/
static void subtract_rows(double *row_left, const double *rows_right, const size_t columns, const double factor)
{
    assert(row_left);
    assert(rows_right);

    for (size_t i = 0; i < columns; i++)
        row_left[i] -= rows_right[i] * factor;
}

/**
 * @brief Находит строку в матрице, у которой ненулевой элемент на главной диагонали
 * 
 * @param row[out] Номер строки
 *  
 * @param mtr Исходная матрица
 * @param rows Количество строк
 * @param columns Количество столбцов
 * 
 * @return true: такая строка есть
 *         false: такой строки нет
*/
static bool find_nonzero_row(size_t *nonzero_row, double **mtr, size_t rows, size_t cur_row)
{
    assert(mtr);
    assert(cur_row <= rows);

    bool find = false;

    for (size_t i = cur_row; i < rows; i++)
    {
        if (!find && fabs(mtr[i][cur_row]) >= EPS)
        {
            *nonzero_row = i;
            find = true;
        }
        else if (find && fabs(mtr[i][cur_row]) >= fabs(mtr[*nonzero_row][cur_row]) && fabs(mtr[i][cur_row]) >= EPS)
            *nonzero_row = i;
    }

    return find;
}

/**
 * @brief Нормализация текущей строки (чтобы диагональный элемент стал равен единице)
 * 
 * @param mtr Исходная матрица
 * @param augmented_mtr Дополнительная матрица (единичная)
 * @param rows Количество строк
 * @param columns Количество столбцов
 * @param cur_row Текущая строка
 * 
 * @return Код ошибки
 */
static int normalize_row(double **mtr, double **augmented_mtr, size_t rows, size_t columns, size_t cur_row)
{
    assert(mtr);
    assert(augmented_mtr);

    size_t row_to_swap;

    //Определяю, есть ли строка с ненулевым элементом с текущем столбце 
    bool found_nonzero = find_nonzero_row(&row_to_swap, mtr, rows, cur_row);

    //Если такой строки нет - матрица вырожденная
    if (!found_nonzero)
        return ERR_NO_INVERSE;

    //Если такая строка нашлась и эта не исходная строка - меняю местами исходную стркоу с найденной
    if (row_to_swap != cur_row)
    {
        swap_double_pointers(&mtr[cur_row], &mtr[row_to_swap]);
        swap_double_pointers(&augmented_mtr[cur_row], &augmented_mtr[row_to_swap]);
    }

    //Делю всю строку на диагональный элемент, чтобы получить единицу
    double diagonal_element = mtr[cur_row][cur_row];
    divide_row(mtr[cur_row], columns, diagonal_element);
    divide_row(augmented_mtr[cur_row], columns, diagonal_element);

    return OK;
}

/**
 * @brief Обнуление столбцов выше и ниже текущего
 * 
 * Вычитаю все строки матрицы со строкой с индексом `cur_row`, чтобы обнулить элементы в столбцах 
 * 
 * @param mtr Исходная матрица
 * @param augmented_mtr Дополнительная матрица (единичная)
 * @param rows Количество строк
 * @param columns Количество столбцов
 * @param cur_row Текущая строка
 * @return Код ошибки
 */
static void reduce_column_to_diagonal(double **mtr, double **augmented_mtr, size_t rows, size_t columns, size_t cur_row)
{
    assert(mtr);
    assert(augmented_mtr);

    for (size_t i = 0; i < rows; i++)
    {
        if (i != cur_row)
        {
            //Коэфицент домножения - элемент столбца строки (не знаю, как написать:( )
            double factor = mtr[i][cur_row];
            
            //Вычитаю строки исходной, умноженные на коэффицент, чтобы обнулить текущий столбец в неё 
            subtract_rows(mtr[i], mtr[cur_row], columns, factor);

            //Также вычитаю строки в присоединённой матрицы, умноженные на ранее найденный коэфицент
            subtract_rows(augmented_mtr[i], augmented_mtr[cur_row], columns, factor);
        }
    }
}

int matrix_inverse(double **mtr, size_t rows, size_t columns, double ***mtr_res, size_t *rows_res, size_t *columns_res)
{
    assert(mtr);

    int rc = OK;
    double **augmented_mtr = NULL;

    //Если матрица не квадратная или кол-во столбцов(строк) = 0, то невозможно найти обратную матрицу
    if (rows != columns || rows == 0 || columns == 0)
        return ERR_NO_INVERSE;

    //Выделяю память под матрицу rows*columns и заполняю её нулями на главной диагонали
    augmented_mtr = make_identity_matrix(rows, columns);
    if (!augmented_mtr)
        return ERR_MEMORY;

    //Прохожусь по строкам матрицы 
    for (size_t i = 0; i < rows && rc == OK; i++)
    {        
        //Нормализую каждую строку
        rc = normalize_row(mtr, augmented_mtr, rows, columns, i);

        //Обнуляю столбцы исходной матрицы выше и ниже текущего, путем складывания строк
        if (rc == OK)
            reduce_column_to_diagonal(mtr, augmented_mtr, rows, columns, i);
    }

    if (rc == OK)
    {
        *rows_res = rows;
        *columns_res = columns;
        *mtr_res = augmented_mtr;
    }
    else
        mtr_free(augmented_mtr, rows);

    return rc;
}
