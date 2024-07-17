#include "concatenate_files.h"
#include "errors.h"

/**
 * @brief Функция объединяет первые два файла в третий так, чтобы числа в третьем остались упорядоченными по возрастанию
 * 
 * @details Функция предполагает, что числа в файлах file_in1 и file_in2 упорядочены по возрастанию.
 * 
 * @param[in] file_in1 Первый файл для чтения
 * @param[in] file_in2 Второй файл для чтения
 * @param[in] file_out Файл, в который будут записаны числа из первых двух файлов
 * @return Код ошибки
*/
int concatenate_files(FILE *file_in1, FILE *file_in2, FILE *file_out)
{
    double num1, num2;
    
    int has_num1 = fscanf(file_in1, "%lf", &num1);
    int has_num2 = fscanf(file_in2, "%lf", &num2); 

    // Пока числа есть в обоих файлах, сравниваем их
    while(has_num1 == 1 && has_num2 == 1)
    {
        if (num1 < num2)
        {
            fprintf(file_out, "%lf\n", num1);
            has_num1 = fscanf(file_in1, "%lf", &num1);
        }
        else
        {
            fprintf(file_out, "%lf\n", num2);
            has_num2 = fscanf(file_in2, "%lf", &num2);
        }
    }

    while (has_num1 == 1)
    {
        fprintf(file_out, "%lf\n", num1);
        has_num1 = fscanf(file_in1, "%lf", &num1);
    }
    while (has_num2 == 1)
    {
        fprintf(file_out, "%lf\n", num2);
        has_num2 = fscanf(file_in2, "%lf", &num2);
    }

    // Если в ходе чтения файла был обноружен символ, а не число
    if (!feof(file_in1) || !feof(file_in2))
        return ERR_FILE_HAS_TRASH;
    
    return OK;
}
