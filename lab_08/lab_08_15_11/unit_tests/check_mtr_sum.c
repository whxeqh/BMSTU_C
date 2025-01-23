#include "check_mtr_sum.h"
#include "check_same_func.h"
#include <stdlib.h>
#include "mtr_op.h"
#include "mtr_alloc.h"
#include "errors.h"

/**
 * Позитивные тесты сложения матриц
 */

//Сложение матриц 1x1
START_TEST(test_sum_1x1_and_1x1_matrix)
{
    int rc = OK;

    size_t rows_1 = 1, columns_1 = 1;
    size_t rows_2 = 1, columns_2 = 1;
    size_t rows_dst = 1, columns_dst = 1;
    size_t rows_res = 0 , columns_res = 0;

    double mtr_1[ROWS_MAX][COLUMNS_MAX] = {{71.42}};
    double *ptrs_1[ROWS_MAX] = {mtr_1[0]};

    double mtr_2[ROWS_MAX][COLUMNS_MAX] = {{71.31}};
    double *ptrs_2[ROWS_MAX] = {mtr_2[0]};

    double mtr_dst[ROWS_MAX][COLUMNS_MAX] = {{142.73}};
    double *ptrs_dst[ROWS_MAX] = {mtr_dst[0]};

    double **mtr_res = NULL;

    rc = matrix_sum(ptrs_1, rows_1, columns_1, ptrs_2, rows_2, columns_2, &mtr_res, &rows_res, &columns_res);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(rows_res, rows_dst);
    ck_assert_int_eq(columns_res, columns_dst);

    bool is_equal = are_double_matrixes_equal(ptrs_dst, rows_dst, columns_dst, mtr_res, rows_res, columns_res);
    ck_assert_int_eq(is_equal, true);

    mtr_free(mtr_res, rows_res);

} 
END_TEST

//Сложение матриц 5x5
START_TEST(test_sum_5x5_and_5x5_matrix)
{
    int rc = OK;

    size_t rows_1 = 5, columns_1 = 5;
    size_t rows_2 = 5, columns_2 = 5;
    size_t rows_dst = 5, columns_dst = 5;
    size_t rows_res = 0 , columns_res = 0;

    double mtr_1[ROWS_MAX][COLUMNS_MAX] = {{1.424, 2.6646, 3.88, 4.99, 5.001}, {6, 7, 8.85, 9.646, 10.535},\
                                            {11.654, 12, 13.64, 14.424, 15.666}, {16, 17.535, 18, 19.424, 20.2424},\
                                            {21.353, 22.3131, 23.7567, 24.777, 25.77}};
    double *ptrs_1[ROWS_MAX] = {mtr_1[0], mtr_1[1], mtr_1[2], mtr_1[3], mtr_1[4]};

    double mtr_2[ROWS_MAX][COLUMNS_MAX] = {{25.42, 24.56, 23, 22, 21}, {20.5353, 19, 18.004, 17.463, 16},\
                                            {15.7655, 14.4242, 13.4242, 12, 11.0}, {10, 9, 8.314, 7, 6},\
                                            {5.1, 4.131, 3.9999, 2.758, 1.00001 }};
    double *ptrs_2[ROWS_MAX] = {mtr_2[0], mtr_2[1], mtr_2[2], mtr_2[3], mtr_2[4]};

    double mtr_dst[ROWS_MAX][COLUMNS_MAX] = {{26.844000, 27.224600, 26.880000, 26.990000, 26.001000}, {26.5353, 26, 26.854, 27.109, 26.535},\
                                             {27.4195, 26.4242, 27.0642, 26.424, 26.666}, {26, 26.535, 26.314, 26.424000, 26.2424},\
                                             {26.453, 26.4441, 27.7566, 27.535, 26.77001}};
    double *ptrs_dst[ROWS_MAX] = {mtr_dst[0], mtr_dst[1], mtr_dst[2], mtr_dst[3], mtr_dst[4]};

    double **mtr_res = NULL;
    
    rc = matrix_sum(ptrs_1, rows_1, columns_1, ptrs_2, rows_2, columns_2, &mtr_res, &rows_res, &columns_res);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(rows_res, rows_dst);
    ck_assert_int_eq(columns_res, columns_dst);

    bool is_equal = are_double_matrixes_equal(ptrs_dst, rows_dst, columns_dst, mtr_res, rows_res, columns_res);
    ck_assert_int_eq(is_equal, true);

    mtr_free(mtr_res, rows_res);

} 
END_TEST

//Сложение матриц 1x5
START_TEST(test_sum_1x5_and_1x5_matrix)
{
    int rc = OK;

    size_t rows_1 = 1, columns_1 = 5;
    size_t rows_2 = 1, columns_2 = 5;
    size_t rows_dst = 1, columns_dst = 5;
    size_t rows_res = 0 , columns_res = 0;

    double mtr_1[ROWS_MAX][COLUMNS_MAX] = {{1.53, 2.006, 3.0004, 4.131, 5.3}};
    double *ptrs_1[ROWS_MAX] = {mtr_1[0]};

    double mtr_2[ROWS_MAX][COLUMNS_MAX] = {{10.3131, 11.5654, 12.4242, 0.00001, 13.312321}};
    double *ptrs_2[ROWS_MAX] = {mtr_2[0]};

    double mtr_dst[ROWS_MAX][COLUMNS_MAX] = {{11.8431, 13.5714, 15.4246, 4.13101, 18.612321}};
    double *ptrs_dst[ROWS_MAX] = {mtr_dst[0]};

    double **mtr_res = NULL;

    rc = matrix_sum(ptrs_1, rows_1, columns_1, ptrs_2, rows_2, columns_2, &mtr_res, &rows_res, &columns_res);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(rows_res, rows_dst);
    ck_assert_int_eq(columns_res, columns_dst);

    bool is_equal = are_double_matrixes_equal(ptrs_dst, rows_dst, columns_dst, mtr_res, rows_res, columns_res);
    ck_assert_int_eq(is_equal, true);

    mtr_free(mtr_res, rows_res);

} 
END_TEST

//Сложение матриц 5x1
START_TEST(test_sum_5x1_and_5x1_matrix)
{
    int rc = OK;

    size_t rows_1 = 5, columns_1 = 1;
    size_t rows_2 = 5, columns_2 = 1;
    size_t rows_dst = 5, columns_dst = 1;
    size_t rows_res = 0 , columns_res = 0;

    double mtr_1[ROWS_MAX][COLUMNS_MAX] = {{5.53}, {4.77}, {3.9877} ,{2.001} ,{1.424}};
    double *ptrs_1[ROWS_MAX] = {mtr_1[0], mtr_1[1], mtr_1[2], mtr_1[3], mtr_1[4]};

    double mtr_2[ROWS_MAX][COLUMNS_MAX] = {{0}, {0}, {0}, {0}, {1.999}};
    double *ptrs_2[ROWS_MAX] = {mtr_2[0], mtr_2[1], mtr_2[2], mtr_2[3], mtr_2[4]};

    double mtr_dst[ROWS_MAX][COLUMNS_MAX] = {{5.53}, {4.77}, {3.9877}, {2.001}, {3.423}};
    double *ptrs_dst[ROWS_MAX] = {mtr_dst[0], mtr_dst[1], mtr_dst[2], mtr_dst[3], mtr_dst[4]};

    double **mtr_res = NULL;

    rc = matrix_sum(ptrs_1, rows_1, columns_1, ptrs_2, rows_2, columns_2, &mtr_res, &rows_res, &columns_res);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(rows_res, rows_dst);
    ck_assert_int_eq(columns_res, columns_dst);

    bool is_equal = are_double_matrixes_equal(ptrs_dst, rows_dst, columns_dst, mtr_res, rows_res, columns_res);
    ck_assert_int_eq(is_equal, true);

    mtr_free(mtr_res, rows_res);

} 
END_TEST

//Сложение матриц 7x15
START_TEST(test_sum_7x15_and_7x15_matrix)
{
    int rc = OK;

    size_t rows_1 = 7, columns_1 = 15;
    size_t rows_2 = 7, columns_2 = 15;
    size_t rows_dst = 7, columns_dst = 15;
    size_t rows_res = 0 , columns_res = 0;

    double mtr_1[ROWS_MAX][COLUMNS_MAX] = {{1.424, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}, {1, 2, 3.53775, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13.424, 14, 15},\
    {1, 2, 3, 4, 5, 6.442, 7, 8, 9, 10, 11, 12, 13, 14, 15.31}, {1, 2, 3, 4, 5, 6, 7, 8.3131, 9, 10, 11, 12, 13, 14, 15.4242}, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10.5757, 11, 12, 13, 14, 15},\
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 1.8682, 13, 14, 15}, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13.878, 14.311, 15.64}};
    double *ptrs_1[ROWS_MAX] = {mtr_1[0], mtr_1[1], mtr_1[2], mtr_1[3], mtr_1[4], mtr_1[5], mtr_1[6]};

    double mtr_2[ROWS_MAX][COLUMNS_MAX] = {{1.424, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}, {1, 2, 3.53775, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13.424, 14, 15},\
    {1, 2, 3, 4, 5, 6.442, 7, 8, 9, 10, 11, 12, 13, 14, 15.31}, {1, 2, 3, 4, 5, 6, 7, 8.3131, 9, 10, 11, 12, 13, 14, 15.4242}, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10.5757, 11, 12, 13, 14, 15},\
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 1.8682, 13, 14, 15}, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13.878, 14.311, 15.64}};
    double *ptrs_2[ROWS_MAX] = {mtr_2[0], mtr_2[1], mtr_2[2], mtr_2[3], mtr_2[4], mtr_2[5], mtr_2[6]};

    double mtr_dst[ROWS_MAX][COLUMNS_MAX] = {
    {2.848, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30},
    {2, 4, 7.0755, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26.848, 28, 30},
    {2, 4, 6, 8, 10, 12.884, 14, 16, 18, 20, 22, 24, 26, 28, 30.62},
    {2, 4, 6, 8, 10, 12, 14, 16.6262, 18, 20, 22, 24, 26, 28, 30.8484},
    {2, 4, 6, 8, 10, 12, 14, 16, 18, 21.1514, 22, 24, 26, 28, 30},
    {2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 3.7364, 26, 28, 30}, 
    {2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 27.756, 28.622, 31.28}
    };
    double *ptrs_dst[ROWS_MAX] = {mtr_dst[0], mtr_dst[1], mtr_dst[2], mtr_dst[3], mtr_dst[4], mtr_dst[5], mtr_dst[6]};

    double **mtr_res = NULL;

    rc = matrix_sum(ptrs_1, rows_1, columns_1, ptrs_2, rows_2, columns_2, &mtr_res, &rows_res, &columns_res);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(rows_res, rows_dst);
    ck_assert_int_eq(columns_res, columns_dst);

    bool is_equal = are_double_matrixes_equal(ptrs_dst, rows_dst, columns_dst, mtr_res, rows_res, columns_res);
    ck_assert_int_eq(is_equal, true);

    mtr_free(mtr_res, rows_res);

} 
END_TEST

//Сложение матриц 15x7
START_TEST(test_sum_15x7_and_15x7_matrix)
{
    int rc = OK;

    size_t rows_1 = 1, columns_1 = 1;
    size_t rows_2 = 1, columns_2 = 1;
    size_t rows_dst = 1, columns_dst = 1;
    size_t rows_res = 0 , columns_res = 0;

    double mtr_1[ROWS_MAX][COLUMNS_MAX] = {{1.77, 2, 3, 4, 5, 6, 7}, {1, 2, 3, 4, 5, 6, 7}, {1, 2.08, 3, 4, 5, 6, 7}, {1, 2, 3, 4, 5, 6, 7},\
    {1, 2, 3, 4.53, 5, 6, 7}, {1, 2, 3, 4, 5, 6, 7}, {1, 2, 3, 4, 5, 6.76575, 7}, {1, 2, 3, 4, 5, 6, 7}, {1, 2, 3.31, 4, 5, 6, 7}, {1, 2, 3, 4, 5, 6, 7},\
    {1, 2, 3, 4, 5, 6, 7}, {1, 2, 3, 4, 5.4242, 6, 7}, {1.313, 2, 3, 4, 5, 6, 7}, {1, 2, 3, 4, 5, 6.645, 7}, {1, 2, 3, 4, 5, 6, 7.3131}};
    double *ptrs_1[ROWS_MAX] = {mtr_1[0], mtr_1[1], mtr_1[2], mtr_1[3], mtr_1[4], mtr_1[5], mtr_1[6], mtr_1[7], mtr_1[8], mtr_1[9], mtr_1[10], mtr_1[11], mtr_1[12], mtr_1[13], mtr_1[14]};

    double mtr_2[ROWS_MAX][COLUMNS_MAX] = {{1.77, 2, 3, 4, 5, 6, 7}, {1, 2, 3, 4, 5, 6, 7}, {1, 2.08, 3, 4, 5, 6, 7}, {1, 2, 3, 4, 5, 6, 7},\
    {1, 2, 3, 4.53, 5, 6, 7}, {1, 2, 3, 4, 5, 6, 7}, {1, 2, 3, 4, 5, 6.76575, 7}, {1, 2, 3, 4, 5, 6, 7}, {1, 2, 3.31, 4, 5, 6, 7}, {1, 2, 3, 4, 5, 6, 7},\
    {1, 2, 3, 4, 5, 6, 7}, {1, 2, 3, 4, 5.4242, 6, 7}, {1.313, 2, 3, 4, 5, 6, 7}, {1, 2, 3, 4, 5, 6.645, 7}, {1, 2, 3, 4, 5, 6, 7.3131}};
    double *ptrs_2[ROWS_MAX] = {mtr_2[0], mtr_2[1], mtr_2[2], mtr_2[3], mtr_2[4], mtr_2[5], mtr_2[6], mtr_2[7], mtr_2[8], mtr_2[9], mtr_2[10], mtr_2[11], mtr_2[12], mtr_2[13], mtr_2[14]};

    double mtr_dst[ROWS_MAX][COLUMNS_MAX] = {{3.54, 4, 6, 8, 10, 12, 14}, {2, 4, 6, 8, 10, 12, 14}, {2, 4, 6, 8, 10, 12, 14}, {2, 4, 6, 8, 10, 12, 14},\
    {2, 4, 6, 8, 10, 12, 14}, {2, 4, 6, 8, 10, 12, 14}, {2, 4, 6, 8, 10, 12, 14}, {2, 4, 6, 8, 10, 12, 14}, {2, 4, 6, 8, 10, 12, 14}, {2, 4, 6, 8, 10, 12, 14},\
    {2, 4, 6, 8, 10, 12, 14}, {2, 4, 6, 8, 10, 12, 14}, {2, 4, 6, 8, 10, 12, 14}, {2, 4, 6, 8, 10, 12, 14}, {2, 4, 6, 8, 10, 12, 14}};
    double *ptrs_dst[ROWS_MAX] = {mtr_dst[0], mtr_dst[1], mtr_dst[2], mtr_dst[3], mtr_dst[4], mtr_dst[5], mtr_dst[6], mtr_dst[7], mtr_dst[8], mtr_dst[9], mtr_dst[10],\
                                 mtr_dst[11], mtr_dst[12], mtr_dst[13], mtr_dst[14]};

    double **mtr_res = NULL;

    rc = matrix_sum(ptrs_1, rows_1, columns_1, ptrs_2, rows_2, columns_2, &mtr_res, &rows_res, &columns_res);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(rows_res, rows_dst);
    ck_assert_int_eq(columns_res, columns_dst);

    bool is_equal = are_double_matrixes_equal(ptrs_dst, rows_dst, columns_dst, mtr_res, rows_res, columns_res);
    ck_assert_int_eq(is_equal, true);

    mtr_free(mtr_res, rows_res);

} 
END_TEST

/**
 * Негативные тесты сложения матриц
 */

//Сложение матриц 0x1
START_TEST(test_sum_0x1_matrix)
{
    int rc = OK;

    size_t rows_1 = 0, columns_1 = 1;
    size_t rows_2 = 0, columns_2 = 1;
    size_t rows_res = 0 , columns_res = 0;

    double mtr_1[ROWS_MAX][COLUMNS_MAX] = {{71,42}};
    double *ptrs_1[ROWS_MAX] = {mtr_1[0]};

    double mtr_2[ROWS_MAX][COLUMNS_MAX] = {{71,31}};
    double *ptrs_2[ROWS_MAX] = {mtr_2[0]};

    double **mtr_res = NULL;

    rc = matrix_sum(ptrs_1, rows_1, columns_1, ptrs_2, rows_2, columns_2, &mtr_res, &rows_res, &columns_res);

    ck_assert_int_ne(rc, OK);

    mtr_free(mtr_res, rows_res);

} 
END_TEST

//Сложение матриц 1x0
START_TEST(test_sum_1x0_matrix)
{
    int rc = OK;

    size_t rows_1 = 1, columns_1 = 0;
    size_t rows_2 = 1, columns_2 = 0;
    size_t rows_res = 0 , columns_res = 0;

    double mtr_1[ROWS_MAX][COLUMNS_MAX] = {{71,42}};
    double *ptrs_1[ROWS_MAX] = {mtr_1[0]};

    double mtr_2[ROWS_MAX][COLUMNS_MAX] = {{71,31}};
    double *ptrs_2[ROWS_MAX] = {mtr_2[0]};

    double **mtr_res = NULL;

    rc = matrix_sum(ptrs_1, rows_1, columns_1, ptrs_2, rows_2, columns_2, &mtr_res, &rows_res, &columns_res);

    ck_assert_int_ne(rc, OK);

    mtr_free(mtr_res, rows_res);

} 
END_TEST

//Сложение матриц 1x5 и 5x1
START_TEST(test_sum_1x5_and_5x1_matrix)
{
    int rc = OK;

    size_t rows_1 = 1, columns_1 = 5;
    size_t rows_2 = 5, columns_2 = 1;
    size_t rows_res = 0 , columns_res = 0;

    double mtr_1[ROWS_MAX][COLUMNS_MAX] = {{1.53, 2.006, 3.0004, 4.131, 5.3}};
    double *ptrs_1[ROWS_MAX] = {mtr_1[0]};

    double mtr_2[ROWS_MAX][COLUMNS_MAX] = {{5.53}, {4.77}, {3.9877} ,{2.001} ,{1.424}};
    double *ptrs_2[ROWS_MAX] = {mtr_2[0], mtr_2[1], mtr_2[2], mtr_2[3], mtr_2[4]};

    double **mtr_res = NULL;

    rc = matrix_sum(ptrs_1, rows_1, columns_1, ptrs_2, rows_2, columns_2, &mtr_res, &rows_res, &columns_res);

    ck_assert_int_ne(rc, OK);

    mtr_free(mtr_res, rows_res);

} 
END_TEST

Suite* matrix_sum_suite(void)
{
    Suite *suite;
    TCase *tc_pos, *tc_neg;

    suite = suite_create("matrix_sum");
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_sum_1x1_and_1x1_matrix);
    tcase_add_test(tc_pos, test_sum_5x5_and_5x5_matrix);
    tcase_add_test(tc_pos, test_sum_1x5_and_1x5_matrix);
    tcase_add_test(tc_pos, test_sum_5x1_and_5x1_matrix);
    tcase_add_test(tc_pos, test_sum_7x15_and_7x15_matrix);
    tcase_add_test(tc_pos, test_sum_15x7_and_15x7_matrix);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_sum_0x1_matrix);
    tcase_add_test(tc_neg, test_sum_1x0_matrix);
    tcase_add_test(tc_neg, test_sum_1x5_and_5x1_matrix);
    
    suite_add_tcase(suite, tc_pos);
    suite_add_tcase(suite, tc_neg);

    return suite;
}