#include "same_functions.h"
#include "check_reverse.h"
#include "list.h"
#include "errors.h"

/*
    Юнит тесты удаления элемента из хвоста списка
*/

START_TEST(zero_elems_list)
{
    node_t *list = NULL;

    list = reverse(list);

    ck_assert_ptr_null(list);
}
END_TEST

//Сортировка одного элемента
START_TEST(one_elem_list)
{
    product_t arr_src[] = { { "a", 10 } };
    size_t length_src = sizeof(arr_src) / sizeof(arr_src[0]);

    product_t arr_dst[] = { { "a", 10 } };
    size_t length_dst = sizeof(arr_dst) / sizeof(arr_dst[0]);  

    node_t *head_src = NULL;
    int rc = list_create(&head_src, arr_src, length_src);

    ck_assert_int_eq(rc, OK);
    ck_assert_ptr_nonnull(head_src);

    head_src = sort(head_src, cmp_products_by_price);

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

//Сортировка двух элементов (элементы сразу отсортированы)
START_TEST(two_elems_sorted_at_once)
{
    product_t arr_src[] = { { "a", 10 }, { "b", 20 } };
    size_t length_src = sizeof(arr_src) / sizeof(arr_src[0]);

    product_t arr_dst[] = { { "a", 10 }, { "b", 20 } };
    size_t length_dst = sizeof(arr_dst) / sizeof(arr_dst[0]);  

    node_t *head_src = NULL;
    int rc = list_create(&head_src, arr_src, length_src);

    ck_assert_int_eq(rc, OK);
    ck_assert_ptr_nonnull(head_src);

    head_src = sort(head_src, cmp_products_by_price);

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

//Сортировка двух элементов (элементы сразу не отсортированы)
START_TEST(two_elems_not_sorted_at_once)
{
    product_t arr_src[] = { { "a", 20 }, { "b", 10 } };
    size_t length_src = sizeof(arr_src) / sizeof(arr_src[0]);

    product_t arr_dst[] = { { "b", 10 }, { "a", 20 } };
    size_t length_dst = sizeof(arr_dst) / sizeof(arr_dst[0]);  

    node_t *head_src = NULL;
    int rc = list_create(&head_src, arr_src, length_src);

    ck_assert_int_eq(rc, OK);
    ck_assert_ptr_nonnull(head_src);

    head_src = sort(head_src, cmp_products_by_price);

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

//Элементы сразу отсортированы в убывающем порядке
START_TEST(elems_in_descending_order)
{
    product_t arr_src[] = { { "a", 20 }, { "b", 10 }, { "c", 8 }, { "d", 6 }, { "e", 5 } };
    size_t length_src = sizeof(arr_src) / sizeof(arr_src[0]);

    product_t arr_dst[] = { { "e", 5 }, { "d", 6 }, { "c", 8 }, { "b", 10 }, { "a", 20 } };
    size_t length_dst = sizeof(arr_dst) / sizeof(arr_dst[0]);  

    node_t *head_src = NULL;
    int rc = list_create(&head_src, arr_src, length_src);

    ck_assert_int_eq(rc, OK);
    ck_assert_ptr_nonnull(head_src);

    head_src = sort(head_src, cmp_products_by_price);

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

//Элементы сразу в возрастающем порядке
START_TEST(elems_in_increasing_order)
{
    product_t arr_src[] = { { "e", 5 }, { "d", 6 }, { "c", 8 }, { "b", 10 }, { "a", 20 } };
    size_t length_src = sizeof(arr_src) / sizeof(arr_src[0]);

    product_t arr_dst[] = { { "e", 5 }, { "d", 6 }, { "c", 8 }, { "b", 10 }, { "a", 20 } };
    size_t length_dst = sizeof(arr_dst) / sizeof(arr_dst[0]);  

    node_t *head_src = NULL;
    int rc = list_create(&head_src, arr_src, length_src);

    ck_assert_int_eq(rc, OK);
    ck_assert_ptr_nonnull(head_src);

    head_src = sort(head_src, cmp_products_by_price);

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

//Элементы сначала убывают, потом возрастают
START_TEST(elems_are_ordered_first_in_descending_order_then_in_increasing_order)
{
    product_t arr_src[] = { { "e", 10 }, { "d", 8 }, { "c", 5 }, { "b", 1 }, { "a", 4 } };
    size_t length_src = sizeof(arr_src) / sizeof(arr_src[0]);

    product_t arr_dst[] = { { "b", 1 }, { "a", 4 }, { "c", 5 }, { "d", 8 }, { "e", 10 } };
    size_t length_dst = sizeof(arr_dst) / sizeof(arr_dst[0]);  

    node_t *head_src = NULL;
    int rc = list_create(&head_src, arr_src, length_src);

    ck_assert_int_eq(rc, OK);
    ck_assert_ptr_nonnull(head_src);

    head_src = sort(head_src, cmp_products_by_price);

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

//Элементы сначала возрастают, потом убывают
START_TEST(elems_are_ordered_first_in_increasing_order_then_in_descending_order)
{
    product_t arr_src[] = { { "e", 10 }, { "d", 20 }, { "c", 30 }, { "b", 5 }, { "a", 2 } };
    size_t length_src = sizeof(arr_src) / sizeof(arr_src[0]);

    product_t arr_dst[] = { { "a", 2 }, { "b", 5 }, { "e", 10 }, { "d", 20 }, { "c", 30 } };
    size_t length_dst = sizeof(arr_dst) / sizeof(arr_dst[0]);   

    node_t *head_src = NULL;
    int rc = list_create(&head_src, arr_src, length_src);

    ck_assert_int_eq(rc, OK);
    ck_assert_ptr_nonnull(head_src);

    head_src = sort(head_src, cmp_products_by_price);

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

//Элементы с отрицательными числовым полем
START_TEST(negative_elems)
{
    product_t arr_src[] = { { "a", -20 }, { "b", -10 }, { "c", -5 }, { "d", -8 } };
    size_t length_src = sizeof(arr_src) / sizeof(arr_src[0]);

    product_t arr_dst[] = { { "a", -20 }, { "b", -10 }, { "d", -8 }, { "c", -5 }  };
    size_t length_dst = sizeof(arr_dst) / sizeof(arr_dst[0]);  

    node_t *head_src = NULL;
    int rc = list_create(&head_src, arr_src, length_src);

    ck_assert_int_eq(rc, OK);
    ck_assert_ptr_nonnull(head_src);

    head_src = sort(head_src, cmp_products_by_price);

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

//Проверка устойчивости сортировки
START_TEST(same_sort_fields)
{
    product_t arr_src[] = { { "a", -20 }, { "b", -10 }, { "c", -20 }, { "d", -8 } };
    size_t length_src = sizeof(arr_src) / sizeof(arr_src[0]);

    product_t arr_dst[] = { { "a", -20 }, { "c", -20 }, { "b", -10 }, { "d", -8 }  };
    size_t length_dst = sizeof(arr_dst) / sizeof(arr_dst[0]);  

    node_t *head_src = NULL;
    int rc = list_create(&head_src, arr_src, length_src);

    ck_assert_int_eq(rc, OK);
    ck_assert_ptr_nonnull(head_src);

    head_src = sort(head_src, cmp_products_by_price);

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

Suite* test_sort(void)
{
    Suite *suite;
    TCase *tc_pos;

    suite = suite_create("sort");
    
    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, zero_elems_list);
    tcase_add_test(tc_pos, one_elem_list);
    tcase_add_test(tc_pos, two_elems_sorted_at_once);
    tcase_add_test(tc_pos, two_elems_not_sorted_at_once);
    tcase_add_test(tc_pos, elems_in_descending_order);
    tcase_add_test(tc_pos, elems_in_increasing_order);
    tcase_add_test(tc_pos, elems_are_ordered_first_in_descending_order_then_in_increasing_order);
    tcase_add_test(tc_pos, elems_are_ordered_first_in_increasing_order_then_in_descending_order);
    tcase_add_test(tc_pos, negative_elems);
    tcase_add_test(tc_pos, same_sort_fields);

    suite_add_tcase(suite, tc_pos);

    return suite;
}
