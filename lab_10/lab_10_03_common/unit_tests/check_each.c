#include "check_each.h"
#include "same_functions.h"

#include <stdbool.h>

START_TEST(one_elem_arr_mul)
{
    assoc_array_error_t rc;

    int mul_num = 2;

    data_t src_arr[] = { { "a", 10 } };
    data_t dst_arr[] = { { "a", 20 } };
    size_t length_src = sizeof(src_arr) / sizeof(src_arr[0]);
    size_t length_dst = sizeof(dst_arr) / sizeof(dst_arr[0]);
    assoc_array_t ass_arr_src = NULL;
    assoc_array_t ass_arr_dst = NULL;

    //Создание и заполнение исходного массива
    {
        ass_arr_src = assoc_array_create();
        ck_assert_ptr_nonnull(ass_arr_src);

        rc = fill_arr(ass_arr_src, src_arr, length_src);

        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        ck_assert_ptr_nonnull(ass_arr_src);
    }

    //Создание и заполнение целевого массива
    {
        ass_arr_dst = assoc_array_create();
        ck_assert_ptr_nonnull(ass_arr_dst);

        rc = fill_arr(ass_arr_dst, dst_arr, length_dst);

        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        ck_assert_ptr_nonnull(ass_arr_dst);
    }

    rc = assoc_array_each(ass_arr_src, mul_value, &mul_num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    bool equal = assoc_arrays_equal(ass_arr_src, ass_arr_dst, dst_arr, length_dst);

    ck_assert_int_eq(equal, true);

    assoc_array_destroy(&ass_arr_src);
    ck_assert_ptr_null(ass_arr_src);

    assoc_array_destroy(&ass_arr_dst);
    ck_assert_ptr_null(ass_arr_src);     
}
END_TEST

START_TEST(two_elems_arr_mul)
{
    assoc_array_error_t rc;

    int mul_num = 2;

    data_t src_arr[] = { { "a", 10 }, { "b", 20 } };
    data_t dst_arr[] = { { "a", 20 }, { "b", 40 } };
    size_t length_src = sizeof(src_arr) / sizeof(src_arr[0]);
    size_t length_dst = sizeof(dst_arr) / sizeof(dst_arr[0]);
    assoc_array_t ass_arr_src = NULL;
    assoc_array_t ass_arr_dst = NULL;

    //Создание и заполнение исходного массива
    {
        ass_arr_src = assoc_array_create();
        ck_assert_ptr_nonnull(ass_arr_src);

        rc = fill_arr(ass_arr_src, src_arr, length_src);

        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        ck_assert_ptr_nonnull(ass_arr_src);
    }

    //Создание и заполнение целевого массива
    {
        ass_arr_dst = assoc_array_create();
        ck_assert_ptr_nonnull(ass_arr_dst);

        rc = fill_arr(ass_arr_dst, dst_arr, length_dst);

        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        ck_assert_ptr_nonnull(ass_arr_dst);
    }

    rc = assoc_array_each(ass_arr_src, mul_value, &mul_num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    bool equal = assoc_arrays_equal(ass_arr_src, ass_arr_dst, dst_arr, length_dst);

    ck_assert_int_eq(equal, true);

    assoc_array_destroy(&ass_arr_src);
    ck_assert_ptr_null(ass_arr_src);

    assoc_array_destroy(&ass_arr_dst);
    ck_assert_ptr_null(ass_arr_src);     
}
END_TEST

START_TEST(six_elems_arr_mul)
{
    assoc_array_error_t rc;

    int mul_num = 2;

    data_t src_arr[] = { { "a", 10 }, { "d", 20 }, { "c", 10 }, { "b", 20 }, { "f", 50 }, { "e", 40 } };
    data_t dst_arr[] = { { "a", 20 }, { "d", 40 }, { "c", 20 }, { "b", 40 }, { "f", 100 }, { "e", 80 }  };
    size_t length_src = sizeof(src_arr) / sizeof(src_arr[0]);
    size_t length_dst = sizeof(dst_arr) / sizeof(dst_arr[0]);
    assoc_array_t ass_arr_src = NULL;
    assoc_array_t ass_arr_dst = NULL;

    //Создание и заполнение исходного массива
    {
        ass_arr_src = assoc_array_create();
        ck_assert_ptr_nonnull(ass_arr_src);

        rc = fill_arr(ass_arr_src, src_arr, length_src);

        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        ck_assert_ptr_nonnull(ass_arr_src);
    }

    //Создание и заполнение целевого массива
    {
        ass_arr_dst = assoc_array_create();
        ck_assert_ptr_nonnull(ass_arr_dst);

        rc = fill_arr(ass_arr_dst, dst_arr, length_dst);

        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        ck_assert_ptr_nonnull(ass_arr_dst);
    }

    rc = assoc_array_each(ass_arr_src, mul_value, &mul_num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    bool equal = assoc_arrays_equal(ass_arr_src, ass_arr_dst, dst_arr, length_dst);
    ck_assert_int_eq(equal, true);

    assoc_array_destroy(&ass_arr_src);
    ck_assert_ptr_null(ass_arr_src);

    assoc_array_destroy(&ass_arr_dst);
    ck_assert_ptr_null(ass_arr_src);     
}
END_TEST

START_TEST(one_elem_arr_sqr)
{
    assoc_array_error_t rc;

    data_t src_arr[] = { { "a", 10 } };
    data_t dst_arr[] = { { "a", 100 } };
    size_t length_src = sizeof(src_arr) / sizeof(src_arr[0]);
    size_t length_dst = sizeof(dst_arr) / sizeof(dst_arr[0]);
    assoc_array_t ass_arr_src = NULL;
    assoc_array_t ass_arr_dst = NULL;

    //Создание и заполнение исходного массива
    {
        ass_arr_src = assoc_array_create();
        ck_assert_ptr_nonnull(ass_arr_src);

        rc = fill_arr(ass_arr_src, src_arr, length_src);

        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        ck_assert_ptr_nonnull(ass_arr_src);
    }

    //Создание и заполнение целевого массива
    {
        ass_arr_dst = assoc_array_create();
        ck_assert_ptr_nonnull(ass_arr_dst);

        rc = fill_arr(ass_arr_dst, dst_arr, length_dst);

        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        ck_assert_ptr_nonnull(ass_arr_dst);
    }

    rc = assoc_array_each(ass_arr_src, sqr_value, NULL);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    bool equal = assoc_arrays_equal(ass_arr_src, ass_arr_dst, dst_arr, length_dst);

    ck_assert_int_eq(equal, true);

    assoc_array_destroy(&ass_arr_src);
    ck_assert_ptr_null(ass_arr_src);

    assoc_array_destroy(&ass_arr_dst);
    ck_assert_ptr_null(ass_arr_src);     
}
END_TEST

START_TEST(two_elems_arr_sqr)
{
    assoc_array_error_t rc;

    data_t src_arr[] = { { "a", 10 }, { "b", -20 } };
    data_t dst_arr[] = { { "a", 100 }, { "b", 400 } };
    size_t length_src = sizeof(src_arr) / sizeof(src_arr[0]);
    size_t length_dst = sizeof(dst_arr) / sizeof(dst_arr[0]);
    assoc_array_t ass_arr_src = NULL;
    assoc_array_t ass_arr_dst = NULL;

    //Создание и заполнение исходного массива
    {
        ass_arr_src = assoc_array_create();
        ck_assert_ptr_nonnull(ass_arr_src);

        rc = fill_arr(ass_arr_src, src_arr, length_src);

        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        ck_assert_ptr_nonnull(ass_arr_src);
    }

    //Создание и заполнение целевого массива
    {
        ass_arr_dst = assoc_array_create();
        ck_assert_ptr_nonnull(ass_arr_dst);

        rc = fill_arr(ass_arr_dst, dst_arr, length_dst);

        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        ck_assert_ptr_nonnull(ass_arr_dst);
    }

    rc = assoc_array_each(ass_arr_src, sqr_value, NULL);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    bool equal = assoc_arrays_equal(ass_arr_src, ass_arr_dst, dst_arr, length_dst);

    ck_assert_int_eq(equal, true);

    assoc_array_destroy(&ass_arr_src);
    ck_assert_ptr_null(ass_arr_src);

    assoc_array_destroy(&ass_arr_dst);
    ck_assert_ptr_null(ass_arr_src);     
}
END_TEST

START_TEST(six_elems_arr_sqr)
{
    assoc_array_error_t rc;

    data_t src_arr[] = { { "a", 10 }, { "d", -20 }, { "c", 1 }, { "b", -5 }, { "f", 0 }, { "e", 40 } };
    data_t dst_arr[] = { { "a", 100 }, { "d", 400 }, { "c", 1 }, { "b", 25 }, { "f", 0 }, { "e", 1600 }  };
    size_t length_src = sizeof(src_arr) / sizeof(src_arr[0]);
    size_t length_dst = sizeof(dst_arr) / sizeof(dst_arr[0]);
    assoc_array_t ass_arr_src = NULL;
    assoc_array_t ass_arr_dst = NULL;

    //Создание и заполнение исходного массива
    {
        ass_arr_src = assoc_array_create();
        ck_assert_ptr_nonnull(ass_arr_src);

        rc = fill_arr(ass_arr_src, src_arr, length_src);

        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        ck_assert_ptr_nonnull(ass_arr_src);
    }

    //Создание и заполнение целевого массива
    {
        ass_arr_dst = assoc_array_create();
        ck_assert_ptr_nonnull(ass_arr_dst);

        rc = fill_arr(ass_arr_dst, dst_arr, length_dst);

        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        ck_assert_ptr_nonnull(ass_arr_dst);
    }

    rc = assoc_array_each(ass_arr_src, sqr_value, NULL);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    bool equal = assoc_arrays_equal(ass_arr_src, ass_arr_dst, dst_arr, length_dst);

    ck_assert_int_eq(equal, true);

    assoc_array_destroy(&ass_arr_src);
    ck_assert_ptr_null(ass_arr_src);

    assoc_array_destroy(&ass_arr_dst);
    ck_assert_ptr_null(ass_arr_src);     
}
END_TEST

START_TEST(null_action)
{
    assoc_array_error_t rc;

    data_t src_arr[] = { { "a", 10 }, { "d", -20 }, { "c", 1 }, { "b", -5 }, { "f", 0 }, { "e", 40 } };
    size_t length_src = sizeof(src_arr) / sizeof(src_arr[0]);
    assoc_array_t ass_arr_src = NULL;
    
    //Создание и заполнение исходного массива
    {
        ass_arr_src = assoc_array_create();
        ck_assert_ptr_nonnull(ass_arr_src);

        rc = fill_arr(ass_arr_src, src_arr, length_src);

        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        ck_assert_ptr_nonnull(ass_arr_src);
    }

    rc = assoc_array_each(ass_arr_src, NULL, &ass_arr_src);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&ass_arr_src);
    ck_assert_ptr_null(ass_arr_src);    
}
END_TEST

START_TEST(null_arr)
{
    assoc_array_error_t rc;

    assoc_array_t arr = NULL;

    rc = assoc_array_each(arr, mul_value, NULL);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM); 
}
END_TEST

Suite *test_assoc_array_each(void)
{
    Suite *suite;
    TCase *tc_pos, *tc_neg;

    suite = suite_create("assoc_array_each");

    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, one_elem_arr_mul);
    tcase_add_test(tc_pos, two_elems_arr_mul);
    tcase_add_test(tc_pos, six_elems_arr_mul);
    tcase_add_test(tc_pos, one_elem_arr_sqr);
    tcase_add_test(tc_pos, two_elems_arr_sqr);
    tcase_add_test(tc_pos, six_elems_arr_sqr);

    suite_add_tcase(suite, tc_pos);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_pos, null_arr);
    tcase_add_test(tc_pos, null_action);

    suite_add_tcase(suite, tc_neg);

    return suite;
}