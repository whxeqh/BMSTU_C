#ifndef __FILE_H__
#define __FILE_H__

#include <stdio.h>

/**
 * @brief Создает и заполняет массив из файла
 * @param pbeg[out] Указатель на указатель на начало массива 
 * @param pend[out] Указатель на указатель на конец массива 
 * @param file_in[in] Файловая переменная
 * @return Код ошибки
*/
int create_array(int **pbeg, int **pend, FILE *file_in);

/**
 * @brief Открывает файл и вызывает функцию создания и заполнения массива из файла
 * @param pbeg[out] Указатель на указатель на начало массива 
 * @param pend[out] Указатель на указатель на конец массива 
 * @param file_name[in] Название файла
 * @return Код ошибки
*/
int create_array_ex(int **pbeg, int **pend, const char *file_name);

/**
 * @brief Открывает файл и вызывает функцию печати массива в файл
 * @param pbeg[out] Указатель на указатель на начало массива 
 * @param pend[out] Указатель на указатель на конец массива 
 * @param file_name[in] Название файла
 * @return Код ошибки
*/
int print_array_int_ex(const int *pbeg, const int *pend, const char *file_name);

/**
 * @brief Печатает массив в файл
 * @param pbeg[out] Указатель на указатель на начало массива 
 * @param pend[out] Указатель на указатель на конец массива 
 * @param file_in[in] Файловая переменная
 * @return Код ошибки
*/
int print_array_int(const int *pbeg, const int *pend, FILE *file_out);

#endif //__FILE_H__