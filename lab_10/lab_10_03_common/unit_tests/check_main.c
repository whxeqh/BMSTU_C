#include <stdio.h>
#include "check_create.h"
#include "check_destroy.h"
#include "check_insert.h"
#include "check_find.h"
#include "check_remove.h"
#include "check_clear.h"
#include "check_each.h"
#include "check_min.h"
#include "check_max.h"

#define RED    "\x1b[31m"
#define GREEN  "\x1b[32m"
#define RESET  "\x1b[0m"

int main(void)
{
   
    SRunner *runner = srunner_create(test_assoc_array_create());
    srunner_add_suite(runner, test_assoc_array_destroy());
    srunner_add_suite(runner, test_assoc_array_insert());
    srunner_add_suite(runner, test_assoc_array_clear());
    srunner_add_suite(runner, test_assoc_array_each());
    srunner_add_suite(runner, test_assoc_array_find());
    srunner_add_suite(runner, test_assoc_array_remove());
    srunner_add_suite(runner, test_assoc_array_min());
    srunner_add_suite(runner, test_assoc_array_max());

    int failed = 0;
    srunner_run_all(runner, CK_VERBOSE);
    failed = srunner_ntests_failed(runner);

    printf(failed ? RED "FAILED TESTS: %d\n" RESET : GREEN "\nCONGRATULATIONS!  TESTS PASSED!!!!\n\n" RESET, failed);

    srunner_free(runner);
    
    return failed;
}

