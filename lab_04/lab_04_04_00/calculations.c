#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "calculations.h"

#define MAX_DIGIT_IN_IP (3 + 1)

/**
 * @brief Функция конвертирует строку цифр в число и проверяет, что оно меньше 255 
 * 
 * @details Допещение: count_digit от 0 до 3. Так как эту функцию я вызываю только в функции is_ip_correct, где проверяю это условие
 *
 * @param[out] number строка цифр
 * @param[in] count_digit кол-во цифр
 * @return true, если число < 255
*/
bool is_ip_num_correct(char *number, const size_t count_digit)
{
    if (count_digit == 0)
        return false;
    
    number[count_digit] = '\0'; 
    long number_in_ip = strtol(number, NULL, 10);
    if (number_in_ip > 255)
        return false;

    return true;
}

/**
 * @brief Функция определяет, является ли ip адрес корректным 
 * @param[in] buf строка с ip адресом
 * @return true, если адрес корректный и false в ином случае
*/ 
bool is_ip_correct(const char *buf)
{
    bool ip_correct = true;
    size_t count_digit = 0, count_mask = 0, count_dot = 0;
    char number[MAX_DIGIT_IN_IP];

    while (ip_correct && *buf)
    {
        /*
          Если текущий элемент - цифра, то увеличиваем счётчик кол-ва цифр, добавляем эту цифру в число (массив символов цифр),
          если кол-во цифр больше 3, ip не коректный
        */
        if (isdigit(*buf))
        {
            number[count_digit] = *buf;
            count_digit++;
            if (count_digit > 3)
                ip_correct = false;
        }
        /*
          Если текущий элемент - точка, то вызываю функцию is_ip_correct, которая проверяет коректность тукущей маски,
          обнуляем кол-во цифр и число, которое было до этой точки
        */
        else if (*buf == '.')
        {
            ip_correct = is_ip_num_correct(number, count_digit);

            count_dot++;
            count_mask++;
            count_digit = 0;
        }
        /*
          Если текущий элемент буква, то сразу возвращаем false, иначе проверяем, что пробельный символ не стоит внутри масок ip адреса
        */
        else if (!isspace(*buf) || (count_mask != 0 && count_mask != 3 && isspace(*buf)))
            ip_correct = false; 

        buf++;
    }

    if (ip_correct && count_digit)
    {
        ip_correct = is_ip_num_correct(number, count_digit);
        count_mask++;
    }
    if (count_mask != 4 || count_dot != 3)
        ip_correct = false;

    return ip_correct;
}
