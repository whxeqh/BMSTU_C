#include "arr_op.h"
#include "arr_alloc.h"
#include "errors.h"
#include <stdbool.h>

/**
 * @brief Проверка, есть ли число num в массиве arr 
 * @param arr Исходный массив
 * @param length Кол-во элементов в массие
 * @param num Число для проверки
 * @return true, если число num есть в массиве
 *         false в ином случае
*/
static bool was_num_in_arr(const int *arr, const size_t length, const int num)
{
    for (size_t i = 0; i < length; i++)
        if (num == arr[i])
            return true;

    return false;
}

/**
 * @brief Добавляет уникальный элементы из множества src_set в множество dst_set
 * 
 * @param dst_set Результирующее множество
 * @param dst_length Кол-во элементов в результирующем множестве
 * 
 * @param src_set Исходное множество, из которого будут взяты элементы
 * @param src_length Кол-во элементов в исходном множестве
 * 
 * @param check_set Множество, в котором будет проверяться отсутствие элементов из множества src_set
 * @param check_length Количество элементов в этом множестве
*/
static void add_unique_elements(int *dst_set, size_t *dst_length, const int *src_set, size_t src_length, const int *check_set, size_t check_length)
{
    for (size_t i = 0; i < src_length; i++)
    {
        if (!was_num_in_arr(check_set, check_length, src_set[i]))
        {
            dst_set[*dst_length] = src_set[i];
            (*dst_length)++;
        }
    }
}

int make_set(int **arr, size_t *length)
{
    int rc = OK;

    if (*length == 0)
        return rc;

    size_t tmp_length = 0;
    for (size_t i = 0; i < *length; i++)
    {
        if (!was_num_in_arr(*arr, i, (*arr)[i]))
        {
            (*arr)[tmp_length] = (*arr)[i];
            tmp_length++;
        }    
    }

    // В случае ошибки выделения памяти, адрес arr не изменится. Утечки не будет.
    if (*length != tmp_length)
    {
        rc = arr_realloc(arr, tmp_length);
        *length = tmp_length;
    }

    return rc;
}   

void arr_op(int *new_set, size_t *new_length, const int *set1, const size_t length1, const int *set2, const size_t length2)
{
    *new_length = 0;

    // Добавляю числа из set1, в new_set, которых нет в set2
    add_unique_elements(new_set, new_length, set1, length1, set2, length2);

    // Добавляю числа из set2, в new_set, которых нет в set1
    add_unique_elements(new_set, new_length, set2, length2, set1, length1);
}
