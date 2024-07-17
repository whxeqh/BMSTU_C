#include <string.h>
#include <stdbool.h>
#include "task_functions.h"
#include "file_size.h"
#include "import_export.h"

/** 
 * @brief Функция считывает студента из бинарного файла по позиции 
 *  
 * @param[in]  file     Файловая переменна
 * @param[in]  pos      Позиция студента
 * @param[out] student  Структура студента
 * 
 * @return Код ошибки
*/
static int get_student_by_pos(FILE *file, const long pos, student_t *student)
{
    if (fseek(file, pos * sizeof(*student), SEEK_SET) != 0)
        return ERR_FILE;
    if (fread(student, sizeof(*student), 1, file) != 1)
        return ERR_READ;
    
    return OK;
}

/** 
 * @brief Функция вставляет студента в бинарный файла по позиции 
 *  
 * @param[in]  file     Файловая переменна
 * @param[in]  pos      Позиция студента
 * @param[out] student  Структура студента
 * 
 * @return Код ошибки
*/
static int put_student_by_pos(FILE *file, const long pos, const student_t *student)
{
    if (fseek(file, pos * sizeof(*student), SEEK_SET) != 0)
        return ERR_FILE;
    if (fwrite(student, sizeof(*student), 1, file) != 1)
        return ERR_WRITE;
    
    return OK;
}

/**
 * @brief Функция находит среднию оценку среди всех оценок студентов в файле
 * 
 * @param[in]   file_bin  Файловая переменная
 * @param[out]  avg       Средняя оценка
 * @param[in]   length    Количество студентов
 * 
 * @return Код ошибки
*/
static int find_file_avg(FILE *file_bin, float *avg, const size_t length)
{
    student_t student;
    float sum = 0;
    int rc = OK;

    for (size_t i = 0; rc == OK && i < length; ++i)
    {
        if (fread(&student, sizeof(student), 1, file_bin) != 1)
            return ERR_IO;
        for (size_t j = 0; j < MARKS_COUNT; ++j)
            sum += student.marks[j];
    }
    
    sum /= (length * MARKS_COUNT);
    *avg = sum;
    rewind(file_bin);

    return OK;
}

/** 
 * @brief Функция смещает студентов с высоким средним баллом в начало массива и уменьшает его длину 
 * 
 * @param[in]   file_bin       Файловая переменная
 * @param[out]  left_students  Количество студентов с avg большим среднего
 * 
 * @return Код ошибки
*/
int move_high_avg_students_back(FILE *file_bin, size_t *left_students)
{
    student_t cur_student;
    size_t left = 0, length;
    int rc = OK;
    float avg, cur;

    rc = get_file_size(file_bin, &length);
    length /= sizeof(student_t);

    rc = find_file_avg(file_bin, &avg, length);

    for (size_t i = 0; rc == OK && i < length; ++i)
    {
        rc = get_student_by_pos(file_bin, i, &cur_student);
        cur = 0.0;
        for (size_t j = 0; j < MARKS_COUNT; ++j)
            cur += cur_student.marks[j];
        // Если avg текущего студента > avg, то смещаем его влево
        if (avg <= cur / MARKS_COUNT) 
        {
            rc = put_student_by_pos(file_bin, left, &cur_student);
            if (rc == OK)
                left++;
        }
    }

    if (rc == OK)
        *left_students = left;

    return rc;
}

/**
 * @brief Функция из исходного файла записывает студентов в выходной файл, если их фамилия совпадает с substr
 * 
 * @param[in]  file_src  Файловая переменная исходного файла 
 * @param[in]  file_dst  Файловая переменная выходного файла
 * @param[in]  substr    Подстрока для сравнения
 * 
 * @return Код ошибки
*/
int fill_with_same_substr(FILE *file_src, FILE *file_dst, const char *substr)
{
    int rc = OK;
    bool is_empty = true;
    size_t count; 
    student_t student[N];

    rc = read_student_txt(file_src, student, &count);

    for (size_t i = 0; rc == OK && i < count; ++i)
    {
        if (strncmp(student[i].surname, substr, strlen(substr)) == 0)
        {
            is_empty = false;
            fprintf(file_dst, "%s\n%s\n", student[i].surname, student[i].name);
            for (size_t j = 0; j < MARKS_COUNT; ++j)
                fprintf(file_dst, "%u ", student[i].marks[j]);
            fputc('\n', file_dst);
        }
    }

    if (is_empty)
        rc = ERR_IO;

    return rc;
}
