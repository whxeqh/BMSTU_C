#include "arr_io.h"
#include "arr_alloc.h"
#include "errors.h"
#include <stdio.h>

int arr_read(int *arr, const size_t length)
{
    for (size_t i = 0; i < length; i++)
        if (scanf("%d", &arr[i]) != 1)
            return ERR_IO;
    return OK;
}

void arr_print(const int *arr, const size_t length)
{
    for (size_t i = 0; i < length; i++)
        printf("%d ", arr[i]);
    puts("");
}

int arr_create(int **arr, size_t *length)
{
    int *tmp_arr = NULL;
    size_t tmp_length;

    if (scanf("%zu", &tmp_length) != 1)
        return ERR_IO;

    if (tmp_length == 0)
    {
        *length = 0;
        *arr = NULL;
        return OK;
    }

    tmp_arr = arr_alloc(tmp_length);
    if (!tmp_arr)
        return ERR_MEMORY;
    
    int rc = arr_read(tmp_arr, tmp_length);
    if (rc == OK)
    {
        *arr = tmp_arr;
        *length = tmp_length;
    }
    else
        arr_free(tmp_arr);

    return rc;
}
