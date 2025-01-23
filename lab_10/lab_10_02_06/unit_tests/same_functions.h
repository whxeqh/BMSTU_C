#ifndef __SAME_FUNCTIONS_H__
#define __SAME_FUNCTIONS_H__

#include <stdbool.h>
#include <stddef.h>

#include "node.h"

#define ROWS_MAX 10
#define COLUMNS_MAX 10

int print_mtr(FILE *f, int (*mtr)[ROWS_MAX], size_t rows, size_t columns);

bool my_check_list_and_arr_equal(node_t *head_first, node_t *head_second, size_t length_arr);

bool my_check_lists_equal(node_t *head_first, node_t *head_second);

size_t list_length(node_t *head);

#endif //__SAME_FUNCTIONS_H__