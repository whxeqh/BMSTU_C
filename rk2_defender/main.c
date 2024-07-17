/*
    Файл содержит вещ числа. Найти такое, которое максимально близко к среднему значению
*/
#include "stdio.h"
#include "stddef.h"
#include "stdbool.h"

#define OK 0
#define ERR_IO 1
#define ERR_ARGS 2
#define ERR_NOT_ENOUGH_DATA 3
#define ERR_FILE 4

#define EPS 1e-7

int find_close_num(FILE *file, double *close_avg, const double avg);
int find_avg(FILE *file, double *avg);
void print_err(const int rc);

int main(int argc, char **argv)
{
    int rc = OK;
    char *filename = NULL;
    FILE *file = NULL;
    double avg = 0.0, close_avg = 0.0;

    if (argc == 2)
    {
        filename = argv[1];
        file = fopen(filename, "r");
        if (file == NULL)
            return ERR_FILE;

        rc = find_avg(file, &avg);
        if (rc == OK)
        {
            rewind(file);
            rc = find_close_num(file, &close_avg, avg);
        }

        fclose(file);
    }
    else
        rc = ERR_ARGS;

    if (rc == OK)
        fprintf(stdout, "Close avg: %lf\n", close_avg);
    else 
        print_err(rc);
        
    return rc;
}


int find_close_num(FILE *file, double *close_avg, const double avg)
{
    bool first = true;
    double dif = 0.0, current = 0.0, min_dif = 0.0;


    while (fscanf(file, "%lf", &current) == 1)
    {
        dif = current - avg;
        if (dif < 0.0)
            dif = -dif;
        
        if (first || min_dif > dif)
        {
            *close_avg = current;
            min_dif = dif;
            first = false;
        }
    }

    if (!feof(file))
        return ERR_IO;

    return OK;
}

int find_avg(FILE *file, double *avg)
{
    double sum = 0.0, current;
    size_t count = 0;

    while (fscanf(file, "%lf", &current) == 1)
    {
        sum += current;
        count++;
    }
    if (!feof(file))
        return ERR_IO;
    if (count == 0)
        return ERR_NOT_ENOUGH_DATA;

    (*avg) = (sum / count);
    return OK; 
}

void print_err(const int rc)
{
    switch (rc)
    {
    case ERR_IO:
        perror("ERROR WITH INPUT/OUTPUT");
        break;
    case ERR_ARGS:
        perror("ERROR WITH ARGS. SHOULD BE: app.exe <file.txt>");
        break;
    case ERR_FILE:
        perror("ERROR WITH FILE");
        break;
    case ERR_NOT_ENOUGH_DATA:
        perror("NEED AT LEAST 1 NUMBER");
        break;
    default:
        perror("UNKNOWN ERROR");
        break;
    }
}