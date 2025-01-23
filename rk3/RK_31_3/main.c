#include "arr_io.h"
#include "arr_alloc.h"
#include "arr_op.h"
#include "errors.h"
#include <stdio.h>

int main(void)
{
    int rc = OK;
    int *arr1 = NULL, *arr2 = NULL, *new_arr = NULL;
    size_t length1 = 0, length2 = 0, new_length = 0;

    rc = arr_create(&arr1, &length1);
    if (rc == OK)
        rc = arr_create(&arr2, &length2);

    if (rc == OK)
        rc = make_set(&arr1, &length1);

    if (rc == OK)
        rc = make_set(&arr2, &length2);

    if (rc == OK)
        new_length = length1 + length2;
    
    if (rc == OK && new_length > 0)
    {
        new_arr = arr_alloc(new_length);
        if (!new_arr)
            rc = ERR_MEMORY;
        else 
            arr_op(new_arr, &new_length, arr1, length1, arr2, length2);
    }

    if (rc == OK)
    {
        puts("Set 1");
        arr_print(arr1, length1);

        puts("Set 2");
        arr_print(arr2, length2);

        puts("Op");
        arr_print(new_arr, new_length);
    }
    
    arr_free(arr1);
    arr_free(arr2);
    arr_free(new_arr);
    
    return rc;
}
