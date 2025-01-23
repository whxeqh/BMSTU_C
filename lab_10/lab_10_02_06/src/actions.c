#define _POSIX_C_SOURCE 200809L

#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "actions.h"
#include "errors.h"
#include "matrix.h"

int act_out(void)
{
    int rc = OK;
    FILE *file_in = stdin;
    FILE *file_out = stdout;
    node_t *mtr = NULL;

    rc = matrix_read(file_in, &mtr);
    if (rc == OK)
        rc = matrix_print(file_out, mtr);

    if (rc != OK)
        print_error(rc);
    
    matrix_free(&mtr);

    return rc;
}

int act_binary_operation(action_e act)
{
    int rc = OK;
    FILE *file_in = stdin;
    FILE *file_out = stdout;
    node_t *mtr1 = NULL, *mtr2 = NULL, *res = NULL;

    //Чтение матриц
    {
        rc = matrix_read(file_in, &mtr1);
        if (rc != OK)
            goto func_end;
        
        rc = matrix_read(file_in, &mtr2);
        if (rc != OK)
            goto func_end;
    }

    //Выполнение операции
    switch (act)
    {
        case ACT_ADD:
            rc = matrix_sum(&res, mtr1, mtr2);
            break;
        case ACT_MUL:
            rc = matrix_mul(&res, mtr1, mtr2);
            break;
        default:
            rc = ERR_ACT;
            break;
    }

    if (rc == OK)
        rc = matrix_print(file_out, res);

    func_end:
        matrix_free(&mtr1);
    matrix_free(&mtr2);
    matrix_free(&res);
    
    if (rc != OK)
        print_error(rc);

    return rc;
}

int act_lin(void)
{
    int rc = OK;
    FILE *file_in = stdin;
    FILE *file_out = stdout;
    node_t *mtr = NULL;

    //Чтение матрицы
    rc = matrix_read(file_in, &mtr);
    if (rc != OK)
        goto func_end;

    //Выполнение операции
    matrix_lin(&mtr);
    if (rc != OK)
        goto func_end;

    //Вывол матрицы
    rc = matrix_print(file_out, mtr);

    func_end:
        matrix_free(&mtr);
    if (rc != OK)
        print_error(rc);

    return rc;
}

int read_act(action_e *act)
{
    action_e tmp_act = ACT_UNKNOWN;

    char *buf = NULL;
    size_t length;
    ssize_t read;

    if ((read = getline(&buf, &length, stdin)) == -1)
    {
        free(buf);
        return ERR_IO;
    }

    buf[strcspn(buf, "\n")] = '\0';

    if (strcmp(buf, "out") == 0)
        tmp_act = ACT_OUT;
    else if (strcmp(buf, "add") == 0)
        tmp_act = ACT_ADD;
    else if (strcmp(buf, "mul") == 0)
        tmp_act = ACT_MUL;
    else if (strcmp(buf, "lin") == 0)
        tmp_act = ACT_LIN;

    if (tmp_act != ACT_UNKNOWN)
        *act = tmp_act;
        
    free(buf);
    
    return OK; 
}