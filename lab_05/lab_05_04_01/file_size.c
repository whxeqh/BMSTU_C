#include "file_size.h"
#include "errors.h"
#include "student.h"

/**
 * @brief Функция определения размера файла в байтах 
 * 
 * @param[in]  file     Файловая переменная
 * @param[out] length   Размер файла в байтах
 *
 * @return Код ошибки
*/
int get_file_size(FILE *file, size_t *length)
{
    if (fseek(file, 0, SEEK_END) < 0)
        return ERR_FILE;
    
    *length = ftell(file);
    rewind(file);
    
    return OK;
}

/**
 * @brief Функция проверяет коректность бинарного файла
 * 
 * 1) Можно перемещать файловый указатель
 * 2) Файл ненулевой длины
 * 3) Размер файла кратен размеру структуры данных
 *
 * @param[in] file_bin  Файловая переменная
 * 
 * @return Код ошибки
*/
int check_bin_file(FILE *file_bin)
{
    size_t length = 0;
    
    if (get_file_size(file_bin, &length) != OK)
        return ERR_FILE;
    if (length == 0)
        return ERR_NOT_ENOUGH_DATA;
    if (length % sizeof(student_t) != 0)
        return ERR_FILE;

    return OK;
}

/**
 * @brief Функция проверяет коректность текстового файла
 * 
 * 1) Можно перемещать файловый указатель
 * 2) Файл ненулевой длины
 * 
 * @param[in] file_txt Файловая переменная
 *
 * @return Код ошибки 
 */
int check_txt_file(FILE *file_bin)
{
    size_t length = 0;
    
    if (get_file_size(file_bin, &length) != OK)
        return ERR_FILE;
    if (length == 0)
        return ERR_NOT_ENOUGH_DATA;

    return OK;
}
