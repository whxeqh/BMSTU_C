#ifndef __RESEARCH_FILES_H__
#define __RESEARCH_FILES_H__

#include <stdio.h>
#include <stddef.h>

#include "research_files.h"
#include "errors.h"

#define num_files 3  // Количество файлов на каждую категорию (random, reverse, sorted)

#define random 0
#define reverse 1
#define sorted 2

void print_arr_in_file(const int *arr, const size_t length, const char *filename);

int open_data_files(const char *mode);

void close_data_files(void);

void print_arr(FILE *file, const int *arr, const size_t length);

#endif //__RESEARCH_FILES_H__
