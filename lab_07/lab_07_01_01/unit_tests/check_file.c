#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include "check_array.h"
#include "check_file.h"
#include "errors.h"  

/*
 * ----------------------------------------------------------------------------------------------------------------------
 *
 * Юнит тесты ввода массива из файла. Позитивы
 *
 * ----------------------------------------------------------------------------------------------------------------------
*/

// В файле одно целое число
START_TEST (test_one_elem_in_file)
{
    char *file_name = "out/unit_test1.txt";
    FILE *file_in = fopen(file_name, "w");
    fprintf(file_in, "1");
    fclose(file_in);

    int arr_expected[] = {1};

    size_t len_arr_expected = sizeof(arr_expected) / sizeof(arr_expected[0]);

    int *pbeg = NULL;
    int *pend = NULL;

    file_in = fopen(file_name, "r");
    int rc = create_array(&pbeg, &pend, file_in);
    fclose(file_in);

    ck_assert_int_eq(rc, OK);

    size_t new_len = pend - pbeg;

    bool equal = is_arrays_equal(pbeg, new_len, arr_expected, len_arr_expected, sizeof(*pbeg), cmp_uni_int);

    ck_assert_int_eq(equal, true);
    
    free(pbeg);
}
END_TEST

// В файле два целых число
START_TEST (test_two_elems_in_file)
{
    char *file_name = "out/unit_test2.txt";
    FILE *file_in = fopen(file_name, "w");
    fprintf(file_in, "1 2");
    fclose(file_in);

    int arr_expected[] = {1, 2};

    size_t len_arr_expected = sizeof(arr_expected) / sizeof(arr_expected[0]);

    int *pbeg = NULL;
    int *pend = NULL;

    file_in = fopen(file_name, "r");
    int rc = create_array(&pbeg, &pend, file_in);
    fclose(file_in);

    ck_assert_int_eq(rc, OK);

    size_t new_len = pend - pbeg;

    bool equal = is_arrays_equal(pbeg, new_len, arr_expected, len_arr_expected, sizeof(*pbeg), cmp_uni_int);

    ck_assert_int_eq(equal, true);
    
    free(pbeg);
}
END_TEST

// В файле 11 целых чисел
START_TEST (test_eleven_elem_in_file)
{
    char *file_name = "out/unit_test3.txt";
    FILE *file_in = fopen(file_name, "w");
    fprintf(file_in, "1 2 3 4 5 6 7 8 9 10 11");
    fclose(file_in);

    int arr_expected[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

    size_t len_arr_expected = sizeof(arr_expected) / sizeof(arr_expected[0]);

    int *pbeg = NULL;
    int *pend = NULL;

    file_in = fopen(file_name, "r");
    int rc = create_array(&pbeg, &pend, file_in);
    fclose(file_in);
    
    ck_assert_int_eq(rc, OK);

    size_t new_len = pend - pbeg;

    bool equal = is_arrays_equal(pbeg, new_len, arr_expected, len_arr_expected, sizeof(*pbeg), cmp_uni_int);

    ck_assert_int_eq(equal, true);
    
    free(pbeg);
}
END_TEST

/*
 * ----------------------------------------------------------------------------------------------------------------------
 *
 * Юнит тесты ввода массива из файла. Негативы
 *
 * ----------------------------------------------------------------------------------------------------------------------
*/

// Пустой файл
START_TEST (test_empty_file)
{
    char *file_name = "out/unit_test4.txt";
    FILE *file_in = fopen(file_name, "w");
    fclose(file_in);

    int *pbeg = NULL;
    int *pend = NULL;

    file_in = fopen(file_name, "r");
    int rc = create_array(&pbeg, &pend, file_in);
    fclose(file_in);
    free(pbeg);

    ck_assert_int_ne(rc, OK);
}
END_TEST

// Посторонний символ в файле
START_TEST (test_symbols_in_file)
{
    char *file_name = "out/unit_test5.txt";
    FILE *file_in = fopen(file_name, "w");
    fprintf(file_in, "1 2 e 4 5");
    fclose(file_in);

    int *pbeg = NULL;
    int *pend = NULL;

    file_in = fopen(file_name, "r");
    int rc = create_array(&pbeg, &pend, file_in);
    fclose(file_in);
    free(pbeg);

    ck_assert_int_ne(rc, OK);
}
END_TEST

Suite* create_array_suite(void)
{
    Suite *suite;
    TCase *tc_pos;
    TCase *tc_neg;

    suite = suite_create("create_array");
    
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_one_elem_in_file);
    tcase_add_test(tc_pos, test_two_elems_in_file);
    tcase_add_test(tc_pos, test_eleven_elem_in_file);
    
    suite_add_tcase(suite, tc_pos);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_empty_file);
    tcase_add_test(tc_neg, test_symbols_in_file);

    suite_add_tcase(suite, tc_neg);

    return suite;
}


/*
 * ----------------------------------------------------------------------------------------------------------------------
 *
 * Юнит тесты открытия файла по строке. Позитивы
 *
 * ----------------------------------------------------------------------------------------------------------------------
*/

// 
START_TEST (test_file_exists)
{
    char *file_name = "out/unit_test6.txt";
    FILE *file_in = fopen(file_name, "w");
    fprintf(file_in, "1 2 3 4 5 6");
    fclose(file_in);

    int *pbeg = NULL;
    int *pend = NULL;

    int rc = create_array_ex(&pbeg, &pend, file_name);
    free(pbeg);
    
    ck_assert_int_eq(rc, OK);
}
END_TEST


/*
 * ----------------------------------------------------------------------------------------------------------------------
 *
 * Юнит тесты ввода массива из файла. Негативы
 *
 * ----------------------------------------------------------------------------------------------------------------------
*/

// 
START_TEST (test_file_doesnt_exists)
{
    char *file_name = "out/unit_test7.txt";

    int *pbeg = NULL;
    int *pend = NULL;

    int rc = create_array_ex(&pbeg, &pend, file_name);
    free(pbeg);

    ck_assert_int_ne(rc, OK);
}
END_TEST

Suite* create_array_ex_suite(void)
{
    Suite *suite;
    TCase *tc_pos;
    TCase *tc_neg;

    suite = suite_create("create_array_ex");
    
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_file_exists);
    
    suite_add_tcase(suite, tc_pos);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_file_doesnt_exists);

    suite_add_tcase(suite, tc_neg);

    return suite;
}
