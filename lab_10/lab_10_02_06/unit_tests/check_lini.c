#include "same_functions.h"
#include "check_lini.h"
#include "list.h"
#include "errors.h"
#include "matrix.h"

static char *filename1 = "tmp_in.txt";
static char *filename2 = "tmp_lin.txt";

/*
    Юнит тесты lin матриц
*/

//lin матриц 1x1
START_TEST(test_lin_1x1_matrix)
{
    int rc = OK;
    node_t *mtr_lin = NULL, *mtr = NULL;

    size_t rows1 = 3;
    size_t columns1 = 3;
    int src_mtr1[ROWS_MAX][COLUMNS_MAX] = { { 1 } };

    size_t rows_lin = 0;
    size_t columns_lin = 0;
    int src_mtr_lin[ROWS_MAX][COLUMNS_MAX] = { { 0 } };
    
    FILE *file = NULL;
    //Запись матрицы в файл
    {
        file = fopen(filename1, "w");
        ck_assert_ptr_nonnull(file);

        rc = print_mtr(file, src_mtr1, rows1, columns1);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }

    //Запись lin матрицы в файл
    {
        file = fopen(filename2, "w");
        ck_assert_ptr_nonnull(file);

        rc = print_mtr(file, src_mtr_lin, rows_lin, columns_lin);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }
    
    //Чтение матрицы
    {
        file = fopen(filename1, "r");
        ck_assert_ptr_nonnull(file);

        rc = matrix_read(file, &mtr);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }

    //Чтение lin матрицы
    {
        file = fopen(filename2, "r");
        ck_assert_ptr_nonnull(file);

        rc = matrix_read(file, &mtr_lin);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }   

    //Выполнение lin
    matrix_lin(&mtr);
    bool equal = my_check_lists_equal(mtr_lin, mtr);
    ck_assert_int_eq(equal, true);

    matrix_free(&mtr);
    matrix_free(&mtr_lin);
}
END_TEST


//lin матрицы 2x2
START_TEST(test_lin_2x2_matrix)
{
    int rc = OK;
    node_t *mtr = NULL;

    size_t rows1 = 2;
    size_t columns1 = 2;
    int src_mtr1[ROWS_MAX][COLUMNS_MAX] = { { 1, 2 }, { -1, -2} };

    node_t src_mtr_lin[] = { { 1, 0, -1, NULL }, { 1, 1, -2, NULL } }; 
    size_t length = sizeof(src_mtr_lin) / sizeof(src_mtr_lin[0]);

    FILE *file = NULL;
    //Запись матрицы в файл
    {
        file = fopen(filename1, "w");
        ck_assert_ptr_nonnull(file);

        rc = print_mtr(file, src_mtr1, rows1, columns1);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }
    
    //Чтение матрицы
    {
        file = fopen(filename1, "r");
        ck_assert_ptr_nonnull(file);

        rc = matrix_read(file, &mtr);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }

    //Выполнение lin
    matrix_lin(&mtr);

    bool equal = my_check_list_and_arr_equal(mtr, src_mtr_lin, length);
    ck_assert_int_eq(equal, true);

    matrix_free(&mtr);
}
END_TEST

//lin матрицы 5x1
START_TEST(test_lin_5x1_matrix)
{
    int rc = OK;
    node_t *mtr = NULL;

    size_t rows1 = 5;
    size_t columns1 = 1;
    int src_mtr1[ROWS_MAX][COLUMNS_MAX] = { { 1 }, { 2 }, { 3 }, { 5 }, { 4 }  };

    node_t src_mtr_lin[] = { { 0, 0, 1, NULL }, { 1, 0, 2, NULL }, { 2, 0, 3, NULL }, { 4, 0, 4, NULL } }; 
    size_t length = sizeof(src_mtr_lin) / sizeof(src_mtr_lin[0]);

    FILE *file = NULL;
    //Запись матрицы в файл
    {
        file = fopen(filename1, "w");
        ck_assert_ptr_nonnull(file);

        rc = print_mtr(file, src_mtr1, rows1, columns1);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }
    
    //Чтение матрицы
    {
        file = fopen(filename1, "r");
        ck_assert_ptr_nonnull(file);

        rc = matrix_read(file, &mtr);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }

    //Выполнение lin
    matrix_lin(&mtr);

    bool equal = my_check_list_and_arr_equal(mtr, src_mtr_lin, length);
    ck_assert_int_eq(equal, true);

    matrix_free(&mtr);
}
END_TEST

//lin матрицы 3x2 
START_TEST(test_lin_3x2_matrix)
{
    int rc = OK;
    node_t *mtr = NULL;

    size_t rows1 = 3;
    size_t columns1 = 2;
    int src_mtr1[ROWS_MAX][COLUMNS_MAX] = { { 1, 0 },  { 1, 2 }, { -1, 4} };

    node_t src_mtr_lin[] = { { 0, 0, 1, NULL }, { 1, 0, 1, NULL }, { 1, 1, 2, NULL } }; 
    size_t length = sizeof(src_mtr_lin) / sizeof(src_mtr_lin[0]);

    FILE *file = NULL;
    //Запись матрицы в файл
    {
        file = fopen(filename1, "w");
        ck_assert_ptr_nonnull(file);

        rc = print_mtr(file, src_mtr1, rows1, columns1);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }
    
    //Чтение матрицы
    {
        file = fopen(filename1, "r");
        ck_assert_ptr_nonnull(file);

        rc = matrix_read(file, &mtr);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }

    //Выполнение lin
    matrix_lin(&mtr);
    
    bool equal = my_check_list_and_arr_equal(mtr, src_mtr_lin, length);
    ck_assert_int_eq(equal, true);

    matrix_free(&mtr);
}
END_TEST

Suite* test_lin(void)
{
    Suite *suite;
    TCase *tc_pos;

    suite = suite_create("mul");
    
    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, test_lin_1x1_matrix);
    tcase_add_test(tc_pos, test_lin_2x2_matrix);
    tcase_add_test(tc_pos, test_lin_5x1_matrix);
    tcase_add_test(tc_pos, test_lin_3x2_matrix);

    suite_add_tcase(suite, tc_pos);

    return suite;
}
