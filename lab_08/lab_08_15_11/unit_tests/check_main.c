#include <stdio.h>
#include "check_mtr_op.h"
#include "check_mtr_sum.h"
#include "check_mtr_mul.h"

#define RED    "\x1b[31m"
#define GREEN  "\x1b[32m"
#define RESET  "\x1b[0m"

int main(void)
{
   
    SRunner *runner = srunner_create(matrix_sum_suite());
    
    srunner_add_suite(runner, matrix_mul_suite());   
    srunner_add_suite(runner, matrix_inverse_suite()); 

    int failed = 0;
    srunner_run_all(runner, CK_VERBOSE);
    failed = srunner_ntests_failed(runner);

    printf(failed ? RED "FAILED TESTS: %d\n" RESET : GREEN "\nCONGRATULATIONS!  TESTS PASSED!!!!\n\n" RESET, failed);

    srunner_free(runner);
    return failed;
}
