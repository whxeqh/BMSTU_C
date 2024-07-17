#include <string.h>
#include "string_functions.h"

/**
 * @brief Функция разбивает строку на слова и записывает их в массив слов words_array 
 * @param[in] string Исходная строка, которая будет разбита на слова
 * @param[out] words_array Массив слов
 * @param[out] row Количество слов
 * @return Код ошибки
*/
int get_words(char *string, char (*words_array)[MAX_WORD_LEN], size_t *row)
{
    int rc = OK;
    size_t array_size = 0;
    char *word = strtok(string, DELIMS);
    while (rc == OK && word) 
    {
        if (strlen(word) < MAX_WORD_LEN)
        {
            strcpy(words_array[array_size++], word);
            word = strtok(NULL, DELIMS); 
        }    
        else 
            rc = ERR_BUFF_TO_BIG;
    }
    if (rc == OK)
        *row = array_size;
        
    return rc;
}

/**
 * @brief Функция удаления элементов из строки, которые совпадают с её первым элементом 
 * 
 * @param[out] string Строка, в которой будут удаляться элементы
 * @param[in] string_size Длина этой строки
*/
void delete_letters(char *string, size_t *string_size)
{
    size_t new_word_size = 1;
    
    for (size_t i = 1; i < *string_size; i++)
        if (string[0] != string[i])
            string[new_word_size++] = string[i];
    string[new_word_size] = '\0';

    *string_size = new_word_size;
}

/**
 * @brief Функция формирует новую строку из массива слов
 * @param[in] words_array Массив слов
 * @param[in] row Количество слов в массиве слов
 * @param[out] ans_string Новая строка, составленная из массива слов
*/
int new_string_creating(char (*words_array)[MAX_WORD_LEN], const size_t row, char *ans_string)
{
    size_t ans_string_size = 0, current_word_size;
    char current_word[MAX_WORD_LEN], last_word[MAX_WORD_LEN];
    
    strcpy(ans_string, "\0"); // Если первый символы будет заполнен мусором, то strcat будет неверно работать

    //Для дальнейшего удобства в массив символов last_word записываю последнее слово массива слов words_array
    strncpy(last_word, words_array[row - 1], sizeof(last_word) - 1);
    last_word[sizeof(last_word) - 1] = '\0';

    //Проходимся от предпоследнего, до первого слова в массиве слов
    for (int i = row - 2; i >= 0; i--)
    {
        //Для дальнейшего удобства в массив символов current_word записываю текущее слово массива слов words_array
        strncpy(current_word, words_array[i], sizeof(current_word) - 1);
        current_word[sizeof(current_word) - 1] = '\0';
        current_word_size = strlen(current_word);

        /*
           Если текущее слово не равно последнему, удаляю из него все символы, схожие с первым,
           Проверяю, что добавление слова к результирующей строке не переполнит буфер и затем добавляю его
        */
        if (strcmp(current_word, last_word) != 0)
        {
            delete_letters(current_word, &current_word_size);
            
            if (ans_string_size + current_word_size > MAX_STRING_LEN)
                return ERR_BUFF_TO_BIG;
            
            strcat(ans_string, current_word);
            strcat(ans_string, " ");
            ans_string_size += current_word_size + 1; // +1 с учётом пробела между словами 
        }
    }
    ans_string[ans_string_size - 1] = '\0'; // Последний пробел заменяю на нуль-терминатор

    return OK;
}
