#include "check_my_snprintf.h"
#include "my_snprintf.h"

#include <stdio.h>
#include <limits.h>

#define MAX_SIZE 64

// Строка из одного слова
START_TEST (test_s_one_word)
{
    char *word = "Hello";
    size_t n = MAX_SIZE;
    char my_str[MAX_SIZE];
    char src_str[MAX_SIZE];

    int rc_snprintf, rc_my_snprintf;

    rc_snprintf = snprintf(src_str, n, "%s", word);
    rc_my_snprintf = my_snprintf(my_str, n, "%s", word);

    ck_assert_int_eq(rc_my_snprintf, rc_snprintf);
    ck_assert_str_eq(my_str, src_str);
}
END_TEST

// Строка из нескольких слов
START_TEST (test_s_several_words)
{
    char *words[] = {"Hello", "my", "name", "is", "Evgenii"};
    size_t n = MAX_SIZE;
    char my_str[MAX_SIZE];
    char src_str[MAX_SIZE];

    int rc_snprintf, rc_my_snprintf;

    rc_snprintf = snprintf(src_str, n, "%s %s %s %s %s", words[0], words[1], words[2], words[3], words[4]);
    rc_my_snprintf = my_snprintf(my_str, n, "%s %s %s %s %s", words[0], words[1], words[2], words[3], words[4]);

    ck_assert_int_eq(rc_my_snprintf, rc_snprintf);
    ck_assert_str_eq(my_str, src_str);
}
END_TEST

// Максимальный размер буфера (n) меньше того, что должно получиться в результате форматирования строки функцией snprintf
START_TEST (test_s_maxlen_lower)
{
    char *words[] = {"Hello", "my", "name", "is", "Evgenii"};
    size_t n = strlen(words[0]) + strlen(words[3]);
    char my_str[MAX_SIZE];
    char src_str[MAX_SIZE];

    int rc_snprintf, rc_my_snprintf;

    rc_snprintf = snprintf(src_str, n, "%s %s %s %s %s", words[0], words[1], words[2], words[3], words[4]);
    rc_my_snprintf = my_snprintf(my_str, n, "%s %s %s %s %s", words[0], words[1], words[2], words[3], words[4]);

    ck_assert_int_eq(rc_my_snprintf, rc_snprintf);
    ck_assert_str_eq(my_str, src_str);
}
END_TEST

// Максимальный размер буфера (n) равен 0
START_TEST (test_s_maxlen_is_zero)
{
    char *words[] = {"Hello", "my", "name", "is", "Evgenii"};
    size_t n = 0;
    
    char my_str[MAX_SIZE];
    my_str[0] = '\0';
    
    char src_str[MAX_SIZE];
    src_str[0] = '\0';

    int rc_snprintf, rc_my_snprintf;

    rc_snprintf = snprintf(src_str, n, "%s %s %s %s %s", words[0], words[1], words[2], words[3], words[4]);
    rc_my_snprintf = my_snprintf(my_str, n, "%s %s %s %s %s", words[0], words[1], words[2], words[3], words[4]);

    ck_assert_int_eq(rc_my_snprintf, rc_snprintf);
    ck_assert_str_eq(my_str, src_str);
}
END_TEST

// без спецификаторов
START_TEST (test_s_no_specs)
{
    size_t n = MAX_SIZE;
    char my_str[MAX_SIZE];
    char src_str[MAX_SIZE];

    int rc_snprintf, rc_my_snprintf;

    rc_snprintf = snprintf(src_str, n, "Hello, my name is Evgenii");
    rc_my_snprintf = my_snprintf(my_str, n, "Hello, my name is Evgenii");

    ck_assert_int_eq(rc_my_snprintf, rc_snprintf);
    ck_assert_str_eq(my_str, src_str);
}
END_TEST

// Одно число
START_TEST (test_llx_one_num)
{
    unsigned long long num[] = { 123 };
    size_t n = MAX_SIZE;
    char my_str[MAX_SIZE];
    char src_str[MAX_SIZE];

    int rc_snprintf, rc_my_snprintf;

    rc_snprintf = snprintf(src_str, n, "%llx", num[0]);
    rc_my_snprintf = my_snprintf(my_str, n, "%llx", num[0]);

    ck_assert_int_eq(rc_my_snprintf, rc_snprintf);
    ck_assert_str_eq(my_str, src_str);
}
END_TEST

// Два числа
START_TEST (test_llx_two_nums)
{
    unsigned long long num[] = { 123, 435367 };
    size_t n = MAX_SIZE;
    char my_str[MAX_SIZE];
    char src_str[MAX_SIZE];

    int rc_snprintf, rc_my_snprintf;

    rc_snprintf = snprintf(src_str, n, "%llx %llx", num[0], num[1]);
    rc_my_snprintf = my_snprintf(my_str, n, "%llx %llx", num[0], num[1]);

    ck_assert_int_eq(rc_my_snprintf, rc_snprintf);
    ck_assert_str_eq(my_str, src_str);
}
END_TEST

// Четыре числа
START_TEST (test_llx_four_nums)
{
    unsigned long long num[] = { 123, 435367, 6754, 135435 };
    size_t n = MAX_SIZE;
    char my_str[MAX_SIZE];
    char src_str[MAX_SIZE];

    int rc_snprintf, rc_my_snprintf;

    rc_snprintf = snprintf(src_str, n, "%llx %llx %llx %llx", num[0], num[1], num[2], num[3]);
    rc_my_snprintf = my_snprintf(my_str, n, "%llx %llx %llx %llx", num[0], num[1], num[2], num[3]);

    ck_assert_int_eq(rc_my_snprintf, rc_snprintf);
    ck_assert_str_eq(my_str, src_str);
}
END_TEST

// Число 0 для подстановки в строку
START_TEST (test_llx_num_zero)
{
    unsigned long long num[] = { 0 };
    size_t n = MAX_SIZE;
    char my_str[MAX_SIZE];
    char src_str[MAX_SIZE];

    int rc_snprintf, rc_my_snprintf;

    rc_snprintf = snprintf(src_str, n, "%llx", num[0]);
    rc_my_snprintf = my_snprintf(my_str, n, "%llx", num[0]);

    ck_assert_int_eq(rc_my_snprintf, rc_snprintf);
    ck_assert_str_eq(my_str, src_str);
}
END_TEST

/**
 * В качетсве числа типа unsigned long long для подстановки в строку форматирования
 * взято Максимально допустимое стандартом число: UINT_MAX
*/
START_TEST (test_llx_uint_max_num)
{
    unsigned long long num[] = { UINT_MAX };
    size_t n = MAX_SIZE;
    char my_str[MAX_SIZE];
    char src_str[MAX_SIZE];

    int rc_snprintf, rc_my_snprintf;

    rc_snprintf = snprintf(src_str, n, "%llx", num[0]);
    rc_my_snprintf = my_snprintf(my_str, n, "%llx", num[0]);

    ck_assert_int_eq(rc_my_snprintf, rc_snprintf);
    ck_assert_str_eq(my_str, src_str);
}
END_TEST

// Максимальный размер буфера (n) меньше того, что должно получиться в результате форматирования строки функцией snprintf
START_TEST (test_llx_maxlen_is_lower)
{
    unsigned long long num[] = { UINT_MAX };
    size_t n = 10;
    char my_str[MAX_SIZE];
    char src_str[MAX_SIZE];

    int rc_snprintf, rc_my_snprintf;

    rc_snprintf = snprintf(src_str, n, "%llx", num[0]);
    rc_my_snprintf = my_snprintf(my_str, n, "%llx", num[0]);

    ck_assert_int_eq(rc_my_snprintf, rc_snprintf);
    ck_assert_str_eq(my_str, src_str);
}
END_TEST

//Одно число, одна строка
START_TEST (test_all_1)
{
    unsigned long long num[] = { 131 };
    char *words[] = { "Hello" };

    size_t n = MAX_SIZE;
    char my_str[MAX_SIZE];
    char src_str[MAX_SIZE];

    int rc_snprintf, rc_my_snprintf;

    rc_snprintf = snprintf(src_str, n, "%s %llx", words[0], num[0]);
    rc_my_snprintf = my_snprintf(my_str, n, "%s %llx", words[0], num[0]);

    ck_assert_int_eq(rc_my_snprintf, rc_snprintf);
    ck_assert_str_eq(my_str, src_str);
}
END_TEST

//Два числа, две строки
START_TEST (test_all_2)
{
    unsigned long long num[] = { 131, 5376575 };
    char *words[] = { "Hello", "<3" };

    size_t n = MAX_SIZE;
    char my_str[MAX_SIZE];
    char src_str[MAX_SIZE];

    int rc_snprintf, rc_my_snprintf;

    rc_snprintf = snprintf(src_str, n, "%s %llx hahaha %llx %s", words[0], num[0], num[1], words[1]);
    rc_my_snprintf = my_snprintf(my_str, n, "%s %llx hahaha %llx %s", words[0], num[0], num[1], words[1]);

    ck_assert_int_eq(rc_my_snprintf, rc_snprintf);
    ck_assert_str_eq(my_str, src_str);
}
END_TEST

// Максимальный размер буфера (n) меньше того, что должно получиться в результате форматирования строки функцией snprintf
START_TEST (test_all_maxlen_lower)
{
    unsigned long long num[] = { 131, 5376575 };
    char *words[] = { "Hello", "<3" };

    size_t n = 15;
    char my_str[MAX_SIZE];
    char src_str[MAX_SIZE];

    int rc_snprintf, rc_my_snprintf;

    rc_snprintf = snprintf(src_str, n, "%s %llx hahaha %llx %s", words[0], num[0], num[1], words[1]);
    rc_my_snprintf = my_snprintf(my_str, n, "%s %llx hahaha %llx %s", words[0], num[0], num[1], words[1]);

    ck_assert_int_eq(rc_my_snprintf, rc_snprintf);
    ck_assert_str_eq(my_str, src_str);
}
END_TEST

// Максимальный размер буфера (n) равен 0
START_TEST (test_all_maxlen_is_zero)
{
    unsigned long long num[] = { 131, 5376575 };
    char *words[] = { "Hello", "<3" };

    size_t n = 0;
    char my_str[MAX_SIZE];
    my_str[0] = '\0';
    char src_str[MAX_SIZE];
    src_str[0] = '\0';

    int rc_snprintf, rc_my_snprintf;

    rc_snprintf = snprintf(src_str, n, "%s %llx hahaha %llx %s", words[0], num[0], num[1], words[1]);
    rc_my_snprintf = my_snprintf(my_str, n, "%s %llx hahaha %llx %s", words[0], num[0], num[1], words[1]);

    ck_assert_int_eq(rc_my_snprintf, rc_snprintf);
    ck_assert_str_eq(my_str, src_str);
}
END_TEST

//Строка с процентами (раньше я думал, что у меня из-за этого падал тест в системе)
START_TEST (test_percents)
{
    unsigned long long num[] = { 5376575 };
    char *words[] = { "Hello" };

    size_t n = MAX_SIZE;
    char my_str[MAX_SIZE];
    char src_str[MAX_SIZE];

    int rc_snprintf, rc_my_snprintf;

    rc_snprintf = snprintf(src_str, n, "hdhd %%llx%%%%%s%% %%%llxx fsfsfs", words[0], num[0]);
    rc_my_snprintf = my_snprintf(my_str, n, "hdhd %%llx%%%%%s%% %%%llxx fsfsfs", words[0], num[0]);

    ck_assert_int_eq(rc_my_snprintf, rc_snprintf);
    ck_assert_str_eq(my_str, src_str);
}
END_TEST

Suite* test_my_snprintf(void)
{
    Suite *suite;
    TCase *tc_s, *tc_llx, *tc_all;

    suite = suite_create("my_snprintf");

    tc_s = tcase_create("s");
    tcase_add_test(tc_s, test_s_one_word);
    tcase_add_test(tc_s, test_s_several_words);
    tcase_add_test(tc_s, test_s_maxlen_lower);
    tcase_add_test(tc_s, test_s_maxlen_is_zero);
    tcase_add_test(tc_s, test_s_no_specs);
    suite_add_tcase(suite, tc_s);

    
    tc_llx = tcase_create("llx");
    tcase_add_test(tc_llx, test_llx_one_num);
    tcase_add_test(tc_llx, test_llx_two_nums);
    tcase_add_test(tc_llx, test_llx_four_nums);
    tcase_add_test(tc_llx, test_llx_num_zero);
    tcase_add_test(tc_llx, test_llx_uint_max_num);
    tcase_add_test(tc_llx, test_llx_maxlen_is_lower);
    suite_add_tcase(suite, tc_llx);
    
    tc_all = tcase_create("all");
    tcase_add_test(tc_all, test_all_1);
    tcase_add_test(tc_all, test_all_2);
    tcase_add_test(tc_all, test_all_maxlen_lower);
    tcase_add_test(tc_all, test_all_maxlen_is_zero);
    tcase_add_test(tc_all, test_percents);
    suite_add_tcase(suite, tc_all);

    return suite;
}
