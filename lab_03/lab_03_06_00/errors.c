#include <stdio.h>
#include "errors.h"

/**
 * @brief Функция вывода сообщений об оибки в консоль
 * @param[in] rc Код ошибки 
*/ 
void print_err(const int rc)
{
    if (rc == ERR_IO)
        printf("Неверный ввод\n");
    else if (rc == ERR_RANGE)
        printf("Неверный диапазон\n");
    else 
        printf("Неизвестная ошибка (%d)\n", rc);
}