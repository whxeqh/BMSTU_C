#include <stdio.h>
#include "check_pop_back.h"
#include "check_insert.h"
#include "check_reverse.h"
#include "check_sort.h"

#define RED    "\x1b[31m"
#define GREEN  "\x1b[32m"
#define RESET  "\x1b[0m"

int main(void)
{
   
    SRunner *runner = srunner_create(test_pop_back());
    srunner_add_suite(runner, test_insert());
    srunner_add_suite(runner, test_reverse());
    srunner_add_suite(runner, test_sort());

    int failed = 0;
    srunner_run_all(runner, CK_VERBOSE);
    failed = srunner_ntests_failed(runner);

    printf(failed ? RED "FAILED TESTS: %d\n" RESET : GREEN "\nCONGRATULATIONS!  TESTS PASSED!!!!\n\n" RESET, failed);

    srunner_free(runner);
    
    return failed;
}
