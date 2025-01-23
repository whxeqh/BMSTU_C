#include "check_mtr_mul.h"
#include "check_same_func.h"
#include <stdbool.h>
#include <stdlib.h>
#include "mtr_op.h"
#include "mtr_alloc.h"
#include "errors.h"
#include "mtr_io.h"

/**
 * Позитивные тесты умножения матриц
 */

//Умножение матриц 1x1
START_TEST(test_mul_1x1_and_1x1_matrix)
{
    int rc = OK;

    size_t rows_1 = 1, columns_1 = 1;
    size_t rows_2 = 1, columns_2 = 1;
    size_t rows_dst = 1, columns_dst = 1;
    size_t rows_res = 0 , columns_res = 0;
    
    double mtr_1[ROWS_MAX][COLUMNS_MAX] = {{71.667}};
    double *ptrs_1[ROWS_MAX] = {mtr_1[0]};

    double mtr_2[ROWS_MAX][COLUMNS_MAX] = {{71.005}};
    double *ptrs_2[ROWS_MAX] = {mtr_2[0]};

    double mtr_dst[ROWS_MAX][COLUMNS_MAX] = {{5088.715335}};
    double *ptrs_dst[ROWS_MAX] = {mtr_dst[0]};
    
    double **mtr_res = NULL;

    rc = matrix_mul(ptrs_1, rows_1, columns_1, ptrs_2, rows_2, columns_2, &mtr_res, &rows_res, &columns_res);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(rows_res, rows_dst);
    ck_assert_int_eq(columns_res, columns_dst);

    bool is_equal = are_double_matrixes_equal(ptrs_dst, rows_dst, columns_dst, mtr_res, rows_res, columns_res);
    ck_assert_int_eq(is_equal, true);

    mtr_free(mtr_res, rows_res);

} 
END_TEST

//Умножение матриц 5x5
START_TEST(test_mul_5x5_and_5x5_matrix)
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

    double mtr_dst[ROWS_MAX][COLUMNS_MAX] = {{227.491680380000, 207.135867000000, 194.301714300000, 173.142667800000, 150.158650010000}, {585.980275000000, 538.348255000000, 505.167960500000, 457.018530000000, 403.761105350000},\
                                             {981.846300, 905.500574, 849.7796574, 773.798828, 688.98415666}, {1348.0617255, 1244.1979544, 1167.794451760000, 1066.010244200000, 951.346602424000},\
                                             {1754.732716280000, 1620.498842140000, 1520.832145540000, 1389.012725300000, 1241.178557700000}};
    double *ptrs_dst[ROWS_MAX] = {mtr_dst[0], mtr_dst[1], mtr_dst[2], mtr_dst[3], mtr_dst[4]};

    double **mtr_res = NULL;

    rc = matrix_mul(ptrs_1, rows_1, columns_1, ptrs_2, rows_2, columns_2, &mtr_res, &rows_res, &columns_res);

    /*printf("rows = %zu, columns = %zu\n", rows_res, columns_res);
    mtr_print(stdout, mtr_res, rows_res, columns_res);
    puts("");
    printf("rows = %zu, columns = %zu\n", rows_dst, columns_dst);
    mtr_print(stdout, ptrs_dst, rows_dst, columns_dst);*/
    
   /*     puts("DBG\n");
    mtr_print(stdout, mtr_res, rows_res, columns_res);
    puts("\nDBG\n\n");*/

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(rows_res, rows_dst);
    ck_assert_int_eq(columns_res, columns_dst);

    bool is_equal = are_double_matrixes_equal(ptrs_dst, rows_dst, columns_dst, mtr_res, rows_res, columns_res);
    ck_assert_int_eq(is_equal, true);

    mtr_free(mtr_res, rows_res);

} 
END_TEST

//Умножение матриц 1x5 и 5x1
START_TEST(test_mul_1x5_and_5x1_matrix)
{
    int rc = OK;

    size_t rows_1 = 1, columns_1 = 5;
    size_t rows_2 = 5, columns_2 = 1;
    size_t rows_dst = 1, columns_dst = 1;
    size_t rows_res = 0 , columns_res = 0;

    double mtr_1[ROWS_MAX][COLUMNS_MAX] = {{1.45, 2.322, 3.45, 4.001, 5.45}};
    double *ptrs_1[ROWS_MAX] = {mtr_1[0]};

    double mtr_2[ROWS_MAX][COLUMNS_MAX] = {{5.313}, {4.4}, {3.3}, {2.1}, {1.5}};
    double *ptrs_2[ROWS_MAX] = {mtr_2[0], mtr_2[1], mtr_2[2], mtr_2[3], mtr_2[4]};

    double mtr_dst[ROWS_MAX][COLUMNS_MAX] = {{45.88275}};
    double *ptrs_dst[ROWS_MAX] = {mtr_dst[0]};

    double **mtr_res = NULL;

    rc = matrix_mul(ptrs_1, rows_1, columns_1, ptrs_2, rows_2, columns_2, &mtr_res, &rows_res, &columns_res);
    
    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(rows_res, rows_dst);
    ck_assert_int_eq(columns_res, columns_dst);

    bool is_equal = are_double_matrixes_equal(ptrs_dst, rows_dst, columns_dst, mtr_res, rows_res, columns_res);
    ck_assert_int_eq(is_equal, true);

    mtr_free(mtr_res, rows_res);

} 
END_TEST

//Умножение матриц 5x1 и 1x5
START_TEST(test_mul_5x1_and_1x5_matrix)
{
    int rc = OK;

    size_t rows_1 = 5, columns_1 = 1;
    size_t rows_2 = 1, columns_2 = 5;
    size_t rows_dst = 5, columns_dst = 5;
    size_t rows_res = 0 , columns_res = 0;

    double mtr_1[ROWS_MAX][COLUMNS_MAX] = {{5.313}, {4.4}, {3.3}, {2.1}, {1.5}};
    double *ptrs_1[ROWS_MAX] = {mtr_1[0], mtr_1[1], mtr_1[2], mtr_1[3], mtr_1[4]};

    double mtr_2[ROWS_MAX][COLUMNS_MAX] = {{1.45, 2.322, 3.45, 4.001, 5.45}};
    double *ptrs_2[ROWS_MAX] = {mtr_2[0]};

    double mtr_dst[ROWS_MAX][COLUMNS_MAX] = {{7.703850, 12.336786, 18.329850, 21.257313, 28.955850}, {6.380000, 10.216800, 15.180000, 17.604400, 23.980000},\
                                             {4.785, 7.6626, 11.385, 13.2033, 17.985}, {3.045, 4.8762, 7.245, 8.40210, 11.445000},\
                                             {2.175, 3.483, 5.175, 6.0015, 8.175}};
    double *ptrs_dst[ROWS_MAX] = {mtr_dst[0], mtr_dst[1], mtr_dst[2], mtr_dst[3], mtr_dst[4]};

    double **mtr_res = NULL;

    rc = matrix_mul(ptrs_1, rows_1, columns_1, ptrs_2, rows_2, columns_2, &mtr_res, &rows_res, &columns_res);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(rows_res, rows_dst);
    ck_assert_int_eq(columns_res, columns_dst);

    bool is_equal = are_double_matrixes_equal(ptrs_dst, rows_dst, columns_dst, mtr_res, rows_res, columns_res);
    ck_assert_int_eq(is_equal, true);

    mtr_free(mtr_res, rows_res);

} 
END_TEST

//Умножение матриц 7x15 и 15x7
START_TEST(test_mul_7x15_and_15x7_matrix)
{
    int rc = OK;

    size_t rows_1 = 7, columns_1 = 15;
    size_t rows_2 = 15, columns_2 = 7;
    size_t rows_dst = 7, columns_dst = 7;
    size_t rows_res = 0 , columns_res = 0;

    double mtr_1[ROWS_MAX][COLUMNS_MAX] = {{1.424, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}, {1, 2, 3.53775, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13.424, 14, 15},\
    {1, 2, 3, 4, 5, 6.442, 7, 8, 9, 10, 11, 12, 13, 14, 15.31}, {1, 2, 3, 4, 5, 6, 7, 8.3131, 9, 10, 11, 12, 13, 14, 15.4242}, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10.5757, 11, 12, 13, 14, 15},\
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 1.8682, 13, 14, 15}, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13.878, 14.311, 15.64}};
    double *ptrs_1[ROWS_MAX] = {mtr_1[0], mtr_1[1], mtr_1[2], mtr_1[3], mtr_1[4], mtr_1[5], mtr_1[6]};

    double mtr_2[ROWS_MAX][COLUMNS_MAX] = {{1.77, 2, 3, 4, 5, 6, 7}, {1, 2, 3, 4, 5, 6, 7}, {1, 2.08, 3, 4, 5, 6, 7}, {1, 2, 3, 4, 5, 6, 7},\
    {1, 2, 3, 4.53, 5, 6, 7}, {1, 2, 3, 4, 5, 6, 7}, {1, 2, 3, 4, 5, 6.76575, 7}, {1, 2, 3, 4, 5, 6, 7}, {1, 2, 3.31, 4, 5, 6, 7}, {1, 2, 3, 4, 5, 6, 7},\
    {1, 2, 3, 4, 5, 6, 7}, {1, 2, 3, 4, 5.4242, 6, 7}, {1.313, 2, 3, 4, 5, 6, 7}, {1, 2, 3, 4, 5, 6.645, 7}, {1, 2, 3, 4, 5, 6, 7.3131}};
    double *ptrs_2[ROWS_MAX] = {mtr_2[0], mtr_2[1], mtr_2[2], mtr_2[3], mtr_2[4], mtr_2[5], mtr_2[6], mtr_2[7], mtr_2[8], mtr_2[9], mtr_2[10], mtr_2[11], mtr_2[12], mtr_2[13], mtr_2[14]};

    double mtr_dst[ROWS_MAX][COLUMNS_MAX] = {
    {125.589480000000, 241.088000000000, 364.062000000000, 484.346000000000, 607.210400000000, 736.934250000000, 847.664500000000},
    {125.933462000000, 242.206520000000, 365.675250000000, 486.497000000000, 609.899150000000, 740.160750000000, 851.428750000000},
    {125.591000000000, 241.744000000000, 365.046000000000, 485.658000000000, 608.850400000000, 738.902250000000, 850.057561000000},
    {125.576300000000, 241.714600000000, 365.001900000000, 485.599200000000, 608.776900000000, 738.814050000000, 849.990417020000},
    {125.414700000000, 241.391400000000, 364.517100000000, 484.952800000000, 607.968900000000, 737.844450000000, 848.726400000000},
    {114.707200000000, 219.976400000000, 332.394600000000, 442.122800000000, 550.133490440000, 673.599450000000, 773.773900000000},
    {126.942814000000, 243.898000000000, 368.277000000000, 489.966000000000, 614.235400000000, 745.564845000000, 857.699884000000}};double *ptrs_dst[ROWS_MAX] = {mtr_dst[0], mtr_dst[1], mtr_dst[2], mtr_dst[3], mtr_dst[4], mtr_dst[5], mtr_dst[6]};

    double **mtr_res = NULL;

    rc = matrix_mul(ptrs_1, rows_1, columns_1, ptrs_2, rows_2, columns_2, &mtr_res, &rows_res, &columns_res);

    /*printf("rows = %zu, columns = %zu\n", rows_res, columns_res);
    mtr_print(stdout, mtr_res, rows_res, columns_res);
    puts("");
    printf("rows = %zu, columns = %zu\n", rows_dst, columns_dst);
    mtr_print(stdout, ptrs_dst, rows_dst, columns_dst);*/

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(rows_res, rows_dst);
    ck_assert_int_eq(columns_res, columns_dst);

    bool is_equal = are_double_matrixes_equal(ptrs_dst, rows_dst, columns_dst, mtr_res, rows_res, columns_res);
    ck_assert_int_eq(is_equal, true);

    mtr_free(mtr_res, rows_res);

} 
END_TEST

/**
 * Негативные тесты унможения матриц
 */

//Умножение матриц 0x1
START_TEST(test_mul_0x1_matrix)
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

    rc = matrix_mul(ptrs_1, rows_1, columns_1, ptrs_2, rows_2, columns_2, &mtr_res, &rows_res, &columns_res);

    ck_assert_int_ne(rc, OK);

    mtr_free(mtr_res, rows_res);

} 
END_TEST

//Умножение матриц 1x0
START_TEST(test_mul_1x0_matrix)
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

    rc = matrix_mul(ptrs_1, rows_1, columns_1, ptrs_2, rows_2, columns_2, &mtr_res, &rows_res, &columns_res);

    ck_assert_int_ne(rc, OK);

    mtr_free(mtr_res, rows_res);

} 
END_TEST

//Умножение матриц 1x5 и 1x4
START_TEST(test_mul_1x5_and_1x4_matrix)
{
    int rc = OK;

    size_t rows_1 = 1, columns_1 = 5;
    size_t rows_2 = 1, columns_2 = 1;
    size_t rows_res = 0 , columns_res = 0;

    double mtr_1[ROWS_MAX][COLUMNS_MAX] = {{1.53, 2.006, 3.0004, 4.131, 5.3}};
    double *ptrs_1[ROWS_MAX] = {mtr_1[0]};

    double mtr_2[ROWS_MAX][COLUMNS_MAX] = {{5.53}};
    double *ptrs_2[ROWS_MAX] = {mtr_2[0]};

    double **mtr_res = NULL;

    rc = matrix_mul(ptrs_1, rows_1, columns_1, ptrs_2, rows_2, columns_2, &mtr_res, &rows_res, &columns_res);

    ck_assert_int_ne(rc, OK);

    mtr_free(mtr_res, rows_res);

} 
END_TEST

Suite* matrix_mul_suite(void)
{
    Suite *suite;
    TCase *tc_pos, *tc_neg;

    suite = suite_create("matrix_mul");
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_mul_1x1_and_1x1_matrix);
    tcase_add_test(tc_pos, test_mul_5x5_and_5x5_matrix);
    tcase_add_test(tc_pos, test_mul_1x5_and_5x1_matrix);
    tcase_add_test(tc_pos, test_mul_5x1_and_1x5_matrix);
    tcase_add_test(tc_pos, test_mul_7x15_and_15x7_matrix);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_mul_0x1_matrix);
    tcase_add_test(tc_neg, test_mul_1x0_matrix);
    tcase_add_test(tc_neg, test_mul_1x5_and_1x4_matrix);
    
    suite_add_tcase(suite, tc_pos);
    suite_add_tcase(suite, tc_neg);

    return suite;
}