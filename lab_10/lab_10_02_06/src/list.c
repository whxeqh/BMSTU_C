#include <stdlib.h>
#include <assert.h>

#include "list.h"
#include "errors.h"

node_t *push_back(node_t *head, node_t *node)
{
    if (!head)
        return node;
    
    node_t *last = head;
    while (last->next != NULL)
        last = last->next;
    
    last->next = node;

    return head;
}

int list_print(FILE *file, node_t *head)
{
    assert(file);

    int rc = OK;
    if (!head)
        return rc;
    
    rc = print_node(file, head);
    if (rc != OK)
        return rc;

    return list_print(file, head->next);
}

int list_read(FILE *file, node_t **head)
{
    free_list(head);
    
    int rc = OK, data;
    node_t *tmp_head = NULL, *node = NULL;
    size_t rows, columns;
    if (fscanf(file, "%zu%zu", &rows, &columns) != 2)
        rc = ERR_IO;
    
    for (size_t i = 0; rc == OK && i < rows; i++)
    {
        for (size_t j = 0; rc == OK && j < columns; j++)
        {
            if (fscanf(file, "%d", &data) != 1)
            {
                rc = ERR_IO;
            }
            else if (data != 0)
            {
                node = node_create(i, j, data);
                if (!node)
                    rc = ERR_MEMORY;
                else 
                    tmp_head = push_back(tmp_head, node);
            }
        }
    }

    if (rc != OK)
        free_list(&tmp_head);
    else 
        *head = tmp_head;
    
    return rc;
}

void free_list(node_t **head)
{
    if (!head || !(*head))
        return;
    
    node_t *next = (*head)->next;
    node_destroy(head);
    free_list(&next);
}
