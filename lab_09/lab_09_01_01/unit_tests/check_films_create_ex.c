#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#include "check_films_create_ex.h"
#include "film_array.h"
#include "film.h"
#include "errors.h"

bool is_films_equal(const film_t *pleft, const film_t *pright)
{
    assert(pleft);
    assert(pright);

    int cmp_title = film_cmp_by_title(pleft, pright);
    if (cmp_title)
        return false;

    int cmp_name = film_cmp_by_name(pleft, pright);
    if (cmp_name)
        return false;

    int cmp_year = film_cmp_by_year(pleft, pright);
    if (cmp_year)
        return false;
    
    return true;
}

bool is_films_arrays_equal(const film_t *left_arr, const size_t left_length, \
                     const film_t *right_arr, const size_t right_length)
{
    assert(left_arr);
    assert(right_arr);
    
    if (left_length != right_length)
        return false;
    
    for (size_t i = 0; i < left_length; i++)
    {
        if (is_films_equal(&left_arr[i], &right_arr[i]) == false)
            return false;
    }

    return true;
}

/*
 * ----------------------------------------------------------------------------------------------------------------------
 *
 * Юнит тесты Создания массива по данным из текстового файла. Поизитивы
 *
 * ----------------------------------------------------------------------------------------------------------------------
*/

// Один фильм в файле. Ключ title
START_TEST (pos_one_film_title)
{
    film_t src[] = {
        {"La La Land", "Ryan Gosling", 2016},
    };
    size_t length_src = sizeof(src) / sizeof(src[0]);

    char *filename = "func_tests/data/pos_01_in.txt";
    film_t *dst;
    size_t length_dst;

    int rc = films_create_ex(filename, &dst, &length_dst, film_cmp_by_title);
    ck_assert_int_eq(rc, OK);

    bool equal = is_films_arrays_equal(src, length_src, dst, length_dst);
    ck_assert_int_eq(equal, true); 

    films_free(dst, length_dst);
}
END_TEST

// Два фильма в файле. Отсортированы по ключу title
START_TEST (pos_two_sorted_films_title)
{
    film_t src[] = {
        {"La La Land  ", "Ryan Gosling  ", 2016},
        {"The Wolf of Wall Street", "Margot Robbie", 2013}
    };
    size_t length_src = sizeof(src) / sizeof(src[0]);

    char *filename = "func_tests/data/pos_02_in.txt";
    film_t *dst;
    size_t length_dst;

    int rc = films_create_ex(filename, &dst, &length_dst, film_cmp_by_title);
    ck_assert_int_eq(rc, OK);

    bool equal = is_films_arrays_equal(src, length_src, dst, length_dst);
    ck_assert_int_eq(equal, true); 

    films_free(dst, length_dst);
}
END_TEST

// Два фильма в файле. Отсортированы в обратном порядке по ключу title
START_TEST (pos_two_unsorted_films_title)
{
    film_t src[] = {
        {"La La Land  ", "Ryan Gosling  ", 2016},
        {"The Wolf of Wall Street", "Margot Robbie  ", 2013}
    };
    size_t length_src = sizeof(src) / sizeof(src[0]);

    char *filename = "func_tests/data/pos_03_in.txt";
    film_t *dst;
    size_t length_dst;

    int rc = films_create_ex(filename, &dst, &length_dst, film_cmp_by_title);
    ck_assert_int_eq(rc, OK);

    bool equal = is_films_arrays_equal(src, length_src, dst, length_dst);
    ck_assert_int_eq(equal, true); 

    films_free(dst, length_dst);
}
END_TEST

// Несколько фильмов в файле. Отсортированы в обратном порядке по ключу title
START_TEST (pos_films_sorted_desc_title)
{
    film_t src[] = {
        {"Black Widow  ", "Scarlett Johansson  ", 2021},
        {"Inception  ", "Leonardo DiCaprio  ", 2010},
        {"John Wick  ", "Keanu Reeves  ", 2014},
        {"La La Land  ", "Ryan Gosling  ", 2016},
        {"Mad Max: Fury Road  ", "Charlize Theron  ", 2015},
        {"The Dark Knight  ", "Christian Bale  ", 2008},
        {"The Wolf of Wall Street", "Margot Robbie  ", 2013},
        {"Wonder Woman  ", "Gal Gadot  ", 2017}
    };
    size_t length_src = sizeof(src) / sizeof(src[0]);

    char *filename = "func_tests/data/pos_04_in.txt";
    film_t *dst;
    size_t length_dst;

    int rc = films_create_ex(filename, &dst, &length_dst, film_cmp_by_title);
    ck_assert_int_eq(rc, OK);
    
    bool equal = is_films_arrays_equal(src, length_src, dst, length_dst);
    ck_assert_int_eq(equal, true); 

    films_free(dst, length_dst);
}
END_TEST

// Несколько фильмов в файле. Отсортированы в правильном порядке по ключу title
START_TEST (pos_films_sorted_asc_title)
{
    film_t src[] = {
        {"Black Widow  ", "Scarlett Johansson", 2021},
        {"Inception  ", "Leonardo DiCaprio", 2010},
        {"John Wick  ", "Keanu Reeves  ", 2014},
        {"La La Land  ", "Ryan Gosling  ", 2016},
        {"Mad Max: Fury Road  ", "Charlize Theron  ", 2015},
        {"The Dark Knight  ", "Christian Bale  ", 2008},
        {"The Wolf of Wall Street", "Margot Robbie  ", 2013},
        {"Wonder Woman  ", "Gal Gadot  ", 2017}
    };
    size_t length_src = sizeof(src) / sizeof(src[0]);

    char *filename = "func_tests/data/pos_05_in.txt";
    film_t *dst;
    size_t length_dst;

    int rc = films_create_ex(filename, &dst, &length_dst, film_cmp_by_title);
    ck_assert_int_eq(rc, OK);

    bool equal = is_films_arrays_equal(src, length_src, dst, length_dst);
    ck_assert_int_eq(equal, true); 

    films_free(dst, length_dst);
}
END_TEST

// Несколько фильмов в файле. Отсортированы в правильном порядке, затем в обратном по ключу title
START_TEST (pos_films_sorted_desc_then_asc_title)
{
    film_t src[] = {
        {"Black Widow  ", "Scarlett Johansson", 2021},
        {"Inception  ", "Leonardo DiCaprio  ", 2010},
        {"John Wick  ", "Keanu Reeves  ", 2014},
        {"La La Land  ", "Ryan Gosling  ", 2016},
        {"Mad Max: Fury Road  ", "Charlize Theron  ", 2015},
        {"The Dark Knight  ", "Christian Bale  ", 2008},
        {"The Wolf of Wall Street", "Margot Robbie  ", 2013},
        {"Wonder Woman  ", "Gal Gadot  ", 2017}
    };
    size_t length_src = sizeof(src) / sizeof(src[0]);

    char *filename = "func_tests/data/pos_06_in.txt";
    film_t *dst;
    size_t length_dst;

    int rc = films_create_ex(filename, &dst, &length_dst, film_cmp_by_title);
    ck_assert_int_eq(rc, OK);

    bool equal = is_films_arrays_equal(src, length_src, dst, length_dst);
    ck_assert_int_eq(equal, true); 

    films_free(dst, length_dst);
}
END_TEST

// Несколько фильмов в файле. Отсортированы в обратном порядке, затем в правильном по ключу title
START_TEST (pos_films_sorted_asc_then_desc_title)
{
    film_t src[] = {
        {"Black Widow  ", "Scarlett Johansson  ", 2021},
        {"Inception  ", "Leonardo DiCaprio  ", 2010},
        {"John Wick  ", "Keanu Reeves  ", 2014},
        {"La La Land  ", "Ryan Gosling  ", 2016},
        {"Mad Max: Fury Road", "Charlize Theron  ", 2015},
        {"The Dark Knight  ", "Christian Bale  ", 2008},
        {"The Wolf of Wall Street", "Margot Robbie  ", 2013},
        {"Wonder Woman  ", "Gal Gadot  ", 2017}
    };
    size_t length_src = sizeof(src) / sizeof(src[0]);

    char *filename = "func_tests/data/pos_07_in.txt";
    film_t *dst;
    size_t length_dst;

    int rc = films_create_ex(filename, &dst, &length_dst, film_cmp_by_title);
    ck_assert_int_eq(rc, OK);

    bool equal = is_films_arrays_equal(src, length_src, dst, length_dst);
    ck_assert_int_eq(equal, true); 

    films_free(dst, length_dst);
}
END_TEST

//Дальше комментарии у тестов аналогичны, как в прошлых. Только ключи меняюнтся: name, year

START_TEST (pos_one_film_name)
{
    film_t src[] = {
        {"La La Land  ", "Ryan Gosling  ", 2016},
    };
    size_t length_src = sizeof(src) / sizeof(src[0]);

    char *filename = "func_tests/data/pos_12_in.txt";
    film_t *dst;
    size_t length_dst;

    int rc = films_create_ex(filename, &dst, &length_dst, film_cmp_by_name);
    ck_assert_int_eq(rc, OK);

    bool equal = is_films_arrays_equal(src, length_src, dst, length_dst);
    ck_assert_int_eq(equal, true); 

    films_free(dst, length_dst);
}
END_TEST

START_TEST (pos_two_sorted_films_name)
{
    film_t src[] = {
        {"The Wolf of Wall Street", "Margot Robbie", 2013},
        {"La La Land  ", "Ryan Gosling  ", 2016}
    };
    size_t length_src = sizeof(src) / sizeof(src[0]);

    char *filename = "func_tests/data/pos_13_in.txt";
    film_t *dst;
    size_t length_dst;

    int rc = films_create_ex(filename, &dst, &length_dst, film_cmp_by_name);
    ck_assert_int_eq(rc, OK);

    bool equal = is_films_arrays_equal(src, length_src, dst, length_dst);
    ck_assert_int_eq(equal, true); 

    films_free(dst, length_dst);
}
END_TEST

START_TEST (pos_two_unsorted_films_name)
{
    film_t src[] = {
        {"The Wolf of Wall Street", "Margot Robbie  ", 2013},
        {"La La Land  ", "Ryan Gosling  ", 2016}
    };
    size_t length_src = sizeof(src) / sizeof(src[0]);

    char *filename = "func_tests/data/pos_14_in.txt";
    film_t *dst;
    size_t length_dst;

    int rc = films_create_ex(filename, &dst, &length_dst, film_cmp_by_name);
    ck_assert_int_eq(rc, OK);

    bool equal = is_films_arrays_equal(src, length_src, dst, length_dst);
    ck_assert_int_eq(equal, true); 

    films_free(dst, length_dst);
}
END_TEST

START_TEST (pos_films_sorted_desc_name)
{
    film_t src[] = {
        {"Mad Max: Fury Road  ", "Charlize Theron  ", 2015},
        {"The Dark Knight  ", "Christian Bale  ", 2008},
        {"Wonder Woman  ", "Gal Gadot  ", 2017},
        {"John Wick  ", "Keanu Reeves  ", 2014},
        {"Inception  ", "Leonardo DiCaprio  ", 2010},
        {"The Wolf of Wall Street", "Margot Robbie  ", 2013},
        {"La La Land  ", "Ryan Gosling  ", 2016},
        {"Black Widow  ", "Scarlett Johansson  ", 2021},
    };
    size_t length_src = sizeof(src) / sizeof(src[0]);

    char *filename = "func_tests/data/pos_15_in.txt";
    film_t *dst;
    size_t length_dst;

    int rc = films_create_ex(filename, &dst, &length_dst, film_cmp_by_name);
    ck_assert_int_eq(rc, OK);

    bool equal = is_films_arrays_equal(src, length_src, dst, length_dst);
    ck_assert_int_eq(equal, true); 

    films_free(dst, length_dst);
}
END_TEST

START_TEST (pos_films_sorted_asc_name)
{
    film_t src[] = {
        {"Mad Max: Fury Road  ", "Charlize Theron  ", 2015},
        {"The Dark Knight  ", "Christian Bale  ", 2008},
        {"Wonder Woman  ", "Gal Gadot  ", 2017},
        {"John Wick  ", "Keanu Reeves  ", 2014},
        {"Inception  ", "Leonardo DiCaprio  ", 2010},
        {"The Wolf of Wall Street", "Margot Robbie  ", 2013},
        {"La La Land  ", "Ryan Gosling  ", 2016},
        {"Black Widow  ", "Scarlett Johansson  ", 2021},
    };
    size_t length_src = sizeof(src) / sizeof(src[0]);

    char *filename = "func_tests/data/pos_16_in.txt";
    film_t *dst;
    size_t length_dst;

    int rc = films_create_ex(filename, &dst, &length_dst, film_cmp_by_name);
    ck_assert_int_eq(rc, OK);

    bool equal = is_films_arrays_equal(src, length_src, dst, length_dst);
    ck_assert_int_eq(equal, true); 

    films_free(dst, length_dst);
}
END_TEST

START_TEST (pos_films_sorted_desc_then_asc_name)
{
    film_t src[] = {
        {"Mad Max: Fury Road  ", "Charlize Theron  ", 2015},
        {"The Dark Knight  ", "Christian Bale  ", 2008},
        {"Wonder Woman  ", "Gal Gadot  ", 2017},
        {"John Wick  ", "Keanu Reeves  ", 2014},
        {"Inception  ", "Leonardo DiCaprio  ", 2010},
        {"The Wolf of Wall Street", "Margot Robbie  ", 2013},
        {"La La Land  ", "Ryan Gosling  ", 2016},
        {"Black Widow  ", "Scarlett Johansson  ", 2021},
    };
    size_t length_src = sizeof(src) / sizeof(src[0]);

    char *filename = "func_tests/data/pos_17_in.txt";
    film_t *dst;
    size_t length_dst;

    int rc = films_create_ex(filename, &dst, &length_dst, film_cmp_by_name);
    ck_assert_int_eq(rc, OK);

    bool equal = is_films_arrays_equal(src, length_src, dst, length_dst);
    ck_assert_int_eq(equal, true); 

    films_free(dst, length_dst);
}
END_TEST

START_TEST (pos_films_sorted_asc_then_desc_name)
{
    film_t src[] = {
        {"Mad Max: Fury Road  ", "Charlize Theron  ", 2015},
        {"The Dark Knight  ", "Christian Bale  ", 2008},
        {"Wonder Woman  ", "Gal Gadot  ", 2017},
        {"John Wick  ", "Keanu Reeves  ", 2014},
        {"Inception  ", "Leonardo DiCaprio  ", 2010},
        {"The Wolf of Wall Street", "Margot Robbie  ", 2013},
        {"La La Land  ", "Ryan Gosling  ", 2016},
        {"Black Widow  ", "Scarlett Johansson  ", 2021},
    };
    size_t length_src = sizeof(src) / sizeof(src[0]);

    char *filename = "func_tests/data/pos_18_in.txt";
    film_t *dst;
    size_t length_dst;

    int rc = films_create_ex(filename, &dst, &length_dst, film_cmp_by_name);
    ck_assert_int_eq(rc, OK);

    bool equal = is_films_arrays_equal(src, length_src, dst, length_dst);
    ck_assert_int_eq(equal, true); 

    films_free(dst, length_dst);
}
END_TEST

START_TEST (pos_one_film_year)
{
    film_t src[] = {
        {"La La Land  ", "Ryan Gosling  ", 2016},
    };
    size_t length_src = sizeof(src) / sizeof(src[0]);

    char *filename = "func_tests/data/pos_23_in.txt";
    film_t *dst;
    size_t length_dst;

    int rc = films_create_ex(filename, &dst, &length_dst, film_cmp_by_year);
    ck_assert_int_eq(rc, OK);

    bool equal = is_films_arrays_equal(src, length_src, dst, length_dst);
    ck_assert_int_eq(equal, true);

    films_free(dst, length_dst); 
}
END_TEST

START_TEST (pos_two_sorted_films_year)
{
    film_t src[] = {
        {"La La Land  ", "Ryan Gosling  ", 2016},
        {"La La Land  ", "Ryan Gosling  ", 2017}
    };
    size_t length_src = sizeof(src) / sizeof(src[0]);

    char *filename = "func_tests/data/pos_24_in.txt";
    film_t *dst;
    size_t length_dst;

    int rc = films_create_ex(filename, &dst, &length_dst, film_cmp_by_year);
    ck_assert_int_eq(rc, OK);

    bool equal = is_films_arrays_equal(src, length_src, dst, length_dst);
    ck_assert_int_eq(equal, true); 

    films_free(dst, length_dst);
}
END_TEST

START_TEST (pos_two_unsorted_films_year)
{
    film_t src[] = {
        {"La La Land  ", "Ryan Gosling  ", 201},
        {"La La Land  ", "Ryan Gosling  ", 2016}
    };
    size_t length_src = sizeof(src) / sizeof(src[0]);

    char *filename = "func_tests/data/pos_25_in.txt";
    film_t *dst;
    size_t length_dst;

    int rc = films_create_ex(filename, &dst, &length_dst, film_cmp_by_year);
    ck_assert_int_eq(rc, OK);

    bool equal = is_films_arrays_equal(src, length_src, dst, length_dst);
    ck_assert_int_eq(equal, true); 

    films_free(dst, length_dst);
}
END_TEST

START_TEST (pos_films_sorted_desc_year)
{
    film_t src[] = {
        {"John Wick  ", "Keanu Reeves  ", 204},
        {"Wonder Woman  ", "Gal Gadot  ", 207},
        {"Black Widow  ", "Scarlett Johansson  ", 1997},
        {"La La Land  ", "Ryan Gosling  ", 1998},
        {"The Wolf of Wall Street", "Margot Robbie  ", 1999},
        {"Inception  ", "Leonardo DiCaprio  ", 2000},
        {"The Dark Knight  ", "Christian Bale  ", 2008},
        {"Mad Max: Fury Road  ", "Charlize Theron  ", 2015}
    };
    size_t length_src = sizeof(src) / sizeof(src[0]);

    char *filename = "func_tests/data/pos_26_in.txt";
    film_t *dst;
    size_t length_dst;

    int rc = films_create_ex(filename, &dst, &length_dst, film_cmp_by_year);
    ck_assert_int_eq(rc, OK);

    bool equal = is_films_arrays_equal(src, length_src, dst, length_dst);
    ck_assert_int_eq(equal, true); 

    films_free(dst, length_dst);
}
END_TEST

START_TEST (pos_films_sorted_asc_year)
{
    film_t src[] = {
        {"Mad Max: Fury Road  ", "Charlize Theron  ", 2015},
        {"The Dark Knight  ", "Christian Bale  ", 2018},
        {"Wonder Woman  ", "Gal Gadot  ", 2019},
        {"John Wick  ", "Keanu Reeves  ", 2020},
        {"Inception  ", "Leonardo DiCaprio  ", 2021},
        {"The Wolf of Wall Street", "Margot Robbie  ", 2022},
        {"La La Land  ", "Ryan Gosling  ", 2023},
        {"Black Widow  ", "Scarlett Johansson  ", 2024},
    };
    size_t length_src = sizeof(src) / sizeof(src[0]);

    char *filename = "func_tests/data/pos_27_in.txt";
    film_t *dst;
    size_t length_dst;

    int rc = films_create_ex(filename, &dst, &length_dst, film_cmp_by_year);
    ck_assert_int_eq(rc, OK);

    bool equal = is_films_arrays_equal(src, length_src, dst, length_dst);
    ck_assert_int_eq(equal, true); 

    films_free(dst, length_dst);
}
END_TEST

START_TEST (pos_films_sorted_desc_then_asc_year)
{
    film_t src[] = {
        {"Wonder Woman  ", "Gal Gadot  ", 2007},
        {"The Dark Knight  ", "Christian Bale  ", 2008},
        {"John Wick  ", "Keanu Reeves  ", 2014},
        {"Mad Max: Fury Road  ", "Charlize Theron  ", 2015},
        {"Inception  ", "Leonardo DiCaprio  ", 2015},
        {"The Wolf of Wall Street", "Margot Robbie  ", 2016},
        {"La La Land  ", "Ryan Gosling  ", 2017},
        {"Black Widow  ", "Scarlett Johansson  ", 2018},
    };
    size_t length_src = sizeof(src) / sizeof(src[0]);

    char *filename = "func_tests/data/pos_28_in.txt";
    film_t *dst;
    size_t length_dst;

    int rc = films_create_ex(filename, &dst, &length_dst, film_cmp_by_year);
    ck_assert_int_eq(rc, OK);

    bool equal = is_films_arrays_equal(src, length_src, dst, length_dst);
    ck_assert_int_eq(equal, true); 

    films_free(dst, length_dst);
}
END_TEST

START_TEST (pos_films_sorted_asc_then_desc_year)
{
    film_t src[] = {
        {"Black Widow  ", "Scarlett Johansson  ", 2004},
        {"La La Land  ", "Ryan Gosling  ", 2006},
        {"The Wolf of Wall Street", "Margot Robbie  ", 2007},
        {"Inception  ", "Leonardo DiCaprio  ", 2010},
        {"Mad Max: Fury Road  ", "Charlize Theron  ", 2015},
        {"The Dark Knight  ", "Christian Bale  ", 2016},
        {"Wonder Woman  ", "Gal Gadot  ", 2017},
        {"John Wick  ", "Keanu Reeves  ", 2018},
    };
    size_t length_src = sizeof(src) / sizeof(src[0]);

    char *filename = "func_tests/data/pos_29_in.txt";
    film_t *dst;
    size_t length_dst;

    int rc = films_create_ex(filename, &dst, &length_dst, film_cmp_by_year);
    ck_assert_int_eq(rc, OK);

    bool equal = is_films_arrays_equal(src, length_src, dst, length_dst);
    ck_assert_int_eq(equal, true); 

    films_free(dst, length_dst);
}
END_TEST

/**
 * Негативные тесты
*/
START_TEST (neg_empty_file)
{
    char *filename = "func_tests/data/neg_01_in.txt";
    film_t *dst;
    size_t length_dst;

    int rc = films_create_ex(filename, &dst, &length_dst, film_cmp_by_title);
    ck_assert_int_ne(rc, OK);
}
END_TEST

START_TEST (neg_missing_title)
{
    char *filename = "func_tests/data/neg_02_in.txt";
    film_t *dst;
    size_t length_dst;

    int rc = films_create_ex(filename, &dst, &length_dst, film_cmp_by_title);
    ck_assert_int_ne(rc, OK);
}
END_TEST

START_TEST (neg_missing_director)
{
    char *filename = "func_tests/data/neg_03_in.txt";
    film_t *dst;
    size_t length_dst;

    int rc = films_create_ex(filename, &dst, &length_dst, film_cmp_by_title);
    ck_assert_int_ne(rc, OK);
}
END_TEST

START_TEST (neg_missing_year)
{
    char *filename = "func_tests/data/neg_04_in.txt";
    film_t *dst;
    size_t length_dst;

    int rc = films_create_ex(filename, &dst, &length_dst, film_cmp_by_title);
    ck_assert_int_ne(rc, OK);
}
END_TEST


START_TEST (neg_year_less_than_zero)
{
    char *filename = "func_tests/data/neg_05_in.txt";
    film_t *dst;
    size_t length_dst;

    int rc = films_create_ex(filename, &dst, &length_dst, film_cmp_by_title);
    ck_assert_int_ne(rc, OK);
}
END_TEST

START_TEST (neg_string_instead_of_year)
{
    char *filename = "func_tests/data/neg_12_in.txt";
    film_t *dst;
    size_t length_dst;

    int rc = films_create_ex(filename, &dst, &length_dst, film_cmp_by_title);
    ck_assert_int_ne(rc, OK);
}
END_TEST

START_TEST (neg_file_not_exist)
{
    char *filename = "func_tests/data/neg_in.txt";
    film_t *dst;
    size_t length_dst;

    int rc = films_create_ex(filename, &dst, &length_dst, film_cmp_by_title);
    ck_assert_int_ne(rc, OK);
}
END_TEST

Suite* test_films_create_ex_suite(void)
{
    Suite *suite;
    TCase *tc_pos;

    suite = suite_create("films_create_ex");

    tc_pos = tcase_create("positives");

    // FIELD = title
    tcase_add_test(tc_pos, pos_one_film_title);
    tcase_add_test(tc_pos, pos_two_sorted_films_title);
    tcase_add_test(tc_pos, pos_two_unsorted_films_title);
    tcase_add_test(tc_pos, pos_films_sorted_desc_title);
    tcase_add_test(tc_pos, pos_films_sorted_asc_title);
    tcase_add_test(tc_pos, pos_films_sorted_desc_then_asc_title);
    tcase_add_test(tc_pos, pos_films_sorted_asc_then_desc_title);

    // FIELD = name
    tcase_add_test(tc_pos, pos_one_film_name);
    tcase_add_test(tc_pos, pos_two_sorted_films_name);
    tcase_add_test(tc_pos, pos_two_unsorted_films_name);
    tcase_add_test(tc_pos, pos_films_sorted_desc_name);
    tcase_add_test(tc_pos, pos_films_sorted_asc_name);
    tcase_add_test(tc_pos, pos_films_sorted_desc_then_asc_name);
    tcase_add_test(tc_pos, pos_films_sorted_asc_then_desc_name);

    // FIELD = year
    tcase_add_test(tc_pos, pos_one_film_year);
    tcase_add_test(tc_pos, pos_two_sorted_films_year);
    tcase_add_test(tc_pos, pos_two_unsorted_films_year);
    tcase_add_test(tc_pos, pos_films_sorted_desc_year);
    tcase_add_test(tc_pos, pos_films_sorted_asc_year);
    tcase_add_test(tc_pos, pos_films_sorted_desc_then_asc_year);
    tcase_add_test(tc_pos, pos_films_sorted_asc_then_desc_year);

    suite_add_tcase(suite, tc_pos);

    // Негативные тесты
    TCase *tc_neg = tcase_create("negatives");

    // Негативные тесты:
    tcase_add_test(tc_neg, neg_empty_file);
    tcase_add_test(tc_neg, neg_missing_title);
    tcase_add_test(tc_neg, neg_missing_director);
    tcase_add_test(tc_neg, neg_missing_year);
    tcase_add_test(tc_neg, neg_year_less_than_zero);
    tcase_add_test(tc_neg, neg_string_instead_of_year);
    tcase_add_test(tc_neg, neg_file_not_exist);

    suite_add_tcase(suite, tc_neg);

    return suite;
}
