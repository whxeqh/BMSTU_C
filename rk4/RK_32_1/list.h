#ifndef __LIST_H__
#define __LIST_H__

#include "errors.h"
#include "node.h"

node_t *list_add_tail(node_t *head, node_t *node);

errors_e list_read(FILE *file, node_t **head);

errors_e list_read_ex(char *filename, node_t **head);

errors_e list_print(node_t *head);

void list_destroy(node_t **head);

errors_e task(node_t *head);

#endif //__LIST_H__
