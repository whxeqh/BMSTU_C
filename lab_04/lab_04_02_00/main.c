#include "io.h"
#include "string_functions.h"

int main(void)
{
    int rc = OK;
    char string[MAX_STRING_LEN], words_array[MAX_WORDS_COUNT][MAX_WORD_LEN];
    size_t row;

    rc = input_string(string, sizeof(string));
    if (rc == OK)
        rc = get_words(string, words_array, &row); 
    if (rc == OK && row == 0)
        rc = ERR_NO_WORDS;
    if (rc == OK)
        print_result(words_array, row);
    else
        print_error(rc);

    return rc;    
}
