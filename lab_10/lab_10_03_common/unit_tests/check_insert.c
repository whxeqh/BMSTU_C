#include "check_insert.h"
#include "same_functions.h"
#include <stdlib.h>
#include <stdbool.h>

START_TEST(arr_empty_one_elem_insert)
{
    assoc_array_error_t rc;

    data_t data_arr[] = { { "a", 10 } };
    size_t length = sizeof(data_arr) / sizeof(data_arr[0]);
    assoc_array_t ass_arr = NULL;

    ass_arr = assoc_array_create();
    ck_assert_ptr_nonnull(ass_arr);

    rc = fill_arr(ass_arr, data_arr, length);
    
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(ass_arr);

    bool equal = assoc_array_equal(ass_arr, data_arr, length);
    ck_assert_int_eq(equal, true);

    assoc_array_destroy(&ass_arr);
    ck_assert_ptr_null(ass_arr);    
}
END_TEST

START_TEST(arr_empty_two_elems_insert)
{
    assoc_array_error_t rc;

    data_t data_arr[] = { { "a", 10 }, { "b", 20 }, };
    size_t length = sizeof(data_arr) / sizeof(data_arr[0]);
    assoc_array_t ass_arr = NULL;

    ass_arr = assoc_array_create();
    ck_assert_ptr_nonnull(ass_arr);

    rc = fill_arr(ass_arr, data_arr, length);
    
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(ass_arr);

    bool equal = assoc_array_equal(ass_arr, data_arr, length);
    ck_assert_int_eq(equal, true);

    assoc_array_destroy(&ass_arr);
    ck_assert_ptr_null(ass_arr);    
}
END_TEST

START_TEST(arr_empty_five_elems_insert)
{
    assoc_array_error_t rc;

    data_t data_arr[] = { { "a", 10 }, { "c", 20 }, { "d", 30 }, { "b", 40 }, { "e", 50 } };
    size_t length = sizeof(data_arr) / sizeof(data_arr[0]);
    assoc_array_t ass_arr = NULL;

    ass_arr = assoc_array_create();
    ck_assert_ptr_nonnull(ass_arr);

    rc = fill_arr(ass_arr, data_arr, length);
    
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(ass_arr);

    bool equal = assoc_array_equal(ass_arr, data_arr, length);
    ck_assert_int_eq(equal, true);
    
    assoc_array_destroy(&ass_arr);
    ck_assert_ptr_null(ass_arr);    
}
END_TEST

START_TEST(arr_empty_ten_elems_insert)
{
    assoc_array_error_t rc;

    data_t data_arr[] = { { "a", 10 }, { "e", 20 }, { "d", 30 }, { "c", 40 }, { "y", 50 }, { "h", 10 }, { "b", 20 }, { "f", 30 }, { "k", 40 }, { "aa", 50 }  };
    size_t length = sizeof(data_arr) / sizeof(data_arr[0]);
    assoc_array_t ass_arr = NULL;

    ass_arr = assoc_array_create();
    ck_assert_ptr_nonnull(ass_arr);

    rc = fill_arr(ass_arr, data_arr, length);
    
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(ass_arr);

    bool equal = assoc_array_equal(ass_arr, data_arr, length);
    ck_assert_int_eq(equal, true);
    
    assoc_array_destroy(&ass_arr);
    ck_assert_ptr_null(ass_arr);    
}
END_TEST

START_TEST(arr_insert_key_exists_in_begin)
{
    assoc_array_error_t rc;

    data_t data_arr[] = { { "b", 10 }, { "c", 20 }, { "d", 30 }, { "e", 40 }, { "f", 50 } };
    size_t length = sizeof(data_arr) / sizeof(data_arr[0]);
    assoc_array_t ass_arr = NULL;

    data_t elem = { "b", 10 };

    ass_arr = assoc_array_create();
    ck_assert_ptr_nonnull(ass_arr);

    rc = fill_arr(ass_arr, data_arr, length);
    
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(ass_arr);

    rc = assoc_array_insert(ass_arr, elem.key, elem.value);
    ck_assert_int_eq(rc, ASSOC_ARRAY_KEY_EXISTS);

    assoc_array_destroy(&ass_arr);
    ck_assert_ptr_null(ass_arr);    
}
END_TEST

START_TEST(arr_insert_key_exists_in_mid)
{
    assoc_array_error_t rc;

    data_t data_arr[] = { { "b", 10 }, { "c", 20 }, { "d", 30 }, { "e", 40 }, { "f", 50 } };
    size_t length = sizeof(data_arr) / sizeof(data_arr[0]);
    assoc_array_t ass_arr = NULL;

    data_t elem = { "d", 30 };

    ass_arr = assoc_array_create();
    ck_assert_ptr_nonnull(ass_arr);

    rc = fill_arr(ass_arr, data_arr, length);
    
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(ass_arr);

    rc = assoc_array_insert(ass_arr, elem.key, elem.value);
    ck_assert_int_eq(rc, ASSOC_ARRAY_KEY_EXISTS);

    bool equal = assoc_array_equal(ass_arr, data_arr, length);
    ck_assert_int_eq(equal, true);

    assoc_array_destroy(&ass_arr);
    ck_assert_ptr_null(ass_arr);    
}
END_TEST

START_TEST(arr_insert_key_exists_in_end)
{
    assoc_array_error_t rc;

    data_t data_arr[] = { { "b", 10 }, { "c", 20 }, { "d", 30 }, { "e", 40 }, { "f", 50 } };
    size_t length = sizeof(data_arr) / sizeof(data_arr[0]);
    assoc_array_t ass_arr = NULL;

    data_t elem = { "f", 50 };

    ass_arr = assoc_array_create();
    ck_assert_ptr_nonnull(ass_arr);

    rc = fill_arr(ass_arr, data_arr, length);
    
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(ass_arr);

    rc = assoc_array_insert(ass_arr, elem.key, elem.value);
    ck_assert_int_eq(rc, ASSOC_ARRAY_KEY_EXISTS);

    bool equal = assoc_array_equal(ass_arr, data_arr, length);
    ck_assert_int_eq(equal, true);

    assoc_array_destroy(&ass_arr);
    ck_assert_ptr_null(ass_arr);    
}
END_TEST

START_TEST(arr_insert_invalid_param_arr)
{
    assoc_array_error_t rc;

    assoc_array_t ass_arr = NULL;

    data_t elem = { "f", 20 };

    rc = assoc_array_insert(ass_arr, elem.key, elem.value);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&ass_arr);
    ck_assert_ptr_null(ass_arr);    
}
END_TEST

START_TEST(arr_insert_invalid_param_key)
{
    assoc_array_error_t rc;

    data_t data_arr[] = { { "a", 10 }, { "b", 20 }, { "d", 30 }, { "e", 40 }, { "f", 50 } };
    size_t length = sizeof(data_arr) / sizeof(data_arr[0]);
    assoc_array_t ass_arr = NULL;

    data_t elem = { "f", 20 };

    ass_arr = assoc_array_create();
    ck_assert_ptr_nonnull(ass_arr);

    rc = fill_arr(ass_arr, data_arr, length);
    
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(ass_arr);

    rc = assoc_array_insert(ass_arr, NULL, elem.value);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&ass_arr);
    ck_assert_ptr_null(ass_arr);    
}
END_TEST

START_TEST(empty_key)
{
    assoc_array_error_t rc;

    data_t data_arr[] = { { "a", 10 }, { "c", 20 }, { "d", 30 }, { "b", 40 }, { "e", 50 } };
    size_t length = sizeof(data_arr) / sizeof(data_arr[0]);
    assoc_array_t ass_arr = NULL;

    ass_arr = assoc_array_create();
    ck_assert_ptr_nonnull(ass_arr);

    rc = fill_arr(ass_arr, data_arr, length);
    
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(ass_arr);

    bool equal = assoc_array_equal(ass_arr, data_arr, length);
    ck_assert_int_eq(equal, true);

    data_t elem = { "", 20 };

    rc = assoc_array_insert(ass_arr, elem.key, elem.value);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
    
    assoc_array_destroy(&ass_arr);
    ck_assert_ptr_null(ass_arr);    
}
END_TEST

Suite *test_assoc_array_insert(void)
{
    Suite *suite;
    TCase *tc_pos, *tc_neg;

    suite = suite_create("assoc_array_insert");

    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, arr_empty_one_elem_insert);
    tcase_add_test(tc_pos, arr_empty_two_elems_insert);
    tcase_add_test(tc_pos, arr_empty_five_elems_insert);
    tcase_add_test(tc_pos, arr_empty_ten_elems_insert);

    suite_add_tcase(suite, tc_pos);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, arr_insert_invalid_param_arr);
    tcase_add_test(tc_neg, arr_insert_invalid_param_key);
    tcase_add_test(tc_neg, arr_insert_key_exists_in_begin);
    tcase_add_test(tc_neg, arr_insert_key_exists_in_mid);
    tcase_add_test(tc_neg, arr_insert_key_exists_in_end);
    tcase_add_test(tc_neg, empty_key);

    suite_add_tcase(suite, tc_neg);

    return suite;
}