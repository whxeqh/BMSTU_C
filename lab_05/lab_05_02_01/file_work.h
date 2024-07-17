#ifndef FILE_WORK_H
#define FILE_WORK_H

#include <stdio.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int calc_avg_value(FILE *file_in, double *avg);
int calc_count_numbers(FILE *file_in, size_t *count, const double avg);

#endif
