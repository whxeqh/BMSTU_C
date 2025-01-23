#define _POSIX_C_SOURCE 199309L
#include <stdlib.h>
#include "sort_measurement.h"

#include "research.h"
#include "research_files.h"
#include "measurement_functions.h"

extern FILE *file_data_mysort[num_files];
extern FILE *file_data_qsort[num_files];

extern char *mysort_out_filenames[num_files];
extern char *mysort_in_filenames[num_files];

extern char *qsort_out_filenames[num_files];
extern char *qsort_in_filenames[num_files];


//Допущение: файлы должны быть открыты на момент вызова этой функии
void print_stats(const size_t reps)
{   
    open_data_files("r");
    printf(BOLD GREEN "\nСортировка и сбор данных прошел успешно!\n" RESET);
    printf(BOLD MAGENTA "Снизу представлены таблицы с результатами.\n\n" RESET);

    for (size_t i = 0; i < num_files; ++i)
    {
        switch (i)
        {
        case random:
            printf(BOLD "Зависимость времени сортировки от кол-ва элементов при случайном распределении данных:\n\n" RESET);
            break;
        case sorted:
            printf(BOLD"\nЗависимость времени сортировки от кол-ва элементов при упорядоченном распределении данных:\n\n" RESET);
            break;
        case reverse:
            printf(BOLD"\nЗависимость времени сортировки от кол-ва элементов при упорядоченном в обратном порядке распределении данных:\n\n"RESET);
            break;
        }

        printf("--------------------------------------------------------\n");
        printf("| Кол-во элементов |    mysort, мкс   |   qsort, мкс   |\n");
        printf("--------------------------------------------------------\n");

        size_t num_elements_mysort = 0, num_elements_qsort = 0;
        unsigned long long mysort_time, qsort_time;

        rewind(file_data_mysort[i]);
        rewind(file_data_qsort[i]);
        // Проходим по всем элементам массива
        for (size_t j = 0; j < reps; j++)
        {
            fscanf(file_data_mysort[i], "%zu %llu\n", &num_elements_mysort, &mysort_time);
            fscanf(file_data_qsort[i], "%zu %llu\n", &num_elements_qsort, &qsort_time);
            //printf("%ld %ld\n", num_elements_mysort, num_elements_qsort);
            if (num_elements_mysort != num_elements_qsort)
            {
                puts(RED "ERORR NUM ELEMENTS" RESET);
                exit(1);
            }
            printf("| %16lu | %15llu | %15llu |\n", num_elements_mysort, mysort_time, qsort_time);
        }

        printf("--------------------------------------------------------\n");
    }
    printf(BOLD GREEN "\nИсследование проведено успешно!\n" RESET);
    printf(BOLD CYAN "Результаты сохранены в соответствующих файлах.\n\n" RESET);
    close_data_files();
}


void make_research(const int *reps, const size_t length)
{   
    unsigned long long time_mysort, time_qsort;   

    open_data_files("w");

    for (size_t i = 0; i < length; ++i)
    {
        // Случайный порядок
        {
            time_mysort = sort_measurement(reps[i], ITERATIONS, mysort_in_filenames[random], mysort_out_filenames[random], init_random, mysort);
            time_qsort = sort_measurement(reps[i], ITERATIONS, qsort_in_filenames[random], qsort_out_filenames[random], init_random, qsort);

            printf("Среднее время для " BOLD "%u" RESET " элементов mysort рандомный порядок: " BOLD "%llu" RESET ", qsort радномный порядок = " BOLD "%llu" RESET "\n", reps[i], time_mysort, time_qsort);
            fprintf(file_data_mysort[random], "%u %llu\n", reps[i], time_mysort);
            fprintf(file_data_qsort[random], "%u %llu\n", reps[i], time_qsort);
        }

        // Обратный порядок
        {
            time_mysort = sort_measurement(reps[i], ITERATIONS, mysort_in_filenames[reverse], mysort_out_filenames[reverse], init_reversed, mysort);
            time_qsort = sort_measurement(reps[i], ITERATIONS, qsort_in_filenames[reverse], qsort_out_filenames[reverse], init_reversed, qsort);

            printf("Среднее время для " BOLD "%u" RESET " элементов mysort обратный порядок: " BOLD "%llu" RESET ", qsort обратный порядок = " BOLD "%llu" RESET "\n", reps[i], time_mysort, time_qsort);
            fprintf(file_data_mysort[reverse], "%u %llu\n", reps[i], time_mysort);
            fprintf(file_data_qsort[reverse], "%u %llu\n", reps[i], time_qsort);
        }

        // Отсортированный порядок
        {
            time_mysort = sort_measurement(reps[i], ITERATIONS, mysort_in_filenames[sorted], mysort_out_filenames[sorted], init_sorted, mysort);
            time_qsort = sort_measurement(reps[i], ITERATIONS, qsort_in_filenames[sorted], qsort_out_filenames[sorted], init_sorted, qsort);

            printf("Среднее время для " BOLD "%u" RESET " элементов mysort отсортированный порядок: " BOLD "%llu" RESET ", qsort отсортированый порядок = " BOLD "%llu" RESET "\n\n", reps[i], time_mysort, time_qsort);
            fprintf(file_data_mysort[sorted], "%u %llu\n", reps[i], time_mysort);
            fprintf(file_data_qsort[sorted], "%u %llu\n", reps[i], time_qsort);
        }
    }
    close_data_files();
}