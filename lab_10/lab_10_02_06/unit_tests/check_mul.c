#include "same_functions.h"
#include "check_mul.h"
#include "list.h"
#include "errors.h"
#include "matrix.h"

static char *filename1 = "tmp_in1.txt";
static char *filename2 = "tmp_in2.txt";
static char *filename3 = "tmp_mul.txt";

/*
    Юнит тесты умножения матриц
*/

//умножения матриц 1x1
START_TEST(test_mul_1x1_and_1x1_matrix)
{
    int rc = OK;
    node_t *mtr_mul = NULL, *mtr1 = NULL, *mtr2 = NULL, *mtr_ans = NULL;

    size_t rows1 = 3;
    size_t columns1 = 3;
    int src_mtr1[ROWS_MAX][COLUMNS_MAX] = { { 1 } };

    size_t rows2 = 3;
    size_t columns2 = 3;
    int src_mtr2[ROWS_MAX][COLUMNS_MAX] = { { 2 } };

    size_t rows_mul = 3;
    size_t columns_mul = 3;
    int src_mtr_mul[ROWS_MAX][COLUMNS_MAX] = { { 2 } };
    
    FILE *file = NULL;
    //Запись первой матрицы в файл
    {
        file = fopen(filename1, "w");
        ck_assert_ptr_nonnull(file);

        rc = print_mtr(file, src_mtr1, rows1, columns1);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }
    
    //Запись второй матрицы в файл
    {
        file = fopen(filename2, "w");
        ck_assert_ptr_nonnull(file);

        rc = print_mtr(file, src_mtr2, rows2, columns2);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }

    //Запись суммы матриц в файл
    {
        file = fopen(filename3, "w");
        ck_assert_ptr_nonnull(file);

        rc = print_mtr(file, src_mtr_mul, rows_mul, columns_mul);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }
    
    //Чтение первой матрицы
    {
        file = fopen(filename1, "r");
        ck_assert_ptr_nonnull(file);

        rc = matrix_read(file, &mtr1);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }

    //Чтение второй матрицы
    {
        file = fopen(filename2, "r");
        ck_assert_ptr_nonnull(file);

        rc = matrix_read(file, &mtr2);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }   

    //Чтение суммы матриц
    {
        file = fopen(filename3, "r");
        ck_assert_ptr_nonnull(file);

        rc = matrix_read(file, &mtr_mul);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }   

    //Выполнение сложения
    rc = matrix_mul(&mtr_ans, mtr1, mtr2);
    ck_assert_int_eq(rc, OK);

    bool equal = my_check_lists_equal(mtr_ans, mtr_mul);
    ck_assert_int_eq(equal, true);

    matrix_free(&mtr1);
    matrix_free(&mtr2);
    matrix_free(&mtr_mul);
    matrix_free(&mtr_ans);
}
END_TEST


//Умножение матриц 3x3
START_TEST(test_mul_3x3_and_3x3_matrix)
{
    int rc = OK;
    node_t *mtr_mul = NULL, *mtr1 = NULL, *mtr2 = NULL, *mtr_ans = NULL;

    size_t rows1 = 3;
    size_t columns1 = 3;
    int src_mtr1[ROWS_MAX][COLUMNS_MAX] = { { 1, 2, 0 }, {0, 0, 1}, {0, 5, 6} };

    size_t rows2 = 3;
    size_t columns2 = 3;
    int src_mtr2[ROWS_MAX][COLUMNS_MAX] = { { 0, 4, 1 }, {1, 0, 0}, {0, 0, -9} };
    
    size_t rows_mul = 3;
    size_t columns_mul = 3;
    int src_mtr_mul[ROWS_MAX][COLUMNS_MAX] = { { 2, 4, 1 }, {0, 0, -9}, {5, 0, -54} };
    

    FILE *file = NULL;
    //Запись первой матрицы в файл
    {
        file = fopen(filename1, "w");
        ck_assert_ptr_nonnull(file);

        rc = print_mtr(file, src_mtr1, rows1, columns1);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }
    
    //Запись второй матрицы в файл
    {
        file = fopen(filename2, "w");
        ck_assert_ptr_nonnull(file);

        rc = print_mtr(file, src_mtr2, rows2, columns2);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }

    //Запись суммы матриц в файл
    {
        file = fopen(filename3, "w");
        ck_assert_ptr_nonnull(file);

        rc = print_mtr(file, src_mtr_mul, rows_mul, columns_mul);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }
    
    //Чтение первой матрицы
    {
        file = fopen(filename1, "r");
        ck_assert_ptr_nonnull(file);

        rc = matrix_read(file, &mtr1);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }

    //Чтение второй матрицы
    {
        file = fopen(filename2, "r");
        ck_assert_ptr_nonnull(file);

        rc = matrix_read(file, &mtr2);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }   

    //Чтение суммы матриц
    {
        file = fopen(filename3, "r");
        ck_assert_ptr_nonnull(file);

        rc = matrix_read(file, &mtr_mul);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }   

    //Выполнение сложения
    rc = matrix_mul(&mtr_ans, mtr1, mtr2);
    ck_assert_int_eq(rc, OK);

    bool equal = my_check_lists_equal(mtr_ans, mtr_mul);
    ck_assert_int_eq(equal, true);
    
    matrix_free(&mtr1);
    matrix_free(&mtr2);
    matrix_free(&mtr_mul);
    matrix_free(&mtr_ans);
}
END_TEST

//Умножение матриц 5x1 и 1x5
START_TEST(test_mul_5x1_and_1x5_matrix)
{
    int rc = OK;
    node_t *mtr_mul = NULL, *mtr1 = NULL, *mtr2 = NULL, *mtr_ans = NULL;

    size_t rows1 = 5;
    size_t columns1 = 1;
    int src_mtr1[ROWS_MAX][COLUMNS_MAX] = { { 1 }, { 2 }, { 3 }, { 4 }, { 5 } };

    size_t rows2 = 1;
    size_t columns2 = 5;
    int src_mtr2[ROWS_MAX][COLUMNS_MAX] = { { 1, 2, 3, 4, 5 } }; 
    
    size_t rows_mul = 5;
    size_t columns_mul = 5;
    int src_mtr_mul[ROWS_MAX][COLUMNS_MAX] = { { 1, 2, 3, 4, 5 }, { 2, 4, 6, 8, 10 }, { 3, 6, 9, 12, 15 }, { 4, 8, 12, 16, 20 }, { 5, 10, 15, 20, 25} };
    

    FILE *file = NULL;
    //Запись первой матрицы в файл
    {
        file = fopen(filename1, "w");
        ck_assert_ptr_nonnull(file);

        rc = print_mtr(file, src_mtr1, rows1, columns1);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }
    
    //Запись второй матрицы в файл
    {
        file = fopen(filename2, "w");
        ck_assert_ptr_nonnull(file);

        rc = print_mtr(file, src_mtr2, rows2, columns2);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }

    //Запись суммы матриц в файл
    {
        file = fopen(filename3, "w");
        ck_assert_ptr_nonnull(file);

        rc = print_mtr(file, src_mtr_mul, rows_mul, columns_mul);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }
    
    //Чтение первой матрицы
    {
        file = fopen(filename1, "r");
        ck_assert_ptr_nonnull(file);

        rc = matrix_read(file, &mtr1);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }

    //Чтение второй матрицы
    {
        file = fopen(filename2, "r");
        ck_assert_ptr_nonnull(file);

        rc = matrix_read(file, &mtr2);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }   

    //Чтение суммы матриц
    {
        file = fopen(filename3, "r");
        ck_assert_ptr_nonnull(file);

        rc = matrix_read(file, &mtr_mul);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }   

    //Выполнение сложения
    rc = matrix_mul(&mtr_ans, mtr1, mtr2);
    ck_assert_int_eq(rc, OK);

    bool equal = my_check_lists_equal(mtr_ans, mtr_mul);
    ck_assert_int_eq(equal, true);

    matrix_free(&mtr1);
    matrix_free(&mtr2);
    matrix_free(&mtr_mul);
    matrix_free(&mtr_ans);
}
END_TEST

//Умножение матриц 3x2 и 3x2
START_TEST(test_mul_3x2_and_3x2_matrix)
{
    int rc = OK;
    node_t *mtr_mul = NULL, *mtr1 = NULL, *mtr2 = NULL, *mtr_ans = NULL;

    size_t rows1 = 3;
    size_t columns1 = 2;
    int src_mtr1[ROWS_MAX][COLUMNS_MAX] = { { 1, 0 }, { 0, 2 }, { 1, 2 } };

    size_t rows2 = 3;
    size_t columns2 = 2;
    int src_mtr2[ROWS_MAX][COLUMNS_MAX] = { { 0, 2 }, { 0, 0 }, { 1, 2 } };
    
    size_t rows_mul = 3;
    size_t columns_mul = 3;
    int src_mtr_mul[ROWS_MAX][COLUMNS_MAX] = { { 0, 2, 0 }, { 0, 0, 0 }, { 0, 2, 0 } };
    

    FILE *file = NULL;
    //Запись первой матрицы в файл
    {
        file = fopen(filename1, "w");
        ck_assert_ptr_nonnull(file);

        rc = print_mtr(file, src_mtr1, rows1, columns1);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }
    
    //Запись второй матрицы в файл
    {
        file = fopen(filename2, "w");
        ck_assert_ptr_nonnull(file);

        rc = print_mtr(file, src_mtr2, rows2, columns2);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }

    //Запись суммы матриц в файл
    {
        file = fopen(filename3, "w");
        ck_assert_ptr_nonnull(file);

        rc = print_mtr(file, src_mtr_mul, rows_mul, columns_mul);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }
    
    //Чтение первой матрицы
    {
        file = fopen(filename1, "r");
        ck_assert_ptr_nonnull(file);

        rc = matrix_read(file, &mtr1);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }

    //Чтение второй матрицы
    {
        file = fopen(filename2, "r");
        ck_assert_ptr_nonnull(file);

        rc = matrix_read(file, &mtr2);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }   

    //Чтение суммы матриц
    {
        file = fopen(filename3, "r");
        ck_assert_ptr_nonnull(file);

        rc = matrix_read(file, &mtr_mul);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }   

    //Выполнение сложения
    rc = matrix_mul(&mtr_ans, mtr1, mtr2);
    ck_assert_int_eq(rc, OK);

    bool equal = my_check_lists_equal(mtr_ans, mtr_mul);
    ck_assert_int_eq(equal, true);

    matrix_free(&mtr1);
    matrix_free(&mtr2);
    matrix_free(&mtr_mul);
    matrix_free(&mtr_ans);
}
END_TEST


//Умножение матриц 2x1 и 1x1
START_TEST(test_mul_2x1_and_1x1_matrix)
{
    int rc = OK;
    node_t *mtr_mul = NULL, *mtr1 = NULL, *mtr2 = NULL, *mtr_ans = NULL;

    size_t rows1 = 2;
    size_t columns1 = 1;
    int src_mtr1[ROWS_MAX][COLUMNS_MAX] = { { 1 }, { 2 } };

    size_t rows2 = 1;
    size_t columns2 = 1;
    int src_mtr2[ROWS_MAX][COLUMNS_MAX] = { { 5 } };
    
    size_t rows_mul = 2;
    size_t columns_mul = 2;
    int src_mtr_mul[ROWS_MAX][COLUMNS_MAX] = { { 5, 0 }, { 10, 0 } };
    

    FILE *file = NULL;
    //Запись первой матрицы в файл
    {
        file = fopen(filename1, "w");
        ck_assert_ptr_nonnull(file);

        rc = print_mtr(file, src_mtr1, rows1, columns1);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }
    
    //Запись второй матрицы в файл
    {
        file = fopen(filename2, "w");
        ck_assert_ptr_nonnull(file);

        rc = print_mtr(file, src_mtr2, rows2, columns2);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }

    //Запись суммы матриц в файл
    {
        file = fopen(filename3, "w");
        ck_assert_ptr_nonnull(file);

        rc = print_mtr(file, src_mtr_mul, rows_mul, columns_mul);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }
    
    //Чтение первой матрицы
    {
        file = fopen(filename1, "r");
        ck_assert_ptr_nonnull(file);

        rc = matrix_read(file, &mtr1);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }

    //Чтение второй матрицы
    {
        file = fopen(filename2, "r");
        ck_assert_ptr_nonnull(file);

        rc = matrix_read(file, &mtr2);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }   

    //Чтение суммы матриц
    {
        file = fopen(filename3, "r");
        ck_assert_ptr_nonnull(file);

        rc = matrix_read(file, &mtr_mul);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }   

    //Выполнение сложения
    rc = matrix_mul(&mtr_ans, mtr1, mtr2);
    ck_assert_int_eq(rc, OK);

    bool equal = my_check_lists_equal(mtr_ans, mtr_mul);
    ck_assert_int_eq(equal, true);

    matrix_free(&mtr1);
    matrix_free(&mtr2);
    matrix_free(&mtr_mul);
    matrix_free(&mtr_ans);
}
END_TEST

START_TEST(test_mul_1x2_and_3x4_matrix)
{
    int rc = OK;
    node_t *mtr_mul = NULL, *mtr1 = NULL, *mtr2 = NULL, *mtr_ans = NULL;

    size_t rows1 = 1;
    size_t columns1 = 2;
    int src_mtr1[ROWS_MAX][COLUMNS_MAX] = { { 1, 0 } };

    size_t rows2 = 3;
    size_t columns2 = 4;
    int src_mtr2[ROWS_MAX][COLUMNS_MAX] = { { 0, 2, 0, 5 }, { 1, 2, 3, 4 }, { 0, 2, 0, 0 } };
    
    size_t rows_mul = 4;
    size_t columns_mul = 4;
    int src_mtr_mul[ROWS_MAX][COLUMNS_MAX] = { { 0, 2, 0, 5 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } };
    

    FILE *file = NULL;
    //Запись первой матрицы в файл
    {
        file = fopen(filename1, "w");
        ck_assert_ptr_nonnull(file);

        rc = print_mtr(file, src_mtr1, rows1, columns1);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }
    
    //Запись второй матрицы в файл
    {
        file = fopen(filename2, "w");
        ck_assert_ptr_nonnull(file);

        rc = print_mtr(file, src_mtr2, rows2, columns2);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }

    //Запись суммы матриц в файл
    {
        file = fopen(filename3, "w");
        ck_assert_ptr_nonnull(file);

        rc = print_mtr(file, src_mtr_mul, rows_mul, columns_mul);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }
    
    //Чтение первой матрицы
    {
        file = fopen(filename1, "r");
        ck_assert_ptr_nonnull(file);

        rc = matrix_read(file, &mtr1);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }

    //Чтение второй матрицы
    {
        file = fopen(filename2, "r");
        ck_assert_ptr_nonnull(file);

        rc = matrix_read(file, &mtr2);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }   

    //Чтение суммы матриц
    {
        file = fopen(filename3, "r");
        ck_assert_ptr_nonnull(file);

        rc = matrix_read(file, &mtr_mul);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }   

    //Выполнение сложения
    rc = matrix_mul(&mtr_ans, mtr1, mtr2);
    ck_assert_int_eq(rc, OK);

    bool equal = my_check_lists_equal(mtr_ans, mtr_mul);
    ck_assert_int_eq(equal, true);

    matrix_free(&mtr1);
    matrix_free(&mtr2);
    matrix_free(&mtr_mul);
    matrix_free(&mtr_ans);
}
END_TEST

//Сложение матриц 3x1 и 2x2
START_TEST(test_mul_3x1_and_2x2_matrix)
{
    int rc = OK;
    node_t *mtr_mul = NULL, *mtr1 = NULL, *mtr2 = NULL, *mtr_ans = NULL;

    size_t rows1 = 3;
    size_t columns1 = 1;
    int src_mtr1[ROWS_MAX][COLUMNS_MAX] = { { 1 }, { 0 }, { 1 } };

    size_t rows2 = 2;
    size_t columns2 = 2;
    int src_mtr2[ROWS_MAX][COLUMNS_MAX] = { { 0, 5 }, { 1, 4 }, };
    
    size_t rows_mul = 3;
    size_t columns_mul = 3;
    int src_mtr_mul[ROWS_MAX][COLUMNS_MAX] = { { 0, 5, 0 }, { 0, 0, 0 }, { 0, 5, 0 } };
    

    FILE *file = NULL;
    //Запись первой матрицы в файл
    {
        file = fopen(filename1, "w");
        ck_assert_ptr_nonnull(file);

        rc = print_mtr(file, src_mtr1, rows1, columns1);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }
    
    //Запись второй матрицы в файл
    {
        file = fopen(filename2, "w");
        ck_assert_ptr_nonnull(file);

        rc = print_mtr(file, src_mtr2, rows2, columns2);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }

    //Запись суммы матриц в файл
    {
        file = fopen(filename3, "w");
        ck_assert_ptr_nonnull(file);

        rc = print_mtr(file, src_mtr_mul, rows_mul, columns_mul);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }
    
    //Чтение первой матрицы
    {
        file = fopen(filename1, "r");
        ck_assert_ptr_nonnull(file);

        rc = matrix_read(file, &mtr1);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }

    //Чтение второй матрицы
    {
        file = fopen(filename2, "r");
        ck_assert_ptr_nonnull(file);

        rc = matrix_read(file, &mtr2);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }   

    //Чтение суммы матриц
    {
        file = fopen(filename3, "r");
        ck_assert_ptr_nonnull(file);

        rc = matrix_read(file, &mtr_mul);
        ck_assert_int_eq(rc, OK);

        fclose(file);
    }   

    //Выполнение сложения
    rc = matrix_mul(&mtr_ans, mtr1, mtr2);
    ck_assert_int_eq(rc, OK);

    bool equal = my_check_lists_equal(mtr_ans, mtr_mul);
    ck_assert_int_eq(equal, true);

    matrix_free(&mtr1);
    matrix_free(&mtr2);
    matrix_free(&mtr_mul);
    matrix_free(&mtr_ans);
}
END_TEST


Suite* test_mul(void)
{
    Suite *suite;
    TCase *tc_pos;

    suite = suite_create("mul");
    
    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, test_mul_1x1_and_1x1_matrix);
    tcase_add_test(tc_pos, test_mul_3x3_and_3x3_matrix);
    tcase_add_test(tc_pos, test_mul_5x1_and_1x5_matrix);
    
    //Нестандартные размер
    tcase_add_test(tc_pos, test_mul_3x2_and_3x2_matrix);
    tcase_add_test(tc_pos, test_mul_1x2_and_3x4_matrix);
    tcase_add_test(tc_pos, test_mul_2x1_and_1x1_matrix);
    tcase_add_test(tc_pos, test_mul_3x1_and_2x2_matrix);

    suite_add_tcase(suite, tc_pos);

    return suite;
}
