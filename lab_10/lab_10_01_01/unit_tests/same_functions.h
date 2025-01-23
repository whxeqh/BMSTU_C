#ifndef __SAME_FUNCTIONS_H__
#define __SAME_FUNCTIONS_H__

#include <stdbool.h>
#include <stddef.h>

#include "node.h"
#include "product.h"

bool products_equal(product_t *first, product_t *second);

size_t list_length(node_t *head);

bool my_check_list_equal(node_t *head_first, node_t *head_second);

node_t *find_elem(node_t *head, size_t count);

#endif //__SAME_FUNCTIONS_H__