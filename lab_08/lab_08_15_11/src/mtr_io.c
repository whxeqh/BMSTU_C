#include "mtr_io.h"
#include "mtr_alloc.h"
#include "errors.h"

static int read_row(FILE *file, double *row, const size_t columns)
{
    int rc = OK;
    for (size_t j = 0; rc == OK && j < columns; j++)
        if (fscanf(file, "%lf", &row[j]) != 1)
            rc = ERR_IO;
    
    return rc;
}

static int print_row(FILE *file, const double *row, const size_t columns)
{
    int rc = OK;
    for (size_t j = 0; rc == OK && j < columns; j++)
        if (fprintf(file, "%.12lf ", row[j]) < 0)
            rc = ERR_IO;
    if (fprintf(file, "\n") < 0)
        rc = ERR_IO;

    return rc;
}

int mtr_read(FILE *f, double **matrix, const size_t rows, const size_t columns)
{
    int rc = OK;
    for (size_t i = 0; rc == OK && i < rows; i++)
        rc = read_row(f, matrix[i], columns);
    
    return rc;
}

int mtr_create(double ***matrix, size_t *rows, size_t *columns, FILE *file)
{
    double **tmp_matrix;
    size_t tmp_rows, tmp_columns;
    int rc = OK;
    
    if (fscanf(file, "%zu%zu", &tmp_rows, &tmp_columns) != 2)
        return ERR_IO;

    tmp_matrix = mtr_alloc(tmp_rows, tmp_columns);
    
    if (!tmp_matrix)
        return ERR_MEMORY;

    rc = mtr_read(file, tmp_matrix, tmp_rows, tmp_columns);
    if (rc != OK)
    {
        mtr_free(tmp_matrix, tmp_rows);
    }
    
    if (rc == OK)
    {
        *matrix = tmp_matrix;
        *rows = tmp_rows;
        *columns = tmp_columns;
    }

    return rc;
}

int mtr_create_ex(double ***matrix, size_t *rows, size_t *columns, const char *filename)
{
    int rc = OK;

    FILE *file = fopen(filename, "r");
    if (!file)
        return ERR_FILE;

    rc = mtr_create(matrix, rows, columns, file);

    fclose(file);

    return rc;
}


int mtr_print_ex(const char *filename, double **matrix, const size_t rows, const size_t columns)
{
    int rc = OK;

    FILE *f = fopen(filename, "w");
    if (!f)
        return ERR_FILE;
    
    rc = mtr_print(f, matrix, rows, columns);

    fclose(f);
    
    return rc;
}

int mtr_print(FILE *file, double **matrix, const size_t rows, const size_t columns)
{
    int rc = OK;
    if (fprintf(file, "%zu %zu\n", rows, columns) < 0)
        rc = ERR_IO;

    for (size_t i = 0; rc == OK && i < rows; i++)
        rc = print_row(file, matrix[i], columns);

    return rc;
}
