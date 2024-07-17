#include <stdio.h>
#include "errors.h"

/**
 * @brief Функция вычисления кол-ва локальный максимумов
 * 
 * @param[in]   file_in  Файловая переменная, откуда будут считываться данные
 * @param[out]  count    Кол-во локальных максимов
 * 
 * @return Код ошибки
*/
int process(FILE *file_in, int *count)
{
    int left, mid, right;
    if (fscanf(file_in, "%d%d%d", &left, &mid, &right) != 3)
        return ERR_NOT_ENOUGH_DATA;

    do 
    {   
        if (mid > left && mid > right)
            (*count)++;
        left = mid;
        mid = right;
    } while (fscanf(file_in, "%d", &right) == 1);
    
    return OK;
}
