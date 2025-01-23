#include "check_max.h"
#include "same_functions.h"
#include <stdlib.h>
#include <stdbool.h>

START_TEST(arr_one_elem)
{
    assoc_array_error_t rc;

    data_t data_arr[] = { { "a", 10 } };
    data_t max_elem = data_arr[0];
    int *value;

    size_t length = sizeof(data_arr) / sizeof(data_arr[0]);
    assoc_array_t ass_arr = NULL;

    ass_arr = assoc_array_create();
    ck_assert_ptr_nonnull(ass_arr);

    rc = fill_arr(ass_arr, data_arr, length);
    
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(ass_arr);

    //rc = assoc_array_find(ass_arr, elem_to_find.key, &value);

    rc = assoc_array_max(ass_arr, &value);

    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*value, max_elem.value);

    assoc_array_destroy(&ass_arr);
    ck_assert_ptr_null(ass_arr);    
}
END_TEST

START_TEST(arr_two_elems)
{
    assoc_array_error_t rc;

    data_t data_arr[] = { { "a", 10 }, { "b", 20 }, };
    data_t max_elem = data_arr[1];
    int *value;

    size_t length = sizeof(data_arr) / sizeof(data_arr[0]);
    assoc_array_t ass_arr = NULL;

    ass_arr = assoc_array_create();
    ck_assert_ptr_nonnull(ass_arr);

    rc = fill_arr(ass_arr, data_arr, length);
    
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(ass_arr);

    //rc = assoc_array_find(ass_arr, elem_to_find.key, &value);

    rc = assoc_array_max(ass_arr, &value);

    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*value, max_elem.value);

    assoc_array_destroy(&ass_arr);
    ck_assert_ptr_null(ass_arr);  
}
END_TEST

START_TEST(arr_six_elems)
{
    assoc_array_error_t rc;

    data_t data_arr[] = { { "a", 10 }, { "c", 20 }, { "d", 30 }, { "t", 40 }, { "e", 50 }, { "b", 50 } };
    data_t max_elem = data_arr[3];
    int *value;

    size_t length = sizeof(data_arr) / sizeof(data_arr[0]);
    assoc_array_t ass_arr = NULL;

    ass_arr = assoc_array_create();
    ck_assert_ptr_nonnull(ass_arr);

    rc = fill_arr(ass_arr, data_arr, length);
    
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(ass_arr);

    //rc = assoc_array_find(ass_arr, elem_to_find.key, &value);

    rc = assoc_array_max(ass_arr, &value);

    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*value, max_elem.value);

    assoc_array_destroy(&ass_arr);
    ck_assert_ptr_null(ass_arr);     
}
END_TEST

START_TEST(find_in_begin)
{
    assoc_array_error_t rc;

    data_t data_arr[] = { { "x", 10 }, { "c", 20 }, { "d", 30 }, { "e", 40 }, { "f", 50 } };
    data_t max_elem = data_arr[0];
    int *value;

    size_t length = sizeof(data_arr) / sizeof(data_arr[0]);
    assoc_array_t ass_arr = NULL;

    ass_arr = assoc_array_create();
    ck_assert_ptr_nonnull(ass_arr);

    rc = fill_arr(ass_arr, data_arr, length);
    
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(ass_arr);

    //rc = assoc_array_find(ass_arr, elem_to_find.key, &value);

    rc = assoc_array_max(ass_arr, &value);

    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*value, max_elem.value);

    assoc_array_destroy(&ass_arr);
    ck_assert_ptr_null(ass_arr);   
}
END_TEST

START_TEST(find_in_mid)
{
    assoc_array_error_t rc;

    data_t data_arr[] = { { "b", 10 }, { "c", 20 }, { "f", 30 }, { "e", 40 }, { "d", 50 } };
    data_t max_elem = data_arr[2];
    int *value;

    size_t length = sizeof(data_arr) / sizeof(data_arr[0]);
    assoc_array_t ass_arr = NULL;

    ass_arr = assoc_array_create();
    ck_assert_ptr_nonnull(ass_arr);

    rc = fill_arr(ass_arr, data_arr, length);
    
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(ass_arr);

    //rc = assoc_array_find(ass_arr, elem_to_find.key, &value);

    rc = assoc_array_max(ass_arr, &value);

    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*value, max_elem.value);

    assoc_array_destroy(&ass_arr);
    ck_assert_ptr_null(ass_arr);   
}
END_TEST

START_TEST(find_in_end)
{
    assoc_array_error_t rc;

    data_t data_arr[] = { { "b", 10 }, { "c", 20 }, { "d", 30 }, { "e", 40 }, { "f", 50 } };
    data_t max_elem = data_arr[4];
    int *value;

    size_t length = sizeof(data_arr) / sizeof(data_arr[0]);
    assoc_array_t ass_arr = NULL;

    ass_arr = assoc_array_create();
    ck_assert_ptr_nonnull(ass_arr);

    rc = fill_arr(ass_arr, data_arr, length);
    
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(ass_arr);

    //rc = assoc_array_find(ass_arr, elem_to_find.key, &value);

    rc = assoc_array_max(ass_arr, &value);

    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*value, max_elem.value);

    assoc_array_destroy(&ass_arr);
    ck_assert_ptr_null(ass_arr);   
}
END_TEST

START_TEST(invalid_param_arr)
{
    assoc_array_error_t rc;

    data_t data_arr[] = { { "b", 10 }, { "c", 20 }, { "d", 30 }, { "e", 40 }, { "f", 50 } };
    data_t elem_to_find = data_arr[4];
    int *value;

    rc = assoc_array_find(NULL, elem_to_find.key, &value);

    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST

START_TEST(not_found)
{
    assoc_array_error_t rc;

    data_t elem_to_find = { "lalala", 10 };
    int *value;

    assoc_array_t ass_arr = NULL;

    ass_arr = assoc_array_create();
    ck_assert_ptr_nonnull(ass_arr);

    rc = assoc_array_find(ass_arr, elem_to_find.key, &value);

    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&ass_arr);
    ck_assert_ptr_null(ass_arr);  
}
END_TEST

START_TEST(num_null)
{
    assoc_array_error_t rc;

    data_t data_arr[] = { { "a", 10 } };
    //data_t max_elem = data_arr[0];

    size_t length = sizeof(data_arr) / sizeof(data_arr[0]);
    assoc_array_t ass_arr = NULL;

    ass_arr = assoc_array_create();
    ck_assert_ptr_nonnull(ass_arr);

    rc = fill_arr(ass_arr, data_arr, length);
    
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(ass_arr);

    //rc = assoc_array_find(ass_arr, elem_to_find.key, &value);

    rc = assoc_array_max(ass_arr, NULL);

    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&ass_arr);
    ck_assert_ptr_null(ass_arr);    
}
END_TEST

Suite *test_assoc_array_max(void)
{
    Suite *suite;
    TCase *tc_pos, *tc_neg;

    suite = suite_create("assoc_array_max");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, arr_one_elem);
    tcase_add_test(tc_pos, arr_two_elems);
    tcase_add_test(tc_pos, arr_six_elems);
    tcase_add_test(tc_pos, find_in_begin);
    tcase_add_test(tc_pos, find_in_mid);
    tcase_add_test(tc_pos, find_in_end);

    suite_add_tcase(suite, tc_pos);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, invalid_param_arr);
    tcase_add_test(tc_neg, not_found);
    tcase_add_test(tc_neg, num_null);

    suite_add_tcase(suite, tc_neg);

    return suite;
}