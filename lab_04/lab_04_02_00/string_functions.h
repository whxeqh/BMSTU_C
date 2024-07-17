#ifndef STRING_FUCNTIONS_H
#define STRING_FUCNTIONS_H

#include <stddef.h>
#include <stdbool.h>
#include "constants.h"
#include "errors.h"

int get_words(const char *string, char (*words_array)[MAX_WORD_LEN], size_t *row);
void print_result(char (*words_array)[MAX_WORD_LEN], const size_t row);
size_t count_word_in_array(char (*words_array)[MAX_WORD_LEN], const size_t row, const char *word);
bool first_word_in_array(char (*words_array)[MAX_WORD_LEN], const size_t row, const char *word);

#endif 
