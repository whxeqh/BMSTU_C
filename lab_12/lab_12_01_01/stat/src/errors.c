#include <stdio.h>
#include "errors.h"

#ifdef LOCAL_BUILD
void print_error(const int rc)
{
    switch (rc)
    {
    case ERR_IO:
        fprintf(stderr, "ERROR WITH INPUT/OUTPUT\n");
        break;
    case ERR_RANGE:
        fprintf(stderr, "ERR RANGE\n");
        break;
    case ERR_FILE:
        fprintf(stderr, "FILE ERROR\n");
        break;
    case ERR_ARGS:
        fprintf(stderr, "ARGS ERROR\n");
        fprintf(stderr, "app.exe file_in file_out [f]\n");
        break;
    case ERR_MEMORY:
        fprintf(stderr, "MEMORY ERROR\n");
        break;
    case ERR_EMPTY_ARRAY:
        fprintf(stderr, "EMPTY ARRAY ERROR\n");
        break;
    default:
        fprintf(stderr, "UNKNOWN ERROR (%d)\n", rc);
        break;
    }
}
#else
void print_error(const int rc)
{
    (void) rc;
}
#endif
