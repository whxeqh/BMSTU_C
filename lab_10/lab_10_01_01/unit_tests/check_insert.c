#include "same_functions.h"
#include "check_reverse.h"
#include "list.h"
#include "errors.h"

/*
    Юнит тесты вставки элемента в список
*/

//Вставка в пустой список
START_TEST(empty_list)
{
    //product_t arr_src[] = { { "a", 10 } };
    //size_t length_src = sizeof(arr_src) / sizeof(arr_src[0]);
    int rc = OK;

    product_t product = { .name="iu7", .price=777 };
    node_t *elem = node_create(&product);

    //size_t ind_before = 0;
    node_t *before = NULL;

    product_t arr_dst[] = { { "iu7", 777 } };
    size_t length_dst = sizeof(arr_dst) / sizeof(arr_dst[0]);  

    node_t *head_src = NULL;
    
    insert(&head_src, elem, before);

    node_t *head_dst = NULL;
    rc = list_create(&head_dst, arr_dst, length_dst);

    ck_assert_int_eq(rc, OK);
    ck_assert_ptr_nonnull(head_dst);

    bool lists_eq = my_check_list_equal(head_src, head_dst);
    ck_assert_int_eq(lists_eq, true);

    free_list(&head_src);
    free_list(&head_dst);
}
END_TEST

//Вставка в начало списка из одного элемента
START_TEST(one_elem_list_before)
{
    product_t arr_src[] = { { "a", 10 } };
    size_t length_src = sizeof(arr_src) / sizeof(arr_src[0]);

    product_t product = { .name="iu7", .price=777 };
    node_t *elem = node_create(&product);

    product_t arr_dst[] = { { "iu7", 777 }, { "a", 10 } };
    size_t length_dst = sizeof(arr_dst) / sizeof(arr_dst[0]);  

    node_t *head_src = NULL;
    int rc = list_create(&head_src, arr_src, length_src);

    size_t ind_before = 0;
    node_t *before = find_elem(head_src, ind_before);

    ck_assert_int_eq(rc, OK);
    ck_assert_ptr_nonnull(head_src);

    insert(&head_src, elem, before);

    node_t *head_dst = NULL;
    rc = list_create(&head_dst, arr_dst, length_dst);

    ck_assert_int_eq(rc, OK);
    ck_assert_ptr_nonnull(head_dst);

    bool lists_eq = my_check_list_equal(head_src, head_dst);
    ck_assert_int_eq(lists_eq, true);

    free_list(&head_src);
    free_list(&head_dst);
}
END_TEST

//Вставка в начало списка из нескольких элементов
START_TEST(seveal_elems_insert_begin)
{
    product_t arr_src[] = { { "a", 10 }, { "b", 20 }, { "c", 30 }, { "d", 40 }, { "e", 50 } };
    size_t length_src = sizeof(arr_src) / sizeof(arr_src[0]);

    product_t product = { .name="iu7", .price=777 };
    node_t *elem = node_create(&product);

    product_t arr_dst[] = { { "iu7", 777 }, { "a", 10 }, { "b", 20 }, { "c", 30 }, { "d", 40 }, { "e", 50 } };
    size_t length_dst = sizeof(arr_dst) / sizeof(arr_dst[0]);  

    node_t *head_src = NULL;
    int rc = list_create(&head_src, arr_src, length_src);

    size_t ind_before = 0;
    node_t *before = find_elem(head_src, ind_before);

    ck_assert_int_eq(rc, OK);
    ck_assert_ptr_nonnull(head_src);

    insert(&head_src, elem, before);

    node_t *head_dst = NULL;
    rc = list_create(&head_dst, arr_dst, length_dst);

    ck_assert_int_eq(rc, OK);
    ck_assert_ptr_nonnull(head_dst);

    bool lists_eq = my_check_list_equal(head_src, head_dst);
    ck_assert_int_eq(lists_eq, true);

    free_list(&head_src);
    free_list(&head_dst);
}
END_TEST

//Вставка в середину списка из нескольких элементов
START_TEST(seveal_elems_insert_mid)
{
    product_t arr_src[] = { { "a", 10 }, { "b", 20 }, { "c", 30 }, { "d", 40 }, { "e", 50 } };
    size_t length_src = sizeof(arr_src) / sizeof(arr_src[0]);

    product_t product = { .name="iu7", .price=777 };
    node_t *elem = node_create(&product);

    product_t arr_dst[] = { { "a", 10 }, { "b", 20 }, { "iu7", 777 }, { "c", 30 }, { "d", 40 }, { "e", 50 } };
    size_t length_dst = sizeof(arr_dst) / sizeof(arr_dst[0]);  

    node_t *head_src = NULL;
    int rc = list_create(&head_src, arr_src, length_src);

    size_t ind_before = sizeof(arr_src) / sizeof(arr_src[0]) / 2;
    node_t *before = find_elem(head_src, ind_before);

    ck_assert_int_eq(rc, OK);
    ck_assert_ptr_nonnull(head_src);

    insert(&head_src, elem, before);

    node_t *head_dst = NULL;
    rc = list_create(&head_dst, arr_dst, length_dst);

    ck_assert_int_eq(rc, OK);
    ck_assert_ptr_nonnull(head_dst);

    bool lists_eq = my_check_list_equal(head_src, head_dst);
    ck_assert_int_eq(lists_eq, true);

    free_list(&head_src);
    free_list(&head_dst);
}
END_TEST

//Вставка в конец списка из нескольких элементов
START_TEST(seveal_elems_insert_end)
{
    product_t arr_src[] = { { "a", 10 }, { "b", 20 }, { "c", 30 }, { "d", 40 }, { "e", 50 } };
    size_t length_src = sizeof(arr_src) / sizeof(arr_src[0]);

    product_t product = { .name="iu7", .price=777 };
    node_t *elem = node_create(&product);

    product_t arr_dst[] = { { "a", 10 }, { "b", 20 }, { "c", 30 }, { "d", 40 }, { "iu7", 777 }, { "e", 50 } };
    size_t length_dst = sizeof(arr_dst) / sizeof(arr_dst[0]);  

    node_t *head_src = NULL;
    int rc = list_create(&head_src, arr_src, length_src);

    size_t ind_before = sizeof(arr_src) / sizeof(arr_src[0]) - 1;
    node_t *before = find_elem(head_src, ind_before);

    ck_assert_int_eq(rc, OK);
    ck_assert_ptr_nonnull(head_src);

    insert(&head_src, elem, before);

    node_t *head_dst = NULL;
    rc = list_create(&head_dst, arr_dst, length_dst);

    ck_assert_int_eq(rc, OK);
    ck_assert_ptr_nonnull(head_dst);

    bool lists_eq = my_check_list_equal(head_src, head_dst);
    ck_assert_int_eq(lists_eq, true);

    free_list(&head_src);
    free_list(&head_dst);
}
END_TEST

//Элемент before не принадлежит списку
START_TEST(before_not_in_list)
{
    product_t arr_src[] = { { "a", 10 }, { "b", 20 } };
    size_t length_src = sizeof(arr_src) / sizeof(arr_src[0]);

    node_t tmp;

    product_t product = { .name="iu7", .price=777 };
    node_t *elem = node_create(&product);

    product_t arr_dst[] = { { "a", 10 }, { "b", 20 } };
    size_t length_dst = sizeof(arr_dst) / sizeof(arr_dst[0]);  

    node_t *head_src = NULL;
    int rc = list_create(&head_src, arr_src, length_src);

    node_t *before = &tmp;

    ck_assert_int_eq(rc, OK);
    ck_assert_ptr_nonnull(head_src);

    insert(&head_src, elem, before);

    node_t *head_dst = NULL;
    rc = list_create(&head_dst, arr_dst, length_dst);

    ck_assert_int_eq(rc, OK);
    ck_assert_ptr_nonnull(head_dst);

    bool lists_eq = my_check_list_equal(head_src, head_dst);
    ck_assert_int_eq(lists_eq, true);

    free_list(&head_src);
    free_list(&head_dst);
    node_destroy(&elem);
}
END_TEST

Suite* test_insert(void)
{
    Suite *suite;
    TCase *tc_pos;

    suite = suite_create("reverse");
    
    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, one_elem_list_before);
    tcase_add_test(tc_pos, empty_list);
    tcase_add_test(tc_pos, seveal_elems_insert_begin);
    tcase_add_test(tc_pos, seveal_elems_insert_mid);
    tcase_add_test(tc_pos, seveal_elems_insert_end);
    tcase_add_test(tc_pos, before_not_in_list);

    suite_add_tcase(suite, tc_pos);

    return suite;
}
