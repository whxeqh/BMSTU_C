#include "same_functions.h"

#include <assert.h>
#include <stdio.h>

assoc_array_error_t fill_arr(assoc_array_t arr, data_t *data, size_t length)
{
    assoc_array_error_t rc = ASSOC_ARRAY_OK;

    for (size_t i = 0; rc == ASSOC_ARRAY_OK && i < length; ++i)
        rc = assoc_array_insert(arr, data[i].key, data[i].value);

    return rc;
}

bool assoc_arrays_equal(assoc_array_t first, assoc_array_t second, data_t *data_arr, size_t length) 
{
    assert(first);
    assert(second);
    assert(data_arr);

    assoc_array_error_t rc = ASSOC_ARRAY_OK;

    for (size_t i = 0; i < length; i++)
    {
        int *num1, *num2;

        //printf("\ndata = %s %d\n", data_arr[i].key, data_arr[i].value);

        rc = assoc_array_find(first, data_arr[i].key, &num1);
        if (rc != ASSOC_ARRAY_OK)
            goto func_end;

        //printf("first rc = %d\n", rc);

        //printf("first value = %d\n", *num1);
        if (*num1 != data_arr[i].value)
        {
            rc = ASSOC_ARRAY_NOT_FOUND;
            goto func_end;
        }

        rc = assoc_array_find(second, data_arr[i].key, &num2);
        if (rc != ASSOC_ARRAY_OK)
            goto func_end;


        //printf("second rc = %d\n", rc);
        //printf("second value = %d\n", *num2);
        if (*num2 != data_arr[i].value)
        {
            rc = ASSOC_ARRAY_NOT_FOUND;
            goto func_end;
        }

        if (*num1 != *num2)
        {
            rc = ASSOC_ARRAY_NOT_FOUND;
            goto func_end;
        }
    }

    func_end:
        return (rc == ASSOC_ARRAY_OK) ? true : false; 
}
bool assoc_array_equal(assoc_array_t arr, data_t *data_arr, size_t length)
{
    assert(arr);

    assoc_array_error_t rc = ASSOC_ARRAY_OK;

    for (size_t i = 0; rc == ASSOC_ARRAY_OK && i < length; i++)
    {
        //printf("data = %s %d\n", data_arr[i].key, data_arr[i].value);

        int *num;
        rc = assoc_array_find(arr, data_arr[i].key, &num);
        if (*num != data_arr[i].value)
            rc = ASSOC_ARRAY_NOT_FOUND;

        //printf("num = %d\n", *num); 
    }

    //printf("rc = %d\n", rc);
    return (rc == ASSOC_ARRAY_OK) ? true : false; 
}

void mul_value(const char *key, int *num, void *param)
{
    (void) key;

    int mul_num = *(int *)param;

    *num *= mul_num;
}


void sqr_value(const char *key, int *num, void *param)
{
    (void) key;

    (void) param;

    *num *= *num;
}
