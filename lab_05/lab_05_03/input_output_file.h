#ifndef INPUT_OUTPUT_FILE_H
#define INPUT_OUTPUT_FILE_H

#include <stdio.h>

int create_bin_file(FILE *file_out, const size_t count_elements);
int print_bin_file(FILE *file_bin, FILE *file_out);
void import(FILE *file_txt, FILE *file_bin);
void export(FILE *file_bin, FILE *file_txt);

#endif
