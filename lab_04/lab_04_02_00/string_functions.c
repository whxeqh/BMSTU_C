#include <string.h>
#include <stdio.h>
#include "string_functions.h"

/**
 * @brief Функция разбивает строку на слова и сохраняет их в массиве слов
 * 
 * @param[in] string Исходная строка для разбивки на слова
 * @param[out] words_array Массив для хранения слов
 * @param[out] row Количество слов в массиве слов
 * 
 * @return Код ошибки
 */
int get_words(const char *string, char (*words_array)[MAX_WORD_LEN], size_t *row)
{
    int rc = OK;
    char buff[MAX_WORD_LEN];  
    size_t buff_size = 0, array_size = 0; 
    for (size_t i = 0; buff_size < MAX_WORD_LEN && string[i]; i++)
    {
        /*
          Если текущий символ строки входит в разделительные символы, то записываем 
          в конец нуль-терминатор и добавляем текущее слово в массив слов
        */
        if (buff_size > 0 && strchr(DELIMS, string[i]) != NULL)
        {
            strncpy(words_array[array_size], buff, buff_size);
            words_array[array_size][buff_size] = '\0';
            buff_size = 0;
            array_size++;
        }
        /*
          Если текущий символ строки не входит в разделительные символы,
          то добавляем его в массив символов current_word[]
        */
        else if (strchr(DELIMS, string[i]) == NULL)
        {
            buff[buff_size] = string[i];
            buff_size++;
        }
    }
    if (buff_size == MAX_WORD_LEN)
        rc = ERR_BUFF_TO_BIG;
    /*
      Так как в конце строки может не быть разделяющего символа, то после цикла прверяем длину последнего слолва
      Если она больше 0, то добавляем его в массив слов 
    */
    if (rc == OK && buff_size)
    {
        strncpy(words_array[array_size], buff, buff_size);
        words_array[array_size][buff_size] = '\0';
        array_size++;
    }

    if (rc == OK)
        *row = array_size;

    return rc;
}

/**
 * @brief Функция проходится по массиву слов и, если слово до этого не встречалось, печает это слово и кол-во встреч во всём массиве 
 * @param[in] words_array Исходный массив слов 
 * @param[in] row Количество слов
*/
void print_result(char (*words_array)[MAX_WORD_LEN], const size_t row)
{
    printf("Result:\n");
    for (size_t i = 0; i < row; i++)
    {
        if (first_word_in_array(words_array, i, words_array[i]))
        {
            size_t count = count_word_in_array(words_array, row, words_array[i]);
            printf("%s %zu\n", words_array[i], count);
        }
    }
}

/**
 * @brief Функция считае, сколько раз слово word встречается в массиве слов 
 * @param[in] words_array Исходный массив слов 
 * @param[in] row Количество слов
 * @param[in] word Слово для сравннения
 * @return Количество слов word во всём массиве слов
*/
size_t count_word_in_array(char (*words_array)[MAX_WORD_LEN], const size_t row, const char *word)
{
    size_t ans = 0;
    for (size_t i = 0; i < row; i++)
        if (strcmp(words_array[i], word) == 0)
            ans++;
    return ans;
}

/**
 * @brief Функция проверяет, встречалось ли с 0-й по (row-ю - 1)строку массива слов слово word 
 * @param words_array Исходный массив слов
 * @param row Количество строк, до которой будет проходить проверка
 * @param word Слово для сравнения
 * @return true, если слово до этого не встречалось, false в ином случае
*/
bool first_word_in_array(char (*words_array)[MAX_WORD_LEN], const size_t row, const char *word)
{
    for (size_t i = 0; i < row; i++)
        if (strcmp(words_array[i], word) == 0)
            return false;
    return true;   
}
