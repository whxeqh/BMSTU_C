#include <stdio.h>
#include <string.h>
#include "io.h"

/**
 * @brief Функция ввода строки
 * @param[out] buf Указатель на буфер для хранения строки
 * @param[in] buf_size Размер буфера
 * @return Код ошибки 
 */
int input_string(char *buf, const size_t buf_size)
{
    char *p;
    printf("Введите строку: ");
    if (!fgets(buf, buf_size, stdin))
        return ERR_IO;

    p = strchr(buf, '\n');
    if (p)
        *p = '\0';
    else
        return ERR_BUFF_TO_BIG;
            
    return OK;
}
