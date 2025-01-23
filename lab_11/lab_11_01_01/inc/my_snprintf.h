#ifndef __MY_SNPRINTF_H__
#define __MY_SNPRINTF_H__

#include <stddef.h>

/**
 * @brief Собственная реализация функции `snprintf`.
 * @param buf Буфер для записи отформатированной строки.
 * @param maxlen Максимальный размер буфера. 
 * @param format Строка форматирования.
 * @param ... Аргумеенты форматирования
 * @return Разме отформатированной строки
*/
int my_snprintf(char *buf, size_t maxlen, const char *format, ...);

#endif //__MY_SNPRINTF_H__
