#include <stdbool.h>
#include "my_str_functions.h"

/**
 * @brief Функция находит первое вхождение в строку символа из строки sym
 * @param[in] str Указатель на исходную строку 
 * @param[in] sym Указатель на строку с набором искомых символов
 * @return Указатель на первый найденный в строке str символ из строки sym
*/
char *my_strpbrk(const char *str, const char *sym)
{
    while (*str != '\0')
    {
        for (const char *current_sym = sym; *current_sym != '\0'; current_sym++)
            if (*current_sym == *str)
                return (char *) str;
        str++;
    }

    return NULL;
}

/**
 * @brief Определяет максимальный участок длины, состоящий только из символов, перечисленных в строке accept
 * @param[in] str Указатель на исходную строку
 * @param[in] accept Указатель на строку с набором символов, которые должны входить в исходную строку str
 * @return Длина префикса строки str, состоящего только из символов строки accept
*/
size_t my_strspn(const char *str, const char *accept)
{
    size_t size = 0;
    bool in_str = true;
    while (in_str && *str != '\0')
    {
        in_str = false;
        for (const char *current = accept; !in_str && *current != '\0'; current++)
            if (*current == *str)
            {
                in_str = true;
                size++;
            }
        str++;
    }

    return size;
}

/**
 * @brief Определяет максимальный участок длины, состоящий только не из символов, перечисленных в строке reject
 * @param[in] str Указатель на исходную строку
 * @param[in] accept Указатель на строку с набором символов, которые не должны входить в исходную строку str
 * @return Длина префикса строки str, не состоящего из символов строки accept
*/
size_t my_strcspn(const char *str, const char *reject)
{
    size_t size = 0;
    bool in_str = false;
    while (in_str == false && *str != '\0')
    {
        for (const char *current = reject; !in_str && *current != '\0'; current++)
            if (*current == *str)
                in_str = true;
        if (in_str == false)
            size++;
        str++;
    }

    return size;
}

/**
 * @brief Функция нахождения первого вхождения символа с кодом 'c' в строку str
 * @param[in] str Испходная строка
 * @param[in] c Символ для поиска
 * @return Указатель на этот символ в строке str
*/
char *my_strchr(const char *str, const int c)
{
    while (*str != '\0')
    {
        if (*str == c)
            return (char*) str;
        str++;
    }
    if (c == '\0')
        return (char*) str;
        
    return NULL;
}

/**
 * @brief Функция нахождения последнего вхождения символа с кодом 'c' в строку str
 * @param[in] str Испходная строка
 * @param[in] c Символ для поиска
 * @return Указатель на этот символ в строке str
*/
char *my_strrchr(const char *str, const int c)
{
    char *position = NULL;
    while (*str != '\0')
    {
        if (*str == c)
            position = (char *) str;
        str++;
    }
    if (c == '\0')
        return (char*) str;

    return position;
}
