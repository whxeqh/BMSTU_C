#include <assert.h>
#include <stdlib.h>

#include "products_array.h"
#include "errors.h"
#include "macro.h"

static int products_cnt(FILE *file, size_t *cnt)
{
    int rc = OK;
    rewind(file);

    product_t tmp = { 0 };
    size_t tmp_cnt = 0;

    do
    {
        rc = product_read(file, &tmp);
        product_free_content(&tmp);
        if (rc == OK)
        {
            tmp_cnt++;
        }
    } while (rc == OK && !feof(file));
    
    if (rc == OK)
        *cnt = tmp_cnt;
    
    return rc;
}

int products_create_ex(char *filename, product_t **arr, size_t *length)
{
    FILE *file_in = fopen(filename, "r");
    if (!file_in)
        return ERR_FILE;
    
    int rc = products_create(file_in, arr, length);

    fclose(file_in);

    return rc;
}

int products_create(FILE *file, product_t **arr, size_t *length)
{
    int rc = OK;
    size_t tmp_length;
    product_t *tmp_arr = NULL;

    rewind(file);
    rc = products_cnt(file, &tmp_length);

    if (rc != OK)
    {
        LOG_PRINT_ERR("Ошибка при подсчёте элементов в файле, rc = %d", rc);
        return rc;
    }

    if (tmp_length == 0)
    {
        LOG_PRINT_ERR("В файле 0 элементов, rc = %d", ERR_RANGE);
        return ERR_RANGE;
    }

    LOG_PRINT_OK("Количество элементов в файле: %zu", tmp_length);

    tmp_arr = calloc(tmp_length, sizeof(product_t));
    if (!tmp_arr)
        return ERR_MEMORY;
    
    rewind(file);
    rc = products_read(file, tmp_arr, tmp_length);
    
    if (rc == OK)
    {
        *arr = tmp_arr;
        *length = tmp_length;   
    }
    else
    {
        LOG_PRINT_ERR("Ошибка при заполнении массива из файла, rc = %d", rc);
        free_products(&tmp_arr, &tmp_length); 
    }

    return rc;
}

int products_read(FILE* file, product_t *arr, const size_t length)
{
    int rc = OK;

    product_t tmp_product = { 0 };

    for (size_t i = 0; rc == OK && i < length; i++)
    {
        rc = product_read(file, &tmp_product);
        if (rc == OK)
            rc = product_copy(&arr[i], &tmp_product);
        product_free_content(&tmp_product);
    }

    return rc;
}

void free_products(product_t **arr, size_t *length)
{
    if (!arr || !(*arr) || !length || *length == 0)
        return;

    for (size_t i = 0; i < *length; i++)
        product_free_content(&(*arr)[i]);

    free(*arr);
    *length = 0;
    *arr = NULL;
}
