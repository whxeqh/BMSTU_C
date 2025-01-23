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
        fprintf(stderr, "app.exe action mtr_1.txt [mtr_2.txt] res.txt\n");
        break;
    case ERR_MEMORY:
        fprintf(stderr, "MEMORY ERROR\n");
        break;
    case ERR_NO_INVERSE:
        fprintf(stderr, "ERROR NO INVERSE MATRIX\n");
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
