#ifndef CMDLINE_CHECKS_H
#define CMDLINE_CHECKS_H

#include <stdio.h>

#define BASE 10

#define TITLE "title"
#define NAME "name"
#define YEAR "year"

typedef enum
{
    FIELD_TITLE,
    FIELD_NAME,
    FIELD_YEAR,
} field_e; 

/**
 * @brief Проверяет аргументы командной строки и определяет поле для сортировки/поиска
 * 
 * @param[in] argc Количество аргументов командной строки
 * @param[in] argv Массив аргументы командной строки
 * @param[out] field Указатель на переменную, в которую будет записано поле для сортировки/поиска

 * @return Код ошибки: OK, если аргументы корректны, ERR_ARGS, если есть ошибки в аргументах
 */
int check_args(const int argc, char **argv, field_e *field);


/**
 * @brief Вывод сообщение о необходимом вводе аргументов командной строки 
*/
void print_arg_info(void);

#endif
