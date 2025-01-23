#include <stdlib.h>
#include <stdbool.h>
#include "check_array.h"
#include "array.h"
#include "errors.h"

bool is_arrays_equal(const void *pfirst, const size_t length_first, const void *psecond, const size_t length_second, \
                     const size_t el_size, int (*uni_cmp )(const void *left, const void *right))
{
    if (length_first != length_second)
        return false;

    const char *pcur_first = (const char *) pfirst;
    const char *pcur_second = (const char *) psecond;
    const char *pend = pcur_first + length_first * el_size;

    for (; pcur_first < pend; pcur_first += el_size, pcur_second += el_size)
        if (uni_cmp(pcur_first, pcur_second) != 0)
           return false;
    return true;
}       

int cmp_uni_char(const void *left, const void *right)
{
    const char *pl = left;
    const char *pr = right;

    return *pl - *pr;
}

int cmp_uni_double(const void *left, const void *right)
{
    const double *pl = left;
    const double *pr = right;

    return (*pl > *pr) - (*pl < *pr);
}

/*
 * ----------------------------------------------------------------------------------------------------------------------
 *
 * Юнит тесты бин поиска  
 *
 * ----------------------------------------------------------------------------------------------------------------------
*/

// Массив из одного элемента
START_TEST (test_one_elem_array)
{
    int arr[] = {1};
    size_t length = sizeof(arr) / sizeof(arr[0]);

    int *pkey = arr;
    int *pbeg = arr;
    int *pend = arr + length;

    void *pos = bynary_search(pbeg, pend, pkey, sizeof(*pkey), cmp_uni_int);

    ck_assert_ptr_eq(pos, pkey);
}
END_TEST

// Массив из двух элементов. Нужно найти первый
START_TEST (test_two_elems_array_find_first_elem)
{
    int arr[] = {1, 2};
    size_t length = sizeof(arr) / sizeof(arr[0]);

    int *pkey = arr;
    int *pbeg = arr;
    int *pend = arr + length;
    
    void *pos = bynary_search(pbeg, pend, pkey, sizeof(*pkey), cmp_uni_int);

    ck_assert_ptr_eq(pos, pkey);
}
END_TEST

// Массив из двух элементов. Нужно найти второй
START_TEST (test_two_elems_array_find_last_elem)
{
    int arr[] = {1, 2};const 
    size_t length = sizeof(arr) / sizeof(arr[0]);

    int *pkey = arr;
    int *pbeg = arr;
    int *pend = arr + length;

    void *pos = bynary_search(pbeg, pend, pkey, sizeof(*pkey), cmp_uni_int);
    ck_assert_ptr_eq(pos, pkey);
}
END_TEST

// Массив из нечетного количества элементов, нужно найти элемент с четным индексом
START_TEST (test_odd_elems_array_find_even_pos_elem)
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    size_t length = sizeof(arr) / sizeof(arr[0]);

    int *pkey = &arr[2];
    int *pbeg = arr;
    int *pend = arr + length;

    void *pos = bynary_search(pbeg, pend, pkey, sizeof(*pkey), cmp_uni_int);
    ck_assert_ptr_eq(pos, pkey);
}
END_TEST

// Массив из нечетного количества элементов, нужно найти элемент с нечетным индексом
START_TEST (test_odd_elems_array_find_odd_pos_elem)
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    size_t length = sizeof(arr) / sizeof(arr[0]);

    int *pkey = &arr[5];
    int *pbeg = arr;
    int *pend = arr + length;

    void *pos = bynary_search(pbeg, pend, pkey, sizeof(*pkey), cmp_uni_int);

    ck_assert_ptr_eq(pos, pkey);
}
END_TEST

//Массив из четного количества элементов, нужно найти элемент, находящийся в середине массива
START_TEST (test_odd_elems_array_find_mid_pos_elem)
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    size_t length = sizeof(arr) / sizeof(arr[0]);

    int *pkey = &arr[3];
    int *pbeg = arr;
    int *pend = arr + length;

    void *pos = bynary_search(pbeg, pend, pkey, sizeof(*pkey), cmp_uni_int);

    ck_assert_ptr_eq(pos, pkey);
}
END_TEST

// Массив из четного количества элементов, нужно найти элемент под четным индексом
START_TEST (test_even_elems_array_find_even_elem)
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    size_t length = sizeof(arr) / sizeof(arr[0]);

    int *pkey = &arr[4];
    int *pbeg = arr;
    int *pend = arr + length;

    void *pos = bynary_search(pbeg, pend, pkey, sizeof(*pkey), cmp_uni_int);

    ck_assert_ptr_eq(pos, pkey);
}
END_TEST

// Массив из четного количества элементов, нужно найти элемент под нечетным индексом
START_TEST (test_even_elems_array_find_odd_pos_elem)
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t length = sizeof(arr) / sizeof(arr[0]);

    int *pkey = &arr[9];
    int *pbeg = arr;
    int *pend = arr + length;

    void *pos = bynary_search(pbeg, pend, pkey, sizeof(*pkey), cmp_uni_int);

    ck_assert_ptr_eq(pos, pkey);
}
END_TEST

Suite* bynary_search_suite(void)
{
    Suite *suite;
    TCase *tc_pos;

    suite = suite_create("bynary_search");
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_one_elem_array);
    tcase_add_test(tc_pos, test_two_elems_array_find_first_elem);
    tcase_add_test(tc_pos, test_two_elems_array_find_last_elem);
    tcase_add_test(tc_pos, test_odd_elems_array_find_even_pos_elem);
    tcase_add_test(tc_pos, test_odd_elems_array_find_odd_pos_elem);
    tcase_add_test(tc_pos, test_odd_elems_array_find_mid_pos_elem);
    tcase_add_test(tc_pos, test_even_elems_array_find_even_elem);
    tcase_add_test(tc_pos, test_even_elems_array_find_odd_pos_elem);
    
    suite_add_tcase(suite, tc_pos);

    return suite;
}

/*
 * ----------------------------------------------------------------------------------------------------------------------
 *
 * Юнит тесты сортировки целых чисел  
 *
 * ----------------------------------------------------------------------------------------------------------------------
*/

// Одно число
START_TEST (test_one_elem_array_sort)
{
    int arr[] = {1};
    int arr_sorted[] = {1};
    
    size_t length_sorted = sizeof(arr_sorted) / sizeof(arr_sorted[0]);
    size_t length = sizeof(arr) / sizeof(arr[0]);

    mysort(arr, length, sizeof(*arr), cmp_uni_int);

    bool equal = is_arrays_equal(arr, length, arr_sorted, length_sorted, sizeof(arr[0]), cmp_uni_int);

    ck_assert_int_eq(equal, true);
}
END_TEST

// Два числа упорядочены сразу
START_TEST (test_two_elems_sorted_at_once)
{
    int arr[] = {1, 2};
    int arr_sorted[] = {1, 2};

    size_t length_sorted = sizeof(arr_sorted) / sizeof(arr_sorted[0]);
    size_t length = sizeof(arr) / sizeof(arr[0]);

    mysort(arr, length, sizeof(*arr), cmp_uni_int);

    bool equal = is_arrays_equal(arr, length, arr_sorted, length_sorted, sizeof(arr[0]), cmp_uni_int);

    ck_assert_int_eq(equal, true);
}
END_TEST

// Два числа не упорядочены сразу
START_TEST (test_two_elems_not_sorted_at_once)
{
    int arr[] = {2, 1};
    int arr_sorted[] = {1, 2};
    
    size_t length_sorted = sizeof(arr_sorted) / sizeof(arr_sorted[0]);
    size_t length = sizeof(arr) / sizeof(arr[0]);

    mysort(arr, length, sizeof(*arr), cmp_uni_int);

    bool equal = is_arrays_equal(arr, length, arr_sorted, length_sorted, sizeof(arr[0]), cmp_uni_int);

    ck_assert_int_eq(equal, true);
}
END_TEST

// Числа упорядочены по убыванию
START_TEST (test_elems_in_descending_order)
{
    int arr[] = {5, 4, 3, 2, 1};
    int arr_sorted[] = {1, 2, 3, 4, 5};
     
    size_t length_sorted = sizeof(arr_sorted) / sizeof(arr_sorted[0]);
    size_t length = sizeof(arr) / sizeof(arr[0]);

    mysort(arr, length, sizeof(*arr), cmp_uni_int);

    bool equal = is_arrays_equal(arr, length, arr_sorted, length_sorted, sizeof(arr[0]), cmp_uni_int);

    ck_assert_int_eq(equal, true);
}
END_TEST

// Числа упорядочены по возрастанию
START_TEST (test_elems_in_increasing_order)
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int arr_sorted[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    size_t length_sorted = sizeof(arr_sorted) / sizeof(arr_sorted[0]);
    size_t length = sizeof(arr) / sizeof(arr[0]);

    mysort(arr, length, sizeof(*arr), cmp_uni_int);

    bool equal = is_arrays_equal(arr, length, arr_sorted, length_sorted, sizeof(arr[0]), cmp_uni_int);

    ck_assert_int_eq(equal, true);
}
END_TEST

// Числа упорядочены сначала по убыванию, потом по возрастанию
START_TEST (test_elems_are_ordered_first_in_descending_order_then_in_increasing_order)
{
    int arr[] = {8, 7, 6, 5, 4, 12, 13, 15};
    int arr_sorted[] = {4, 5, 6, 7, 8, 12, 13, 15};
    
    size_t length_sorted = sizeof(arr_sorted) / sizeof(arr_sorted[0]);
    size_t length = sizeof(arr) / sizeof(arr[0]);

    mysort(arr, length, sizeof(*arr), cmp_uni_int);

    bool equal = is_arrays_equal(arr, length, arr_sorted, length_sorted, sizeof(arr[0]), cmp_uni_int);

    ck_assert_int_eq(equal, true);
}
END_TEST

// Числа упорядочены сначала по возрастанию, потом по убыванию
START_TEST (test_elems_are_ordered_first_in_increasing_order_then_in_descending_order)
{
    int arr[] = {4, 5, 6, 7, 8, 2, -1, -5};
    int arr_sorted[] = {-5, -1, 2, 4, 5, 6, 7, 8};
    
    size_t length_sorted = sizeof(arr_sorted) / sizeof(arr_sorted[0]);
    size_t length = sizeof(arr) / sizeof(arr[0]);

    mysort(arr, length, sizeof(*arr), cmp_uni_int);

    bool equal = is_arrays_equal(arr, length, arr_sorted, length_sorted, sizeof(arr[0]), cmp_uni_int);

    ck_assert_int_eq(equal, true);
}
END_TEST

// Отрицательные числа
START_TEST (test_negative_elems)
{
    int arr[] = {-8, -7, -6, -5, -4, -12, -13, -15};
    int arr_sorted[] = {-15, -13, -12, -8, -7, -6, -5, -4};
    
    size_t length_sorted = sizeof(arr_sorted) / sizeof(arr_sorted[0]);
    size_t length = sizeof(arr) / sizeof(arr[0]);

    mysort(arr, length, sizeof(*arr), cmp_uni_int);

    bool equal = is_arrays_equal(arr, length, arr_sorted, length_sorted, sizeof(arr[0]), cmp_uni_int);

    ck_assert_int_eq(equal, true);
}
END_TEST

// Сто чисел
START_TEST (test_one_hundred_elems)
{
    int arr[] = {
                 1, 2, 3, 4, 5, 6, 7, 8, 9, 0,\
                 1, 2, 3, 4, 5, 6, 7, 8, 9, 0,\
                 1, 2, 3, 4, 5, 6, 7, 8, 9, 0,\
                 1, 2, 3, 4, 5, 6, 7, 8, 9, 0,\
                 1, 2, 3, 4, 5, 6, 7, 8, 9, 0,\
                 1, 2, 3, 4, 5, 6, 7, 8, 9, 0,\
                 1, 2, 3, 4, 5, 6, 7, 8, 9, 0,\
                 1, 2, 3, 4, 5, 6, 7, 8, 9, 0,\
                 1, 2, 3, 4, 5, 6, 7, 8, 9, 0,\
                 1, 2, 3, 4, 5, 6, 7, 8, 9, 0
                };
    int arr_sorted[] = {
                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,\
                 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,\
                 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,\
                 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,\
                 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,\
                 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,\
                 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,\
                 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,\
                 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,\
                 9, 9, 9, 9, 9, 9, 9, 9, 9, 9
                };
    
    size_t length_sorted = sizeof(arr_sorted) / sizeof(arr_sorted[0]);
    size_t length = sizeof(arr) / sizeof(arr[0]);

    mysort(arr, length, sizeof(*arr), cmp_uni_int);

    bool equal = is_arrays_equal(arr, length, arr_sorted, length_sorted, sizeof(arr[0]), cmp_uni_int);

    ck_assert_int_eq(equal, true);
}
END_TEST

Suite* mysort_int_suite(void)
{
    Suite *suite;
    TCase *tc_pos;

    suite = suite_create("mysort_int");
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_one_elem_array_sort);
    tcase_add_test(tc_pos, test_two_elems_sorted_at_once);
    tcase_add_test(tc_pos, test_two_elems_not_sorted_at_once);
    tcase_add_test(tc_pos, test_elems_in_descending_order);
    tcase_add_test(tc_pos, test_elems_in_increasing_order);
    tcase_add_test(tc_pos, test_elems_are_ordered_first_in_descending_order_then_in_increasing_order);
    tcase_add_test(tc_pos, test_elems_are_ordered_first_in_increasing_order_then_in_descending_order);
    tcase_add_test(tc_pos, test_negative_elems);
    tcase_add_test(tc_pos, test_one_hundred_elems);
    
    suite_add_tcase(suite, tc_pos);

    return suite;
}


/*
 * ----------------------------------------------------------------------------------------------------------------------
 *
 * Юнит тесты сортировки вещественных чисел. Позитивы  
 *
 * ----------------------------------------------------------------------------------------------------------------------
*/

// Одно число
START_TEST (test_double_one_elem_array_sort)
{
    double arr[] = {1.500000000000001};
    double arr_sorted[] = {1.500000000000001};
    
    size_t length_sorted = sizeof(arr_sorted) / sizeof(arr_sorted[0]);
    size_t length = sizeof(arr) / sizeof(arr[0]);

    mysort(arr, length, sizeof(*arr), cmp_uni_double);

    bool equal = is_arrays_equal(arr, length, arr_sorted, length_sorted, sizeof(arr[0]), cmp_uni_double);

    ck_assert_int_eq(equal, true);
}
END_TEST

// Два числа упорядочены сразу
START_TEST (test_double_two_elems_sorted_at_once)
{
    double arr[] = {1.1, 2.3e10};
    double arr_sorted[] = {1.1, 2.3e10};

    size_t length_sorted = sizeof(arr_sorted) / sizeof(arr_sorted[0]);
    size_t length = sizeof(arr) / sizeof(arr[0]);

    mysort(arr, length, sizeof(*arr), cmp_uni_double);

    bool equal = is_arrays_equal(arr, length, arr_sorted, length_sorted, sizeof(arr[0]), cmp_uni_double);

    ck_assert_int_eq(equal, true);
}
END_TEST

// Два числа не упорядочены сразу
START_TEST (test_double_two_elems_not_sorted_at_once)
{
    double arr[] = {2.9, 1.4};
    double arr_sorted[] = {1.4, 2.9};
    
    size_t length_sorted = sizeof(arr_sorted) / sizeof(arr_sorted[0]);
    size_t length = sizeof(arr) / sizeof(arr[0]);

    mysort(arr, length, sizeof(*arr), cmp_uni_double);

    bool equal = is_arrays_equal(arr, length, arr_sorted, length_sorted, sizeof(arr[0]), cmp_uni_double);

    ck_assert_int_eq(equal, true);
}
END_TEST

// Числа упорядочены по убыванию
START_TEST (test_double_elems_in_descending_order)
{
    double arr[] = {5.55, 4.44, 3.33, 2.22, 1.11};
    double arr_sorted[] = {1.11, 2.22, 3.33, 4.44, 5.55};
     
    size_t length_sorted = sizeof(arr_sorted) / sizeof(arr_sorted[0]);
    size_t length = sizeof(arr) / sizeof(arr[0]);

    mysort(arr, length, sizeof(*arr), cmp_uni_double);

    bool equal = is_arrays_equal(arr, length, arr_sorted, length_sorted, sizeof(arr[0]), cmp_uni_double);

    ck_assert_int_eq(equal, true);
}
END_TEST

// Числа упорядочены по возрастанию
START_TEST (test_double_elems_in_increasing_order)
{
    double arr[] = {1.1, 2.2, 3.3, 4.4, 5.5};
    double arr_sorted[] = {1.1, 2.2, 3.3, 4.4, 5.5};
    
    size_t length_sorted = sizeof(arr_sorted) / sizeof(arr_sorted[0]);
    size_t length = sizeof(arr) / sizeof(arr[0]);

    mysort(arr, length, sizeof(*arr), cmp_uni_double);

    bool equal = is_arrays_equal(arr, length, arr_sorted, length_sorted, sizeof(arr[0]), cmp_uni_double);

    ck_assert_int_eq(equal, true);
}
END_TEST

// Числа упорядочены сначала по убыванию, потом по возрастанию
START_TEST (test_double_elems_are_ordered_first_in_descending_order_then_in_increasing_order)
{
    double arr[] = {8.1, 7.7, 6.6, 5.5, 4.4, 12.12, 13.13, 15.15};
    double arr_sorted[] = {4.4, 5.5, 6.6, 7.7, 8.1, 12.12, 13.13, 15.15};
    
    size_t length_sorted = sizeof(arr_sorted) / sizeof(arr_sorted[0]);
    size_t length = sizeof(arr) / sizeof(arr[0]);

    mysort(arr, length, sizeof(*arr), cmp_uni_double);

    bool equal = is_arrays_equal(arr, length, arr_sorted, length_sorted, sizeof(arr[0]), cmp_uni_double);

    ck_assert_int_eq(equal, true);
}
END_TEST

// Числа упорядочены сначала по возрастанию, потом по убыванию
START_TEST (test_double_elems_are_ordered_first_in_increasing_order_then_in_descending_order)
{
    double arr[] = {4.0, 5.0, 6.0, 7.0, 8.0, 2.0, -1.1, -5.5};
    double arr_sorted[] = {-5.5, -1.1, 2.0, 4.0, 5.0, 6.0, 7.0, 8.0};
    
    size_t length_sorted = sizeof(arr_sorted) / sizeof(arr_sorted[0]);
    size_t length = sizeof(arr) / sizeof(arr[0]);

    mysort(arr, length, sizeof(*arr), cmp_uni_double);

    bool equal = is_arrays_equal(arr, length, arr_sorted, length_sorted, sizeof(arr[0]), cmp_uni_double);

    ck_assert_int_eq(equal, true);
}
END_TEST

// Отрицательные числа
START_TEST (test_double_negative_elems)
{
    double arr[] = {-8.88, -7.77, -6.66, -5.55, -4.44, -12.12, -13.13, -15.15};
    double arr_sorted[] = {-15.15, -13.13, -12.12, -8.88, -7.77, -6.66, -5.55, -4.44};
    
    size_t length_sorted = sizeof(arr_sorted) / sizeof(arr_sorted[0]);
    size_t length = sizeof(arr) / sizeof(arr[0]);

    mysort(arr, length, sizeof(*arr), cmp_uni_double);

    bool equal = is_arrays_equal(arr, length, arr_sorted, length_sorted, sizeof(arr[0]), cmp_uni_double);

    ck_assert_int_eq(equal, true);
}
END_TEST

/*
 * ----------------------------------------------------------------------------------------------------------------------
 *
 * Юнит тесты сортировки вещественных чисел. Негативы  
 *
 * ----------------------------------------------------------------------------------------------------------------------
*/

// Одно число
START_TEST (test_neg_double_one_elem_array_sort)
{
    double arr[] = {1.50000000000001};
    double arr_sorted[] = {1.5000000000000012};
    
    size_t length_sorted = sizeof(arr_sorted) / sizeof(arr_sorted[0]);
    size_t length = sizeof(arr) / sizeof(arr[0]);

    mysort(arr, length, sizeof(*arr), cmp_uni_double);

    bool equal = is_arrays_equal(arr, length, arr_sorted, length_sorted, sizeof(arr[0]), cmp_uni_double);

    ck_assert_int_eq(equal, false);
}
END_TEST

// Два числа упорядочены сразу
START_TEST (test_neg_double_two_elems_sorted_at_once)
{
    double arr[] = {1, 4.0000000001};
    double arr_sorted[] = {1, 4};

    printf("%.20lf %.20lf\n", arr[0], arr_sorted[0]);

    size_t length_sorted = sizeof(arr_sorted) / sizeof(arr_sorted[0]);
    size_t length = sizeof(arr) / sizeof(arr[0]);

    mysort(arr, length, sizeof(*arr), cmp_uni_double);

    bool equal = is_arrays_equal(arr, length, arr_sorted, length_sorted, sizeof(arr[0]), cmp_uni_double);

    ck_assert_int_eq(equal, false);
}
END_TEST

// Два числа не упорядочены сразу
START_TEST (test_neg_double_two_elems_not_sorted_at_once)
{
    double arr[] = {2.9e-10, 1.4};
    double arr_sorted[] = {1.4, 2.9e-11};
    
    size_t length_sorted = sizeof(arr_sorted) / sizeof(arr_sorted[0]);
    size_t length = sizeof(arr) / sizeof(arr[0]);

    mysort(arr, length, sizeof(*arr), cmp_uni_double);

    bool equal = is_arrays_equal(arr, length, arr_sorted, length_sorted, sizeof(arr[0]), cmp_uni_double);

    ck_assert_int_eq(equal, false);
}
END_TEST

Suite* mysort_double_suite(void)
{
    Suite *suite;
    TCase *tc_pos, *tc_neg;

    suite = suite_create("mysort_double");
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_double_one_elem_array_sort);
    tcase_add_test(tc_pos, test_double_two_elems_sorted_at_once);
    tcase_add_test(tc_pos, test_double_two_elems_not_sorted_at_once);
    tcase_add_test(tc_pos, test_double_elems_in_descending_order);
    tcase_add_test(tc_pos, test_double_elems_in_increasing_order);
    tcase_add_test(tc_pos, test_double_elems_are_ordered_first_in_descending_order_then_in_increasing_order);
    tcase_add_test(tc_pos, test_double_elems_are_ordered_first_in_increasing_order_then_in_descending_order);
    tcase_add_test(tc_pos, test_double_negative_elems);
    
    suite_add_tcase(suite, tc_pos);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_neg_double_one_elem_array_sort);
    tcase_add_test(tc_neg, test_neg_double_two_elems_sorted_at_once);
    tcase_add_test(tc_neg, test_neg_double_two_elems_not_sorted_at_once);

    suite_add_tcase(suite, tc_neg);
    

    return suite;
}


/*
 * ----------------------------------------------------------------------------------------------------------------------
 *
 * Юнит тесты сортировки массива символов  
 *
 * ----------------------------------------------------------------------------------------------------------------------
*/

//Один символ
START_TEST (test_one_letter)
{
    char arr[] = "a";
    char arr_sorted[] = "a";

    mysort(arr, strlen(arr), sizeof(arr[0]), cmp_uni_char);

    bool equal = is_arrays_equal(arr, strlen(arr), arr_sorted, strlen(arr_sorted), sizeof(arr[0]), cmp_uni_char);

    ck_assert_int_eq(equal, true);
}
END_TEST

//Два отсортированных символа
START_TEST (test_two_letters_sorted_at_once)
{
    char arr[] = "ab";
    char arr_sorted[] = "ab";

    mysort(arr, strlen(arr), sizeof(arr[0]), cmp_uni_char);
   
    bool equal = is_arrays_equal(arr, strlen(arr), arr_sorted, strlen(arr_sorted), sizeof(arr[0]), cmp_uni_char);

    ck_assert_int_eq(equal, true);
}
END_TEST

//Два не отсортированных символа
START_TEST (test_two_letters_not_sorted_at_once)
{
    char arr[] = "ba";
    char arr_sorted[] = "ab";

    mysort(arr, strlen(arr), sizeof(arr[0]), cmp_uni_char);
    bool equal = is_arrays_equal(arr, strlen(arr), arr_sorted, strlen(arr_sorted), sizeof(arr[0]), cmp_uni_char);

    ck_assert_int_eq(equal, true);}
END_TEST

//Символы отсортированны по возрастанию
START_TEST (test_letters_in_increasing_order)
{
    char arr[] = "abcdef";
    char arr_sorted[] = "abcdef";

    mysort(arr, strlen(arr), sizeof(arr[0]), cmp_uni_char);
    
    bool equal = is_arrays_equal(arr, strlen(arr), arr_sorted, strlen(arr_sorted), sizeof(arr[0]), cmp_uni_char);

    ck_assert_int_eq(equal, true);
}
END_TEST

//Символы не отсортированны по возрастанию
START_TEST (test_letters_in_descending_order)
{
    char arr[] = "fedcba";
    char arr_sorted[] = "abcdef";

    mysort(arr, strlen(arr), sizeof(arr[0]), cmp_uni_char);
    
    bool equal = is_arrays_equal(arr, strlen(arr), arr_sorted, strlen(arr_sorted), sizeof(arr[0]), cmp_uni_char);

    ck_assert_int_eq(equal, true);
}
END_TEST

//Символы сначала упорядочены по убыванию, затем по возрастанию
START_TEST (test_letters_are_ordered_first_in_descending_order_then_in_increasing_order)
{
    char arr[] = "cbadef";
    char arr_sorted[] = "abcdef";

    mysort(arr, strlen(arr), sizeof(arr[0]), cmp_uni_char);

    bool equal = is_arrays_equal(arr, strlen(arr), arr_sorted, strlen(arr_sorted), sizeof(arr[0]), cmp_uni_char);

    ck_assert_int_eq(equal, true);
}
END_TEST

//Символы сначала упорядочены по возрастанию, затем по убыванию
START_TEST (test_letters_are_ordered_first_in_increasing_order_then_in_descending_order)
{
    char arr[] = "abcfed";
    char arr_sorted[] = "abcdef";

    mysort(arr, strlen(arr), sizeof(arr[0]), cmp_uni_char);
    
    bool equal = is_arrays_equal(arr, strlen(arr), arr_sorted, strlen(arr_sorted), sizeof(arr[0]), cmp_uni_char);

    ck_assert_int_eq(equal, true);
}
END_TEST

//Сто символов
START_TEST (test_one_hundred_letters)
{
    char arr[] = "\
abcdefghij\
abcdefghij\
abcdefghij\
abcdefghij\
abcdefghij\
abcdefghij\
abcdefghij\
abcdefghij\
abcdefghij\
abcdefghij";
    
    char arr_sorted[] = "\
aaaaaaaaaa\
bbbbbbbbbb\
cccccccccc\
dddddddddd\
eeeeeeeeee\
ffffffffff\
gggggggggg\
hhhhhhhhhh\
iiiiiiiiii\
jjjjjjjjjj";

    mysort(arr, strlen(arr), sizeof(arr[0]), cmp_uni_char);
    
    bool equal = is_arrays_equal(arr, strlen(arr), arr_sorted, strlen(arr_sorted), sizeof(arr[0]), cmp_uni_char);

    ck_assert_int_eq(equal, true);
}
END_TEST

Suite* mysort_char_suite(void)
{
    Suite *suite;
    TCase *tc_pos;

    suite = suite_create("mysort_char");
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_one_letter);
    tcase_add_test(tc_pos, test_two_letters_not_sorted_at_once);
    tcase_add_test(tc_pos, test_two_letters_sorted_at_once);
    tcase_add_test(tc_pos, test_letters_in_descending_order);
    tcase_add_test(tc_pos, test_letters_in_increasing_order);
    tcase_add_test(tc_pos, test_letters_are_ordered_first_in_increasing_order_then_in_descending_order);
    tcase_add_test(tc_pos, test_letters_are_ordered_first_in_descending_order_then_in_increasing_order);
    tcase_add_test(tc_pos, test_one_hundred_letters);

    suite_add_tcase(suite, tc_pos);

    return suite;    
}
/*
 * ----------------------------------------------------------------------------------------------------------------------
 *
 * Юнит тесты фильрации. Позитивы  
 *
 * ----------------------------------------------------------------------------------------------------------------------
*/

// Минимальный элемент перед максимальным  
START_TEST (test_min_elem_before_max)
{
    int arr[] = {2, 1, 6, 8, 7};
    int arr_expected[] = {6};
    size_t length_src = sizeof(arr) / sizeof(arr[0]);
    size_t length_expected = sizeof(arr_expected) / sizeof(arr_expected[0]);

    int *pb_src = arr;
    int *pe_src = arr + length_src;

    size_t cnt_elems = filter_arr_size(pb_src, pe_src);
    ck_assert_int_eq(cnt_elems, length_expected);

    int *pb_dst = malloc(cnt_elems * sizeof(int));
    ck_assert_ptr_nonnull(pb_dst);

    int *pe_dst = NULL;

    int rc = key(pb_src, pe_src, pb_dst, &pe_dst);
    
    ck_assert_int_eq(rc, OK);
    size_t length_dst = pe_dst - pb_dst;

    bool equal = is_arrays_equal(pb_dst, length_dst, arr_expected, length_expected, sizeof(arr[0]), cmp_uni_int);

    ck_assert_int_eq(equal, true);
    free(pb_dst);
}
END_TEST

// Минимальный элемент после максимального
START_TEST (test_min_elem_after_max)
{
    int arr[] = {8, 10, 4, 3, 2, 7};
    int arr_expected[] = {4, 3};
    size_t length_src = sizeof(arr) / sizeof(arr[0]);
    size_t length_expected = sizeof(arr_expected) / sizeof(arr_expected[0]);

    int *pb_src = arr;
    int *pe_src = arr + length_src;

    size_t cnt_elems = filter_arr_size(pb_src, pe_src);
    ck_assert_int_eq(cnt_elems, length_expected);

    int *pb_dst = malloc(cnt_elems * sizeof(int));
    ck_assert_ptr_nonnull(pb_dst);

    int *pe_dst = NULL;

    int rc = key(pb_src, pe_src, pb_dst, &pe_dst);
    
    ck_assert_int_eq(rc, OK);
    size_t length_dst = pe_dst - pb_dst;
    ck_assert_int_eq(length_dst, length_expected);

    bool equal = is_arrays_equal(pb_dst, length_dst, arr_expected, length_expected, sizeof(arr[0]), cmp_uni_int);

    ck_assert_int_eq(equal, true);
    free(pb_dst);
}
END_TEST

// Несколько минимальных и один максимальный элемент
START_TEST (test_several_min_elems_one_max)
{
    int arr[] = {4, 5, 6, 3, 3, 7, 8, 7, 6, 10, 6, 5, 3};
    int arr_expected[] = {3, 7, 8, 7, 6};
    size_t length_src = sizeof(arr) / sizeof(arr[0]);
    size_t length_expected = sizeof(arr_expected) / sizeof(arr_expected[0]);

    int *pb_src = arr;
    int *pe_src = arr + length_src;

    size_t cnt_elems = filter_arr_size(pb_src, pe_src);
    ck_assert_int_eq(cnt_elems, length_expected);

    int *pb_dst = malloc(cnt_elems * sizeof(int));
    ck_assert_ptr_nonnull(pb_dst);
    
    int *pe_dst = NULL;

    int rc = key(pb_src, pe_src, pb_dst, &pe_dst);
    
    ck_assert_int_eq(rc, OK);
    size_t length_dst = pe_dst - pb_dst;
    ck_assert_int_eq(length_dst, length_expected);

    bool equal = is_arrays_equal(pb_dst, length_dst, arr_expected, length_expected, sizeof(arr[0]), cmp_uni_int);

    ck_assert_int_eq(equal, true);
    free(pb_dst);
}
END_TEST

// Несколько максимальных и один минимальный элемент
START_TEST (test_several_max_elems_one_min) 
{
    int arr[] = {5, 4, 2, 4, 3, 5, 6, 6, 6, 3, 4, 6};
    int arr_expected[] = {4, 3, 5};
    size_t length_src = sizeof(arr) / sizeof(arr[0]);
    size_t length_expected = sizeof(arr_expected) / sizeof(arr_expected[0]);

    int *pb_src = arr;
    int *pe_src = arr + length_src;

    size_t cnt_elems = filter_arr_size(pb_src, pe_src);
    ck_assert_int_eq(cnt_elems, length_expected);

    int *pb_dst = malloc(cnt_elems * sizeof(int));
    ck_assert_ptr_nonnull(pb_dst);
    
    int *pe_dst = NULL;

    int rc = key(pb_src, pe_src, pb_dst, &pe_dst);
    
    ck_assert_int_eq(rc, OK);
    size_t length_dst = pe_dst - pb_dst;
    ck_assert_int_eq(length_dst, length_expected);

    bool equal = is_arrays_equal(pb_dst, length_dst, arr_expected, length_expected, sizeof(arr[0]), cmp_uni_int);

    ck_assert_int_eq(equal, true);
    free(pb_dst);
}
END_TEST

// Несколько минимальных и несколько максимальный элементов
START_TEST (test_several_min_elems_several_max)
{
    int arr[] = {4, 5, 3, 3, 3, 5, 6, 7, 7, 7, 7, 4};
    int arr_expected[] = {3, 3, 5, 6};
    size_t length_src = sizeof(arr) / sizeof(arr[0]);
    size_t length_expected = sizeof(arr_expected) / sizeof(arr_expected[0]);

    int *pb_src = arr;
    int *pe_src = arr + length_src;

    size_t cnt_elems = filter_arr_size(pb_src, pe_src);
    ck_assert_int_eq(cnt_elems, length_expected);

    int *pb_dst = malloc(cnt_elems * sizeof(int));
    ck_assert_ptr_nonnull(pb_dst);
    
    int *pe_dst = NULL;

    int rc = key(pb_src, pe_src, pb_dst, &pe_dst);
    
    ck_assert_int_eq(rc, OK);
    size_t length_dst = pe_dst - pb_dst;
    ck_assert_int_eq(length_dst, length_expected);

    bool equal = is_arrays_equal(pb_dst, length_dst, arr_expected, length_expected, sizeof(arr[0]), cmp_uni_int);

    ck_assert_int_eq(equal, true);
    free(pb_dst);
}
END_TEST

// Один элемент между минимальным и максимальным
START_TEST (test_one_elem_between_min_and_max)
{
    int arr[] = {4, 5, 2, 6, 8, 7};
    int arr_expected[] = {6};
    size_t length_src = sizeof(arr) / sizeof(arr[0]);
    size_t length_expected = sizeof(arr_expected) / sizeof(arr_expected[0]);

    int *pb_src = arr;
    int *pe_src = arr + length_src;

    size_t cnt_elems = filter_arr_size(pb_src, pe_src);
    ck_assert_int_eq(cnt_elems, length_expected);

    int *pb_dst = malloc(cnt_elems * sizeof(int));
    ck_assert_ptr_nonnull(pb_dst);
    
    int *pe_dst = NULL;

    int rc = key(pb_src, pe_src, pb_dst, &pe_dst);
    
    ck_assert_int_eq(rc, OK);
    size_t length_dst = pe_dst - pb_dst;
    ck_assert_int_eq(length_dst, length_expected);

    bool equal = is_arrays_equal(pb_dst, length_dst, arr_expected, length_expected, sizeof(arr[0]), cmp_uni_int);

    ck_assert_int_eq(equal, true);
    free(pb_dst);
}
END_TEST

// Минимальный элемент в начале массива
START_TEST (test_min_elem_at_the_begin_of_array)
{
    int arr[] = {2, 8, 7, 6, 10, 4, 3, 2};
    int arr_expected[] = {8, 7, 6};
    size_t length_src = sizeof(arr) / sizeof(arr[0]);
    size_t length_expected = sizeof(arr_expected) / sizeof(arr_expected[0]);

    int *pb_src = arr;
    int *pe_src = arr + length_src;

    size_t cnt_elems = filter_arr_size(pb_src, pe_src);
    ck_assert_int_eq(cnt_elems, length_expected);

    int *pb_dst = malloc(cnt_elems * sizeof(int));
    ck_assert_ptr_nonnull(pb_dst);
    
    int *pe_dst = NULL;

    int rc = key(pb_src, pe_src, pb_dst, &pe_dst);
    
    ck_assert_int_eq(rc, OK);
    size_t length_dst = pe_dst - pb_dst;
    ck_assert_int_eq(length_dst, length_expected);

    bool equal = is_arrays_equal(pb_dst, length_dst, arr_expected, length_expected, sizeof(arr[0]), cmp_uni_int);

    ck_assert_int_eq(equal, true);
    free(pb_dst);
}
END_TEST

// Минимальный элемент в конце массива (максимальный до минимального)
START_TEST (test_min_elem_at_the_end_of_array)
{
    int arr[] = {8, 7, 6, 10, 4, 3, 2};
    int arr_expected[] = {4, 3};
    size_t length_src = sizeof(arr) / sizeof(arr[0]);
    size_t length_expected = sizeof(arr_expected) / sizeof(arr_expected[0]);

    int *pb_src = arr;
    int *pe_src = arr + length_src;

    size_t cnt_elems = filter_arr_size(pb_src, pe_src);
    ck_assert_int_eq(cnt_elems, length_expected);

    int *pb_dst = malloc(cnt_elems * sizeof(int));
    ck_assert_ptr_nonnull(pb_dst);
    
    int *pe_dst = NULL;

    int rc = key(pb_src, pe_src, pb_dst, &pe_dst);
    
    ck_assert_int_eq(rc, OK);
    size_t length_dst = pe_dst - pb_dst;
    ck_assert_int_eq(length_dst, length_expected);

    bool equal = is_arrays_equal(pb_dst, length_dst, arr_expected, length_expected, sizeof(arr[0]), cmp_uni_int);

    ck_assert_int_eq(equal, true);
    free(pb_dst);
}
END_TEST

// Максимальный элемент в начале массива (минимальный после максимального)
START_TEST (test_max_elem_at_the_begin_of_array)
{
    int arr[] = {10, 5, 4, 3, 2, 8};
    int arr_expected[] = {5, 4, 3};
    size_t length_src = sizeof(arr) / sizeof(arr[0]);
    size_t length_expected = sizeof(arr_expected) / sizeof(arr_expected[0]);

    int *pb_src = arr;
    int *pe_src = arr + length_src;

    size_t cnt_elems = filter_arr_size(pb_src, pe_src);
    ck_assert_int_eq(cnt_elems, length_expected);

    int *pb_dst = malloc(cnt_elems * sizeof(int));
    ck_assert_ptr_nonnull(pb_dst);
    
    int *pe_dst = NULL;

    int rc = key(pb_src, pe_src, pb_dst, &pe_dst);
    
    ck_assert_int_eq(rc, OK);
    size_t length_dst = pe_dst - pb_dst;
    ck_assert_int_eq(length_dst, length_expected);

    bool equal = is_arrays_equal(pb_dst, length_dst, arr_expected, length_expected, sizeof(arr[0]), cmp_uni_int);

    ck_assert_int_eq(equal, true);
    free(pb_dst);
}
END_TEST

// Максимальный элемент в конце массива
START_TEST (test_max_elem_at_the_end_of_array)
{
    int arr[] = {2, 6, 8, 9, 10};
    int arr_expected[] = {6, 8, 9};
    size_t length_src = sizeof(arr) / sizeof(arr[0]);
    size_t length_expected = sizeof(arr_expected) / sizeof(arr_expected[0]);

    int *pb_src = arr;
    int *pe_src = arr + length_src;

    size_t cnt_elems = filter_arr_size(pb_src, pe_src);
    ck_assert_int_eq(cnt_elems, length_expected);

    int *pb_dst = malloc(cnt_elems * sizeof(int));
    ck_assert_ptr_nonnull(pb_dst);
    
    int *pe_dst = NULL;

    int rc = key(pb_src, pe_src, pb_dst, &pe_dst);
    
    ck_assert_int_eq(rc, OK);
    size_t length_dst = pe_dst - pb_dst;
    ck_assert_int_eq(length_dst, length_expected);

    bool equal = is_arrays_equal(pb_dst, length_dst, arr_expected, length_expected, sizeof(arr[0]), cmp_uni_int);

    ck_assert_int_eq(equal, true);
    free(pb_dst);
}
END_TEST

/*
 * ----------------------------------------------------------------------------------------------------------------------
 *
 * Юнит тесты фильтрации. Негативы  
 *
 * ----------------------------------------------------------------------------------------------------------------------
*/

// Один элемент
START_TEST (test_one_elem_key)
{
    int arr[] = {1};
    size_t length_src = sizeof(arr) / sizeof(arr[0]);

    int *pb_src = arr;
    int *pe_src = arr + length_src;

    size_t cnt_elems = filter_arr_size(pb_src, pe_src);
    ck_assert_int_le(cnt_elems, 0);
}
END_TEST

// Все числа одинаковые
START_TEST (test_all_numbers_are_the_same)
{
    int arr[] = {1, 1, 1, 1};
    size_t length_src = sizeof(arr) / sizeof(arr[0]);

    int *pb_src = arr;
    int *pe_src = arr + length_src;

    size_t cnt_elems = filter_arr_size(pb_src, pe_src);
    ck_assert_int_le(cnt_elems, 0);
}
END_TEST

// Минимальный и максимальный элементы находятся рядом
START_TEST (test_min_max_elem_next_to_each_other)
{
    int arr[] = {1, 0, 10, 1};
    size_t length_src = sizeof(arr) / sizeof(arr[0]);

    int *pb_src = arr;
    int *pe_src = arr + length_src;

    size_t cnt_elems = filter_arr_size(pb_src, pe_src);
    ck_assert_int_le(cnt_elems, 0);
    
}
END_TEST

Suite* key_suite(void)
{
    Suite *suite;
    TCase *tc_pos;
    TCase *tc_neg;

    suite = suite_create("key");
    
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_min_elem_before_max);
    tcase_add_test(tc_pos, test_min_elem_after_max);
    tcase_add_test(tc_pos, test_several_min_elems_one_max);
    tcase_add_test(tc_pos, test_several_max_elems_one_min);
    tcase_add_test(tc_pos, test_several_min_elems_several_max);
    tcase_add_test(tc_pos, test_one_elem_between_min_and_max);
    tcase_add_test(tc_pos, test_min_elem_at_the_end_of_array);
    tcase_add_test(tc_pos, test_min_elem_at_the_begin_of_array);
    tcase_add_test(tc_pos, test_max_elem_at_the_begin_of_array);
    tcase_add_test(tc_pos, test_max_elem_at_the_end_of_array);
    
    suite_add_tcase(suite, tc_pos);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_one_elem_key);
    tcase_add_test(tc_neg, test_all_numbers_are_the_same);
    tcase_add_test(tc_neg, test_min_max_elem_next_to_each_other);

    suite_add_tcase(suite, tc_neg);

    return suite;
}
