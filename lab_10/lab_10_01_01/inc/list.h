#ifndef __LIST_H__
#define __LIST_H__

#include <stdbool.h>

#include "node.h"
#include "product.h"

/**
 * @brief Удаляет последний элемент из списка и возвращает его данные
 * @param[in,out] head Указатель на указатель на голову списка
 * @return Указатель на данные удаленного элемента или NULL, если список пуст
 */
void *pop_back(node_t **head);

/**
 * @brief Вставляет элемент в отсортированный список в нужную позицию
 * @param[in,out] head Указатель на указатель на голову списка
 * @param[in] element Указатель на элемент, который нужно вставить
 * @param[in] comparator Указатель на функцию сравнения элементов
 */
void sorted_insert(node_t **head, node_t *element, int (*comparator)(const void *left, const void *right));

/**
 * @brief Сортирует список с использованием указанной функции сравнения
 * @param[in] head Указатель на голову списка
 * @param[in] comparator Указатель на функцию сравнения элементов
 * @return Указатель на голову отсортированного списка
 */
node_t *sort(node_t *head, int (*comparator)(const void *left, const void *right));

/**
 * @brief Вставляет элемент в список перед заданным узлом
 * @param[in,out] head Указатель на указатель на голову списка
 * @param[in] elem Указатель на элемент, который нужно вставить
 * @param[in] before Указатель на узел, перед которым нужно вставить элемент
 */
void insert(node_t **head, node_t *elem, node_t *before);

/**
 * @brief Разворачивает список
 * @param[in] head Указатель на голову списка
 * @return Указатель на новую голову списка
 */
node_t *reverse(node_t *head);

/**
 * @brief Открывает файл и вызывает функцию для вывода списка
 * @param[in] filename Имя файла для записи
 * @param[in] head Указатель на голову списка
 * @return Код ошибки
 */
int print_list_ex(char *filename, node_t *head);

/**
 * @brief Выводит список в открытый файл или поток вывода
 * @param[in] file Указатель на открытый файл для записи
 * @param[in] head Указатель на голову списка
 * @return Код ошибки
 */
int print_list(FILE *file, node_t *head);

/**
 * @brief Освобождает память, выделенную под список
 * @param[in,out] head Указатель на указатель на голову списка
 */
void free_list(node_t **head);

/**
 * @brief Создает список на основе массива структур
 * @param[out] head Указатель на указатель на голову списка
 * @param[in] arr Массив структур
 * @param[in] length Длина массива
 * @return Код ошибки
 */
int list_create(node_t **head, product_t *arr, size_t length);

#endif // __LIST_H__
