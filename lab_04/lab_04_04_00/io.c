#include <stdio.h>
#include <string.h>
#include "io.h"

/**
 * @brief Функция ввода строки
 * @param[out] buf указатель на первый элемент буфера
 * @param[in] buf_size размер буфера
 * @return код ошибки
 */
int input_string(char *buf, const size_t buf_size)
{
    char *p;
    if (!fgets(buf, buf_size, stdin))
        return ERR_IO;

    p = strchr(buf, '\n');
    if (p)
        *p = '\0';
    else
        return ERR_BUFF_TO_BIG;
            
    return OK;
}

/**
 * @brief Функция печати значения булевой переменной 
 * @param[in] ans Исходная булева переменная
*/
void print_ans(const bool ans)
{
    printf((ans ? "YES\n" : "NO\n"));
}
