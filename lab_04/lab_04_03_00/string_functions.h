#ifndef STRING_FUNCTIONS_H
#define STRING_FUNCTIONS_H

#include <stddef.h>
#include <stdbool.h>
#include "constants.h"
#include "errors.h"

int get_words(char *string, char(*words_array)[MAX_WORD_LEN], size_t *row);
void delete_letters(char *string, size_t *string_size);
void add_word_in_string(char *ans_string, size_t *ans_string_size, const char *word, const size_t word_size);
int new_string_creating(char (*words_array)[MAX_WORD_LEN], const size_t row, char *ans_string);

#endif 
