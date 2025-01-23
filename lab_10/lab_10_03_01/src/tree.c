#define _POSIX_C_SOURCE 200809L

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "tree.h"
#include "associative_array.h"

node_t *tree_search(node_t *head, const char *key)
{
    int cmp = 0;
    while (head && (cmp = strcmp(key, head->key)) != 0)
    {
        if (cmp < 0)
            head = head->lhs;
        else 
            head = head->rhs;
    }

    return head;
}

void tree_insert(node_t **head, node_t *node)
{
    if (!head || !(*head))
    {
        *head = node;
        return;
    }
    node_t *tmp_head = *head, *parent = NULL;
    int cmp = 0;
    while (tmp_head)
    {
        parent = tmp_head;
        cmp = strcmp(node->key, tmp_head->key);
        if (cmp < 0)
            tmp_head = tmp_head->lhs;
        else 
            tmp_head = tmp_head->rhs;
    }

    if (cmp < 0)
        parent->lhs = node;
    else 
        parent->rhs = node;
}

void tree_apply_infix(node_t *head, void (*action)(const char *key, int *num, void *param), void *param)
{
    if (!head)
        return;

    tree_apply_infix(head->lhs, action, param);
    if (action)
        action(head->key, &head->value, param);
    tree_apply_infix(head->rhs, action, param);
}

node_t *tree_search_min(node_t *head)
{
    if (!head)
        return NULL;

    while (head->lhs != NULL)
        head = head->lhs;
    
    return head;
}

node_t *tree_search_max(node_t *head)
{
    if (!head)
        return NULL;

    while (head->rhs != NULL)
        head = head->rhs;
    
    return head;
}


assoc_array_error_t node_remove(node_t **head, node_t *node)
{
    assert(node);

    if (!head || !(*head) || !node)
        return ASSOC_ARRAY_INVALID_PARAM;

    int cmp = strcmp(node->key, (*head)->key);
    if (cmp < 0)
    {
        return node_remove(&(*head)->lhs, node);
    }
    else if (cmp > 0)
    {
        return node_remove(&(*head)->rhs, node);
    }
    else 
    {
        if ((*head)->lhs && (*head)->rhs)
        {
            node_t *min = tree_search_min((*head)->rhs);
            node_free_content(*head);

            if (node_deep_copy(*head, min) != ASSOC_ARRAY_OK)
            {
                return ASSOC_ARRAY_MEM;
            }
            return node_remove(&(*head)->rhs, min);
        }
        else
        {
            node_t *tmp = (*head)->lhs ? (*head)->lhs : (*head)->rhs;
            node_free_content(*head);
            node_destroy(head);
            *head = tmp;
        }
    }
    return ASSOC_ARRAY_OK;
}


void tree_destroy(node_t **head)
{
    if (!head || !(*head))
        return;

    tree_destroy(&(*head)->lhs);
    tree_destroy(&(*head)->rhs);

    node_destroy(head);
}
