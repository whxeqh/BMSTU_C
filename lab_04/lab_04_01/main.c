#include <stdio.h>
#include <string.h>
#include "my_str_functions.h"

#define OK 0
#define ERR 1 

int main(void)
{
    int rc = OK;
    size_t errors_count = 0;

    // 1) strpbrk
    {
        // Один символ в str2 
        errors_count += (my_strpbrk("hello", "l") != strpbrk("hello", "l"));
        errors_count += (my_strpbrk("hello world", "q") != strpbrk("hello world", "q"));
    
        // Нет совпадающих элементов в строках
        errors_count += (my_strpbrk("HELLO", "hello") != strpbrk("HELLO", "hello"));
        errors_count += (my_strpbrk("Test string", "1234567890") != strpbrk("Test string", "1234567890"));

        // Есть совпадающие элементы в строках
        errors_count += (my_strpbrk("Same string", "Same string") != strpbrk("Same string", "Same string"));
        errors_count += (my_strpbrk("Same elements", "el;,") != strpbrk("Same elements", "el;,"));

        //Строка с набором символов для поиска пустая
        errors_count += (my_strpbrk("Sam123e ! string", "") != strpbrk("Sam123e ! string", ""));

        //Исходная строка пустая
        errors_count += (my_strpbrk("", "QWERTYytrewq") != strpbrk("", "QWERTYytrewq"));
    }


    // 2) strspn
    {
        //Один символ в str2
        errors_count += (my_strspn("0123456789", "0") != strspn("0123456789", "0"));
        errors_count += (my_strspn("0123456789", "w") != strspn("0123456789", "w"));
        
        //Несколько символов в str2, строки имеют одинаковый префикс
        errors_count += (my_strspn("Hello", "leH") != strspn("Hello", "leH"));
        errors_count += (my_strspn("0123456789", "9876543210") != strspn("0123456789", "9876543210"));
        
        //Несколько символов в str2, строки не имеют одинаковый префикс
        errors_count += (my_strspn("Hello", "123") != strspn("Hello", "123"));
        errors_count += (my_strspn("0123456789", "hello") != strspn("0123456789", "hello"));

        //Строка с набором символов для поиска пустая
        errors_count += (my_strspn("Sam123e ! string", "") != strspn("Sam123e ! string", ""));

        //Исходная строка пустая
        errors_count += (my_strspn("", "QWERTYytrewq") != strspn("", "QWERTYytrewq"));
    }


    // 3) strcspn
    {
        //Один символ в str2
        errors_count += (my_strcspn("0123456789", "0") != strcspn("0123456789", "0"));
        errors_count += (my_strcspn("0123456789", "w") != strcspn("0123456789", "w"));
        
        //Несколько символов в str2, Ответ 0
        errors_count += (my_strcspn("Hello", "leH") != strcspn("Hello", "leH"));
        errors_count += (my_strcspn("0123456789", "9876543210") != strcspn("0123456789", "9876543210"));
        
        //Несколько символов в str2, Ответ > 0
        errors_count += (my_strcspn("Hello", "lo") != strcspn("Hello", "lo"));
        errors_count += (my_strcspn("0123456789", "987") != strcspn("0123456789", "987"));

        //Строка с набором символов для поиска пустая
        errors_count += (my_strcspn("Sam123e ! string", "") != strcspn("Sam123e ! string", ""));

        //Исходная строка пустая
        errors_count += (my_strcspn("", "QWERTYytrewq") != strcspn("", "QWERTYytrewq"));
    }


    // 4) strchr
    {
        errors_count += (my_strchr("Simple line", 'l') != strchr("Simple line", 'l'));
        errors_count += (my_strchr("Test string", 'q') != strchr("Test string", 'q'));
        errors_count += (my_strchr("hello", '\0') != strchr("hello", '\0'));
        errors_count += (my_strchr("", 'a') != strchr("", 'a'));
    }    



    // 5) strrchr
    {
        errors_count += (my_strrchr("Simple line", 'l') != strrchr("Simple line", 'l'));
        errors_count += (my_strrchr("Test string", 'q') != strrchr("Test string", 'q'));
        errors_count += (my_strrchr("hello", '\0') != strrchr("hello", '\0'));
        errors_count += (my_strrchr("", 'a') != strrchr("", 'a'));
    }

    if (errors_count)
        rc = ERR;

    printf("errors = %zu", errors_count);

    return rc;
}
