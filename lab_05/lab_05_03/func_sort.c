#include "errors.h"
#include "func_sort.h"
#include "file_size.h"

/**
 * Метод сортировки: метод выбора
 * Целочисленный тип: int
 * Направление упорядочивания: Неубывание
 */


/** 
 * @brief Функция считывает целое число из бинарного файла по позиции 
 *  
 * @param[in]   file     Файловая переменна
 * @param[in]   pos      Позиция числа
 * @param[out]  number   считанное число
 * 
 * @return Код ошибки
*/
static int get_number_by_pos(FILE *file, const long pos, int *number)
{
    if (fseek(file, pos * sizeof(*number), SEEK_SET) != 0)
        return ERR_FILE;
    if (fread(number, sizeof(*number), 1, file) != 1)
        return ERR_READ;
    
    return OK;
}

/** 
 * @brief Функция записвает целое число в бинарный файла по позиции 
 *  
 * @param[in]   file     Файловая переменна
 * @param[in]   pos      Позиция числа
 * @param[out]  number   Число для записи
 * 
 * @return Код ошибки
*/
static int put_number_by_pos(FILE *file, const long pos, const int number)
{
    if (fseek(file, pos * sizeof(number), SEEK_SET) != 0)
        return ERR_FILE;
    if (fwrite(&number, sizeof(number), 1, file) != 1)
        return ERR_WRITE;
    
    return OK;
}

/**
 * @brief Функция сортирует числа в бинарном файле методом выбора 
 * 
 * @param[in] file_in  Файловая переменная
 * 
 * @return Код ошибки
*/
int sort_file(FILE* file_in)
{
    int rc = OK;
    size_t length = 0;
    
    rc = get_file_size(file_in, &length);
    length /= sizeof(int);

    for (size_t i = 0; rc == OK && i < length; i++)
    {
        int cur_i, cur_j, min;
        size_t id = i;
        rc = get_number_by_pos(file_in, i, &cur_i);
        if (rc == OK)
            min = cur_i;

        for (size_t j = i + 1; rc == OK && j < length; j++)
        {
            rc = get_number_by_pos(file_in, j, &cur_j);
            
            if (rc == OK && cur_j < min)
            {
                min = cur_j;
                id = j;
            }
        }
        if (id != i)
        {
            int tmp = cur_i;
            rc = put_number_by_pos(file_in, i, min);
            if (rc == OK)
                rc = put_number_by_pos(file_in, id, tmp);
        }
    }
    
    return rc;
}
