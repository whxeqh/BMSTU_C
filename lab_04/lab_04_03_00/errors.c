#include <stdio.h>
#include "errors.h"

/**
 * @brief Функция печати сообщений об ошибке 
 * @param[in] rc код ошибки
*/
void print_error(const int rc)
{
    if (rc == ERR_IO)
        printf("Incorrect input");
    else if (rc == ERR_BUFF_TO_BIG)
        printf("String size to big");
    else if (rc == ERR_NOT_ENOUGH_WORDS)
        printf("Not enough words");
    else
        printf("Неизвестаня ошибка (%d)", rc);
}
