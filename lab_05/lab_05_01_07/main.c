#include "process.h"
#include "errors.h"

int main(void)
{
    int rc = OK, count = 0;
    FILE *file_in = stdin;
    FILE *file_out = stdout;
    
    rc = process(file_in, &count);

    if (rc == OK)
        fprintf(file_out, "Count of local maximum: %d\n", count);

    return rc;
}
