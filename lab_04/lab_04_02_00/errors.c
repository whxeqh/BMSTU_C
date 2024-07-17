#include <stdio.h>
#include "errors.h"

/**
 * @brief Функция печати сообщений об ошибке 
 * @param[in] rc код ошибки
*/
void print_error(const int rc)
{
    if (rc == ERR_IO)
        printf("Некорректный ввод");
    if (rc == ERR_BUFF_TO_BIG)
        printf("Превышен размер строки");
    else if (rc == ERR_NO_WORDS)
        printf("В строке нет слов");
    else
        printf("Неизвестаня ошибка (%d)", rc);
}
