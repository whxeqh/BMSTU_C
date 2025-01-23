#include "errors.h"

#include <stdio.h>

void print_error(errors_e rc)
{
    switch (rc)
    {
    case ERR_IO:
        puts("ERR IO");
        break;
    case ERR_EMPTY:
        puts("ERR EMPTY");
        break;
    case ERR_OVERFLOW:
        puts("ERR OVERFLOW");
        break;
    case ERR_MEM:
        puts("ERR MEM");
        break;
    case ERR_FILE:
        puts("ERR FILE");
        break;
    case ERR_ARGS:
        puts("app.exe file_in");
        break;
    default:
        printf("UNKNOWN ERROR, rc = (%d)", rc);
        break;
    }
}
