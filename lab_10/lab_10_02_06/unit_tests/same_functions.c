#include "same_functions.h"
#include "list.h"
#include "errors.h"
#include "matrix.h"

#include <assert.h>
#include <stdio.h>

static bool nodes_equal(node_t *first, node_t *second)
{
    if (first->column != second->column)
        return false;

    if (first->row != second->row)
        return false;
    
    if (first->data != second->data)
        return false;
    
    return true;
}

int print_mtr(FILE *f, int (*mtr)[ROWS_MAX], size_t rows, size_t columns)
{
    assert(f);

    int rc = OK;
    if (fprintf(f, "%zu %zu\n", rows, columns) < 0)
        rc = ERR_IO;

    for (size_t i = 0; rc == OK && i < rows; i++)
    {
        for (size_t j = 0; rc == OK && j < columns; j++)
            if (fprintf(f, "%d ", mtr[i][j]) < 0)
                rc = ERR_IO;
        fputs("\n", f);
    }
    return rc;
}

bool my_check_list_and_arr_equal(node_t *head_first, node_t *head_second, size_t length_arr)
{
    size_t length_first = list_length(head_first);

    //printf("%zu %zu\n", length_first, length_second);
    
    if (length_first != length_arr)
        return false;

    for (size_t i = 0; i < length_first; i++)
    {
        if (!nodes_equal(head_first, &head_second[i]))
            return false;
        head_first = head_first->next;
    }

    //puts("dsad");
    return true;
}

bool my_check_lists_equal(node_t *head_first, node_t *head_second)
{
    size_t length_first = list_length(head_first);
    size_t length_second = list_length(head_second);

    if (length_first != length_second)
        return false;

    for (size_t i = 0; i < length_first; i++)
    {
        if (!nodes_equal(head_first, head_second))
            return false;
        head_first = head_first->next;
        head_second = head_second->next;
    }

    //puts("dsad");
    return true;
}

size_t list_length(node_t *head)
{
    if (!head)
        return 0;
    
    return list_length(head->next) + 1;
}