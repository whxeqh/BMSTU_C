#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "errors.h"
#include "mtr_alloc.h"

#define MIN(A, B) ((A) < (B) ? (A) : (B))

//Функции для защиты

//Особождение памяти из-под объединённого подхода с двумя массивами
void mtr_free(double **matrix, const size_t rows)
{
    //assert(rows);

    if (!matrix)
        return;

    double *min_ptr = matrix[0];
    for (size_t i = 1; i < rows; i++)
        min_ptr = MIN(min_ptr, matrix[i]);
    
    free(min_ptr);
    free(matrix);

    matrix = NULL;
}

//Выделение памяти под объединённый подход с двумя массивами
double **mtr_alloc(const size_t rows, const size_t columns)
{
    int rc = OK;
    double **ptrs = malloc(rows * sizeof(double*));

    if (!ptrs)
        return NULL;

    double *data = malloc(rows * columns * sizeof(double));

    if (data)
    {
        for (size_t i = 0; rc == OK && i < rows; ++i)
            ptrs[i] = data + i * columns;
    }
    else
    {
        mtr_free(ptrs, rows);
        ptrs = NULL;
    }
    
    return ptrs;
}

double **make_identity_matrix(const size_t rows, const size_t columns)
{
    assert(rows == columns);
    assert(rows > 0);
    
    double **mtr = mtr_alloc(rows, columns);

    if (!mtr)
        return NULL;
    
    memset(mtr[0], 0, sizeof(double) * rows * columns);


    for (size_t i = 0; i < rows; i++)
        mtr[i][i] = 1.0;

    return mtr;
}

/*
//Освобождение памяти из-под массив указателей на строки
void mtr_free(double **matrix, const size_t rows)
{
    for (size_t i = 0; i < rows; i++)
        free(matrix[i]);
    free(matrix);
}
*/

/*
//Выделение памяти под массив указателей на строки
double **mtr_alloc(const size_t rows, const size_t columns)
{
    int rc = OK;
    double **ptrs = calloc(rows, sizeof(double*));

    if (!ptrs)
        rc = ERR_MEMORY;

    for (size_t i = 0; rc == OK && i < rows; ++i)
    {
        ptrs[i] = malloc(columns * sizeof(double));
        if (!ptrs[i])
            rc = ERR_MEMORY;
    } 

    if (rc != OK)
    {
        mtr_free(ptrs, rows);
        ptrs = NULL;
    }
    
    return ptrs;
}
*/
