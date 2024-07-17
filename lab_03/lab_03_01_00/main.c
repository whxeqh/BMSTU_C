#include "io.h"
#include "errors.h"
#include "calculations.h"

int main(void)
{
    int rc = OK;
    int ans[M], matrix[N][M];
    size_t a_n, a_m;
    
    rc = input_size(&a_n, &a_m);
    if (rc == OK)
        rc = input_matrix(a_n, a_m, matrix);
    
    if (rc == OK)
    {
        ans_array(ans, matrix, a_n, a_m);
        print_arr(a_m, ans);
    }
    else 
        print_err(rc);

    return rc;
}
