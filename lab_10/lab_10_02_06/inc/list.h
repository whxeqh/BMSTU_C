#ifndef __LIST_H__
#define __LIST_H__

#include "node.h"

/**
 * @brief Добавляет элемент в конец списка
 * @param[in] head Указатель на голову списка
 * @param[in] node Указатель на узел, который нужно добавить
 * @return Указатель на голову списка
 */
node_t *push_back(node_t *head, node_t *node);

/**
 * @brief Выводит элементы списка в файл или поток вывода
 * @param[in] file Указатель на открытый файл для записи
 * @param[in] head Указатель на голову списка
 * @return Код ошибки
 */
int list_print(FILE *file, node_t *head);

/**
 * @brief Считывает данные из файла и формирует список
 * @param[in] file Указатель на открытый файл для чтения
 * @param[out] head Указатель на указатель на голову списка
 * @return Код ошибки
 */
int list_read(FILE *file, node_t **head);

/**
 * @brief Освобождает память, выделенную под список
 * @param[in,out] head Указатель на указатель на голову списка
 */
void free_list(node_t **head);

#endif // __LIST_H__
