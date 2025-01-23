#include <stdlib.h>
#include "check_same_func.h"
#include "check_mtr_op.h"
#include "mtr_op.h"
#include "mtr_alloc.h"
#include "errors.h"
#include "mtr_io.h"

void copy_matrix(double **dst_matrix, double (*src_matrix)[COLUMNS_MAX], size_t rows, size_t columns)
{
    for (size_t i = 0; i < rows; i++)
        memcpy(dst_matrix[i], src_matrix[i], columns * sizeof(double));
}

/**
 * Позитивные тесты нахождения обратной матриц
 */

//матрица 1x1
START_TEST(test_inverse_1x1_matrix)
{
    int rc = OK;

    size_t rows = 1, columns = 1;
    size_t rows_dst = 1, columns_dst = 1;
    size_t rows_res = 0 , columns_res = 0;
    
    double data[ROWS_MAX][COLUMNS_MAX] = {{4.32132152}};

    double **mtr_src = mtr_alloc(rows, columns);
    copy_matrix(mtr_src, data, rows, columns);

    double mtr_dst[ROWS_MAX][COLUMNS_MAX] = {{0.231410691237}};
    double *ptrs_dst[ROWS_MAX] = {mtr_dst[0]};
    
    double **mtr_res = NULL;

    rc = matrix_inverse(mtr_src, rows, columns, &mtr_res, &rows_res, &columns_res);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(rows_res, rows);
    ck_assert_int_eq(columns_res, columns);

    bool is_equal = are_double_matrixes_equal(ptrs_dst, rows_dst, columns_dst, mtr_res, rows_res, columns_res);
    ck_assert_int_eq(is_equal, true);

    mtr_free(mtr_src, rows);
    mtr_free(mtr_res, rows_res);

} 
END_TEST

//Матрицa 5x5
START_TEST(test_inverse_5x5_matrix)
{
    int rc = OK;

    size_t rows = 5, columns = 5;
    size_t rows_dst = 5, columns_dst = 5;
    size_t rows_res = 0 , columns_res = 0;
    
    double data[ROWS_MAX][COLUMNS_MAX] = {{1.424, 2.6646, 3.88, 4.99, 5.001}, {6, 7, 8.85, 9.646, 10.535},\
                                            {11.654, 12, 13.64, 14.424, 15.666}, {16, 17.535, 18, 19.424, 20.2424},\
                                            {21.353, 22.3131, 23.7567, 24.777, 25.77}};

    double **mtr_src = mtr_alloc(rows, columns);
    copy_matrix(mtr_src, data, rows, columns);

    double mtr_dst[ROWS_MAX][COLUMNS_MAX] = {
    {0.760706674510, -1.761860366808, 1.577281658263, -0.456951652773, -0.027279450414},
    {-1.114877670221, 1.562133534625, -1.565286796108, 1.094190281277, -0.330183467613},
    {-1.046229410928, 2.253167767183, -1.946745407001, -0.932907798554, 1.198179170520},
    {2.465852727735, -2.997589329532, 1.437388562362, -0.559712990606, 0.312754331328},
    {-1.071341384009, 0.912239144905, 0.461031267451, 0.829388084697, -1.057973703210}};
    double *ptrs_dst[ROWS_MAX] = {mtr_dst[0], mtr_dst[1], mtr_dst[2], mtr_dst[3], mtr_dst[4]};
    
    double **mtr_res = NULL;

    rc = matrix_inverse(mtr_src, rows, columns, &mtr_res, &rows_res, &columns_res);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(rows_res, rows);
    ck_assert_int_eq(columns_res, columns);

    bool is_equal = are_double_matrixes_equal(ptrs_dst, rows_dst, columns_dst, mtr_res, rows_res, columns_res);
    ck_assert_int_eq(is_equal, true);

    mtr_free(mtr_src, rows);
    mtr_free(mtr_res, rows_res);

} 
END_TEST

//Единичная аатрица 10x10
START_TEST(test_inverse_10x10_identity_matrix)
{
    int rc = OK;

    size_t rows = 10, columns = 10;
    size_t rows_dst = 10, columns_dst = 10;
    size_t rows_res = 0 , columns_res = 0;
    
    double data[ROWS_MAX][COLUMNS_MAX] = {{1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 1, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 1, 0, 0, 0, 0, 0, 0, 0},\
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 1, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 1, 0, 0, 0},\
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0, 1, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0, 1}};
    
    double **mtr_src = mtr_alloc(rows, columns);
    copy_matrix(mtr_src, data, rows, columns);

    double mtr_dst[ROWS_MAX][COLUMNS_MAX] = {{1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 1, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 1, 0, 0, 0, 0, 0, 0, 0},\
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 1, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 1, 0, 0, 0},\
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0, 1, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0, 1}};
    double *ptrs_dst[ROWS_MAX] = {mtr_dst[0], mtr_dst[1], mtr_dst[2], mtr_dst[3], mtr_dst[4], mtr_dst[5], mtr_dst[6], mtr_dst[7], mtr_dst[8], mtr_dst[9]};
    
    double **mtr_res = NULL;

    rc = matrix_inverse(mtr_src, rows, columns, &mtr_res, &rows_res, &columns_res);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(rows_res, rows);
    ck_assert_int_eq(columns_res, columns);

    bool is_equal = are_double_matrixes_equal(ptrs_dst, rows_dst, columns_dst, mtr_res, rows_res, columns_res);
    ck_assert_int_eq(is_equal, true);

    mtr_free(mtr_src, rows);
    mtr_free(mtr_res, rows_res);

} 
END_TEST

//Разреженная матрица 15x15
START_TEST(test_inverse_15x15_sparse_matrix)
{
    int rc = OK;

    size_t rows = 15, columns = 15;
    size_t rows_dst = 15, columns_dst = 15;
    size_t rows_res = 0 , columns_res = 0;
    
    double data[ROWS_MAX][COLUMNS_MAX] = {{1.53, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0}, {0, 1.0424, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 1.4242, 0, 0, 3, 0, 0, 0, 1, 0, 0, 0, 0, 0},\
    {0, 0, 0, 1.31, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 1.564, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0}, {0, 1, 0, 0, 0, 1.997, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1.3131, 0, 0, 0, 0, 0, 4, 0, 0},\
    {0, 0, 0, 0, 2, 0, 0, 1.5353, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 1.7575, 0, 0, 0, 0, 0, 0}, {0, 0, 3, 0, 0, 0, 0, 0, 0, 4241.5353, 0, 0, 0, 0, 0}, {0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 1.664, 0, 0, 0, 0},\
    {0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 31.51, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5436.1, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 457451.42, 0}, {0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 1.311}};
    double **mtr_src = mtr_alloc(rows, columns);
    copy_matrix(mtr_src, data, rows, columns);

    double mtr_dst[ROWS_MAX][COLUMNS_MAX] = {
    {0.653594771242, 0.000000000000, 0.000000000000, 0.000000000000, 0.265248790926, 0.000000000000, 0.000000000000, 0.000000000000, -0.754619604341, 0.000000000000, 0.000000000000, -0.082969821802, 0.000000000000, 0.000000000000, 0.000000000000},
    {0.000000000000, 0.959324635457, 0.000000000000, 0.000000000000, -2.453515691705, 0.000000000000, 0.000000000000, 0.000000000000, 6.980129990626, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000},
    {0.000000000000, 1.012403272000, 0.702497451318, 0.000000000000, -2.589266680308, -1.055329170733, 0.000000000000, 0.000000000000, 7.366334794618, -0.000165623389, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000},
    {0.000000000000, 0.000000000000, 0.000000000000, 0.763358778626, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000},
    {0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.639386189258, 0.000000000000, 0.000000000000, 0.000000000000, -1.819021875557, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000},
    {0.000000000000, -0.480382892066, 0.000000000000, 0.000000000000, 1.228600746973, 0.500751126690, 0.000000000000, 0.000000000000, -3.495307957249, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000},
    {0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.761556621735, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, -0.000560369840, 0.000000000000, 0.000000000000},
    {0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, -0.832913683656, 0.000000000000, 0.000000000000, 0.651338500619, 2.369597962036, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000},
    {0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.568990042674, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000},
    {0.000000000000, -0.000716063784, -0.000496870167, 0.000000000000, 0.001831365176, 0.000746424888, 0.000000000000, 0.000000000000, -0.005210142748, 0.000235880831, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000},
    {0.000000000000, 0.000000000000, 0.000000000000, -1.834997064005, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.600961538462, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000},
    {0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, -0.101457662529, 0.000000000000, 0.000000000000, 0.000000000000, 0.288641998660, 0.000000000000, 0.000000000000, 0.031735956839, 0.000000000000, 0.000000000000, 0.000000000000},
    {0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000183955409, 0.000000000000, 0.000000000000},
    {0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000002186024, 0.000000000000},
    {0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 2.541307959285, 0.000000000000, 0.000000000000, -1.987302824161, -7.229894621010, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.762776506484}
    };
    double *ptrs_dst[ROWS_MAX] = {mtr_dst[0], mtr_dst[1], mtr_dst[2], mtr_dst[3], mtr_dst[4], mtr_dst[5], mtr_dst[6], mtr_dst[7], mtr_dst[8], mtr_dst[9], mtr_dst[10], mtr_dst[11], mtr_dst[12], mtr_dst[13], mtr_dst[14]};

    
    double **mtr_res = NULL;

    rc = matrix_inverse(mtr_src, rows, columns, &mtr_res, &rows_res, &columns_res);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(rows_res, rows);
    ck_assert_int_eq(columns_res, columns);

    bool is_equal = are_double_matrixes_equal(ptrs_dst, rows_dst, columns_dst, mtr_res, rows_res, columns_res);
    ck_assert_int_eq(is_equal, true);

    mtr_free(mtr_src, rows);
    mtr_free(mtr_res, rows_res);

} 
END_TEST

//Матрица, у которой есть нули на главной диагонали
START_TEST(test_inverse_12x12_matrix_zeros_on_the_main_diagonal)
{
    int rc = OK;

    size_t rows = 12, columns = 12;
    size_t rows_dst = 12, columns_dst = 12;
    size_t rows_res = 0 , columns_res = 0;
    
    double data[ROWS_MAX][COLUMNS_MAX] = {
    {1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 2, 5, 0, 0, 7, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 3, 0},
    {0, 0, 0, 1, 0, 6, 0, 0, 0, 3, 0, 4},
    {5, 0, 0, 0, 1, 0, 0, 8, 0, 0, 4, 0},
    {0, 6, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 7, 0, 0, 6, 4},
    {0, 0, 0, 4, 0, 3, 0, 1, 0, 8, 0, 0},
    {0, 0, 0, 0, 9, 0, 0, 0, 1, 0, 0, 0},
    {0, 3, 4, 10, 0, 5, 0, 0, 3, 1, 0, 0},
    {0, 0, 11, 0, 0, 0, 7, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 1}
    };
    double **mtr_src = mtr_alloc(rows, columns);
    copy_matrix(mtr_src, data, rows, columns);

    double mtr_dst[ROWS_MAX][COLUMNS_MAX] = {
        {0.363563211703, -0.033479935485, -0.258056379194, 0.001863051220, 0.127287357659, -0.123544910524, 0.039531180493, 0.029598290101, -0.014143039740, 0.004714346580, 0.027832623986, -0.165576926853},
        {0.318218394148, 0.016739967742, 0.129028189597, -0.000931525610, -0.063643678830, 0.061772455262, -0.019765590247, -0.014799145051, 0.007071519870, -0.002357173290, -0.013916311993, 0.082788463427},
        {1.011465193302, -0.050025742894, 0.434052085174, 0.024206004626, -0.202293038660, -0.333408897051, -0.092708997718, 0.075211514374, 0.022477004296, -0.007492334765, 0.063269885425, 0.274011972367},
        {1.753206335057, 0.113288712317, 0.819023614302, 0.041957074685, -0.350641267011, -0.577908754889, -0.160695596044, 0.130366624915, 0.038960140779, -0.012986713593, -0.090332198597, 0.474954085436},
        {0.671351617192, 0.044288706341, 0.400368170342, 0.050254568617, -0.134270323438, -0.202778866408, -0.105808331135, 0.037100504868, 0.126030035938, -0.042010011979, -0.029173230464, 0.222215050073},
        {-0.766984546579, 0.058446871022, 0.196332470114, 0.186773019398, 0.153396909316, 0.252820832021, -0.195340664295, -0.133955261156, -0.017044101035, 0.005681367012, -0.030541061837, 0.034270579587},
        {-1.541280294556, 0.076229703457, -0.709031748837, -0.036885340383, 0.308256058911, 0.508051652650, 0.141270853665, -0.114608021903, -0.034250673212, 0.011416891071, 0.046445888876, -0.417542053130},
        {-0.142568427246, 0.007051247570, 0.016914563233, -0.003411893985, 0.028513685449, 0.046994777870, -0.026932446036, -0.010601242026, -0.003168187272, 0.001056062424, -0.003203755279, 0.121377360085},
        {-6.042164554725, -0.398598357065, -3.603313533078, -0.452291117549, 1.208432910945, 1.825009797669, 0.952274980213, -0.333904543813, -0.134270323438, 0.378090107813, 0.262559074178, -1.999935450654},
        {-0.571162909156, -0.079443338738, -0.485250803848, -0.090591932869, 0.114232581831, 0.188272218203, 0.156967102887, 0.111375065729, -0.012692509092, 0.004230836364, 0.057019466897, -0.265500680073},
        {-0.337155064434, 0.016675247631, 0.188649304942, -0.008068668209, 0.067431012887, 0.111136299017, 0.030902999239, -0.025070504791, -0.007492334765, 0.002497444922, -0.021089961808, -0.091337324122},
        {1.140547417971, -0.056409980558, -0.135316505860, 0.027295151883, -0.228109483594, -0.375958222961, 0.215459568288, 0.084809936208, 0.025345498177, -0.008448499392, 0.025630042232, 0.028981119316}
    };
    double *ptrs_dst[ROWS_MAX] = {mtr_dst[0], mtr_dst[1], mtr_dst[2], mtr_dst[3], mtr_dst[4], mtr_dst[5], mtr_dst[6], mtr_dst[7], mtr_dst[8], mtr_dst[9], mtr_dst[10], mtr_dst[11]};

    double **mtr_res = NULL;

    rc = matrix_inverse(mtr_src, rows, columns, &mtr_res, &rows_res, &columns_res);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(rows_res, rows);
    ck_assert_int_eq(columns_res, columns);

    bool is_equal = are_double_matrixes_equal(ptrs_dst, rows_dst, columns_dst, mtr_res, rows_res, columns_res);
    ck_assert_int_eq(is_equal, true);

    mtr_free(mtr_src, rows);
    mtr_free(mtr_res, rows_res);

} 
END_TEST

//Перемножение исходной и обратной к ней матрицы 1x1
START_TEST(test_multipli_inverse_1x1_and_src_matrix)
{
    int rc = OK;

    size_t rows_inverse = 1, columns_inverse = 1;
    size_t rows_src = 1, columns_src = 1;
    size_t rows_dst = 1, columns_dst = 1;
    size_t rows_res = 0 , columns_res = 0;
    
    double data[ROWS_MAX][COLUMNS_MAX] = {{2.0}};

    double **mtr_src = mtr_alloc(rows_src, columns_src);
    copy_matrix(mtr_src, data, rows_src, columns_src);

    double mtr_inverse[ROWS_MAX][COLUMNS_MAX] = {{0.5}};
    double *ptrs_inverse[ROWS_MAX] = {mtr_inverse[0], mtr_inverse[1], mtr_inverse[2], mtr_inverse[3], mtr_inverse[4]};
    
    //Результат умножения исходной и обратной матриц - единичная матрица
    double **mtr_dst = make_identity_matrix(rows_dst, columns_dst);

    double **mtr_res = NULL;

    rc = matrix_mul(mtr_src, rows_src, columns_src, ptrs_inverse, rows_inverse, columns_inverse, &mtr_res, &rows_res, &columns_res);

    ck_assert_int_eq(rc, OK);
    
    bool is_equal = are_double_matrixes_equal(mtr_res, rows_res, columns_res, mtr_dst, rows_dst, columns_dst);
    ck_assert_int_eq(is_equal, true);

    mtr_free(mtr_src, rows_src);
    mtr_free(mtr_res, rows_res);
    mtr_free(mtr_dst, rows_dst);

} 
END_TEST

//Перемножение исходной и обратной к ней матрицы 5x5
START_TEST(test_multipli_inverse_5x5_and_src_matrix)
{
    int rc = OK;

    size_t rows_inverse = 5, columns_inverse = 5;
    size_t rows_src = 5, columns_src = 5;
    size_t rows_dst = 5, columns_dst = 5;
    size_t rows_res = 0 , columns_res = 0;
    
    double data[ROWS_MAX][COLUMNS_MAX] = {{1.424, 2.6646, 3.88, 4.99, 5.001}, {6, 7, 8.85, 9.646, 10.535},\
                                            {11.654, 12, 13.64, 14.424, 15.666}, {16, 17.535, 18, 19.424, 20.2424},\
                                            {21.353, 22.3131, 23.7567, 24.777, 25.77}};

    double **mtr_src = mtr_alloc(rows_src, columns_src);
    copy_matrix(mtr_src, data, rows_src, columns_src);

    double mtr_inverse[ROWS_MAX][COLUMNS_MAX] = {
    {0.760706674510, -1.761860366808, 1.577281658263, -0.456951652773, -0.027279450414},
    {-1.114877670221, 1.562133534625, -1.565286796108, 1.094190281277, -0.330183467613},
    {-1.046229410928, 2.253167767183, -1.946745407001, -0.932907798554, 1.198179170520},
    {2.465852727735, -2.997589329532, 1.437388562362, -0.559712990606, 0.312754331328},
    {-1.071341384009, 0.912239144905, 0.461031267451, 0.829388084697, -1.057973703210}};
    
    double *ptrs_inverse[ROWS_MAX] = {mtr_inverse[0], mtr_inverse[1], mtr_inverse[2], mtr_inverse[3], mtr_inverse[4]};
    
    //Результат умножения исходной и обратной матриц - единичная матрица
    double **mtr_dst = make_identity_matrix(rows_dst, columns_dst);

    double **mtr_res = NULL;

    rc = matrix_mul( ptrs_inverse, rows_inverse, columns_inverse, mtr_src, rows_src, columns_src, &mtr_res, &rows_res, &columns_res);
    //rc = matrix_mul(mtr_src, rows_src, columns_src, ptrs_inverse, rows_inverse, columns_inverse, &mtr_res, &rows_res, &columns_res);
    mtr_print(stdout, mtr_res, rows_res, columns_res);
    puts("");
    //mtr_print(stdout, mtr_dst, rows_res, columns_res);
    ck_assert_int_eq(rc, OK);
    
    bool is_equal = are_double_matrixes_equal(mtr_res, rows_res, columns_res, mtr_dst, rows_dst, columns_dst);
    ck_assert_int_eq(is_equal, true);


    mtr_free(mtr_src, rows_src);
    mtr_free(mtr_res, rows_res);
    mtr_free(mtr_dst, rows_dst);

} 
END_TEST

/**
 * Негативные тесты нахождения обратной матрицы
 */

//Матрица 0x1
START_TEST(test_inverse_0x1_matrix)
{
    int rc = OK;

    size_t rows = 0, columns = 1;
    size_t rows_res = 0 , columns_res = 0;

    double data[][COLUMNS_MAX] = {{71,42}};
    
    double **mtr_src = mtr_alloc(1, columns);
    copy_matrix(mtr_src, data, rows, columns);

    double **mtr_res = NULL;

    rc = matrix_inverse(mtr_src, rows, columns, &mtr_res, &rows_res, &columns_res);
    
    ck_assert_int_ne(rc, OK);

    mtr_free(mtr_src, rows);
    mtr_free(mtr_res, rows_res);
} 
END_TEST

//Матрица 1x0
START_TEST(test_inverse_1x0_matrix)
{
    int rc = OK;

    size_t rows = 1, columns = 0;
    size_t rows_res = 0 , columns_res = 0;

    double data[][COLUMNS_MAX] = {{71,42}};
    
    double **mtr_src = mtr_alloc(rows, 1);
    copy_matrix(mtr_src, data, rows, columns);

    double **mtr_res = NULL;

    rc = matrix_inverse(mtr_src, rows, columns, &mtr_res, &rows_res, &columns_res);
    
    ck_assert_int_ne(rc, OK);

    mtr_free(mtr_src, rows);
    mtr_free(mtr_res, rows_res);
}
END_TEST

//Матрица 1x5
START_TEST(test_inverse_1x5_matrix)
{
    int rc = OK;

    size_t rows = 1, columns = 5;
    size_t rows_res = 0 , columns_res = 0;

    double data[ROWS_MAX][COLUMNS_MAX] = {{1, 2, 3, 4, 5}};
    
    double **mtr_src = mtr_alloc(rows, columns);
    copy_matrix(mtr_src, data, rows, columns);

    double **mtr_res = NULL;

    rc = matrix_inverse(mtr_src, rows, columns, &mtr_res, &rows_res, &columns_res);
    
    ck_assert_int_ne(rc, OK);

    mtr_free(mtr_src, rows);
    mtr_free(mtr_res, rows_res);
} 
END_TEST

//Вырожденная матрицаы
START_TEST(test_inverse_singular_matrix_matrix)
{
    int rc = OK;

    size_t rows = 3, columns = 3;
    size_t rows_res = 0 , columns_res = 0;

    double data[ROWS_MAX][COLUMNS_MAX] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    double **mtr_src = mtr_alloc(rows, columns);
    copy_matrix(mtr_src, data, rows, columns);

    double **mtr_res = NULL;

    rc = matrix_inverse(mtr_src, rows, columns, &mtr_res, &rows_res, &columns_res);
    
    ck_assert_int_ne(rc, OK);

    mtr_free(mtr_src, rows);
    mtr_free(mtr_res, rows_res);
} 
END_TEST

Suite* matrix_inverse_suite(void)
{
    Suite *suite;
    TCase *tc_pos, *tc_neg;

    suite = suite_create("matrix_inverse");
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_inverse_1x1_matrix);
    tcase_add_test(tc_pos, test_inverse_5x5_matrix);
    tcase_add_test(tc_pos, test_inverse_10x10_identity_matrix);
    tcase_add_test(tc_pos, test_inverse_15x15_sparse_matrix);
    tcase_add_test(tc_pos, test_inverse_12x12_matrix_zeros_on_the_main_diagonal);
    tcase_add_test(tc_pos, test_multipli_inverse_1x1_and_src_matrix);
    tcase_add_test(tc_pos, test_multipli_inverse_5x5_and_src_matrix);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_inverse_0x1_matrix);
    tcase_add_test(tc_neg, test_inverse_1x0_matrix);
    tcase_add_test(tc_neg, test_inverse_1x5_matrix);
    tcase_add_test(tc_neg, test_inverse_singular_matrix_matrix);
    
    suite_add_tcase(suite, tc_pos);
    suite_add_tcase(suite, tc_neg);

    return suite;
}
