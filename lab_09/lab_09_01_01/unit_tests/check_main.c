#include <stdio.h>
#include "check_binary_search.h"
#include "check_films_create_ex.h"

#define RED    "\x1b[31m"
#define GREEN  "\x1b[32m"
#define RESET  "\x1b[0m"

int main(void)
{
   
    SRunner *runner = srunner_create(test_binary_search_suite());
    srunner_add_suite(runner, test_films_create_ex_suite());

    int failed = 0;
    srunner_run_all(runner, CK_VERBOSE);
    failed = srunner_ntests_failed(runner);

    printf(failed ? RED "FAILED TESTS: %d\n" RESET : GREEN "\nCONGRATULATIONS!  TESTS PASSED!!!!\n\n" RESET, failed);

    srunner_free(runner);
    
    return failed;
}
