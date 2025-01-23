#ifndef __ERRORS_H__
#define __ERRORS_H__

typedef enum errors
{
    OK,
    ERR_IO,        //<- Ошибка чтения данных из файла
    ERR_EMPTY,     //<- Пустая строка
    ERR_OVERFLOW,  //<- Переполнение строки
    ERR_MEM,       //<- Ошибка выделения памяти
    ERR_FILE,      //<- Ошибка открытия файла
    ERR_ARGS       //<- Неверно переданные аргументы
} errors_e;

void print_error(errors_e rc);

#endif //__ERRORS_H__