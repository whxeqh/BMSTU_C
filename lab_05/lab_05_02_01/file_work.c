#include "file_work.h"
#include "errors.h"

/**
 * @brief Функция считает среднее значение между минимумом и максимумом в файле 
 * 
 * @param[in]   file_in  Входной файл
 * @param[out]  mid      Среднее значение
 * 
 * @return Код ошибки
*/
int calc_avg_value(FILE *file_in, double *avg)
{
    double left, current, min, max;
    if (fscanf(file_in, "%lf%lf", &left, &current) != 2)
        return ERR_NOT_ENOUGH_DATA;

    min = MIN(left, current);
    max = MAX(left, current);
    
    while (fscanf(file_in, "%lf", &current) == 1)
    {   
        min = MIN(min, current);
        max = MAX(max, current);
    }
    if (!feof(file_in))
        return ERR_IO;

    *avg = (min + max) / 2;
    rewind(file_in);
    
    return OK;
}


/**
 * @brief Функция считает кол-во элементов, больших среднего значения между минимумом и максимумом в файле 
 * 
 * @param[in]   file_in  Входной файл
 * @param[out]  count    Кол-во элементов, больших среднего значение между минимумом и максимумом в файле 
 * @param[out]  mid      Среднее значение
 * 
 * @return Код ошибки
*/
int calc_count_numbers(FILE *file_in, size_t *count, const double avg)
{
    double current;
    size_t ans = 0;

    while (fscanf(file_in, "%lf", &current) == 1)
    {
        if (current > avg)
            ans++;
    }
    if (!feof(file_in))
        return ERR_IO;

    *count = ans;
    return OK;
}
