#include <stdlib.h>
#include "input_output_file.h"
#include "errors.h"
#include "file_size.h"

/**
 * @brief Функция заполняет бинарный файл случайными числами 
 * 
 * @param[in]  file_in  Открытый на запись бинарный файл
 * @param[in]  count    Количество элементов для записи
 * 
 * @return Код ошибки
*/
int create_bin_file(FILE *file_out, const size_t count)
{
    int rc = OK;
    size_t i = 0;
    
    while (rc == OK && i++ < count)
    {   
        int num = rand();
        if (fwrite(&num, sizeof(num), 1, file_out) != 1)
            rc = ERR_WRITE;
    }

    return rc;
}

/**
 * @brief Функция читает целые числа из бинарного файла и зписывает вы выходной файл 
 * 
 * @param[in]  file_bin  Открытый на чтение бинарный файл
 * @param[in]  file_out  Открытый на чтение текстовый файл
 * 
 * @return Код ошибки
*/
int print_bin_file(FILE *file_bin, FILE *file_out)
{
    int rc = OK;
    size_t i = 0, length = 0;
    
    rc = get_file_size(file_bin, &length);
    length /= sizeof(int);
    
    while (rc == OK && i++ < length)
    {
        int number;
        if (fread(&number, sizeof(number), 1, file_bin) != 1)
            rc = ERR_READ;
        if (rc == OK)
            fprintf(file_out, "%d ", number);
    }            

    return rc;
}


/** 
 * @brief Функция записывает данные из текстового файла в бинарный файл
 * 
 * @param[in] file_txt Файловая переменная
 * @param[in] file_bin Файловая перемення
 * 
 * @return Код ошибки
*/
void import(FILE *file_txt, FILE *file_bin)
{
    int num;
    while (fscanf(file_txt, "%d", &num) == 1)
        fwrite(&num, sizeof(int), 1, file_bin);
}

/** 
 * @brief Функция записывает данные из бинарного файла в текстовый файл
 * 
 * @param[in] file_bin Файловая переменная
 * @param[in] file_txt Файловая перемення
 * 
 * @return Код ошибки
*/
void export(FILE *file_bin, FILE *file_txt)
{
    int num;
    while (fread(&num, sizeof(int), 1, file_bin) == 1)
        fprintf(file_txt, "%d\n", num);
}
