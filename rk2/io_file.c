#include "io_file.h"
#include "errors.h"

/**
 * @brief Функция ввода вещественных чисел с входного потока и их записи в файл "file_in";
 * @param[in] file_in Файл для записи
*/
void fill_file(FILE *file_in)
{
    double num = 0.0;
    while (fscanf(stdin, "%lf", &num) == 1)
        fprintf(file_in, "%lf\n", num);
}

/**
 * @brief Функция печати вещественных чисел из файла в выходной поток; 
 * @param[in] file_in Файл для печати
 * @return Код ошибки
*/
int print_file(FILE *file_in)
{
    double num = 0.0;
    
    while (fscanf(file_in, "%lf", &num) == 1)
        fprintf(stdout, "%lf\n", num);
    if (!feof(file_in))
        return ERR_FILE;

    return OK;
}
