#include "io.h"
#include "errors.h"
#include "calculations.h"

int main(void)
{
    int rc = OK, matrix[N][M];
    size_t a_n, a_m;
    
    rc = input_size(&a_n, &a_m);
    if (rc == OK)
    {
        fiil_matrix(a_n, a_m, matrix);
        print_matrix(a_n, a_m, matrix);
    }
    else 
        print_err(rc);

    return rc;
}
