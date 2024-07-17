#include "io.h"
#include "errors.h"
#include "calculations.h"

int main(void)
{
    int rc = OK, matrix[N * 2][M];
    short digit;
    size_t a_n, a_m;
    
    rc = input_size(&a_n, &a_m);
    if (rc == OK)
        rc = input_matrix(a_n, a_m, matrix);
    if (rc == OK)
        rc = input_digit(&digit);

    if (rc == OK)
    {
        rc = new_edit_matrix(&a_n, a_m, matrix, digit);
        if (rc == OK)
            print_matrix(a_n, a_m, matrix);
    }
    else
        print_err(rc);
    
    return rc;
}
