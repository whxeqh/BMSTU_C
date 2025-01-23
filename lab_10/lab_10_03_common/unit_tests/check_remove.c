#include "check_remove.h"
#include "same_functions.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

START_TEST(empty_array)
{
    assoc_array_error_t rc;

    data_t src_arr[] = { { "a", 10 } };
    data_t elem_to_remove = src_arr[0];

    assoc_array_t ass_arr_src = NULL;

    ass_arr_src = assoc_array_create();
    ck_assert_ptr_nonnull(ass_arr_src);

    rc = assoc_array_remove(ass_arr_src, elem_to_remove.key);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&ass_arr_src);
    ck_assert_ptr_null(ass_arr_src);   
}
END_TEST

START_TEST(arr_one_elem)
{
    assoc_array_error_t rc;

    data_t src_arr[] = { { "a", 10 } };
    data_t elem_to_remove = src_arr[0];
    data_t dst_arr[] = { { "b", 20 } };
    
    size_t length_src = sizeof(src_arr) / sizeof(src_arr[0]);
    size_t length_dst = 0;
    
    assoc_array_t ass_arr_src = NULL;

    ass_arr_src = assoc_array_create();
    ck_assert_ptr_nonnull(ass_arr_src);

    rc = fill_arr(ass_arr_src, src_arr, length_src);
    
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(ass_arr_src);

    rc = assoc_array_remove(ass_arr_src, elem_to_remove.key);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    bool equal = assoc_array_equal(ass_arr_src, dst_arr, length_dst);
    ck_assert_int_eq(equal, true);
    
    assoc_array_destroy(&ass_arr_src);
    ck_assert_ptr_null(ass_arr_src);
}
END_TEST

START_TEST(arr_two_elems)
{
    assoc_array_error_t rc;

    data_t src_arr[] = { { "a", 10 }, { "b", 20 } };
    data_t elem_to_remove = src_arr[0];
    data_t dst_arr[] = { { "b", 20 } };
    
    size_t length_src = sizeof(src_arr) / sizeof(src_arr[0]);
    size_t length_dst = sizeof(dst_arr) / sizeof(dst_arr[0]);
    
    assoc_array_t ass_arr_src = NULL;

    ass_arr_src = assoc_array_create();
    ck_assert_ptr_nonnull(ass_arr_src);

    rc = fill_arr(ass_arr_src, src_arr, length_src);
    
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(ass_arr_src);

    rc = assoc_array_remove(ass_arr_src, elem_to_remove.key);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    bool equal = assoc_array_equal(ass_arr_src, dst_arr, length_dst);
    ck_assert_int_eq(equal, true);

    assoc_array_destroy(&ass_arr_src);
    ck_assert_ptr_null(ass_arr_src);
}
END_TEST

START_TEST(arr_six_elems)
{
    assoc_array_error_t rc;

    data_t src_arr[] = { { "a", 10 }, { "c", 20 }, { "d", 30 }, { "b", 40 }, { "t", 50 }, { "e", 50 } };
    data_t elem_to_remove = src_arr[1];
    data_t dst_arr[] = { { "a", 10 }, { "d", 30 }, { "b", 40 }, { "t", 50 }, { "e", 50 } };
    
    size_t length_src = sizeof(src_arr) / sizeof(src_arr[0]);
    size_t length_dst = sizeof(dst_arr) / sizeof(dst_arr[0]);
    
    assoc_array_t ass_arr_src = NULL;

    ass_arr_src = assoc_array_create();
    ck_assert_ptr_nonnull(ass_arr_src);

    rc = fill_arr(ass_arr_src, src_arr, length_src);
    
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(ass_arr_src);

    rc = assoc_array_remove(ass_arr_src, elem_to_remove.key);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    bool equal = assoc_array_equal(ass_arr_src, dst_arr, length_dst);
    ck_assert_int_eq(equal, true);

    assoc_array_destroy(&ass_arr_src);
    ck_assert_ptr_null(ass_arr_src);
}
END_TEST

START_TEST(remove_in_begin)
{
    assoc_array_error_t rc;

    data_t src_arr[] = { { "a", 10 }, { "c", 20 }, { "d", 30 }, { "b", 40 }, { "t", 50 }, { "e", 50 } };
    data_t elem_to_remove = src_arr[0];
    data_t dst_arr[] = { { "c", 20 }, { "d", 30 }, { "b", 40 }, { "t", 50 }, { "e", 50 } };
    
    size_t length_src = sizeof(src_arr) / sizeof(src_arr[0]);
    size_t length_dst = sizeof(dst_arr) / sizeof(dst_arr[0]);
    
    assoc_array_t ass_arr_src = NULL;

    ass_arr_src = assoc_array_create();
    ck_assert_ptr_nonnull(ass_arr_src);

    rc = fill_arr(ass_arr_src, src_arr, length_src);
    
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(ass_arr_src);

    rc = assoc_array_remove(ass_arr_src, elem_to_remove.key);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    bool equal = assoc_array_equal(ass_arr_src, dst_arr, length_dst);
    ck_assert_int_eq(equal, true);
    
    assoc_array_destroy(&ass_arr_src);
    ck_assert_ptr_null(ass_arr_src);
}
END_TEST

START_TEST(remove_in_mid)
{
    assoc_array_error_t rc;

    data_t src_arr[] = { { "a", 10 }, { "c", 20 }, { "d", 30 }, { "b", 40 }, { "t", 50 }, { "e", 50 } };
    data_t elem_to_remove = src_arr[2];
    data_t dst_arr[] = { { "a", 10 }, { "c", 20 }, { "b", 40 }, { "t", 50 }, { "e", 50 } };
    
    size_t length_src = sizeof(src_arr) / sizeof(src_arr[0]);
    size_t length_dst = sizeof(dst_arr) / sizeof(dst_arr[0]);
    
    assoc_array_t ass_arr_src = NULL;

    ass_arr_src = assoc_array_create();
    ck_assert_ptr_nonnull(ass_arr_src);

    rc = fill_arr(ass_arr_src, src_arr, length_src);
    
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(ass_arr_src);

    rc = assoc_array_remove(ass_arr_src, elem_to_remove.key);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    bool equal = assoc_array_equal(ass_arr_src, dst_arr, length_dst);
    ck_assert_int_eq(equal, true);
    
    assoc_array_destroy(&ass_arr_src);
    ck_assert_ptr_null(ass_arr_src);
}
END_TEST

START_TEST(remove_in_end)
{
    assoc_array_error_t rc;

    data_t src_arr[] = { { "a", 10 }, { "c", 20 }, { "d", 30 }, { "b", 40 }, { "t", 50 }, { "e", 50 } };
    data_t elem_to_remove = src_arr[5];
    data_t dst_arr[] = { { "a", 10 }, { "c", 20 }, { "d", 30 }, { "b", 40 }, { "t", 50 } };
    
    size_t length_src = sizeof(src_arr) / sizeof(src_arr[0]);
    size_t length_dst = sizeof(dst_arr) / sizeof(dst_arr[0]);
    
    assoc_array_t ass_arr_src = NULL;

    ass_arr_src = assoc_array_create();
    ck_assert_ptr_nonnull(ass_arr_src);

    rc = fill_arr(ass_arr_src, src_arr, length_src);
    
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(ass_arr_src);

    rc = assoc_array_remove(ass_arr_src, elem_to_remove.key);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    bool equal = assoc_array_equal(ass_arr_src, dst_arr, length_dst);
    ck_assert_int_eq(equal, true);
    
    assoc_array_destroy(&ass_arr_src);
    ck_assert_ptr_null(ass_arr_src);
}
END_TEST

START_TEST(invalid_param_arr)
{
    assoc_array_error_t rc;

    data_t data_arr[] = { { "b", 10 }, { "c", 20 }, { "d", 30 }, { "e", 40 }, { "f", 50 } };
    data_t elem_to_find = data_arr[4];

    rc = assoc_array_remove(NULL, elem_to_find.key);

    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST

START_TEST(not_found)
{
    assoc_array_error_t rc;

    data_t data_arr[] = { { "b", 10 }, { "c", 20 }, { "d", 30 }, { "e", 40 }, { "f", 50 } };
    data_t elem_to_find = { "lalala", 10 };

    size_t length = sizeof(data_arr) / sizeof(data_arr[0]);
    assoc_array_t ass_arr = NULL;

    ass_arr = assoc_array_create();
    ck_assert_ptr_nonnull(ass_arr);

    rc = fill_arr(ass_arr, data_arr, length);
    
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(ass_arr);

    rc = assoc_array_remove(ass_arr, elem_to_find.key);

    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

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

    rc = assoc_array_remove(ass_arr, elem.key);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
    
    assoc_array_destroy(&ass_arr);
    ck_assert_ptr_null(ass_arr);    
}
END_TEST

START_TEST(key_null)
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

    rc = assoc_array_remove(ass_arr, NULL);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
    
    assoc_array_destroy(&ass_arr);
    ck_assert_ptr_null(ass_arr);    
}
END_TEST

Suite *test_assoc_array_remove(void)
{
    Suite *suite;
    TCase *tc_pos, *tc_neg;

    suite = suite_create("assoc_array_remove");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, empty_array);
    tcase_add_test(tc_pos, arr_one_elem);
    tcase_add_test(tc_pos, arr_two_elems);
    tcase_add_test(tc_pos, arr_six_elems);
    tcase_add_test(tc_pos, remove_in_begin);
    tcase_add_test(tc_pos, remove_in_mid);
    tcase_add_test(tc_pos, remove_in_end);

    suite_add_tcase(suite, tc_pos);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, invalid_param_arr);
    tcase_add_test(tc_neg, not_found);
    tcase_add_test(tc_neg, empty_key);
    tcase_add_test(tc_neg, key_null);

    suite_add_tcase(suite, tc_neg);

    return suite;
}