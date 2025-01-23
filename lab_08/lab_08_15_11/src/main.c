#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "mtr_io.h"
#include "errors.h"
#include "mtr_op.h"

/**  
 * @brief Возможные действия в программе  
*/
typedef enum
{
    ACT_SUMM,
    ACT_MULTIPLY,
    ACT_INVERSE_MATRIX,
    ACT_UNKNOWN
} action_e;

/**
 * @brief Указатель на функцию бинарной операции, 
 *        Принимает две исходные матрицы и результирующую матрицу
*/
typedef int (*matrix_binary_operation_t)(double **mtr_1, size_t rows_1, size_t columns_1, \
double **mtr_2, size_t rows_2, size_t columns_2, \
double ***mtr_res, size_t *rows_res, size_t *columns_res);

/**
 * @brief Указатель на функцию унарной операции, 
 *        Принимает одну исходную матрицу и результирующую матрицу
*/
typedef int (*matrix_unary_operation_t)(double **mtr, size_t rows, size_t columns, \
double ***mtr_res, size_t *rows_res, size_t *columns_res);

/**
 * @brief Выполнение бинарной операции над матрицами
 * 
 * @param filename_mtr_1 Название файла, в котором содержится первая матрица
 * @param filename_mtr_2 Название файла, в котором содержится вторая матрица
 * @param filename_mtr_res Название файла, в который будет записана результирующая матрица
 * @param operation Указатель на функцию, которая произведет бинарную операцию над матрицами
 * 
 * @return Код ошибки
*/
int matrix_binary_operation(const char *filename_mtr_1, \
const char *filename_mtr_2, \
const char *filename_mtr_res, \
matrix_binary_operation_t operation);

/**
 * @brief Выполнение унарной операции над матрицей
 * 
 * @param filename_mtr Название файла, в котором содержится матрица
 * @param filename_mtr_res Название файла, в который будет записана результирующая матрица
 * @param operation Указатель на функцию, которая произведет бинарную операцию над матрицами
 * 
 * @return Код ошибки
*/
int matrix_unary_operation(const char *filename_mtr, const char *filename_mtr_res, matrix_unary_operation_t operation);

bool check_args(const int argc, const char **argv);
action_e act_read(const char *str);

int main(int argc, const char **argv)
{
    int rc = OK;
    action_e act;

    if (!check_args(argc, argv))
    {
        print_error(ERR_ARGS);
        return ERR_ARGS;
    }

    act = act_read(argv[1]);

    switch (act)
    {
        case ACT_SUMM:
            rc = matrix_binary_operation(argv[2], argv[3], argv[4], matrix_sum);
            break;
        case ACT_MULTIPLY:
            rc = matrix_binary_operation(argv[2], argv[3], argv[4], matrix_mul);
            break;
        case ACT_INVERSE_MATRIX:
            rc = matrix_unary_operation(argv[2], argv[3], matrix_inverse);
            break;
        default:
            rc = ERR_ARGS;
            break;
    }

    if (rc != OK)
        print_error(rc);

    return rc;
}

int matrix_binary_operation(const char *filename_mtr_1, const char *filename_mtr_2, const char *filename_mtr_res, matrix_binary_operation_t operation)
{
    assert(filename_mtr_1);
    assert(filename_mtr_2);
    assert(filename_mtr_res);
    assert(operation);
    
    int rc = OK;
    double **mtr_1 = NULL, **mtr_2 = NULL, **mtr_res = NULL;
    size_t rows_1 = 0, columns_1 = 0, rows_2 = 0, columns_2 = 0, rows_res = 0, columns_res = 0;;

    rc = mtr_create_ex(&mtr_1, &rows_1, &columns_1, filename_mtr_1);
    if (rc != OK)
        goto func_end;
    
    rc = mtr_create_ex(&mtr_2, &rows_2, &columns_2, filename_mtr_2);
    if (rc != OK)
        goto func_end;

    rc = operation(mtr_1, rows_1, columns_1, mtr_2, rows_2, columns_2, &mtr_res, &rows_res, &columns_res);
    if (rc != OK)
        goto func_end;

    rc = mtr_print_ex(filename_mtr_res, mtr_res, rows_res, columns_res);

    func_end:
        mtr_free(mtr_1, rows_1);
    mtr_free(mtr_2, rows_2);
    mtr_free(mtr_res, rows_res);
    mtr_1 = NULL;
    mtr_2 = NULL;
    mtr_res = NULL;

    return rc;
}

int matrix_unary_operation(const char *filename_mtr, const char *filename_mtr_res, matrix_unary_operation_t operation)
{
    assert(filename_mtr);
    assert(filename_mtr_res);
    assert(operation);

    int rc = OK;
    double **mtr = NULL, **mtr_res = NULL;
    size_t rows = 0, columns = 0, rows_res = 0, columns_res = 0;;

    rc = mtr_create_ex(&mtr, &rows, &columns, filename_mtr);
    if (rc != OK)
        goto func_end;

    rc = operation(mtr, rows, columns, &mtr_res, &rows_res, &columns_res);
    if (rc != OK)
        goto func_end;

    rc = mtr_print_ex(filename_mtr_res, mtr_res, rows_res, columns_res);

    func_end:
        mtr_free(mtr, rows);
    mtr_free(mtr_res, rows_res);
    mtr = NULL;
    mtr_res = NULL;

    return rc;
}

action_e act_read(const char *str)
{
    action_e act = ACT_UNKNOWN;

    if (strcmp(str, "a") == 0)
        act = ACT_SUMM;
    else if (strcmp(str, "m") == 0)
        act = ACT_MULTIPLY;
    else if (strcmp(str, "o") == 0)
        act = ACT_INVERSE_MATRIX;
    
    return act;
}

bool check_args(const int argc, const char **argv)
{
    if (argc < 2)
        return false;

    action_e act = act_read(argv[1]);

    if (act == ACT_UNKNOWN)
        return false;
    
    if ((act == ACT_MULTIPLY || act == ACT_SUMM) && argc != 5)
        return false;
    if (act == ACT_INVERSE_MATRIX && argc != 4)
        return false;

    return true;
}
