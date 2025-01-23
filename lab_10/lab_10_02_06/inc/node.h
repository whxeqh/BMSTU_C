#ifndef __NODE_H__
#define __NODE_H__

#include <stdio.h>

/**
 * @brief Структура узла для представления элемента матрицы
 */
typedef struct node node_t;

struct node
{
    size_t row;    // Номер строки элемента
    size_t column; // Номер столбца элемента
    int data;      // Значение элемента

    node_t *next;  // Указатель на следующий узел
};

/**
 * @brief Уничтожает узел и освобождает память из-под него
 * @param[in,out] node Указатель на указатель на узел
 */
void node_destroy(node_t **node);

/**
 * @brief Создаёт узел с заданными значениями
 * @param[in] row Номер строки элемента
 * @param[in] column Номер столбца элемента
 * @param[in] data Значение элемента
 * @return Указатель на созданный узел или NULL в случае ошибки
 */
node_t *node_create(size_t row, size_t column, int data);

/**
 * @brief Выводит содержимое узла в файл или поток вывода
 * @param[in] file Указатель на открытый файл для записи
 * @param[in] node Указатель на узел
 * @return Код ошибки
 */
int print_node(FILE *file, node_t *node);

#endif // __NODE_H__
