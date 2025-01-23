#include <stdlib.h>
#include <string.h>

#include "associative_array.h"
#include "tree.h"


struct assoc_array_type
{
    node_t *head;
};


assoc_array_t assoc_array_create(void)
{
    assoc_array_t arr = calloc(1, sizeof(struct assoc_array_type));
    if (!arr)
        return NULL;
    
    return arr;
}

void assoc_array_destroy(assoc_array_t *arr)
{
    if (!arr)
        return;

    assoc_array_clear(*arr);
    free(*arr);
    *arr = NULL;
}

assoc_array_error_t assoc_array_insert(assoc_array_t arr, const char *key, int num)
{
    assoc_array_error_t rc = ASSOC_ARRAY_OK;
    if (!arr || !key || !strlen(key))
    {
        rc = ASSOC_ARRAY_INVALID_PARAM;
        goto func_end;
    }

    node_t *head = arr->head;
    if (tree_search(head, key))
    {
        rc = ASSOC_ARRAY_KEY_EXISTS;
        goto func_end;
    }

    node_t *node = node_create(key, num);
    if (!node)
    {
        rc = ASSOC_ARRAY_MEM;
        goto func_end;
    }
    
    tree_insert(&head, node);
    arr->head = head;

    func_end:
        return rc;
}

assoc_array_error_t assoc_array_find(const assoc_array_t arr, const char *key, int **num)
{
    if (!arr || !key || !num || !strlen(key))
        return ASSOC_ARRAY_INVALID_PARAM;
    
    node_t *node = tree_search(arr->head, key);
    if (!node)
        return ASSOC_ARRAY_NOT_FOUND;
    
    *num = &node->value;

    return ASSOC_ARRAY_OK; 
}

assoc_array_error_t assoc_array_remove(assoc_array_t arr, const char *key)
{
    if (!arr || !key || !strlen(key))
        return ASSOC_ARRAY_INVALID_PARAM;
    
    node_t *node = tree_search(arr->head, key);
    if (!node)
        return ASSOC_ARRAY_NOT_FOUND;
    
    node_t *tmp_head = arr->head;

    assoc_array_error_t rc = node_remove(&tmp_head, node);
    if (rc != ASSOC_ARRAY_OK)
        return rc;

    arr->head = tmp_head;

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_clear(assoc_array_t arr)
{
    if (!arr)
        return ASSOC_ARRAY_INVALID_PARAM;

    node_t *head = arr->head;

    tree_destroy(&head);

    arr->head = head;

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_each(const assoc_array_t arr, void (*action)(const char *key, int *num, void *param), void *param)
{  
    if (!arr || !action)
        return ASSOC_ARRAY_INVALID_PARAM;
    
    tree_apply_infix(arr->head, action, param);

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_min(const assoc_array_t arr, int **num)
{
    if (!arr || !num)
        return ASSOC_ARRAY_INVALID_PARAM;
    
    node_t *node = tree_search_min(arr->head);
    if (!node)
        return ASSOC_ARRAY_NOT_FOUND;
    
    *num = &node->value;

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_max(const assoc_array_t arr, int **num)
{
    if (!arr || !num)
        return ASSOC_ARRAY_INVALID_PARAM;
    
    node_t *node = tree_search_max(arr->head);
    if (!node)
        return ASSOC_ARRAY_NOT_FOUND;
    
    *num = &node->value;
    
    return ASSOC_ARRAY_OK;
}
