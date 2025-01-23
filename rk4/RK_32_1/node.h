#ifndef __NODE_H__
#define __NODE_H__

#include "errors.h"

#include <stdio.h>

typedef struct node node_t;

#define MAX_BUF_LEN (128 + 1)

struct node
{
    char *data;
    node_t *next;
};

node_t *node_create();

void node_free_content(node_t *node);

errors_e node_add_content(node_t *dst, node_t *src);

void node_destroy(node_t **node);

errors_e node_read(FILE *file, node_t **node);

errors_e node_print(node_t *node);

#endif //__NODE_H__
