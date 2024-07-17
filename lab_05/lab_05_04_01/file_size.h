#ifndef FILE_SIZE_H
#define FILE_SIZE_H

#include <stdio.h>

int get_file_size(FILE *file, size_t *length);
int check_bin_file(FILE *file_bin);
int check_txt_file(FILE *file_txt);

#endif
