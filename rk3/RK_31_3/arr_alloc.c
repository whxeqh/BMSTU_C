#include "arr_alloc.h"
#include "errors.h"
#include <stdlib.h>

void arr_free(int *arr)
{
    free(arr);
}

int *arr_alloc(size_t length)
{   
    int *tmp_arr = malloc(length * sizeof(int));

    return tmp_arr;
}

int arr_realloc(int **arr, size_t length)
{
    int *tmp_arr = realloc(*arr, length * sizeof(int));
    if (!tmp_arr)
        return ERR_MEMORY;
    
    *arr = tmp_arr;

    return OK;
}
