#include <stdio.h>
#include "errors.h"
#include "io.h"
#include "calculations.h"

int main(void)
{
    int number, rc = OK, matrix[N][M];
    size_t a_n, a_m;
    
    rc = input_size(&a_n, &a_m);
    if (rc == OK && a_n != a_m)
        rc = ERR_INCORRECT_MATRIX;

    if (rc == OK)
        rc = input_matrix(a_n, a_m, matrix);
    if (rc == OK)
        rc = find_number(a_n, matrix, &number);

    if (rc == OK)
        printf("Ответ: %d\n", number);
    else 
        print_err(rc);

    return rc;
}
