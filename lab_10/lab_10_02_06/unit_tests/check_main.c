#include <stdio.h>
#include "check_lini.h"
#include "check_matrix_read.h"
#include "check_mul.h"
#include "check_sum.h"

#define RED    "\x1b[31m"
#define GREEN  "\x1b[32m"
#define RESET  "\x1b[0m"

int main(void)
{
   
    SRunner *runner = srunner_create(test_matrix_read());
    srunner_add_suite(runner, test_sum());
    srunner_add_suite(runner, test_mul());
    srunner_add_suite(runner, test_lin());

    int failed = 0;
    srunner_run_all(runner, CK_VERBOSE);
    failed = srunner_ntests_failed(runner);

    printf(failed ? RED "FAILED TESTS: %d\n" RESET : GREEN "\nCONGRATULATIONS!  TESTS PASSED!!!!\n\n" RESET, failed);

    srunner_free(runner);
    
    return failed;
}
