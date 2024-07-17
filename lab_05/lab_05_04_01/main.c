#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "import_export.h"
#include "task_functions.h"
#include "file_size.h"

enum action_e 
{
    ACT_FILL,
    ACT_DELETE,
    ACT_IMPORT,
    ACT_EXPORT,
    ACT_UNKNOWN
};

int main(int argc, char **argv)
{
    enum action_e act = ACT_UNKNOWN;
    int rc = OK;

    //Для действия (b) и import/export
    FILE *file_bin = NULL, *file_txt = NULL;
    const char *filename_bin = NULL, *filename_txt = NULL;
    const char *mode_bin = NULL, *mode_txt = NULL;
    
    //Для действия (c)
    FILE *file_src = NULL, *file_dst = NULL;
    const char *filename_src = NULL, *filename_dst = NULL;
    const char *mode_src = NULL, *mode_dst = NULL;
    const char *substr = NULL;

    // Парс аргументов коммандной строки
    switch (argc)
    {
        case 3:
            if (strcmp("db", argv[1]) == 0)
            {
                filename_bin = argv[2];
                act = ACT_DELETE;
                mode_bin = "r+b";
            }
            else
                act = ACT_UNKNOWN;
            break;
        case 4:
            if (strcmp("import", argv[1]) == 0)
            {
                act = ACT_IMPORT;
                filename_txt = argv[2];
                filename_bin = argv[3];
                mode_txt = "r";
                mode_bin = "wb";
            }
            else if (strcmp("export", argv[1]) == 0)
            {
                act = ACT_EXPORT;
                filename_bin = argv[2];
                filename_txt = argv[3];
                mode_txt = "w";
                mode_bin = "rb";    
            }
            else
                act = ACT_UNKNOWN;
            break;
        case 5:
            if (strcmp("ft", argv[1]) == 0)
            {
                act = ACT_FILL;
                filename_src = argv[2];
                filename_dst = argv[3];
                substr = argv[4];
                mode_src = "r";
                mode_dst = "w";
            }
            else
                act = ACT_UNKNOWN;
            break;
        default:
            act = ACT_UNKNOWN;
            break;
    }

    //Выполнение действий
    switch (act)
    {
        case ACT_IMPORT:
            //Открытие и проверка корректности текстового файла: (открылся, не пустой)
            file_txt = fopen(filename_txt, mode_txt);
            if (!file_txt)
                return ERR_FILE;
            
            rc = check_txt_file(file_txt);
            if (rc != OK)
            {
                fclose(file_txt);
                return rc;
            }

            file_bin = fopen(filename_bin, mode_bin);
            if (!file_bin)
                return ERR_FILE;

            import(file_txt, file_bin);
            
            fclose(file_txt);
            fclose(file_bin);
            break;
        case ACT_EXPORT:
            //Открытие и проверка корректности бинарного файла: (открылся, не пустой, кратен структуре)
            file_bin = fopen(filename_bin, mode_bin);
            if (!file_bin)
                return ERR_FILE;
            
            rc = check_bin_file(file_bin);
            if (rc != OK)
            {
                fclose(file_bin);
                return rc;
            }
            
            file_txt = fopen(filename_txt, mode_txt);
            if (!file_txt)
                return ERR_FILE;
        
            export(file_bin, file_txt);
            
            fclose(file_txt);
            fclose(file_bin);
            break;
        case ACT_DELETE:
            //Открытие и проверка корректности бинарного файла: (открылся, не пустой, кратен структуре)
            file_bin = fopen(filename_bin, mode_bin);
            if (!file_bin)
                return ERR_FILE;
            
            rc = check_bin_file(file_bin);
            if (rc != OK)
            {
                fclose(file_bin);
                return rc;
            }

            size_t left_students;
            rc = move_high_avg_students_back(file_bin, &left_students);        
            
            fclose(file_bin);
            if (rc == OK)
                truncate(filename_bin, left_students * sizeof(student_t));
            break;
        case ACT_FILL:
            //Открытие и проверка корректности текстового файла: (открылся, не пустой)
            file_src = fopen(filename_src, mode_src);
            if (!file_src)
                return ERR_FILE;
            
            rc = check_txt_file(file_src);
            if (rc != OK)
            {
                fclose(file_src);
                return rc;
            }

            file_dst = fopen(filename_dst, mode_dst);
            if (!file_dst)
                return ERR_FILE;

            rc = fill_with_same_substr(file_src, file_dst, substr);
            
            fclose(file_src);
            fclose(file_dst);
            break;
        default:
            rc = ERR_ARGS;
    }
    
    return rc;
}
