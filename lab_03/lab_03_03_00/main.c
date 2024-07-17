#include "io.h"
#include "calculations.h"
#include "errors.h"

int main(void)
{
    int rc = OK, matrix[N][M], keys[N];
    size_t a_n, a_m;
    
    rc = input_size(&a_n, &a_m);
    if (rc == OK)
        rc = input_matrix(a_n, a_m, matrix);

    if (rc == OK)
    {
        form_key_array(a_n, a_m, matrix, keys);
        sort(a_n, a_m, matrix, keys);
        print_matrix(a_n, a_m, matrix);
    }
    else 
        print_err(rc);
    
    return rc;
}
