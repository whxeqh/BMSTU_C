#include "film_array.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Вставляет новый фильм в массив фильмов на указанную позицию
 * @param[out] films Массив фильмов
 * @param[in] length Количество элементов в массиве
 * @param[in] pos Позиция, на которую нужно вставить новый фильм
 * @param[in] new_film Указатель на новый фильм, который нужно вставить
 * @return Код ошибки
 */
static int film_insert(film_t *films, const size_t length, const size_t pos, film_t *new_film)
{
    assert(films);
    assert(pos <= length);
    
    int rc = OK;

    film_t tmp_film = { 0 };
    rc = film_copy(&tmp_film, new_film);  //Глубоко копирую фильм, который нужно вставить

    memmove(&films[pos + 1], &films[pos], (length - pos) * sizeof(film_t)); //Передвигаю срез массива вправо на 1 элемент
    
    films[pos] = tmp_film;  //Вставляю скопированный фильм по индексу

    return rc;
}

int films_create_ex(const char *filename, film_t **films, size_t *length, const comparator_t cmp)
{
    int rc = OK;
    FILE *file = fopen(filename, "r");
    if (!file)
        return ERR_FILE;
    
    rc = films_create(file, films, length, cmp);
    fclose(file);

    return rc;
}

int films_create(FILE *file, film_t **films, size_t *length, const comparator_t cmp)
{
    assert(file);

    int rc = OK;
    size_t tmp_length = 0;
    film_t *tmp_films = NULL;

    rewind(file);
    rc = films_count(file, &tmp_length);

    if (rc != OK)
        return rc;

    if (tmp_length == 0)
        return ERR_DATA;

    
    tmp_films = calloc(tmp_length, sizeof(film_t));
    if (!tmp_films)
        return ERR_MEMORY;
    
    rewind(file);
    rc = films_array_read(file, tmp_films, tmp_length, cmp);
    
    if (rc == OK)
    {
        *films = tmp_films;
        *length = tmp_length;   
    }
    else
        films_free(tmp_films, tmp_length); 
    
    return rc;
}

void films_free(film_t *films, const size_t length)
{
    for (size_t i = 0; i < length; i++)
        film_free_content(&films[i]);
    
    free(films);
    films = NULL;
}


int films_count(FILE *file, size_t *length)
{
    assert(file);

    film_t film;
    size_t count = 0;
    int rc = OK;

    memset(&film, 0, sizeof(film_t));

    while (!feof(file) && (rc = film_read(file, &film)) == OK)
    {
        film_free_content(&film);
        count++;
    }

    if (rc == OK)
        *length = count;
    
    return rc;
}

bool binary_search(size_t *pos, film_t *films, const size_t length, const film_t *pkey, const comparator_t cmp)
{
    assert(pkey);
    assert(films);
    
    bool find = false;
    int left = 0, right = length - 1, result = 0;
    size_t mid = 0;

    while (!find && left <= right)
    {
        mid = left + (right - left) / 2; 
        
        result = cmp(&films[mid], pkey);

        if (result > 0)
            right = mid - 1;
        else if (result < 0)
            left = mid + 1;
        else
        {
            // Пока справа есть фильм и он по ключу такой же, как найденный, сдвигаю позицию для вставки
            while (mid + 1 < length && cmp(&films[mid + 1], pkey) == 0)
                mid++;
            find = true;
            *pos = mid;
        }
    }

    // Если фильм найден не был. Левая граница - то, куда нужно вставить фильм
    if (!find)
        *pos = left;

    return find;
}

int films_array_read(FILE *file, film_t *films, const size_t length, const comparator_t cmp)
{
    assert(file);
    assert(films);
    
    size_t pos;
    int rc = OK;
    bool find;

    film_t tmp_film = { 0 };

    for (size_t i = 0; rc == OK && i < length; i++)
    {
        rc = film_read(file, &tmp_film);
        if (rc == OK)
            find = binary_search(&pos, films, i, &tmp_film, cmp); 
       
        if (rc == OK && find) 
            pos++; //Нужно увеличить позицию, так как из бин поиска вернется индекс последнего элемента, совпавшего с ключем, а нужно вставить после него

        if (rc == OK)
            rc = film_insert(films, i, pos, &tmp_film);
    }

    film_free_content(&tmp_film);

    return rc;
}

int films_array_print(FILE *file, const film_t *films, const size_t length)
{
    assert(file);
    assert(films);

    int rc = OK;
    for (size_t i = 0; i < length; ++i)
        rc = film_print(file, &films[i]);
    
    return rc;
}
