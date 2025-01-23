#include "same_functions.h"
#include <assert.h>

bool products_equal(product_t *first, product_t *second)
{
    assert(first);
    assert(second);

    if (cmp_products_by_name(first, second) != 0)
        return false;

    if (cmp_products_by_price(first, second) != 0)
        return false;
    
    return true;
}

size_t list_length(node_t *head)
{
    if (!head)
        return 0;
    
    return list_length(head->next) + 1;
}

bool my_check_list_equal(node_t *head_first, node_t *head_second)
{
    size_t length_first = list_length(head_first);
    size_t length_second = list_length(head_second);

    //printf("%zu %zu\n", length_first, length_second);
    
    if (length_first != length_second)
        return false;

    for (size_t i = 0; i < length_first; i++)
    {
        product_t *data1 = head_first->data;
        product_t *data2 = head_second->data;

        if (!products_equal(data1, data2))
        {
            //product_print(stdout, data1);
            //product_print(stdout, data2);
            //puts("");
            return false;
        }

        head_first = head_first->next;
        head_second = head_second->next;
    }

    //puts("dsad");
    return true;
}

node_t *find_elem(node_t *head, size_t count)
{
    size_t lst_length = list_length(head);

    assert(count <= lst_length);

    for (size_t i = 0; i < count; i++)
        head = head->next;
    
    return head;
}