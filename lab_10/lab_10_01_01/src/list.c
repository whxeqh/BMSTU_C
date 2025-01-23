#include <assert.h>

#include "list.h"
#include "product.h"
#include "errors.h"
#include "macro.h"

static node_t *push_back(node_t *head, node_t *node) 
{
    if (!head)
        return node;
    head->next = push_back(head->next, node);
    return head;
}

void insert(node_t **head, node_t *elem, node_t *before)
{
    assert(elem);
    if (*head == before)
    {
        elem->next = *head;
        *head = elem;
        return;
    }

    node_t *cur = *head;
    while (cur && cur->next != before)
    {
        cur = cur->next;
    }

    if (cur && cur->next == before)
    {
        cur->next = elem;
        elem->next = before; 
    }
}

void sorted_insert(node_t **head, node_t *element, int (*comparator)(const void *left, const void *right))
{
    if (!(*head))
    {
        element->next = NULL;
        *head = element;
        return;
    }

    node_t *cur_head = *head;

    int cmp;
    while (cur_head && (cmp = comparator(element->data, cur_head->data)) >= 0)
    {
        cur_head = cur_head->next;
    }

    insert(head, element, cur_head);
}

node_t *sort(node_t *head, int (*comparator)(const void *left, const void *right))
{
    if (!head)
        return NULL;

    node_t *sorted_list = NULL;
    node_t *cur = head;
    
    while (cur)
    {
        node_t *next = cur->next;
        cur->next = NULL;
        sorted_insert(&sorted_list, cur, comparator);
        cur = next;
    }

    return sorted_list;
}

void *pop_back(node_t **head)
{
    if (!head || !(*head))
        return NULL;

    if ((*head)->next == NULL)
    {
        void *data = (*head)->data;
        node_destroy(head);
        return data;
    }

    return pop_back(&(*head)->next);
}

node_t *reverse(node_t *head)
{
    if (!head || !head->next)    
        return head;

    node_t *reversed = reverse(head->next);

    head->next->next = head;
    head->next = NULL;

    return reversed;
}

int print_list_ex(char *filename, node_t *head)
{
    assert(filename);

    int rc = ERR_FILE;
    FILE *file_out = fopen(filename, "w");
    if (!file_out)
        return rc;

    rc = print_list(file_out, head);

    fclose(file_out);
    
    return rc;
}

int print_list(FILE *file, node_t *head)
{
    assert(file);

    int rc = OK;
    if (!head)
        return rc;
    
    rc = print_node(file, head);
    if (rc != OK)
        return rc;

    return print_list(file, head->next);
}

void free_list(node_t **head)
{
    while (*head)
    {
        pop_back(head);
    }
}

int list_create(node_t **head, product_t *arr, size_t length)
{
    assert(arr);

    free_list(head);
    
    int rc = OK;
    node_t *tmp_head = NULL, *tmp_node = NULL;
    
    for (size_t i = 0; rc == OK && i < length; i++)
    {
        tmp_node = node_create(&arr[i]);
        if (!tmp_node)
            rc = ERR_MEMORY;
        else
            tmp_head = push_back(tmp_head, tmp_node);
    }

    if (rc != OK)
        free_list(&tmp_head);
    else 
        *head = tmp_head;

    return rc;
}
