#include <assert.h>
#include <stdbool.h>

#include "matrix.h"
#include "list.h"
#include "errors.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

/**
 * @brief Находит максимальное значение строки в матрице
 * @param[in] mtr Указатель на начало списка узлов матрицы
 * @return Максимальное значение строки
 */
static size_t find_max_row(node_t *mtr)
{
    assert(mtr);

    size_t max = mtr->row; 
    mtr = mtr->next;
    while (mtr != NULL)
    {
        max = MAX(max, mtr->row); 
        mtr = mtr->next;
    }
    
    return max;
}

/**
 * @brief Находит максимальное значение столбца в матрице
 * @param[in] mtr Указатель на начало списка узлов матрицы
 * @return Максимальное значение столбца
 */
static size_t find_max_column(node_t *mtr)
{
    assert(mtr);

    size_t max = mtr->column; 
    mtr = mtr->next;
    while (mtr != NULL)
    {
        max = MAX(max, mtr->column); 
        mtr = mtr->next;
    }
    
    return max;
}

/**
 * @brief Находит узел с максимальным значением данных в матрице
 * @param[in] mtr Указатель на начало списка узлов матрицы
 * @return Указатель на узел с максимальным значением
 */
static node_t *find_max_elem(node_t *mtr)
{
    assert(mtr);

    node_t *max = mtr;  
    mtr = mtr->next;
    while (mtr != NULL)
    {
        if (mtr->data > max->data) 
            max = mtr;
        mtr = mtr->next;
    }

    return max;
}

/**
 * @brief Находит следующий узел с таким же столбцом
 * @param[in] mtr Указатель на текущий узел матрицы
 * @param[in] column Столбец, по которому нужно найти следующий узел
 * @return Указатель на следующий узел в том же столбце или NULL, если не найден
 */
static node_t *find_next_same_column_node(node_t *mtr, const size_t column)
{
    if (!mtr)
        return NULL;

    node_t *cur = mtr;
    while (cur && cur->column != column)
        cur = cur->next;

    // Если такой узел не найден, возвращаем NULL
    if (!cur || cur->column != column)
        cur = NULL;
    
    return cur;
}

/**
 * @brief Находит следующий узел с такой же строкой
 * @param[in] mtr Указатель на текущий узел матрицы
 * @param[in] row Строка, по которой нужно найти следующий узел
 * @return Указатель на следующий узел в той же строке или NULL, если не найден
 */
static node_t *find_next_same_row_node(node_t *mtr, const size_t row)
{
    if (!mtr)
        return NULL;

    node_t *cur = mtr;
    while (cur && cur->row < row)
        cur = cur->next;
    
    // Если такой узел не найден, возвращаем NULL
    if (cur->row != row)
        cur = NULL;

    return cur;
}

int matrix_sum(node_t **mtr_sum, node_t *mtr1, node_t *mtr2)
{
    int rc = OK;

    node_t *res = NULL;

    node_t *cur1 = mtr1;
    node_t *cur2 = mtr2;

    while (cur1 && cur2)
    {
        if ((cur1->row == cur2->row && cur1->column < cur2->column) || (cur1->row < cur2->row))
        {
            node_t *tmp_cur = node_create(cur1->row, cur1->column, cur1->data);
            if (!tmp_cur)
            {
                rc = ERR_MEMORY;
                goto func_end;
            }

            res = push_back(res, tmp_cur);
            cur1 = cur1->next;
        }
        else if ((cur2->row == cur1->row && cur2->column < cur1->column) || (cur2->row < cur1->row))
        {
            node_t *tmp_cur = node_create(cur2->row, cur2->column, cur2->data);
            if (!tmp_cur)
            {
                rc = ERR_MEMORY;
                goto func_end;
            }
            
            res = push_back(res, tmp_cur);
            cur2 = cur2->next;
        }
        else 
        {
            node_t *tmp_cur = node_create(cur1->row, cur1->column, cur1->data + cur2->data);
            if (!tmp_cur)
            {
                rc = ERR_MEMORY;
                goto func_end;
            }

            res = push_back(res, tmp_cur);
            
            cur1 = cur1->next;
            cur2 = cur2->next;
        }
    }

    while (cur1)
    {
        node_t *tmp_cur = node_create(cur1->row, cur1->column, cur1->data);
        if (!tmp_cur)
        {
            rc = ERR_MEMORY;
            goto func_end;
        }

        res = push_back(res, tmp_cur);
        cur1 = cur1->next;
    }

    while (cur2)
    {
        node_t *tmp_cur = node_create(cur2->row, cur2->column, cur2->data);
        if (!tmp_cur)
        {
            rc = ERR_MEMORY;
            goto func_end;
        }
        res = push_back(res, tmp_cur);
        cur2 = cur2->next;
    }

    func_end:
    if (rc == OK)
        *mtr_sum = res; 
    else 
        matrix_free(&res);
    return rc;
}

int matrix_mul(node_t **mtr_mul, node_t *mtr1, node_t *mtr2)
{
    int rc = OK;

    node_t *res = NULL;

    node_t *cur1 = NULL;
    node_t *cur2 = NULL;

    size_t max_row = find_max_row(mtr1);
    size_t max_column = find_max_column(mtr2);

    for (size_t i = 0; i <= max_row; i++)
    {
        node_t *remeber_cur1 = find_next_same_row_node(mtr1, i);
        for (size_t j = 0; remeber_cur1 && j <= max_column; j++)
        {
            cur1 = remeber_cur1;
            cur2 = find_next_same_column_node(mtr2, j);
            while (cur1 && cur2)
            {
                if (cur1->column < cur2->row)
                {
                    cur1 = find_next_same_row_node(cur1->next, i);
                }
                else if (cur2->row < cur1->column)
                {
                    cur2 = find_next_same_column_node(cur2->next, j);
                }
                else 
                {
                    node_t *insert_node = node_create(i, j, cur1->data * cur2->data);
                    if (!insert_node)
                    {
                        rc = ERR_MEMORY;
                        goto func_end;
                    }

                    res = push_back(res, insert_node);
                    cur1 = find_next_same_row_node(cur1->next, i);
                    cur2 = find_next_same_column_node(cur2->next, j);
                }
            }
        }
    }
    
    func_end:
    if (rc == OK)
        *mtr_mul = res; 
    else 
        matrix_free(&res);
    return rc;
}

void matrix_lin(node_t **mtr)
{
    node_t *max = find_max_elem(*mtr);

    node_t *cur = NULL;
    node_t *parent_first = NULL;
    node_t *first = NULL;
    node_t *end = NULL;

    first = find_next_same_row_node(*mtr, max->row);
    end = first;
    cur = first;
    
    while ((cur = find_next_same_row_node(cur->next, max->row)) != NULL)
    {
        if (cur->row == first->row)
            end = cur;
    }

    cur = *mtr;
    while (cur && cur->next != first)
        cur = cur->next;
    
    parent_first = cur;

    if (parent_first)
        parent_first->next = end->next;
    else 
        *mtr = end->next;

    for (cur = first; cur != end;)
    {
        node_t *tmp = cur->next;
        node_destroy(&cur);
        cur = tmp;
    }
    if (end)
        node_destroy(&end);
}

int matrix_print(FILE *file, node_t *mtr)
{
    return list_print(file, mtr);
}

int matrix_read(FILE *file, node_t **mtr)
{
    return list_read(file, mtr);
}

void matrix_free(node_t **mtr)
{
    free_list(mtr);
}