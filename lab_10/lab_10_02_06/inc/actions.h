#ifndef __ACTIONS_H__
#define __ACTIONS_H__

/**
 * @brief Перечисление доступных действий для работы с матрицами
 */
typedef enum 
{
    ACT_OUT,
    ACT_ADD,
    ACT_MUL,
    ACT_LIN,
    ACT_UNKNOWN
} action_e;

/**
 * @brief Выполняет действие вывода матрицы
 * @return Код ошибки
 */
int act_out(void);

/**
 * @brief Выполняет бинарную операцию (сложение или умножение) на матрицах
 * @param[in] act Действие, которое нужно выполнить 
 * @return Код ошибки
 */
int act_binary_operation(action_e act);

/**
 * @brief Выполняет удаление строки с наибольшим элементом в матрице
 * @return Код ошибки
 */
int act_lin(void);

/**
 * @brief Считывает действие, которое нужно выполнить, из потока ввода
 * @param[out] act Указатель на переменную для хранения действия
 * @return Код ошибки
 */
int read_act(action_e *act);

#endif // __ACTIONS_H__
