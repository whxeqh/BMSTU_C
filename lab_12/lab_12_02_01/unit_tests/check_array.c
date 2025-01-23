#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "array.h"
#include "check_array.h"

/*
 * ----------------------------------------------------------------------------------------------------------------------
 *
 * Юнит тесты циклического сдвига  
 *
 * ----------------------------------------------------------------------------------------------------------------------
*/

// Массив из одного элемента
START_TEST (test_one_elem_array)
{
    int src_arr[] = {1};
    int dst_arr[] = {1};
    size_t length = sizeof(src_arr) / sizeof(src_arr[0]);

    size_t shift = 2;

    cyclic_shift(src_arr, length, shift);

    ck_assert_mem_eq(src_arr, dst_arr, length * sizeof(int));
}
END_TEST

// Массив из двух элементов. Чётный сдвиг
START_TEST (test_two_elems_array_odd_shift)
{
    int src_arr[] = {1, 2};
    int dst_arr[] = {1, 2};
    size_t length = sizeof(src_arr) / sizeof(src_arr[0]);

    size_t shift = 2;

    cyclic_shift(src_arr, length, shift);

    ck_assert_mem_eq(src_arr, dst_arr, length * sizeof(int));
}
END_TEST

// Массив из двух элементов. Нечётный сдвиг
START_TEST (test_two_elems_arrayeven_shift)
{
    int src_arr[] = {1, 2};
    int dst_arr[] = {2, 1};
    size_t length = sizeof(src_arr) / sizeof(src_arr[0]);

    size_t shift = 3;

    cyclic_shift(src_arr, length, shift);

    ck_assert_mem_eq(src_arr, dst_arr, length * sizeof(int));
}
END_TEST

// Массив из нечетного количества элементов, сдвиг на 0
START_TEST (test_three_elems_array_zero_shift)
{
    int src_arr[] = {1, 2, 3};
    int dst_arr[] = {1, 2, 3};
    size_t length = sizeof(src_arr) / sizeof(src_arr[0]);

    size_t shift = 0;

    cyclic_shift(src_arr, length, shift);

    ck_assert_mem_eq(src_arr, dst_arr, length * sizeof(int));
}
END_TEST

// Массив из нечетного количества элементов, сдвиг на кол-во элементов в массиве
START_TEST (test_five_elems_array_five_shifts)
{
    int src_arr[] = {1, 2, 3, 4, 5};
    int dst_arr[] = {1, 2, 3, 4, 5};
    size_t length = sizeof(src_arr) / sizeof(src_arr[0]);

    size_t shift = length;

    cyclic_shift(src_arr, length, shift);

    ck_assert_mem_eq(src_arr, dst_arr, length * sizeof(int));
}
END_TEST

//Массив из четного количества элементов, сдвиг на 1 элемент больше размера массива
START_TEST (test_five_elems_array_six_shifts)
{
    int src_arr[] = {1, 2, 3, 4, 5};
    int dst_arr[] = {2, 3, 4, 5, 1};
    size_t length = sizeof(src_arr) / sizeof(src_arr[0]);

    size_t shift = length + 1;

    cyclic_shift(src_arr, length, shift);

    ck_assert_mem_eq(src_arr, dst_arr, length * sizeof(int));
}
END_TEST

// Массив из четного количества элементов, сдвиг на 2 элемента больше размера массива
START_TEST (test_five_elems_array_seven_shifts)
{
    int src_arr[] = {1, 2, 3, 4, 5};
    int dst_arr[] = {3, 4, 5, 1, 2};
    size_t length = sizeof(src_arr) / sizeof(src_arr[0]);

    size_t shift = length + 2;

    cyclic_shift(src_arr, length, shift);

    ck_assert_mem_eq(src_arr, dst_arr, length * sizeof(int));
}
END_TEST

// Массив из четного количества элементов, сдвиг на 3 элемент больше размера массива
START_TEST (test_five_elems_array_eight_shifts)
{
    int src_arr[] = {1, 2, 3, 4, 5};
    int dst_arr[] = {4, 5, 1, 2, 3};
    size_t length = sizeof(src_arr) / sizeof(src_arr[0]);

    size_t shift = length + 3;

    cyclic_shift(src_arr, length, shift);

    ck_assert_mem_eq(src_arr, dst_arr, length * sizeof(int));
}
END_TEST

// Массив из четного количества элементов, сдвиг на 4 элемент больше размера массива
START_TEST (test_five_elems_array_nine_shifts)
{
    int src_arr[] = {1, 2, 3, 4, 5};
    int dst_arr[] = {5, 1, 2, 3, 4};
    size_t length = sizeof(src_arr) / sizeof(src_arr[0]);

    size_t shift = length + 4;

    cyclic_shift(src_arr, length, shift);

    ck_assert_mem_eq(src_arr, dst_arr, length * sizeof(int));
}
END_TEST

Suite* check_cyclic_shift(void)
{
    Suite *suite;
    TCase *tc_pos;

    suite = suite_create("cyclic_shift");
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_one_elem_array);
    tcase_add_test(tc_pos, test_two_elems_array_odd_shift);
    tcase_add_test(tc_pos, test_two_elems_arrayeven_shift);
    tcase_add_test(tc_pos, test_three_elems_array_zero_shift);
    tcase_add_test(tc_pos, test_five_elems_array_five_shifts);
    tcase_add_test(tc_pos, test_five_elems_array_six_shifts);
    tcase_add_test(tc_pos, test_five_elems_array_seven_shifts);
    tcase_add_test(tc_pos, test_five_elems_array_eight_shifts);
    tcase_add_test(tc_pos, test_five_elems_array_nine_shifts);
    suite_add_tcase(suite, tc_pos);

    return suite;
}

/*
 * ----------------------------------------------------------------------------------------------------------------------
 *
 * Юнит тесты для фильтрации массива (полные квадраты)
 *
 * ----------------------------------------------------------------------------------------------------------------------
*/


// Тест 2: Массив без чисел, являющихся полными квадратами
START_TEST(test_no_squares)
{
    int src_arr[] = {2, 3, 5, 6, 7, 8, 10};
    size_t src_len = sizeof(src_arr) / sizeof(src_arr[0]);
    size_t dst_len = 0;

    int rc = filter(src_arr, src_len, NULL, &dst_len);
    ck_assert_int_eq(rc, 0);
    ck_assert_int_eq(dst_len, 0);
}
END_TEST

// Массив из одного элемента, полный квадрат
START_TEST(test_one_elem_square)
{
    int src_arr[] = {4};
    int dst_arr[] = {4};  
    size_t src_len = sizeof(src_arr) / sizeof(src_arr[0]);
    size_t dst_len = sizeof(dst_arr) / sizeof(dst_arr[0]);

    int *filter_arr = NULL;
    size_t filter_len = 0;

    int rc = filter(src_arr, src_len, NULL, &filter_len);
    ck_assert_int_eq(rc, 1);
    ck_assert_int_eq(filter_len, dst_len);
    
    filter_arr = malloc(sizeof(int) * filter_len);
    ck_assert_ptr_nonnull(filter_arr);

    rc = filter(src_arr, src_len, filter_arr, &filter_len);
    ck_assert_int_eq(rc, 0);

    ck_assert_mem_eq(dst_arr, filter_arr, dst_len * sizeof(int));

    free(filter_arr);
}
END_TEST
// Тест 3: Массив с полными квадратами
START_TEST(test_with_squares)
{
    int src_arr[] = {1, 4, 9, 16, 25};
    int dst_arr[] = {1, 4, 9, 16, 25};
    size_t src_len = sizeof(src_arr) / sizeof(src_arr[0]);
    size_t dst_len = sizeof(dst_arr) / sizeof(dst_arr[0]);

    int *filter_arr = NULL;
    size_t filter_len = 0;

    int rc = filter(src_arr, src_len, NULL, &filter_len);
    ck_assert_int_eq(rc, 1);
    ck_assert_int_eq(filter_len, dst_len);

    filter_arr = malloc(sizeof(int) * dst_len);
    ck_assert_ptr_nonnull(filter_arr);

    rc = filter(src_arr, src_len, filter_arr, &dst_len);
    ck_assert_int_eq(rc, 0);
    ck_assert_mem_eq(dst_arr, filter_arr, dst_len * sizeof(int));

    free(filter_arr);
}
END_TEST

// Тест 4: Массив с несколькими полными квадратами и другими числами
START_TEST(test_mixed_squares)
{
    int src_arr[] = {1, 3, 4, 7, 9, 10, 16};
    int dst_arr[] = {1, 4, 9, 16};
    size_t src_len = sizeof(src_arr) / sizeof(src_arr[0]);
    size_t dst_len = sizeof(dst_arr) / sizeof(dst_arr[0]);

    int *filter_arr = NULL;
    size_t filter_len = 0;

    int rc = filter(src_arr, src_len, NULL, &filter_len);
    ck_assert_int_eq(rc, 1);
    ck_assert_int_eq(filter_len, dst_len);

    filter_arr = malloc(sizeof(int) * dst_len);
    ck_assert_ptr_nonnull(filter_arr);

    rc = filter(src_arr, src_len, filter_arr, &dst_len);
    ck_assert_int_eq(rc, 0);
    ck_assert_mem_eq(dst_arr, filter_arr, dst_len * sizeof(int));

    free(filter_arr);
}
END_TEST

// Тест 6: Массив с 0
START_TEST(test_zero_number)
{
    int src_arr[] = {0, 1, 2, 3, 4};
    int dst_arr[] = {0, 1, 4};
    size_t src_len = sizeof(src_arr) / sizeof(src_arr[0]);
    size_t dst_len = sizeof(dst_arr) / sizeof(dst_arr[0]);

    int *filter_arr = NULL;
    size_t filter_len = 0;

    int rc = filter(src_arr, src_len, NULL, &filter_len);
    ck_assert_int_eq(rc, 1);
    ck_assert_int_eq(filter_len, dst_len);

    filter_arr = malloc(sizeof(int) * dst_len);
    ck_assert_ptr_nonnull(filter_arr);

    rc = filter(src_arr, src_len, filter_arr, &dst_len);
    ck_assert_int_eq(rc, 0);
    ck_assert_mem_eq(dst_arr, filter_arr, dst_len * sizeof(int));

    free(filter_arr);
}
END_TEST

// Тест 7: Массив нужного размера передается сразу
START_TEST(test_already)
{
    int src_arr[] = {0, 1, 2, 3, 4};
    int dst_arr[] = {0, 1, 4};
    size_t src_len = sizeof(src_arr) / sizeof(src_arr[0]);
    size_t dst_len = sizeof(dst_arr) / sizeof(dst_arr[0]);
    
    int rc;

    int *filter_arr = NULL;

    filter_arr = malloc(sizeof(int) * dst_len);
    ck_assert_ptr_nonnull(filter_arr);

    rc = filter(src_arr, src_len, filter_arr, &dst_len);
    ck_assert_int_eq(rc, 0);
    ck_assert_mem_eq(dst_arr, filter_arr, dst_len * sizeof(int));

    free(filter_arr);
}
END_TEST

Suite* check_filter(void)
{
    Suite *suite;
    TCase *tc_pos;

    suite = suite_create("filter");
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_no_squares);
    tcase_add_test(tc_pos, test_one_elem_square);
    tcase_add_test(tc_pos, test_with_squares);
    tcase_add_test(tc_pos, test_mixed_squares);
    tcase_add_test(tc_pos, test_zero_number);
    tcase_add_test(tc_pos, test_already);
    suite_add_tcase(suite, tc_pos);

    return suite;
}