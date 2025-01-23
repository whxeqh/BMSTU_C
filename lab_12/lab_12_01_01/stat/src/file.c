#include <file.h>

#include "consts.h"
#include "array.h"

#include <stdlib.h>
#include <assert.h>

/** 
 * @brief Считывает данные из файла в массив
 * @param file_in Файловый дескриптор
 * @param pbeg Указатель на первый элемент массива
 * @param pend Указатель на за последний элемент массива
 * @return Код ошибки
*/
static int read_array_from_file(FILE *file_in, int *pbeg, int *pend);

/**
 * @brief Подсчитывает количество элементов в массиве 
 * @param cnt Количество элементов
 * @param file_in Файловый дескриптор
 * @return Код ошибки
*/
static int get_count_elements(size_t *cnt, FILE *file_in);

static int read_array_from_file(FILE *file_in, int *pbeg, int *pend)
{
    assert(file_in != NULL);

    int rc = OK;

    for (int *pcur = pbeg; rc == OK && pcur < pend; pcur++)
        if (fscanf(file_in, "%d\n", pcur) != 1)
            rc = ERR_IO;

    if (rc == OK && !feof(file_in))
        rc = ERR_FILE;

    return rc;
}

static int get_count_elements(size_t *cnt, FILE *file_in)
{
    assert(file_in != NULL);

    size_t tmp_cnt = 0;
    int value;

    while (fscanf(file_in, "%d\n", &value) == 1)
        tmp_cnt++;
    
    if (!feof(file_in))
        return ERR_IO;

    *cnt = tmp_cnt;    
    return OK;
}

int create_array_ex(int **pbeg, int **pend, const char *file_name)
{
    assert(file_name);

    int rc = OK;
    FILE *file_in = fopen(file_name, "r");
    if (!file_in)
        return ERR_FILE;
    
    rc = create_array(pbeg, pend, file_in);
    fclose(file_in);

    return rc;
}

int create_array(int **pbeg, int **pend, FILE *file_in)
{
    assert(file_in != NULL);

    int rc = OK;
    int *arr = NULL;
    size_t length;

    rc = get_count_elements(&length, file_in);
    if (rc != OK)
        return rc;
    
    if (length == 0)
        return ERR_EMPTY_ARRAY;

    arr = malloc(length * sizeof(int));

    if (arr == NULL)
        return ERR_MEMORY;
    
    rewind(file_in);

    rc = read_array_from_file(file_in, arr, arr + length);
    if (rc == OK)
    {
        *pbeg = arr;
        *pend = arr + length;    
    }
    else 
    {   
        rc = ERR_IO;
        destroy_array(&arr);
        arr = NULL;
    }

    return rc;
}

int print_array_int_ex(const int *pbeg, const int *pend, const char *file_name)
{
    assert(pbeg < pend);
    assert(pbeg != NULL);
    assert(pend != NULL);
    assert(file_name != NULL);

    int rc = OK;

    FILE *file_out = fopen(file_name, "w");
    if (!file_out)
        return ERR_FILE;
    
    rc = print_array_int(pbeg, pend, file_out);
    fclose(file_out);
    
    return rc;
}

int print_array_int(const int *pbeg, const int *pend, FILE *file_out)
{
    assert(pbeg < pend);
    assert(pbeg != NULL);
    assert(pend != NULL);
    assert(file_out != NULL);
    
    for (const int *pcur = pbeg; pcur < pend; pcur++)
        if (fprintf(file_out, "%d ", *pcur) < 0)
            return ERR_IO;
    return OK;
}
