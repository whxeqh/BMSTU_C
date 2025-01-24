#ifndef __ARR_OP_H__
#define __ARR_OP_H__

#include <stddef.h>

/**
 * @brief Удаляет повторяющиеся элементы в массиве, оставляя только уникальные (множество)
 * 
 * @param[out] arr    Указатель на массив, который нужно преобразовать в множество
 *                    В случае успешного завершения массив будет содержать
 *                    только уникальные элементы
 * @param[out] length Указатель на размер массива. После выполнения функции
 *                    будет содержать количество уникальных элементов
 * 
 * @return Код ошибки
 */
int make_set(int **arr, size_t *length);

/**
 * @brief Вычисление симметрической разности двух множеств
 * 
 * @param[out] new_set      Указатель на результирующий массив
 * @param[out] new_length   Указатель на размер результирующего массива
 * 
 * @param[in] set1          Указатель на первое множество элементов
 * @param[in] length1       Количество элементов в первом множестве `set1`
 * 
 * @param[in] set2          Указатель на второе множество элементов
 * @param[in] length2       Количество элементов во втором множестве `set2`
 */
void arr_op(int *new_set, size_t *new_length, const int *set1, const size_t length1, const int *set2, const size_t length2);

#endif //__ARR_H__
