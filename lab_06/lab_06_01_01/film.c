#include <string.h>
#include "film.h"

/**
 * @brief Считывает строку из файла и проверяет корректность её длины
 * @param[in] file Указатель на открытый файл
 * @param[out] str Буфер для записи строки
 * @param[in] max_len Максимальная длина строки, которую можно считать
 * @return Код ошибки
 */
static int read_str_from_file(FILE *file, char *str, const size_t max_len)
{
    if (!fgets(str, max_len, file))
        return ERR_IO;
    char *p = strchr(str, '\n');
    if (!p)
        return ERR_OWERFLOW;
    *p = '\0';

    if (str[0] == '\0')
        return ERR_RANGE;
    return OK;
}

/**
 * @brief Считывает год из файла и проверяет его корректность
 * @param[in] file Указатель на открытый файл
 * @param[out] year Указатель на переменную для года
 * @return Код ошибки
 */
static int read_year_from_file(FILE *file, int *year)
{
    int tmp;
    if (fscanf(file, "%d\n", &tmp) != 1)
        return ERR_IO;
    if (tmp < 0)
        return ERR_DATA;
    
    *year = tmp;
    return OK;
}

int film_read(FILE *file, film_t *pfilm)
{
    int rc = OK;
    
    char tmp_title[MAX_TITLE_LEN + 2];
    char tmp_name[MAX_NAME_LEN + 2];
    int tmp_year;

    rc = read_str_from_file(file, tmp_title, sizeof(tmp_title));
    if (rc != OK)
        return rc;
    rc = read_str_from_file(file, tmp_name, sizeof(tmp_name));
    if (rc != OK)
        return rc;
    rc = read_year_from_file(file, &tmp_year);
    
    if (rc == OK)
    {
        strcpy(pfilm->title, tmp_title);
        strcpy(pfilm->name, tmp_name);
        pfilm->year = tmp_year;
    }
    return rc;
}

void film_print(FILE *file, const film_t *pfilm)
{
    fprintf(file, "%s\n%s\n%d\n", pfilm->title, pfilm->name, pfilm->year);
}

int compare_film_by_title(const film_t *first, const film_t *second)
{
    return strcmp(first->title, second->title);
}
int compare_film_by_name(const film_t *first, const film_t *second)
{
    return strcmp(first->name, second->name);
}

int compare_film_by_year(const film_t *first, const film_t *second)
{
    return first->year - second->year;
}
