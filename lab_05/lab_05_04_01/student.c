#include <string.h>
#include <ctype.h>
#include "student.h"
#include "errors.h"
#include "file_size.h"

/** 
 * @brief Функция чтения сткрутур студентов из текстовго файла в массив 
 * 
 * @param[in]  file_txt  Файловая переменная
 * @param[out] student   Массив структур
 * @param[out] count     Количество студентов
 * 
 * @return Код ошибки
*/
int read_student_txt(FILE *file_txt, student_t student[], size_t *count)
{
    size_t i = 0;
    int ch;
    do
    {
        // Ввод фамилии
        if (fgets(student[i].surname, sizeof(student[i].surname), file_txt) == NULL)
            return ERR_IO;
        
        char *p = strchr(student[i].surname, '\n');
        if (!p)
            return ERR_BUF_TO_BIG;
        *p = '\0';

        // Ввод имени
        if (fgets(student[i].name, sizeof(student[i].name), file_txt) == NULL)
            return ERR_IO;
        
        p = strchr(student[i].name, '\n');
        if (!p)
            return ERR_BUF_TO_BIG;
        *p = '\0';

        // Ввод оценок
        for (size_t cnt = 0; cnt < MARKS_COUNT; ++cnt)
        {
            if (fscanf(file_txt, "%u", &student[i].marks[cnt]) != 1)
                return ERR_IO;
        }

        do
        {
            ch = fgetc(file_txt);  // Пропуск символа переноса строки после ввода оценок
        } while (isspace(ch)); 
        ungetc(ch, file_txt);
        
        ++i;
    } while (ch != EOF);

    *count = i;
    return OK;
}
