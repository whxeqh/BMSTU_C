#ifndef STUDENT_H
#define STUDENT_H

#include <stdint.h>
#include <stdio.h>
#include "defines.h"

typedef struct
{
    char surname[SURNAME_MAX_LEN];
    char name[NAME_MAX_LEN];
    uint32_t marks[MARKS_COUNT];
} student_t;

int read_student_txt(FILE *file_txt, student_t student[], size_t *count);

#endif 
