#include "check_create.h"
#include "same_functions.h"
#include <stdlib.h>

/**
 * ----------------------------------------------
 * | Юнит тест Очистки ассоциативного массива   |
 * ----------------------------------------------
 */

START_TEST(arr_empty)
{
    assoc_array_t arr = NULL;
    assoc_array_error_t rc;

    arr = assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    rc = assoc_array_clear(arr);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    assoc_array_destroy(&arr);
    ck_assert_ptr_null(arr);
}
END_TEST

START_TEST(arr_not_empty)
{
    assoc_array_t arr = NULL;
    assoc_array_error_t rc;
    
    data_t data_arr[] = { { "a", 10 }, { "b", 20 }, { "d", 30 }, { "e", 40 }, { "f", 50 } };
    size_t length = sizeof(data_arr) / sizeof(data_arr[0]);

    arr = assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    rc = fill_arr(arr, data_arr, length);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(arr);

    rc = assoc_array_clear(arr);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    assoc_array_destroy(&arr);
    ck_assert_ptr_null(arr);
}
END_TEST

START_TEST(double_clear_arr)
{
    assoc_array_t arr = NULL;
    assoc_array_error_t rc;
    
    data_t data_arr[] = { { "a", 10 }, { "b", 20 }, { "d", 30 }, { "e", 40 }, { "f", 50 } };
    size_t length = sizeof(data_arr) / sizeof(data_arr[0]);

    arr = assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    rc = fill_arr(arr, data_arr, length);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(arr);

    rc = assoc_array_clear(arr);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_clear(arr);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    assoc_array_destroy(&arr);
    ck_assert_ptr_null(arr);
}
END_TEST

START_TEST(invalid_param)
{
    assoc_array_error_t rc;

    rc = assoc_array_clear(NULL);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST

Suite *test_assoc_array_clear(void)
{
    Suite *suite;
    TCase *tc_pos, *tc_neg;

    suite = suite_create("assoc_array_clear");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, arr_empty);
    tcase_add_test(tc_pos, arr_not_empty);
    tcase_add_test(tc_pos, double_clear_arr);

    suite_add_tcase(suite, tc_pos);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_pos, invalid_param);

    suite_add_tcase(suite, tc_neg);

    return suite;
}