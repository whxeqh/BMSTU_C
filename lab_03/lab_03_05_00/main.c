#include "io.h"
#include "errors.h"
#include "calculations.h"

int main(void)
{
    int rc = OK, matrix[N][M], arr[N*M];
    size_t a_n, a_m, arr_size;
    
    rc = input_size(&a_n, &a_m);
    if (rc == OK)
        rc = input_matrix(a_n, a_m, matrix);

    if (rc == OK)
    {
        arr_size = fill_array(a_n, a_m, matrix, arr);
        if (arr_size == 0)
            rc = ERR_NO_SIMPLE_NUMBERS;
        else
        {
            reverse_array(arr_size, arr);
            fill_matrix(a_n, a_m, matrix, arr_size, arr);
            print_matrix(a_n, a_m, matrix);
        }
    }
    if (rc != OK)
        print_err(rc);
        
    return rc;
}
