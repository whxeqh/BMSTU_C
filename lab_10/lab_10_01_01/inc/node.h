#ifndef __NODE_H__
#define __NODE_H__

#include <stdio.h>

typedef struct node node_t;

/**
 * @brief Структура узла односвязного списка
 * @param data Указатель на данные, хранимые в узле
 * @param next Указатель на следующий узел списка
 */
struct node
{
    void *data;
    node_t *next;
};

/**
 * @brief Освобождает память, выделенную под узел списка
 * @param[out] node Указатель на указатель на узел списка
 */
void node_destroy(node_t **node);

/**
 * @brief Создает новый узел списка с заданными данными
 * @param[in] data Указатель на данные, которые будут храниться в узле
 * @return Указатель на созданный узел или NULL в случае ошибки выделения памяти
 */
node_t *node_create(void *data);

/**
 * @brief Выводит данные узла списка в файл или поток вывода
 * @param[in] file Указатель на открытый файл для записи
 * @param[in] node Указатель на узел списка
 * @return Код ошибки
 */
int print_node(FILE *file, node_t *node);

#endif // __NODE_H__
