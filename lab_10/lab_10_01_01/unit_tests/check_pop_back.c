#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "same_functions.h"
#include "check_pop_back.h"
#include "errors.h"
#include "product.h"
#include "list.h"

/*
    Юнит тесты удаления элемента из хвоста списка
*/

START_TEST(zero_elems_list)
{
    node_t *list = NULL;
    void *data = NULL;

    data = pop_back(&list);

    ck_assert_ptr_null(data);
}
END_TEST

START_TEST(one_elem_list)
{
    product_t arr_src[] = { { "a", 10 } };
    size_t length = sizeof(arr_src) / sizeof(arr_src[0]); 

    node_t *head_src = NULL;
    int rc = list_create(&head_src, arr_src, length);

    ck_assert_int_eq(rc, OK);
    ck_assert_ptr_nonnull(head_src);

    void *expected = &arr_src[length - 1];

    void *data = pop_back(&head_src);

    ck_assert_ptr_eq(data, expected);

    node_t *head_dst = NULL;
    ck_assert_ptr_eq(head_src, head_dst);

    free_list(&head_src);
    free_list(&head_dst);
}
END_TEST

START_TEST(two_elems_list)
{
    product_t arr_src[] = { { "a", 10 }, {"b", 20} };
    product_t arr_dst[] = { { "a", 10 } }; 
    size_t length_src = sizeof(arr_src) / sizeof(arr_src[0]); 
    size_t length_dst = sizeof(arr_dst) / sizeof(arr_dst[0]);

    node_t *head_src = NULL;
    int rc = list_create(&head_src, arr_src, length_src);

    ck_assert_int_eq(rc, OK);
    ck_assert_ptr_nonnull(head_src);

    void *expected = &arr_src[length_src - 1];

    void *data = pop_back(&head_src);

    ck_assert_ptr_eq(data, expected);

    node_t *head_dst = NULL;
    rc = list_create(&head_dst, arr_dst, length_dst);
    ck_assert_int_eq(rc, OK);

    bool lists_eq = my_check_list_equal(head_src, head_dst);
    ck_assert_int_eq(lists_eq, true);

    free_list(&head_src);
    free_list(&head_dst);
}
END_TEST

START_TEST(three_elems_list)
{
    product_t arr_src[] = { { "a", 10 }, { "b", 20 }, { "c", 30 } };
    product_t arr_dst[] = { { "a", 10 }, { "b", 20 } }; 
    size_t length_src = sizeof(arr_src) / sizeof(arr_src[0]); 
    size_t length_dst = sizeof(arr_dst) / sizeof(arr_dst[0]);

    node_t *head_src = NULL;
    int rc = list_create(&head_src, arr_src, length_src);

    ck_assert_int_eq(rc, OK);
    ck_assert_ptr_nonnull(head_src);

    void *expected = &arr_src[length_src - 1];

    void *data = pop_back(&head_src);

    ck_assert_ptr_eq(data, expected);

    node_t *head_dst = NULL;
    rc = list_create(&head_dst, arr_dst, length_dst);
    ck_assert_int_eq(rc, OK);

    bool lists_eq = my_check_list_equal(head_src, head_dst);
    ck_assert_int_eq(lists_eq, true);

    free_list(&head_src);
    free_list(&head_dst);
}
END_TEST

Suite* test_pop_back(void)
{
    Suite *suite;
    TCase *tc_pos;

    suite = suite_create("pop_back");
    
    tc_pos = tcase_create("positives");


    tcase_add_test(tc_pos, zero_elems_list);
    tcase_add_test(tc_pos, one_elem_list);
    tcase_add_test(tc_pos, two_elems_list);
    tcase_add_test(tc_pos, three_elems_list);

    suite_add_tcase(suite, tc_pos);

    return suite;
}
