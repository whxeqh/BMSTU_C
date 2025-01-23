#include <stdlib.h>

#include "same_functions.h"
#include "check_matrix_read.h"
#include "node.h"
#include "matrix.h"
#include "errors.h"

static char *filename = "tmp_in.txt";

/*
    Юнит тесты чтение матрицы из входного потока в односвязный список
*/

//Пустая матрица 3x3
START_TEST(mtr_3x3_empty)
{
    int rc = OK;
    node_t *mtr_ans = NULL;
    //node_t mtr_src[] = { { 0, 0, 0, NULL} }; 
    //size_t length = sizeof(mtr_src) / sizeof(mtr_src[0]);

    size_t rows = 3;
    size_t columns = 3;
    int mtr[ROWS_MAX][COLUMNS_MAX] = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
    
    FILE *file = fopen(filename, "w");
    ck_assert_ptr_nonnull(file);

    rc = print_mtr(file, mtr, rows, columns);
    ck_assert_int_eq(rc, OK);

    fclose(file);

    file = fopen(filename, "r");
    ck_assert_ptr_nonnull(file);

    rc = matrix_read(file, &mtr_ans);
    ck_assert_int_eq(rc, OK);

    fclose(file);

    ck_assert_int_eq(list_length(mtr_ans), 0);
    //my_check_list_equal(mtr_ans, mtr_src, length);

    matrix_free(&mtr_ans);
}
END_TEST


//Один ненулевой элемент в матрице 3x3
START_TEST(mtr_3x3_one_nonzero)
{
    int rc = OK;
    node_t *mtr_ans = NULL;
    node_t mtr_src[] = { { 1, 1, 5, NULL} }; 
    size_t length = sizeof(mtr_src) / sizeof(mtr_src[0]);

    size_t rows = 3;
    size_t columns = 3;
    int mtr[ROWS_MAX][COLUMNS_MAX] = { {0, 0, 0}, {0, 5, 0}, {0, 0, 0} };
    
    FILE *file = fopen(filename, "w");
    ck_assert_ptr_nonnull(file);

    rc = print_mtr(file, mtr, rows, columns);
    ck_assert_int_eq(rc, OK);

    fclose(file);

    file = fopen(filename, "r");
    ck_assert_ptr_nonnull(file);

    rc = matrix_read(file, &mtr_ans);
    ck_assert_int_eq(rc, OK);

    fclose(file);

    my_check_list_and_arr_equal(mtr_ans, mtr_src, length);

    matrix_free(&mtr_ans);
}
END_TEST

//В каждой строке есть ровно один ненулевой элемент
START_TEST(mtr_3x3_one_nonzero_in_all_rows)
{
    int rc = OK;
    node_t *mtr_ans = NULL;
    node_t mtr_src[] = { { 0, 2, 1, NULL}, { 1, 1, 5, NULL}, { 2, 0, 2, NULL} }; 
    size_t length = sizeof(mtr_src) / sizeof(mtr_src[0]);

    size_t rows = 3;
    size_t columns = 3;
    int mtr[ROWS_MAX][COLUMNS_MAX] = { {0, 0, 1}, {0, 5, 0}, {2, 0, 0} };
    
    FILE *file = fopen(filename, "w");
    ck_assert_ptr_nonnull(file);

    rc = print_mtr(file, mtr, rows, columns);
    ck_assert_int_eq(rc, OK);

    fclose(file);

    file = fopen(filename, "r");
    ck_assert_ptr_nonnull(file);

    rc = matrix_read(file, &mtr_ans);
    ck_assert_int_eq(rc, OK);

    fclose(file);

    my_check_list_and_arr_equal(mtr_ans, mtr_src, length);

    matrix_free(&mtr_ans);
}
END_TEST

//В каждой строке есть несколько ненулевых элементов
START_TEST(mtr_3x3_several_nonzero_in_all_rows)
{
    int rc = OK;
    node_t *mtr_ans = NULL;
    node_t mtr_src[] = { { 0, 0, 4, NULL}, { 0, 2, 1, NULL}, { 1, 1, 5, NULL}, { 1, 2, -1, NULL}, { 2, 0, 2, NULL}, { 2, 1, 3, NULL} }; 
    size_t length = sizeof(mtr_src) / sizeof(mtr_src[0]);

    size_t rows = 3;
    size_t columns = 3;
    int mtr[ROWS_MAX][COLUMNS_MAX] = { {4, 0, 1}, {0, 5, -1}, {2, 3, 0} };
    
    FILE *file = fopen(filename, "w");
    ck_assert_ptr_nonnull(file);

    rc = print_mtr(file, mtr, rows, columns);
    ck_assert_int_eq(rc, OK);

    fclose(file);

    file = fopen(filename, "r");
    ck_assert_ptr_nonnull(file);

    rc = matrix_read(file, &mtr_ans);
    ck_assert_int_eq(rc, OK);

    fclose(file);

    my_check_list_and_arr_equal(mtr_ans, mtr_src, length);

    matrix_free(&mtr_ans);
}
END_TEST

//Матрца полностью заполнена
START_TEST(mtr_3x3_all_nonzero)
{
    int rc = OK;
    node_t *mtr_ans = NULL;
    node_t mtr_src[] = { { 0, 0, 4, NULL}, { 0, 1, 7, NULL}, { 0, 2, 1, NULL}, { 1, 0, 8, NULL}, { 1, 1, 5, NULL}, { 1, 2, -1, NULL}, { 2, 0, 2, NULL}, { 2, 1, 3, NULL}, { 2, 2, 9, NULL} }; 
    size_t length = sizeof(mtr_src) / sizeof(mtr_src[0]);

    size_t rows = 3;
    size_t columns = 3;
    int mtr[ROWS_MAX][COLUMNS_MAX] = { {4, 7, 1}, {8, 5, -1}, {2, 3, 9} };
    
    FILE *file = fopen(filename, "w");
    ck_assert_ptr_nonnull(file);

    rc = print_mtr(file, mtr, rows, columns);
    ck_assert_int_eq(rc, OK);

    fclose(file);

    file = fopen(filename, "r");
    ck_assert_ptr_nonnull(file);

    rc = matrix_read(file, &mtr_ans);
    ck_assert_int_eq(rc, OK);

    fclose(file);

    my_check_list_and_arr_equal(mtr_ans, mtr_src, length);

    matrix_free(&mtr_ans);
}
END_TEST

//Прямоугольная матрица не полностью заполнена
START_TEST(mtr_3x2_not_all_nonzero)
{
    int rc = OK;
    node_t *mtr_ans = NULL;
    node_t mtr_src[] = { { 0, 0, 4, NULL}, { 0, 1, 7, NULL}, { 1, 1, 5, NULL}, { 1, 2, -1, NULL} }; 
    size_t length = sizeof(mtr_src) / sizeof(mtr_src[0]);

    size_t rows = 3;
    size_t columns = 2;
    int mtr[ROWS_MAX][COLUMNS_MAX] = { {4, 7, 0}, {0, 5, -1} };
    
    FILE *file = fopen(filename, "w");
    ck_assert_ptr_nonnull(file);

    rc = print_mtr(file, mtr, rows, columns);
    ck_assert_int_eq(rc, OK);

    fclose(file);

    file = fopen(filename, "r");
    ck_assert_ptr_nonnull(file);

    rc = matrix_read(file, &mtr_ans);
    ck_assert_int_eq(rc, OK);

    fclose(file);

    my_check_list_and_arr_equal(mtr_ans, mtr_src, length);

    matrix_free(&mtr_ans);
}
END_TEST

Suite* test_matrix_read(void)
{
    Suite *suite;
    TCase *tc_pos;

    suite = suite_create("matrix_read");
    
    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, mtr_3x3_empty);
    tcase_add_test(tc_pos, mtr_3x3_one_nonzero);
    tcase_add_test(tc_pos, mtr_3x3_one_nonzero_in_all_rows);
    tcase_add_test(tc_pos, mtr_3x3_several_nonzero_in_all_rows);
    tcase_add_test(tc_pos, mtr_3x3_all_nonzero);
    tcase_add_test(tc_pos, mtr_3x2_not_all_nonzero);

    suite_add_tcase(suite, tc_pos);

    return suite;
}
