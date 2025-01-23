#include "check_create.h"
#include <stdlib.h>

/**
 * ----------------------------------------------
 * | Юнит тест Создания ассоциативного массива  |
 * ----------------------------------------------
 */

START_TEST(arr_create)
{
    assoc_array_t arr = NULL;

    arr = assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    assoc_array_destroy(&arr);
    ck_assert_ptr_null(arr);
}
END_TEST

Suite *test_assoc_array_create(void)
{
    Suite *suite;
    TCase *tc_pos;

    suite = suite_create("assoc_array_create");

    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, arr_create);

    suite_add_tcase(suite, tc_pos);

    return suite;
}