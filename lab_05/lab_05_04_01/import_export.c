#include <stdint.h>
#include <string.h>
#include "import_export.h"
#include "student.h"
#include "file_size.h"


/** 
 * @brief Функция записывает данные из текстового файла в бинарный файл
 * 
 * @param[in] file_txt Файловая переменная
 * @param[in] file_bin Файловая перемення
 * 
 * @return Код ошибки
*/
int import(FILE *file_txt, FILE *file_bin)
{
    student_t tmp;
    
    do
    {
        // Ввод фамилии
        if (fgets(tmp.surname, sizeof(tmp.surname), file_txt) == NULL)
            return ERR_IO;
        
        char *p = strchr(tmp.surname, '\n');
        if (!p)
            return ERR_BUF_TO_BIG;
        *p = '\0';

        // Ввод имени
        if (fgets(tmp.name, sizeof(tmp.name), file_txt) == NULL)
            return ERR_IO;
        
        p = strchr(tmp.name, '\n');
        if (!p)
            return ERR_BUF_TO_BIG;
        *p = '\0';

        // Ввод оценок
        size_t cnt = 0;
        while (cnt < MARKS_COUNT)
        {
            if (fscanf(file_txt, "%u", &tmp.marks[cnt]) != 1)
                return ERR_IO;
            ++cnt;
        }

        fgetc(file_txt);  // Пропуск символа новой строки после ввода оценок
        
        if (fwrite(&tmp, sizeof(tmp), 1, file_bin) != 1)
            return ERR_FILE;
    } while (!feof(file_txt));

    return OK;
}

/** 
 * @brief Функция записывает данные из бинарного файла в текстовый файл
 * 
 * @param[in] file_bin Файловая переменная
 * @param[in] file_txt Файловая перемення
 * 
 * @return Код ошибки
*/
int export(FILE *file_bin, FILE *file_txt)
{
    int rc = OK;
    size_t length = 0;
    student_t student;

    get_file_size(file_bin, &length);
    length /= sizeof(student);

    for (size_t i = 0; rc == OK && i < length; ++i)
    {
        if (fread(&student, sizeof(student), 1, file_bin) != 1)
            return ERR_IO;
        if (fprintf(file_txt, "%s\n%s\n", student.surname, student.name) < 0)
            return ERR_IO;

        for (size_t j = 0; j < MARKS_COUNT; ++j)
        {
            if (fprintf(file_txt, "%d ", student.marks[j]) < 0)
                return ERR_IO;
        }
        fprintf(file_txt, "\n");
    }

    return OK;
}
