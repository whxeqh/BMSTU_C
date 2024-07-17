#include <string.h>
#include "io_file.h"
#include "errors.h"
#include "concatenate_files.h"

// Набор доступных действий
enum action_e
{
    ACT_UNKNOWN,
    ACT_CREATE,
    ACT_PRINT,
    ACT_CONCATENATE
};

int main(int argc, char **argv)
{
    int rc = OK;
    enum action_e act = ACT_UNKNOWN;

    // Для действий 1-2 (запись и печать файла)
    const char *mode = NULL;
    const char *filename = NULL;

    // Для действия 3 (запись двух файлов в третий)
    const char *first_mode = NULL, *second_mode = NULL;
    const char *filename_in1 = NULL, *filename_in2 = NULL, *filename_out = NULL;
    
    // Обработка введеных аргументов
    if (argc == 3)
    {
        filename = argv[2];
        if (strcmp(argv[1], "c") == 0)
        {
            act = ACT_CREATE;
            mode = "w";
        }
        else if (strcmp(argv[1], "p") == 0)
        {
            act = ACT_PRINT;
            mode = "r";
        }
        else 
            act = ACT_UNKNOWN;
    }

    else if (argc == 5)
    {
        if (strcmp(argv[1], "m") == 0)
        {
            act = ACT_CONCATENATE;
            first_mode = "r";
            second_mode = "w";
            filename_in1 = argv[2];
            filename_in2 = argv[3];
            filename_out = argv[4];
        }
        else
            act = ACT_UNKNOWN;
    }
    else 
    {
        print_err(ERR_ARGS);
        return ERR_ARGS;
    }
    
    // Выполнение действий
    if (act == ACT_CREATE)
    {
        FILE *file_in = fopen(filename, mode);
        if (file_in == NULL)
            rc = ERR_FILE;
        else
        {
            fill_file(file_in);
            fclose(file_in);
        }
    }  
    else if (act == ACT_PRINT)
    {
        FILE *file_in = fopen(filename, mode);
        if (file_in == NULL)
            rc = ERR_FILE;
        else 
        {
            rc = print_file(file_in);
            fclose(file_in);
        }
    }
    else if (act == ACT_CONCATENATE)
    {
        FILE *file_in1 = fopen(filename_in1, first_mode);
        if (file_in1 == NULL)
        {
            print_err(ERR_FILE);
            return ERR_ARGS;
        }

        FILE *file_in2 = fopen(filename_in2, first_mode);
        if (file_in2 == NULL)
        {
            print_err(ERR_FILE);
            return ERR_ARGS;
        }
        
        FILE *file_out = fopen(filename_out, second_mode);
        if (file_out == NULL)
        {
            print_err(ERR_FILE);
            return ERR_ARGS;
        }

        rc = concatenate_files(file_in1, file_in2, file_out);

        fclose(file_in1);
        fclose(file_in2);
        fclose(file_out);
    }
    else
        rc = ERR_UNKNOWN_ACT;

    if (rc != OK)
        print_err(rc);

    return rc;
}
