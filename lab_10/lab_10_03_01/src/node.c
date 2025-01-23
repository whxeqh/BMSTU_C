#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#include "node.h"
#include "associative_array.h"

node_t *node_create(const char *key, int value)
{
    assert(key);

    node_t *tmp = malloc(sizeof(node_t));
    if (!tmp)
        return NULL;
    
    tmp->key = strdup(key);
    if (!tmp->key)
    {
        free(tmp);
        return NULL;
    }

    tmp->value = value;
    tmp->lhs = NULL;
    tmp->rhs = NULL;

    return tmp;
}

void node_free_content(node_t *head)
{
    free(head->key);
    head->key = NULL;
}

void node_destroy(node_t **head)
{
    node_free_content(*head);
    free(*head);
    *head = NULL;
}

int node_deep_copy(node_t *dst, node_t *src)
{
    char *tmp = strdup(src->key);
    if (!tmp)
        return ASSOC_ARRAY_MEM;
    
    dst->key = tmp;
    dst->value = src->value;

    return ASSOC_ARRAY_OK;
}
