// gnu99
#define _POSIX_C_SOURCE 199309L
#include "errors.h"
#include "sort_measurement.h"
#include "research_files.h"
#include "measurement_functions.h"
#include <stdio.h>
#include <time.h>

unsigned long long sort_measurement(const size_t length, const size_t reps, const char *filename_in, const char *filename_out, init_array_t init_array, uni_sort_t uni_sort)
{
    unsigned long long summ = 0;
    srand(time(NULL));
    struct timespec t_beg, t_end;
    int *src_arr = malloc(length * sizeof(int));
    if (!src_arr)
    {
        printf("Memory allocation error in file: %s\n Line: %d\n", __FILE__, __LINE__);
        exit(ERR_MEMORY);
    }

    int *arr = malloc(length * sizeof(int));
    if (!arr)
    {
        free(src_arr);
        printf("Memory allocation error in file: %s\n Line: %d\n", __FILE__, __LINE__);
        exit(ERR_MEMORY);
    }

    init_array(length, src_arr);
    print_arr_in_file(src_arr, length, filename_in);

    for (size_t i = 0; i < reps + 10; i++)
    {
        appropriate(length, arr, src_arr);

        clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
        uni_sort(arr, length, sizeof(arr[0]), cmp_uni_int);
        clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

        unsigned long long time = calc_elapsed_time(&t_beg, &t_end);

        if (i >= 10)
            summ += time;
    }

    print_arr_in_file(arr, length, filename_out);

    free(src_arr);
    free(arr);

    return summ / reps;
}
