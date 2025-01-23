#include "film_array.h"

/**
 * @brief Вставляет новый фильм в массив фильмов на указанную позицию
 * @param[out] films Массив фильмов
 * @param[in] length Количество элементов в массиве
 * @param[in] pos Позиция, на которую нужно вставить новый фильм
 * @param[in] length_max Максимальное количество элементов массива
 * @param[in] new_film Указатель на новый фильм, который нужно вставить
 * @return true, если запись прошла успешно, false в ином случае
 */
static bool film_insert(film_t *films, const size_t length, const size_t length_max, const size_t pos, const film_t *new_film)
{
    if (length >= length_max || pos > length)
        return false;

    for (size_t i = length; i > pos; --i)
        films[i] = films[i - 1];
    
    films[pos] = *new_film;

    return true;
}

bool binary_search(size_t *pos, film_t *films, const size_t length, const film_t *pkey, const comparator_t cmp)
{
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

int films_array_read(FILE *file, film_t *films, size_t *length, const size_t length_max, const comparator_t cmp)
{
    size_t i = 0, pos;
    film_t tmp;
    int rc = OK;
    do
    {
        rc = film_read(file, &tmp);
        if (rc != OK)
            return rc;

        bool find = binary_search(&pos, films, i, &tmp, cmp); 
        if (find) 
            pos++; //Нужно увеличить позицию, так как из бин поиска вернется индекс последнего элемента, совпавшего с ключем, а нужно вставить после него

        if (!film_insert(films, i++, length_max, pos, &tmp))
            return ERR_RANGE;
    } while (!feof(file));
    
    
    *length = i;

    return OK;
}

void films_array_print(FILE *file, const film_t *films, const size_t length)
{
    for (size_t i = 0; i < length; ++i)
        film_print(file, &films[i]);
}

