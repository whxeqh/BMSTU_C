#include "list.h"

#include <stdlib.h>
#include <assert.h>

node_t *list_add_tail(node_t *head, node_t *node)
{
    if (!head)
        return node;
    
    node_t *tmp_head = head;
    while (tmp_head->next)
    {
        tmp_head = tmp_head->next;
    }
    
    tmp_head->next = node;

    return head; 
}

errors_e list_read_ex(char *filename, node_t **head)
{
    assert(filename);

    FILE *file = fopen(filename, "r");
    if (!file)
        return ERR_FILE;
    
    errors_e rc = list_read(file, head);

    fclose(file);

    return rc;
}

errors_e list_read(FILE *file, node_t **head)
{
    assert(file);
    assert(head);
    
    errors_e rc = OK;
    node_t *tmp_head = NULL;
    
    while(rc == OK)
    {
        node_t *node = NULL;
        rc = node_read(file, &node);
        if (rc == OK)
        {
            tmp_head = list_add_tail(tmp_head, node);
        }
    }
    if (feof(file))
        rc = OK;
    
    if (rc == OK)
        *head = tmp_head;
    
    return rc;
}

errors_e list_print(node_t *head)
{
    errors_e rc = OK;
    if (!head)
        puts("Empty list");

    while (rc == OK && head)
    {
        rc = node_print(head);
        head = head->next;
    }

    return rc;
}

void list_destroy(node_t **head)
{
    if (!head || !*head)
        return;
        
    node_t *cur_head = *head;

    while (cur_head)
    {
        node_t *tmp = cur_head->next;
        node_destroy(&cur_head);
        cur_head = tmp;
    }
}

errors_e task(node_t *head)
{
    assert(head);
    
    errors_e rc = OK;
    
    node_t *tmp_head = head;
    node_t *next = tmp_head->next;
    
    while (rc == OK && next)
    {
        rc = node_add_content(tmp_head, next);
        if (rc == OK)
        {
            tmp_head->next = next->next;
            node_destroy(&next);
            tmp_head = tmp_head->next;
            if (tmp_head)
                next = tmp_head->next;
            else 
                next = NULL;
        }
    }
    
    return rc;
}
