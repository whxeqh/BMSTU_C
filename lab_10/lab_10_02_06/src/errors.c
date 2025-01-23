#include <stdio.h>

#include "errors.h"

#ifdef LOCAL_BUILD
void print_error(const int rc)
{
    switch (rc)
    {
    case ERR_IO:
        puts("ERR WITH INPUT/OUTPUT");
        break;
    case ERR_MEMORY:
        puts("ERR WITH MEMORY");
        break;
    case ERR_EMPTY:
        puts("ERR EMPTY");
        break;
    case ERR_ACT:
        puts("ERR ACT");
        break;
    default:
        printf("UNKNOWN ERROR (%d)\n", rc);
        break;
    }
}
#else
void print_error(const int rc)
{
    (void) rc;   
}
#endif