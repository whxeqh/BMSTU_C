#include <stdlib.h>
#include <stdio.h>

#include "node.h"
#include "errors.h"
#include "product.h"

void node_destroy(node_t **node)
{
    free(*node);
    *node = NULL;
}

node_t *node_create(void *data)
{
    node_t *tmp = malloc(sizeof(node_t));
    if (!tmp)
        return NULL;
    
    tmp->data = data;
    tmp->next = NULL;
    return tmp;
}

int print_node(FILE *file, node_t *node)
{
    product_t *elem = node->data;
    return product_print(file, elem);
}
