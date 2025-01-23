#ifndef __NODE_H__
#define __NODE_H__

/**
 * @brief Структура узла для представления элемента дерева
 */
typedef struct node node_t;

struct node
{
    char *key;      ///< Ключ узла
    int value;      ///< Значение узла

    node_t *lhs;    ///< Указатель на левое поддерево
    node_t *rhs;    ///< Указатель на правое поддерево
};

/**
 * @brief Создаёт новый узел дерева с заданными значениями
 * @param[in] key Ключ узла
 * @param[in] value Значение узла
 * @return Указатель на созданный узел или NULL в случае ошибки
 */
node_t *node_create(const char *key, int value);

/**
 * @brief Освобождает содержимое узла (ключ и другие ресурсы)
 * @param[in,out] head Указатель на узел
 */
void node_free_content(node_t *head);

/**
 * @brief Освобождат память из-под узла
 * @param[in,out] head Указатель на указатель на узел
 */
void node_destroy(node_t **head);

/**
 * @brief Выполняет глубокое копирование узла дерева
 * @param[out] dst Указатель на узел назначения
 * @param[in] src Указатель на узел источник
 * @return Код ошибки
 */
int node_deep_copy(node_t *dst, node_t *src);

#endif // __NODE_H__
