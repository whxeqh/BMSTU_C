#include "errors.h"
#include "file_work.h"

int main(int argc, char **argv)
{
    int rc = OK;
    double avg = 0.0;
    size_t count = 0;
    char *file_name = NULL;
    FILE *file_in = NULL;
    FILE *file_out = stdout;

    if (argc != 2)
        return ERR_ARGS_COUNT;
    
    file_name = argv[1];
    file_in = fopen(file_name, "r");
    if (file_in == NULL)
        return ERR_FILE;

    rc = calc_avg_value(file_in, &avg);
    
    if (rc == OK)
        rc = calc_count_numbers(file_in, &count, avg);

    if (rc == OK)
        fprintf(file_out, "Ans: %zu\n", count);
    
    fclose(file_in);

    return rc;
}
