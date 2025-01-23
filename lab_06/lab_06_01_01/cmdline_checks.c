#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cmdline_checks.h"
#include "errors.h"

/**
 * @brief Проверяет корректность года, переданного в командной строке
 * 
 * @param[in] str Строка, содержащая число
 * 
 * @return Код ошибки: OK, если год корректен, ERR_DATA, если строка не является числом или оно отрицательное
 */
static bool is_positive_num(const char *str)
{
    char *endptr;
    long value = strtol(str, &endptr, BASE);
    if (*endptr != '\0' || value < 0)
        return false;
        
    return true;
}

int check_args(const int argc, char **argv, field_e *field)
{   
    if (argc != 3 && argc != 4)
        return ERR_ARGS;

    field_e tmp;

    if (strcmp(argv[2], TITLE) == 0)
        tmp = FIELD_TITLE;
    else if (strcmp(argv[2], NAME) == 0)
        tmp = FIELD_NAME;
    else if (strcmp(argv[2], YEAR) == 0)
        tmp = FIELD_YEAR;
    else 
        return ERR_ARGS;

    if (argc == 4)
    {
        if (strlen(argv[3]) == 0)
            return ERR_ARGS;

        if (tmp == FIELD_YEAR && !is_positive_num(argv[3]))
            return ERR_ARGS;
    }

    *field = tmp;

    return OK;
}

void print_arg_info(void)
{
    printf("./app.exe FILE FIELD [KEY]\n");
}
