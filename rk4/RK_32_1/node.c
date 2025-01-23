#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "node.h"

static errors_e read_str(FILE *file, char *buf)
{
    assert(file);
    assert(buf);

    if (!fgets(buf, MAX_BUF_LEN, file))
        return ERR_IO;

    char *p = strchr(buf, '\n');
    if (p)
        *p = '\0';
    else 
        return ERR_OVERFLOW;

    if (!(*buf))
        return ERR_EMPTY;
    
    return OK;
}

node_t *node_create(char *data)
{
    node_t *tmp = malloc(sizeof(node_t));
    if (!tmp)
        return NULL;
    
    tmp->data = data;
    tmp->next = NULL;

    return tmp;
}

void node_free_content(node_t *node)
{
    if (!node)
        return;

    free(node->data);
    node->data = NULL;
}

errors_e node_add_content(node_t *dst, node_t *src)
{
    assert(dst);
    assert(src);
    
    void *tmp = NULL;
    // почему +2. 1 байт под \0 и 1 байт под пробел
    tmp = realloc(dst->data, (strlen(dst->data) + strlen(src->data) + 2) * sizeof(char));
    if (!tmp)
        return ERR_MEM;
    
    dst->data = tmp;
    
    strcat(dst->data, " ");
    strcat(dst->data, src->data);

    return OK;
}

void node_destroy(node_t **node)
{
    if (!node || !*node)
        return;

    node_free_content(*node);
    free(*node);
    *node = NULL;
}

errors_e node_read(FILE *file, node_t **node)
{
    assert(file);
    assert(node);

    errors_e rc = OK;
    char read_data[MAX_BUF_LEN], *node_data = NULL;
    node_t *tmp_node = NULL;

    rc = read_str(file, read_data);

    if (rc != OK)
        return rc;

    node_data = malloc((strlen(read_data) + 1) * sizeof(char));
    if (!node_data)
        return ERR_MEM;
    
    memcpy(node_data, read_data, (strlen(read_data) + 1) * sizeof(char));

    tmp_node = node_create(node_data);
    if (!tmp_node)
    {
        rc = ERR_MEM;
        free(tmp_node);
    }
    else 
        *node = tmp_node;

    return rc;
}

errors_e node_print(node_t *node)
{
    assert(node);

    if (fprintf(stdout, "%s\n", node->data) < 0)
        return ERR_IO;
    
    return OK;
}
