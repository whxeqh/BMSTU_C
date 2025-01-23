#include <stdio.h>
#include <stdlib.h>
#include "film_array.h"
#include "check_binary_search.h"
#include "errors.h"  

/*
 * ----------------------------------------------------------------------------------------------------------------------
 *
 * Юнит тесты Бинарного поиска
 *
 * ----------------------------------------------------------------------------------------------------------------------
*/
// Фильм найден. Массив из одного элемента, поиск по названию.
START_TEST(pos_one_elem_array_title_cmp)
{
    film_t arr[] = {
        {"aa", "aa", 2009},
    };
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = {.title = "aa"};
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_title);

    ck_assert_int_eq(find, true);  // Фильм найден.
    ck_assert_uint_eq(pos, 0);    // Ожидаемая позиция вставки 0.
}
END_TEST

// Фильм найден. Массив из двух элементов. Поиск найденного фильма перед первым элементом.
START_TEST(pos_two_elems_array_find_first_elem_title_cmp)
{
    film_t arr[] = {
        {"aa", "aa", 2009},
        {"bb", "bb", 2013},
    };
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = {.title = "aa"};
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_title);

    ck_assert_int_eq(find, true);  // Фильм найден.
    ck_assert_uint_eq(pos, 0);    // Ожидаемая позиция вставки 0.
}
END_TEST

// Фильм найден. Массив из двух элементов. Поиск найденного фильма после последнего элемента.
START_TEST(pos_two_elems_array_find_last_elem_title_cmp)
{
    film_t arr[] = {
        {"aa", "aa", 2009},
        {"bb", "bb", 2013},
    };
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = {.title = "bb"};
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_title);

    ck_assert_int_eq(find, true);  // Фильм найден.
    ck_assert_uint_eq(pos, 1);    // Ожидаемая позиция вставки 1.
}
END_TEST

// Фильм найден. Массив из нечетного количества элементов. Поиск найденного фильма на четной позиции.
START_TEST(pos_odd_elems_array_find_even_pos_elem_title_cmp)
{
    film_t arr[] = {
        {"aa", "aa", 2009},
        {"bb", "bb", 2013},
        {"cc", "cc", 2010},
    };
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = {.title = "bb"};
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_title);

    ck_assert_int_eq(find, true);  // Фильм найден.
    ck_assert_uint_eq(pos, 1);    // Ожидаемая позиция вставки 1.
}
END_TEST

// Фильм найден. Массив из нечетного количества элементов. Поиск найденного фильма на нечетной позиции.
START_TEST(pos_odd_elems_array_find_odd_pos_elem_title_cmp)
{
    film_t arr[] = {
        {"aa", "aa", 2009},
        {"bb", "bb", 2013},
        {"cc", "cc", 2010},
    };
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = {.title = "cc"};
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_title);

    ck_assert_int_eq(find, true);  // Фильм найден.
    ck_assert_uint_eq(pos, 2);    // Ожидаемая позиция вставки 2.
}
END_TEST

// Фильм найден. Массив из четного количества элементов. Поиск найденного фильма на четной позиции.
START_TEST(pos_even_elems_array_find_even_elem_title_cmp)
{
    film_t arr[] = {
        {"aa", "aa", 2009},
        {"bb", "bb", 2013},
        {"cc", "cc", 2010},
        {"dd", "dd", 2016}
    };
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = {.title = "bb"};
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_title);

    ck_assert_int_eq(find, true);  // Фильм найден.
    ck_assert_uint_eq(pos, 1);    // Ожидаемая позиция вставки 1.
}
END_TEST

// Фильм найден. Массив из четного количества элементов. Поиск найденного фильма на нечетной позиции.
START_TEST(pos_even_elems_array_find_odd_pos_elem_title_cmp)
{
    film_t arr[] = {
        {"aa", "aa", 2009},
        {"bb", "bb", 2013},
        {"cc", "cc", 2010},
        {"dd", "dd", 2016}
    };
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = {.title = "cc"};
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_title);

    ck_assert_int_eq(find, true);  // Фильм найден.
    ck_assert_uint_eq(pos, 2);    // Ожидаемая позиция вставки 2.
}
END_TEST

// В массиве несколько фильмов с одинаковым названием. Ищем первый из них.
START_TEST (pos_multiple_matching_titles)
{
    film_t arr[] = {
        {"aa", "Leonardo DiCaprio", 2010},
        {"bb", "Ryan Gosling", 2016},
        {"bb", "Emma Stone", 2016},
        {"cc", "Matthew McConaughey", 2014}
    };
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = { .title = "bb" };
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_title);

    ck_assert_int_eq(find, true);
    ck_assert_uint_eq(pos, 2);  
}
END_TEST

// Фильм найден. Массив из одного элемента. Сравнение по имени актера.
START_TEST(pos_one_elem_array_name_cmp)
{
    film_t arr[] = {
        {"aa", "aa", 2009},
    };
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = {.name = "aa"};
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_name);

    ck_assert_int_eq(find, true);  // Фильм найден.
    ck_assert_uint_eq(pos, 0);    // Ожидаемая позиция вставки 0.
}
END_TEST

// Фильм найден. Массив из двух элементов. Поиск найденного фильма перед первым элементом.
START_TEST(pos_two_elems_array_find_first_elem_name_cmp)
{
    film_t arr[] = {
        {"aa", "aa", 2009},
        {"bb", "bb", 2013},
    };
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = {.name = "aa"};
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_name);

    ck_assert_int_eq(find, true);  // Фильм найден.
    ck_assert_uint_eq(pos, 0);    // Ожидаемая позиция вставки 0.
}
END_TEST

// Фильм найден. Массив из двух элементов. Поиск найденного фильма после последнего элемента.
START_TEST(pos_two_elems_array_find_last_elem_name_cmp)
{
    film_t arr[] = {
        {"aa", "aa", 2009},
        {"bb", "bb", 2013},
    };
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = {.name = "bb"};
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_name);

    ck_assert_int_eq(find, true);  // Фильм найден.
    ck_assert_uint_eq(pos, 1);    // Ожидаемая позиция вставки 1.
}
END_TEST

// Фильм найден. Массив из нечетного количества элементов. Поиск найденного фильма на четной позиции.
START_TEST(pos_odd_elems_array_find_even_pos_elem_name_cmp)
{
    film_t arr[] = {
        {"aa", "aa", 2009},
        {"bb", "bb", 2013},
        {"cc", "cc", 2010},
    };
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = {.name = "aa"};
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_name);

    ck_assert_int_eq(find, true);  // Фильм найден.
    ck_assert_uint_eq(pos, 0);    // Ожидаемая позиция вставки 1.
}
END_TEST

// Фильм найден. Массив из нечетного количества элементов. Поиск найденного фильма на нечетной позиции.
START_TEST(pos_odd_elems_array_find_odd_pos_elem_name_cmp)
{
    film_t arr[] = {
        {"aa", "aa", 2009},
        {"bb", "bb", 2013},
        {"cc", "cc", 2010},
    };
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = {.name = "cc"};
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_name);

    ck_assert_int_eq(find, true);  // Фильм найден.
    ck_assert_uint_eq(pos, 2);    // Ожидаемая позиция вставки 2.
}
END_TEST

// Фильм найден. Массив из нечетного количества элементов. Поиск найденного фильма на нечетной позиции.
START_TEST(pos_odd_elems_array_find_mid_pos_elem_name_cmp)
{
    film_t arr[] = {
        {"aa", "aa", 2009},
        {"bb", "bb", 2013},
        {"cc", "cc", 2010},
    };
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = {.name = "bb"};
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_name);

    ck_assert_int_eq(find, true);  // Фильм найден.
    ck_assert_uint_eq(pos, 1);    // Ожидаемая позиция вставки 2.
}
END_TEST

// Фильм найден. Массив из четного количества элементов. Поиск найденного фильма на четной позиции.
START_TEST(pos_even_elems_array_find_even_elem_name_cmp)
{
    film_t arr[] = {
        {"aa", "aa", 2009},
        {"bb", "bb", 2013},
        {"cc", "cc", 2010},
        {"dd", "dd", 2016}
    };
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = {.name = "bb"};
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_name);

    ck_assert_int_eq(find, true);  // Фильм найден.
    ck_assert_uint_eq(pos, 1);    // Ожидаемая позиция вставки 1.
}
END_TEST

// Фильм найден. Массив из четного количества элементов. Поиск найденного фильма на нечетной позиции.
START_TEST(pos_even_elems_array_find_odd_pos_elem_name_cmp)
{
    film_t arr[] = {
        {"aa", "aa", 2009},
        {"bb", "bb", 2013},
        {"cc", "cc", 2010},
        {"dd", "dd", 2016}
    };
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = {.name = "cc"};
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_name);

    ck_assert_int_eq(find, true);  // Фильм найден.
    ck_assert_uint_eq(pos, 2);    // Ожидаемая позиция вставки 2.
}
END_TEST

// В массиве несколько фильмов с одинаковым названием. Ищем первый из них.
START_TEST (pos_multiple_matching_names)
{
    film_t arr[] = {
        {"Inception", "aa", 2010},
        {"La La Land", "bb", 2016},
        {"La La Land", "bb", 2016},
        {"Interstellar", "cc", 2014}
    };
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = { .name = "bb" };
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_name);

    ck_assert_int_eq(find, true);
    ck_assert_uint_eq(pos, 2);  
}
END_TEST

// Фильм присутствует. Массив из одного элемента, отсортирован по году. Сравнение по году
START_TEST (pos_one_elem_array_year_cmp)
{
    film_t arr[] = {{"aa", "Ryan Gosling", 2016}};
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = {.year = 2016};
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_year);

    ck_assert_int_eq(find, true);  // Фильм найден
    ck_assert_uint_eq(pos, 0);    // Ожидаемая позиция вставки 0
}
END_TEST

// Фильм присутствует. Массив из двух элементов, отсортирован по году. Поиск фильма, который находится на первой позиции
START_TEST (pos_two_elems_array_find_first_elem_year_cmp)
{
    film_t arr[] = {
        {"aa", "Sam Worthington", 2009},
        {"bb", "Matthew McConaughey", 2014}
    };
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = {.year = 2009};
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_year);

    ck_assert_int_eq(find, true);  // Фильм найден
    ck_assert_uint_eq(pos, 0);    // Ожидаемая позиция вставки 0
}
END_TEST

// Фильм присутствует. Массив из двух элементов, отсортирован по году. Поиск фильма, который находится на второй позиции
START_TEST (pos_two_elems_array_find_last_elem_year_cmp)
{
    film_t arr[] = {
        {"aa", "Sam Worthington", 2009},
        {"bb", "Matthew McConaughey", 2014}
    };
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = {.year = 2014};
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_year);

    ck_assert_int_eq(find, true);  // Фильм найден
    ck_assert_uint_eq(pos, 1);    // Ожидаемая позиция вставки 1
}
END_TEST

// Фильм присутствует. Массив из нечетного количества элементов, отсортирован по году. Поиск фильма, который находится на средней позиции
START_TEST (pos_odd_elems_array_find_mid_pos_elem_year_cmp)
{
    film_t arr[] = {
        {"aa", "Sam Worthington", 2009},
        {"bb", "Leonardo DiCaprio", 2010},
        {"cc", "Matthew McConaughey", 2014}
    };
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = {.year = 2010};
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_year);

    ck_assert_int_eq(find, true);  // Фильм найден
    ck_assert_uint_eq(pos, 1);    // Ожидаемая позиция вставки 1
}
END_TEST

// В массиве несколько фильмов с одинаковым названием. Ищем первый из них.
START_TEST (pos_multiple_matching_years)
{
    film_t arr[] = {
        {"Inception", "Leonardo DiCaprio", 2010},
        {"La La Land", "Ryan Gosling", 2016},
        {"La La Land", "Emma Stone", 2016},
        {"Interstellar", "Matthew McConaughey", 2014}
    };
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = { .year = 2016 };
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_year);

    ck_assert_int_eq(find, true);
    ck_assert_uint_eq(pos, 2);  // Ожидаем, что вернется позиция первого подходящего фильма
}
END_TEST

// Фильм найден. Массив из нечетного количества элементов. Поиск найденного фильма на четной позиции.
START_TEST(pos_odd_elems_array_find_even_pos_elem_year_cmp)
{
    film_t arr[] = {
        {"aa", "aa", 2009},
        {"bb", "bb", 2013},
        {"cc", "cc", 2010},
    };
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = {.year = 2013};
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_year);

    ck_assert_int_eq(find, true);  // Фильм найден.
    ck_assert_uint_eq(pos, 1);    // Ожидаемая позиция 1.
}
END_TEST

// Фильм найден. Массив из нечетного количества элементов. Поиск найденного фильма на нечетной позиции.
START_TEST(pos_odd_elems_array_find_odd_pos_elem_year_cmp)
{
    film_t arr[] = {
        {"aa", "aa", 2009},
        {"bb", "bb", 2013},
        {"cc", "cc", 2010},
    };
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = {.year = 2009};
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_year);

    ck_assert_int_eq(find, true);  // Фильм найден.
    ck_assert_uint_eq(pos, 0);    // Ожидаемая позиция 0.
}
END_TEST

// Фильм найден. Массив из четного количества элементов. Поиск найденного фильма на четной позиции.
START_TEST(pos_even_elems_array_find_even_elem_year_cmp)
{
    film_t arr[] = {
        {"aa", "aa", 2009},
        {"bb", "bb", 2013},
        {"cc", "cc", 2010},
        {"dd", "dd", 2016}
    };
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = {.year = 2013};
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_year);

    ck_assert_int_eq(find, true);  // Фильм найден.
    ck_assert_uint_eq(pos, 1);    // Ожидаемая позиция 1.
}
END_TEST

// Фильм найден. Массив из четного количества элементов. Поиск найденного фильма на нечетной позиции.
START_TEST(pos_even_elems_array_find_odd_pos_elem_year_cmp)
{
    film_t arr[] = {
        {"aa", "aa", 2009},
        {"bb", "bb", 2013},
        {"cc", "cc", 2010},
        {"dd", "dd", 2016}
    };
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = {.year = 2013};
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_year);

    ck_assert_int_eq(find, true);  // Фильм найден.
    ck_assert_uint_eq(pos, 1);    // Ожидаемая позиция 2.
}
END_TEST


/** 
 * --------------------------
 * Фильм отсутствует
 * --------------------------
*/

// Фильм отсутствует. Массив из одного элемента. Сравнение по имени актера
START_TEST (neg_one_elem_array_title_cmp)
{
    film_t arr[] = {
        {"aa", "aa", 2009},
    };
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = {.title = "a"};
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_title);

    ck_assert_int_eq(find, false);
    ck_assert_uint_eq(pos, 0); 
}
END_TEST

// Фильм отсутствует. Массив из двух элементов. Поиск отсутствующего фильма перед первым элементом
START_TEST (neg_two_elems_array_find_first_elem_title_cmp)
{
    film_t arr[] = {
        {"aa", "aa", 2009},
        {"bb", "bb", 2013},
    };
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = {.title = "a"};
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_title);

    ck_assert_int_eq(find, false);
    ck_assert_uint_eq(pos, 0);  
}
END_TEST

// Фильм отсутствует. Массив из двух элементов. Поиск отсутствующего фильма после последнего элемента
START_TEST (neg_two_elems_array_find_last_elem_title_cmp)
{
    film_t arr[] = {
        {"aa", "aa", 2009},
        {"bb", "bb", 2013},
    };
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = {.title = "ba"};
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_title);

    ck_assert_int_eq(find, false);
    ck_assert_uint_eq(pos, 1);
}
END_TEST

// Фильм отсутствует. Массив из нечетного количества элементов. Поиск отсутствующего фильма на четной позиции
START_TEST (neg_odd_elems_array_find_even_pos_elem_title_cmp)
{
    film_t arr[] = {
        {"aa", "aa", 2009},
        {"bb", "bb", 2013},
        {"cc", "cc", 2010},
    };
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = {.title = "ba"};
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_title);

    ck_assert_int_eq(find, false);
    ck_assert_uint_eq(pos, 1); 
}
END_TEST

// Фильм отсутствует. Массив из нечетного количества элементов. Поиск отсутствующего фильма на нечетной позиции
START_TEST (neg_odd_elems_array_find_odd_pos_elem_title_cmp)
{
    film_t arr[] = {
        {"aa", "aa", 2009},
        {"bb", "bb", 2013},
        {"cc", "cc", 2010},
    };
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = {.title = "ca"};
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_title);

    ck_assert_int_eq(find, false);
    ck_assert_uint_eq(pos, 2); 
}
END_TEST

// Фильм отсутствует. Массив из четного количества элементов. Поиск отсутствующего фильма на четной позиции
START_TEST (neg_even_elems_array_find_even_elem_title_cmp)
{
    film_t arr[] = {
        {"aa", "aa", 2009},
        {"bb", "bb", 2013},
        {"cc", "cc", 2010},
        {"dd", "dd", 2016}
    };
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = {.title = "ba"};
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_title);

    ck_assert_int_eq(find, false);
    ck_assert_uint_eq(pos, 1);
}
END_TEST

// Фильм отсутствует. Массив из четного количества элементов. Поиск отсутствующего фильма на нечетной позиции
START_TEST (neg_even_elems_array_find_odd_pos_elem_title_cmp)
{
    film_t arr[] = {
        {"aa", "aa", 2009},
        {"bb", "bb", 2013},
        {"cc", "cc", 2010},
        {"dd", "dd", 2016}
    };
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = {.title = "da"};
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_title);

    ck_assert_int_eq(find, false);
    ck_assert_uint_eq(pos, 3); 
}
END_TEST

// Фильм отсутствует. Массив из одного элемента. Сравнение по имени актера
START_TEST (neg_one_elem_array_name_cmp)
{
    film_t arr[] = {
        {"aa", "aa", 2009},
    };
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = {.name = "a"};
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_name);

    ck_assert_int_eq(find, false);
    ck_assert_uint_eq(pos, 0); 
}
END_TEST

// Фильм отсутствует. Массив из двух элементов. Поиск отсутствующего фильма перед первым элементом
START_TEST (neg_two_elems_array_find_first_elem_name_cmp)
{
    film_t arr[] = {
        {"aa", "aa", 2009},
        {"bb", "bb", 2013},
    };
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = {.name = "a"};
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_name);

    ck_assert_int_eq(find, false);
    ck_assert_uint_eq(pos, 0);  
}
END_TEST

// Фильм отсутствует. Массив из двух элементов. Поиск отсутствующего фильма после последнего элемента
START_TEST (neg_two_elems_array_find_last_elem_name_cmp)
{
    film_t arr[] = {
        {"aa", "aa", 2009},
        {"bb", "bb", 2013},
    };
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = {.name = "ba"};
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_name);

    ck_assert_int_eq(find, false);
    ck_assert_uint_eq(pos, 1);
}
END_TEST

// Фильм отсутствует. Массив из нечетного количества элементов. Поиск отсутствующего фильма на четной позиции
START_TEST (neg_odd_elems_array_find_even_pos_elem_name_cmp)
{
    film_t arr[] = {
        {"aa", "aa", 2009},
        {"bb", "bb", 2013},
        {"cc", "cc", 2010},
    };
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = {.name = "ba"};
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_name);

    ck_assert_int_eq(find, false);
    ck_assert_uint_eq(pos, 1); 
}
END_TEST

// Фильм отсутствует. Массив из нечетного количества элементов. Поиск отсутствующего фильма на нечетной позиции
START_TEST (neg_odd_elems_array_find_odd_pos_elem_name_cmp)
{
    film_t arr[] = {
        {"aa", "aa", 2009},
        {"bb", "bb", 2013},
        {"cc", "cc", 2010},
    };
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = {.name = "ca"};
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_name);

    ck_assert_int_eq(find, false);
    ck_assert_uint_eq(pos, 2); 
}
END_TEST

// Фильм отсутствует. Массив из четного количества элементов. Поиск отсутствующего фильма на четной позиции
START_TEST (neg_even_elems_array_find_even_elem_name_cmp)
{
    film_t arr[] = {
        {"aa", "aa", 2009},
        {"bb", "bb", 2013},
        {"cc", "cc", 2010},
        {"dd", "dd", 2016}
    };
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = {.name = "ba"};
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_name);

    ck_assert_int_eq(find, false);
    ck_assert_uint_eq(pos, 1);
}
END_TEST

// Фильм отсутствует. Массив из четного количества элементов. Поиск отсутствующего фильма на нечетной позиции
START_TEST (neg_even_elems_array_find_odd_pos_elem_name_cmp)
{
    film_t arr[] = {
        {"aa", "aa", 2009},
        {"bb", "bb", 2013},
        {"cc", "cc", 2010},
        {"dd", "dd", 2016}
    };
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = {.name = "da"};
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_name);

    ck_assert_int_eq(find, false);
    ck_assert_uint_eq(pos, 3); 
}
END_TEST

// Фильм отсутствует. Массив из одного элемента, отсортирован по году. Сравнение по году
START_TEST (neg_one_elem_array_year_cmp)
{
    film_t arr[] = {{"La La Land", "Ryan Gosling", 2016}};
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = {.year = 2010};
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_year);

    ck_assert_int_eq(find, false);
    ck_assert_uint_eq(pos, 0);  // Позиция для вставки в начало
}
END_TEST

// Фильм отсутствует. Массив из двух элементов, отсортирован по году. Поиск отсутствующего фильма перед первым элементом
START_TEST (neg_two_elems_array_find_first_elem_year_cmp)
{
    film_t arr[] = {
        {"Avatar", "Sam Worthington", 2009},
        {"Interstellar", "Matthew McConaughey", 2014}
    };
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = {.year = 2010};
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_year);

    ck_assert_int_eq(find, false);
    ck_assert_uint_eq(pos, 1);  // Позиция для вставки перед первым элементом
}
END_TEST

// Фильм отсутствует. Массив из двух элементов, отсортирован по году. Поиск отсутствующего фильма между двумя элементами
START_TEST (neg_two_elems_array_find_last_elem_year_cmp)
{
    film_t arr[] = {
        {"Avatar", "Sam Worthington", 2009},
        {"Interstellar", "Matthew McConaughey", 2014}
    };
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = {.year = 2012};
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_year);

    ck_assert_int_eq(find, false);
    ck_assert_uint_eq(pos, 1);  // Позиция для вставки между элементами
}
END_TEST

// Фильм отсутствует. Массив из нечетного количества элементов, отсортирован по году. Поиск отсутствующего фильма на четной позиции
START_TEST (neg_odd_elems_array_find_even_pos_elem_year_cmp)
{
    film_t arr[] = {
        {"Avatar", "Sam Worthington", 2009},
        {"Inception", "Leonardo DiCaprio", 2010},
        {"Interstellar", "Matthew McConaughey", 2014}
    };
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = {.year = 2013};
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_year);

    ck_assert_int_eq(find, false);
    ck_assert_uint_eq(pos, 2);  // Позиция для вставки после второго элемента
}
END_TEST

// Фильм отсутствует. Массив из нечетного количества элементов, отсортирован по году. Поиск отсутствующего фильма на нечетной позиции
START_TEST (neg_odd_elems_array_find_odd_pos_elem_year_cmp)
{
    film_t arr[] = {
        {"Avatar", "Sam Worthington", 2009},
        {"Gravity", "Sandra Bullock", 2013},
        {"Interstellar", "Matthew McConaughey", 2014}
    };
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = {.year = 2011};
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_year);

    ck_assert_int_eq(find, false);
    ck_assert_uint_eq(pos, 1);  // Позиция для вставки между первым и вторым элементами
}
END_TEST

// Фильм отсутствует. Массив из четного количества элементов, отсортирован по году. Поиск отсутствующего фильма на четной позиции
START_TEST (neg_even_elems_array_find_even_elem_year_cmp)
{
    film_t arr[] = {
        {"Avatar", "Sam Worthington", 2009},
        {"Gravity", "Sandra Bullock", 2010},
        {"Inception", "Leonardo DiCaprio", 2013},
        {"Interstellar", "Matthew McConaughey", 2014}
    };
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = {.year = 2012};
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_year);

    ck_assert_int_eq(find, false);
    ck_assert_uint_eq(pos, 2);  // Позиция для вставки между вторым и третьим элементами
}
END_TEST

// Фильм отсутствует. Массив из четного количества элементов, отсортирован по году. Поиск отсутствующего фильма на нечетной позиции
START_TEST (neg_even_elems_array_find_odd_pos_elem_year_cmp)
{
    film_t arr[] = {
        {"Avatar", "Sam Worthington", 2009},
        {"Gravity", "Sandra Bullock", 2010},
        {"Inception", "Leonardo DiCaprio", 2013},
        {"La La Land", "Ryan Gosling", 2016}
    };
    size_t length = sizeof(arr) / sizeof(arr[0]);

    film_t pkey = {.year = 2015};
    size_t pos;

    bool find = binary_search(&pos, arr, length, &pkey, film_cmp_by_year);

    ck_assert_int_eq(find, false);
    ck_assert_uint_eq(pos, 3);  // Позиция для вставки между третьим и четвертым элементами
}
END_TEST


Suite* test_binary_search_suite(void)
{
    Suite *suite;
    TCase *tc_pos;

    suite = suite_create("binary_search");
    
    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, pos_one_elem_array_title_cmp);
    tcase_add_test(tc_pos, pos_two_elems_array_find_first_elem_title_cmp);
    tcase_add_test(tc_pos, pos_two_elems_array_find_last_elem_title_cmp);
    tcase_add_test(tc_pos, pos_odd_elems_array_find_even_pos_elem_title_cmp);
    tcase_add_test(tc_pos, pos_odd_elems_array_find_odd_pos_elem_title_cmp);
    tcase_add_test(tc_pos, pos_even_elems_array_find_even_elem_title_cmp);
    tcase_add_test(tc_pos, pos_even_elems_array_find_odd_pos_elem_title_cmp);
    tcase_add_test(tc_pos, pos_multiple_matching_titles);

    tcase_add_test(tc_pos, pos_one_elem_array_name_cmp);
    tcase_add_test(tc_pos, pos_two_elems_array_find_first_elem_name_cmp);
    tcase_add_test(tc_pos, pos_two_elems_array_find_last_elem_name_cmp);
    tcase_add_test(tc_pos, pos_odd_elems_array_find_even_pos_elem_name_cmp);
    tcase_add_test(tc_pos, pos_odd_elems_array_find_odd_pos_elem_name_cmp);
    tcase_add_test(tc_pos, pos_odd_elems_array_find_mid_pos_elem_name_cmp);
    tcase_add_test(tc_pos, pos_even_elems_array_find_even_elem_name_cmp);
    tcase_add_test(tc_pos, pos_even_elems_array_find_odd_pos_elem_name_cmp);
    tcase_add_test(tc_pos, pos_multiple_matching_names);


    tcase_add_test(tc_pos, pos_one_elem_array_year_cmp);
    tcase_add_test(tc_pos, pos_two_elems_array_find_first_elem_year_cmp);
    tcase_add_test(tc_pos, pos_two_elems_array_find_last_elem_year_cmp);
    tcase_add_test(tc_pos, pos_odd_elems_array_find_even_pos_elem_year_cmp);
    tcase_add_test(tc_pos, pos_odd_elems_array_find_odd_pos_elem_year_cmp);
    tcase_add_test(tc_pos, pos_odd_elems_array_find_mid_pos_elem_year_cmp);
    tcase_add_test(tc_pos, pos_even_elems_array_find_even_elem_year_cmp);
    tcase_add_test(tc_pos, pos_even_elems_array_find_odd_pos_elem_year_cmp);
    tcase_add_test(tc_pos, pos_multiple_matching_years);
    
    //tc_pos = tcase_create("negatives");
    
    tcase_add_test(tc_pos, neg_one_elem_array_title_cmp);
    tcase_add_test(tc_pos, neg_two_elems_array_find_first_elem_title_cmp);
    tcase_add_test(tc_pos, neg_two_elems_array_find_last_elem_title_cmp);
    tcase_add_test(tc_pos, neg_odd_elems_array_find_even_pos_elem_title_cmp);
    tcase_add_test(tc_pos, neg_odd_elems_array_find_odd_pos_elem_title_cmp);
    tcase_add_test(tc_pos, neg_even_elems_array_find_even_elem_title_cmp);
    tcase_add_test(tc_pos, neg_even_elems_array_find_odd_pos_elem_title_cmp);


    tcase_add_test(tc_pos, neg_one_elem_array_name_cmp);
    tcase_add_test(tc_pos, neg_two_elems_array_find_first_elem_name_cmp);
    tcase_add_test(tc_pos, neg_two_elems_array_find_last_elem_name_cmp);
    tcase_add_test(tc_pos, neg_odd_elems_array_find_even_pos_elem_name_cmp);
    tcase_add_test(tc_pos, neg_odd_elems_array_find_odd_pos_elem_name_cmp);
    tcase_add_test(tc_pos, neg_even_elems_array_find_even_elem_name_cmp);
    tcase_add_test(tc_pos, neg_even_elems_array_find_odd_pos_elem_name_cmp);

    tcase_add_test(tc_pos, neg_one_elem_array_year_cmp);
    tcase_add_test(tc_pos, neg_two_elems_array_find_first_elem_year_cmp);
    tcase_add_test(tc_pos, neg_two_elems_array_find_last_elem_year_cmp);
    tcase_add_test(tc_pos, neg_odd_elems_array_find_even_pos_elem_year_cmp);
    tcase_add_test(tc_pos, neg_odd_elems_array_find_odd_pos_elem_year_cmp);
    tcase_add_test(tc_pos, neg_even_elems_array_find_even_elem_year_cmp);
    tcase_add_test(tc_pos, neg_even_elems_array_find_odd_pos_elem_year_cmp);

    suite_add_tcase(suite, tc_pos);

    return suite;
}
