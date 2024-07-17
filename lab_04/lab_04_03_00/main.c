#include <string.h>
#include <stdio.h>
#include "io.h"
#include "string_functions.h"

int main(void)
{
    int rc = OK;
    char string[MAX_STRING_LEN], ans_string[MAX_STRING_LEN], words_array[MAX_WORDS_COUNT][MAX_WORD_LEN];
    size_t row;

    rc = input_string(string, sizeof(string));
    if (rc == OK)
        rc = get_words(string, words_array, &row);
    if (rc == OK && row < 2)
        rc = ERR_NOT_ENOUGH_WORDS;

    if (rc == OK)
        rc = new_string_creating(words_array, row, ans_string);

    if (rc == OK)
        printf("Result: %s\n", ans_string);
    else
        print_error(rc);
    
    return rc;    
}
