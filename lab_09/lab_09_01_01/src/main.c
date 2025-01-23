#include <stdio.h>
#include <stdlib.h>
#include "film.h"
#include "film_array.h"
#include "cmdline_checks.h"
#include "errors.h"

int main(int argc, char **argv)
{
    comparator_t cmp = NULL;   //Функция компаратор
    
    field_e field;             //Поле для сортировки
    
    film_t *films = NULL;      //Массив фильмов
    size_t length = 0;         //Длина массива фильмов

    film_t key = { 0 };        //Ключ для двоичного поиска. Занулен при инициализации

    int rc = OK;               //Код ошибки
    char *file_in = argv[1];   //Файл для чтения фильмов

    rc = check_args(argc, argv, &field);

    if (rc != OK)
    {
        #ifdef LOCAL_BUILD
        print_arg_info();
        #endif
        
        return rc;
    }

    switch (field)
    {
        case FIELD_TITLE:
            if (argc == 4)
                key.title = argv[3];
            cmp = film_cmp_by_title;
            break;
        case FIELD_NAME:
            if (argc == 4)
                key.name = argv[3];
            cmp = film_cmp_by_name;
            break;
        case FIELD_YEAR:
            if (argc == 4)
                key.year = atoi(argv[3]);
            cmp = film_cmp_by_year;
            break;
    }

    rc = films_create_ex(file_in, &films, &length, cmp);

    if (rc == OK)
    {
        if (argc == 3)
            rc = films_array_print(stdout, films, length);
        else
        {
            size_t pos;
            bool find = binary_search(&pos, films, length, &key, cmp); 
            if (find)
                rc = film_print(stdout, &films[pos]);
            else 
                puts("Not found");
        }
    }

    films_free(films, length);

    return rc;
}
