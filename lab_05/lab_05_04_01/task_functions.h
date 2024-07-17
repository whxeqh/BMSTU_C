#ifndef TASK_FUNCTIONS_H
#define TASK_FUNCTIONS_H

#include <stdio.h>
#include "student.h"

int fill_with_same_substr(FILE *file_src, FILE *file_dst, const char *substr);
int move_high_avg_students_back(FILE *file_bin, size_t *left_students);

#endif
