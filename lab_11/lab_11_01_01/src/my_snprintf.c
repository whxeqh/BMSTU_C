#include "my_snprintf.h"

#include <stdarg.h>
#include <assert.h>
#include <limits.h>

#define MIN(A, B) ((A) < (B) ? (A) : (B))

#define HEX_DIGITS "0123456789abcdef"

#define HEX_BASE 16
#define MAX_BUF_LEN (16 + 1) // Максимум 16 символов для 64-битного числа

/** 
 * @brief Добавление символа в буфер, если в нём еще есть место. Увеличение размера текущей строки форматирования.
 * @param buf Буфер для заполнения.
 * @param cur_len Текущее количество элементов в буфере.
 * @param maxlen Максимально доступное количество элементов в буфере.
 * @param symb Символ для добавления
*/
static void buf_add_symb(char *buf, size_t *cur_len, size_t maxlen, char symb)
{
    if (*cur_len < maxlen)
        buf[*cur_len] = symb;
    (*cur_len)++;
}

/** 
 * @brief Добавление строки в буфер, Увеличение размера текущей строки форматирования.
 * @param buf Буфер для заполнения.
 * @param cur_len Текущее количество элементов в буфере.
 * @param maxlen Максимально доступное количество элементов в буфере.
 * @param str Строка для добавления
*/
static inline void buf_add_str(char *buf, size_t *cur_len, size_t maxlen, char *str)
{       
    for (; *str != '\0'; str++)
        buf_add_symb(buf, cur_len, maxlen, *str);
}

/**
 * @brief Обмен двух символов местами
 * @param[out] l указатель на первый символ
 * @param[out] r указатель на втор символ
*/
static void swap_char(char *l, char *r)
{
    char tmp = *l;
    *l = *r;
    *r = tmp;
}

/** 
 * @brief Добавление числа в 16-й СС в строку.
 * @param str Строка, в которую будет записано число в 16-й СС.
 * @param value Число для записи
*/
static void str_add_hex(char *str, unsigned long long value)
{
    size_t len = 0;
    do
    {
        str[len++] = HEX_DIGITS[value % HEX_BASE];
        value /= HEX_BASE;
    } while (value);
    str[len] = '\0';

    for (size_t i = 0; i < len / 2; i++)
    {
        swap_char(&str[i], &str[len - i - 1]);
    }
}

int my_snprintf(char *buf, size_t maxlen, const char *format, ...)
{
    assert(format);
    
    if (maxlen > INT_MAX)
        return -1;

    va_list args;
    va_start(args, format);

    char *strvalue;
    unsigned long long ullvalue;

    size_t written_len = 0;

    while (*format != '\0')
    {
        if (*format != '%')
        {
            buf_add_symb(buf, &written_len, maxlen, *format);
            format++;
        }
        else if (*format == '%' && *(format + 1) == '%')
        {
            buf_add_symb(buf, &written_len, maxlen, *format);
            format += 2;
        }
        else if (*format == '%' && *(format + 1) == 's')
        {
            strvalue = va_arg(args, char *);
            buf_add_str(buf, &written_len, maxlen, strvalue);
            format += 2;
        }
        else if (*format == '%' && *(format + 1) == 'l' && *(format + 2) == 'l' && *(format + 3) == 'x')
        {
            ullvalue = va_arg(args, unsigned long long);
            char strnum[MAX_BUF_LEN]; 
            str_add_hex(strnum, ullvalue);
            buf_add_str(buf, &written_len, maxlen, strnum);
            format += 4;
        }
    }
    
    va_end(args);

    if (buf)
        buf[MIN(written_len, maxlen - 1)] = '\0';

    return written_len;
}
