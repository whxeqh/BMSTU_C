#include <stdlib.h>
#include "research_files.h"
#include "errors.h"

// Глобальные массивы для хранения указателей на файлы
FILE *file_data_mysort[num_files];
FILE *file_data_qsort[num_files];

// Выходные файлы для mysort
char *mysort_out_filenames[num_files] = {
    "research/data/mysort/random_order/%u_out.txt",
    "research/data/mysort/reverse_order/%u_out.txt",
    "research/data/mysort/sorted_order/%u_out.txt"
};
// Исходные файлы для mysort
char *mysort_in_filenames[num_files] = {
    "research/data/mysort/random_order/%u_in.txt",
    "research/data/mysort/reverse_order/%u_in.txt",
    "research/data/mysort/sorted_order/%u_in.txt"
};

// Выходные файлы для qsort
char *qsort_out_filenames[num_files] = {
    "research/data/qsort/random_order/%u_out.txt",
    "research/data/qsort/reverse_order/%u_out.txt",
    "research/data/qsort/sorted_order/%u_out.txt"
};

// Исходные файлы для qsort
char *qsort_in_filenames[num_files] = {
    "research/data/qsort/random_order/%u_in.txt",
    "research/data/qsort/reverse_order/%u_in.txt",
    "research/data/qsort/sorted_order/%u_in.txt"
};


void print_arr_in_file(const int *arr, const size_t length, const char *filename)
{
    size_t size = snprintf(NULL, 0, filename, length);
    char *file_name = malloc((size + 1) * sizeof(char));
    snprintf(file_name, size + 2, filename, length);

    FILE *file_out = fopen(file_name, "w");
    free(file_name);

    for (size_t i = 0; i < length; ++i)
        fprintf(file_out, "%d\n", arr[i]);
    fclose(file_out);
}

int open_data_files(const char *mode)
{
    char *mysort_data_filenames[num_files] = {
        "research/data/mysort/random_order/data.txt",
        "research/data/mysort/reverse_order/data.txt",
        "research/data/mysort/sorted_order/data.txt"
    };

    char *qsort_data_filenames[num_files] = {
        "research/data/qsort/random_order/data.txt",
        "research/data/qsort/reverse_order/data.txt",
        "research/data/qsort/sorted_order/data.txt"
    };

    //Файлы с данными о кол-ве элементов и времени сортировки для моей сортировки:
    for (size_t i = 0; i < num_files; i++)
    {
        file_data_mysort[i] = fopen(mysort_data_filenames[i], mode);
        if (!file_data_mysort[i])
            return ERR_FILE;
    }

    //----------------------------------------------------------------------------------//

    for (size_t i = 0; i < num_files; i++)
    {
        file_data_qsort[i] = fopen(qsort_data_filenames[i], mode);
        if (!file_data_qsort[i])
            return ERR_FILE;
    }
    return OK;
}

void close_data_files(void)
{
    // Закрываею файлы для mysort
    for (size_t i = 0; i < num_files; i++)
    {
        if (file_data_mysort[i])
        {
            fclose(file_data_mysort[i]);
            file_data_mysort[i] = NULL;
        }
    }

    // Закрываю файлы для qsort
    for (size_t i = 0; i < num_files; i++)
    {
        if (file_data_qsort[i])
        {
            fclose(file_data_qsort[i]);
            file_data_qsort[i] = NULL;
        }
    }
}

void print_arr(FILE *file, const int *arr, const size_t length)
{
    for (size_t i = 0; i < length; ++i)
        fprintf(file, "%d\n", arr[i]);
}