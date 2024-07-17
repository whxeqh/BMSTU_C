#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "input_output_file.h"
#include "func_sort.h"
#include "errors.h"
#include "file_size.h"

enum action_e 
{
    ACT_CREATE,
    ACT_PRINT,
    ACT_SORT,
    ACT_IMPORT,
    ACT_EXPORT,
    ACT_UNKNOWN
};

int main(int argc, char **argv)
{
    enum action_e act = ACT_UNKNOWN;
    int rc = OK, count_elements;
    char *file_name_bin = NULL, *file_name_txt = NULL;
    char *mode_bin = NULL, *mode_txt = NULL; 
    FILE *file_txt = NULL, *file_bin = NULL;
    
    srand(time(NULL));

    // Парс аргументов коммандной строки
    if (argc == 3)
    {
        if (strcmp(argv[1], "p") == 0)
        {
            act = ACT_PRINT;
            mode_bin = "rb";
            file_name_bin = argv[2];
        }
        else if (strcmp(argv[1], "s") == 0)
        {
            act = ACT_SORT;
            mode_bin = "r+b";
            file_name_bin = argv[2];
        }
        else 
            act = ACT_UNKNOWN;
    }
    else if (argc == 4)
    {
        if (strcmp(argv[1], "c") == 0)
        {
            count_elements = atoi(argv[2]);
            if (count_elements <= 0)
                return ERR_RANGE;   
            act = ACT_CREATE;
            mode_bin = "wb";
            file_name_bin = argv[3];
        }
        else if (strcmp(argv[1], "import") == 0)
        {
            act = ACT_IMPORT;
            mode_txt = "r";
            mode_bin = "wb";
            file_name_txt = argv[2];
            file_name_bin = argv[3];
        }
        else if (strcmp(argv[1], "export") == 0)
        {
            act = ACT_EXPORT;
            mode_txt = "w";
            mode_bin = "rb";
            file_name_bin = argv[2];
            file_name_txt = argv[3];
        }
        else
            act = ACT_UNKNOWN;
    }
    else
        act = ACT_UNKNOWN; 

    if (act == ACT_UNKNOWN)
        return ERR_ARGS;
    
    // Открытие файлов для дальнейших действия и их проверка на корректность
    if (act == ACT_IMPORT || act == ACT_EXPORT)
    {
        file_txt = fopen(file_name_txt, mode_txt);
        if (!file_txt)
            return ERR_FILE;
    }
    if (act != ACT_UNKNOWN)
    {
        // Открытие и проверка корректности бинарного файла: (открылся, не пустой, файл кратен int)
        file_bin = fopen(file_name_bin, mode_bin);
        if (!file_bin)
            return ERR_FILE;
        
        if (act == ACT_PRINT || act == ACT_SORT)
        {
            rc = check_bin_file(file_bin); 
            if (rc != OK)
            {
                fclose(file_bin);
                return rc;
            }
        }
    }

    //Выполнение действий
    switch (act)
    {
        case ACT_CREATE:
            rc = create_bin_file(file_bin, count_elements);
            break;
        case ACT_PRINT:
            rc = print_bin_file(file_bin, stdout);
            break;
        case ACT_SORT:
            rc = sort_file(file_bin);
            break;  
        case ACT_IMPORT:
            import(file_txt, file_bin);
            fclose(file_txt);
            break;
        case ACT_EXPORT:
            export(file_bin, file_txt);
            fclose(file_txt);
            break;
        default:
            rc = ERR_ARGS;
    }
    fclose(file_bin);
    
    return rc;
}
