#ifndef __TREE_H__
#define __TREE_H__

#include "node.h"
#include "associative_array.h"

/**
 * @brief Поиск узла в дереве по ключу
 * @param[in] head Указатель на корень дерева
 * @param[in] key Ключ, по которому ищется узел
 * @return Указатель на найденный узел, или NULL, если узел не найден
 */
node_t *tree_search(node_t *head, const char *key);

/**
 * @brief Вставка нового узла в дерево
 * @param[in,out] head Указатель на корень дерева
 * @param[in] node Указатель на вставляемый узел
 */
void tree_insert(node_t **head, node_t *node);

/**
 * @brief Применяет функцию к каждому узлу дерева в порядке инфикса
 * @param[in] head Указатель на корень дерева
 * @param[in] action Функция, которая будет применена к каждому узлу
 * @param[in] param Дополнительный параметр для функции action
 */
void tree_apply_infix(node_t *head, void (*action)(const char *key, int *num, void *param), void *param);

/**
 * @brief Поиск узла с минимальным значением ключа в дереве
 * @param[in] head Указатель на корень дерева
 * @return Указатель на узел с минимальным значением ключа
 */
node_t *tree_search_min(node_t *head);

/**
 * @brief Поиск узла с максимальным значением ключа в дереве
 * @param[in] head Указатель на корень дерева
 * @return Указатель на узел с максимальным значением ключа
 */
node_t *tree_search_max(node_t *head);

/**
 * @brief Удаление узла из дерева
 * @param[in,out] head Указатель на корень дерева
 * @param[in] node Узел, который нужно удалить
 * @return Код ошибки, если удаление не удалось
 */
assoc_array_error_t node_remove(node_t **head, node_t *node);

/**
 * @brief Уничтожение дерева и освобождение памяти
 * @param[in,out] head Указатель на корень дерева
 */
void tree_destroy(node_t **head);

#endif // __TREE_H__
