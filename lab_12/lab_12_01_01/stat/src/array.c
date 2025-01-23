#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "array.h"
#include "consts.h"


/**
 * @brief Нахождение адреса первого минимального элемента в массиве  
 * @param pbeg [in] Указатель на первый элемент массива
 * @param pend [in] Указатель на элемент массива, расположенный за последним
 * @return Указатель на адрес первого минимального элемента массива
*/
static const int *array_min_element(const int *pbeg, const int *pend);

/**
 * @brief Нахождение адресса первого максимального элемента в массиве  
 * @param pbeg[in] Указатель на первый элемент массива
 * @param pend[in] Указатель на элемент массива, расположенный за последним
 * @return Указатель на адресс первого максимального элемент массива
*/
static const int *array_max_element(const int *pbeg, const int *pend);

/**
 * @brief Сдвигает элементы массива вправо на одну позицию
 * @param pbeg[in] Указатель на первый элемент массива
 * @param pend[in] Указатель на элемент массива, расположенный за последним
 * @param el_size[in] Размер типа данных
 * 
 * @pre Массив должен содержать хотя бы один элемент, т.е. pbeg < pend.
 * @pre Размер элемента должен быть натуральным числом, т.е. el_size > 0
*/
static void shift_elements_right(void *pbeg, void *pend, const size_t el_size);

/**
 * @brief Обмен двух указателей.
 * @param left Первый указатель.
 * @param right Второй указатель.
*/
static void swap_int_pointers(const int **left, const int **right);

static const int *array_min_element(const int *pbeg, const int *pend)
{
    const int *min = pbeg;

    for (const int *pcur = pbeg + 1; pcur < pend; pcur++)
        if (*pcur < *min)
            min = pcur;
            
    return min;
}

static const int *array_max_element(const int *pbeg, const int *pend)
{
    const int *max = pbeg;

    for (const int *pcur = pbeg + 1; pcur < pend; pcur++)
        if (*pcur > *max)
            max = pcur;

    return max;
}

static void shift_elements_right(void *pbeg, void *pend, const size_t el_size)
{
    assert(pbeg < pend);
    assert(pbeg != NULL);
    assert(pend != NULL);
    assert(el_size > 0);

    char elem[el_size];

    memcpy(elem, pend, el_size); //Запоминаю новый элемент

    memmove((char*) pbeg + el_size, pbeg, (char *) pend - (char *) pbeg); //Сдвигаю массив

    memcpy(pbeg, elem, el_size); //Вставляю новый элемент в начало
}

int cmp_uni_int(const void *left, const void *right)
{
    assert(left != NULL);
    assert(right != NULL);
    
    const int *pl = left;
    const int *pr = right;
    return *pl - *pr;
}

/**
 * Идея для поиск центрального элемента в массиве: mid = pleft + (((pright - pleft) / el_size / 2) * el_size)
 * 
 * pleft - Адрес крайнего левого элемента
 * pright - Адрес крайнего правого элемента
 * el_size - Размер элемента в байтах
 * 
 * (pright - pleft) - Количество байт между элементами pright и pleft
 * 
 * (pright - pleft) / el_size - Количество элементов в полуинтервале [pleft; pright)
 * 
 * (pright - pleft) / el_size / 2 - Центральный элемент полуинтервала [pleft; prigth)
 * 
 *   Делить на el_size нужно, чтобы верно определить байт, с которого начинается средний элнемент интервала. Например:
 * Если в массиве 5 элемента типа int (в моем случае 4 байта), то объем памяти под них: 5 * 4 = 20 байт
 * Тогда, если просто искать средний байт между ними, то 20 / 2 - 10 байт. Но этот байт не указывает на начало элемента
 * Этот байт находится в самом элементе (не формально говоря). Такое поведение свойственно для всех массивов нечетной длины
 * 
 * Именно поэтому нужно еще делать на el_size: 
 * 1) 20 / 4 = 5;
 * 2) 5 / 2 = 2 - средний элемент в полуинтервале [pleft; pright). (Именно элемент, не байт!) Именно его буду сравнивать в бин поиске
 * 
 * Затем нужно умножить на el_size, так как мы работаем с отдельными байтами
 * 
 * 3) 2 * 4 = 8. Байт, с которого начинается второй элемент, найденный во втором действии
 * 
 */
void *bynary_search(const void *pbeg, const void *pend, const void *key, size_t el_size, cmp_t uni_cmp)
{
    const char *pleft = pbeg;
    const char *pright = pend;
    const char *mid;

    while (pleft <= pright)
    {
        mid = pleft + (((pright - pleft) / el_size / 2) * el_size);

        int result = uni_cmp(key, mid);
        
        if (result < 0)
            pright = mid - el_size;
        else if (result > 0)
            pleft = mid + el_size;
        else 
            return (void *) mid;
    }

    return (void*) pleft;
}

void mysort(void *pbeg, const size_t length, size_t el_size, cmp_t uni_cmp)
{
    char *pend = (char *)pbeg + length * el_size; 
    for (char *pcur = (char *) pbeg; pcur < pend; pcur += el_size)
    {
        void *pos = bynary_search(pbeg, pcur, pcur, el_size, uni_cmp);

        if (pcur != pos)
            shift_elements_right(pos, pcur, el_size);
    }
}

static void swap_int_pointers(const int **left, const int **right)
{
    const int *tmp = *left;
    *left = *right;
    *right = tmp;
}

int filter_arr_size(const int *pb_src, const int *pe_src)
{
    const int *pfirst = array_min_element(pb_src, pe_src);     // Указатель на минимальный элемент в массиве
    const int *psecond = array_max_element(pb_src, pe_src);     // Указатель на максимальный элемент в массиве

    if (pfirst > psecond)
        swap_int_pointers(&pfirst, &psecond);
    
    return psecond - pfirst - 1;
}

int key(const int *pb_src, const int *pe_src, int *pb_dst, int **pe_dst)
{   
    const int *pfirst = array_min_element(pb_src, pe_src);     // Указатель на минимальный элемент в массиве
    const int *psecond = array_max_element(pb_src, pe_src);     // Указатель на максимальный элемент в массиве

    if (pfirst > psecond)
        swap_int_pointers(&pfirst, &psecond);
    
    assert(psecond - pfirst >= 1);

    size_t cnt_elems = psecond - pfirst - 1;
    
    *pe_dst = pb_dst + cnt_elems;

    memcpy(pb_dst, pfirst + 1, cnt_elems * sizeof(int));
    return OK;
}

void destroy_array(int **arr)
{
    free(*arr);
    *arr = NULL;
}
