#include "check_create.h"
#include <stdlib.h>

/**
 * ----------------------------------------------
 * | Юнит тест Очистки ассоциативного массива   |
 * ----------------------------------------------
 */

START_TEST(arr_destroy)
{
    assoc_array_t arr = NULL;

    arr = assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    assoc_array_destroy(&arr);
    ck_assert_ptr_null(arr);
}
END_TEST

START_TEST(arr_destroy_null)
{
    assoc_array_t arr = NULL;
    assoc_array_destroy(&arr);
    ck_assert_ptr_null(arr);
}
END_TEST

Suite *test_assoc_array_destroy(void)
{
    Suite *suite;
    TCase *tc_pos;

    suite = suite_create("assoc_array_destroy");

    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, arr_destroy);
    tcase_add_test(tc_pos, arr_destroy_null);

    suite_add_tcase(suite, tc_pos);

    return suite;
}