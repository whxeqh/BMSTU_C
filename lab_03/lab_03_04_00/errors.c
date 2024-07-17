#include <stdio.h>
#include "errors.h"

/**
 * @brief Функция вывода сообщений об оибки в консоль
 * @param[in] rc Код ошибки 
*/ 
void print_err(const int rc)
{
    switch (rc)
    {
        case ERR_IO:
            printf("Неверный ввод\n");
            break;
        case ERR_RANGE:
            printf("Неверный диапазон\n");
            break;
        case ERR_INCORRECT_MATRIX:
            printf("Матрица должна быть квадратной\n");
            break;
        case ERR_NO_ODD_NUMBER:
            printf("Нет нечетных элементов\n");
            break;
        default:
            printf("Неизвестная ошибка (%d)\n", rc);
    }
}