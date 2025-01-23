#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "film.h"
#include "film_array.h"
#include "cmdline_checks.h"
#include "errors.h"

int main(int argc, char **argv)
{
    comparator_t cmp = NULL;
    size_t length;
    field_e field;
    FILE *file;
    film_t films[MAX_LENGTH], key;
    int rc = OK;

    rc = check_args(argc, argv, &field);

    if (rc != OK)
    {
        #ifdef LOCAL_BUILD
        print_arg_info();
        #endif
        
        return rc;
    }

    memset(&key, 0, sizeof(film_t));

    switch (field)
    {
        case FIELD_NAME:
            if (argc == 4)
                strcpy(key.name, argv[3]);
            cmp = compare_film_by_name;
            break;
        case FIELD_TITLE:
            if (argc == 4)
                strcpy(key.title, argv[3]);
            cmp = compare_film_by_title;
            break;
        case FIELD_YEAR:
            cmp = compare_film_by_year;
            if (argc == 4)
                key.year = atoi(argv[3]);
            break;
    }


    file = fopen(argv[1], "r");
    if (!file)
        return ERR_IO;
        
    rc = films_array_read(file, films, &length, MAX_LENGTH, cmp);
    fclose(file);

    if (rc == OK)
    {
        if (argc == 3)
            films_array_print(stdout, films, length);
        else
        {
            size_t pos;
            bool find = binary_search(&pos, films, length, &key, cmp); 
            if (find)
                film_print(stdout, &films[pos]);
            else 
                puts("Not found");
        }
    }

    return rc;
}
