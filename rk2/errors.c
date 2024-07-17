#include "errors.h"
#include <stdio.h>

/**
 * @brief Функция печати сообщений об ошибке
 * @param[in] rc код ошибки 
*/
void print_err(const int rc)
{
    
    if (rc == ERR_ARGS)
        fprintf(stderr, "ERR WITH ARGS!\nShould be either\napp.exe <mode> <file_name>\nor\napp.exe <mode> <file_name1> <file_name2> <file_name3>\n");
    else if (rc == ERR_IO)
        fprintf(stderr, "ERR WITH INPUT/OUTPUT");
    else if (rc == ERR_FILE)
        fprintf(stderr, "ERR WITH FILE");  
    else if (rc == ERR_UNKNOWN_ACT)
        fprintf(stderr, "UNKNOWN_ACT!");
    else if (rc == ERR_FILE_HAS_TRASH)
        fprintf(stderr, "TRASH IN FILE!");
    else 
        fprintf(stderr, "Unknown err(%d)", rc);
}
