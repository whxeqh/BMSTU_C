#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "node.h"
#include "errors.h"

void node_destroy(node_t **node)
{
    free(*node);
    *node = NULL;
}

node_t *node_create(size_t row, size_t column, int data)
{
    node_t *tmp = malloc(sizeof(node_t));
    if (!tmp)
        return NULL;

    tmp->row = row;
    tmp->column = column;
    tmp->data = data;

    tmp->next = NULL;
    
    return tmp;
}

int print_node(FILE *file, node_t *node)
{
    assert(file);
    assert(node);

    if (fprintf(file, "%zu %zu %d ", node->row, node->column, node->data) < 0)
        return ERR_IO;
    
    return OK;
}
