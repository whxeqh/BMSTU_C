#define _POSIX_C_SOURCE 200809L
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "film.h"

/**
 * @brief Считывает строку из файла и проверяет корректность её длины
 * @param[in] file Указатель на открытый файл
 * @param[out] str Буфер для записи строки
 *  @return Код ошибки
 */
static int read_str_from_file(FILE *file, char **str)
{
    assert(file);

    int rc = ERR_IO;
    char *buf = NULL;
    size_t length = 0;
    ssize_t read;
    
    if ((read = getline(&buf, &length, file)) == -1)
    {
        free(buf);
        return rc;
    }

    char *p = strchr(buf, '\n');
    if (p)
        *p = '\0';
    
    if (*buf)
        rc = OK;
    
    *str = buf;
    return rc;
}

/**
 * @brief Считывает год из файла и проверяет его корректность
 * @param[in] file Указатель на открытый файл
 * @param[out] year Указатель на переменную для года
 * @return Код ошибки
 */
static int read_uint_from_file(FILE *file, int *year)
{
    assert(file);

    int tmp;
    if (fscanf(file, "%d\n", &tmp) != 1)
        return ERR_IO;
    if (tmp < 0)
        return ERR_DATA;
    
    *year = tmp;
    return OK;
}

int film_init(film_t *pfilm, char *title, char *name, int year)
{
    assert(pfilm);
    assert(name);
    assert(title);

    char *ptitle = NULL, *pname = NULL;

    ptitle = strdup(title);
    pname = strdup(name);
    
    if (ptitle && pname)
    {
        film_free_content(pfilm);
        pfilm->name = pname;
        pfilm->title = ptitle;
        pfilm->year = year;
        return OK;
    }

    free(ptitle);
    free(pname);

    return ERR_MEMORY;
}

int film_copy(film_t *dst, film_t *src)
{
    return film_init(dst, src->title, src->name, src->year);
}

void film_free_content(film_t *pfilm)
{
    if (!pfilm)
        return;

    free(pfilm->name);
    free(pfilm->title);
    pfilm->name = NULL;
    pfilm->title = NULL;
}

int film_read(FILE *file, film_t *pfilm)
{
    assert(file);

    int rc = OK;
    
    char *tmp_title = NULL;
    char *tmp_name = NULL;
    int tmp_year;

    rc = read_str_from_file(file, &tmp_title);
    if (rc != OK)
        goto func_end;

    rc = read_str_from_file(file, &tmp_name);
    if (rc != OK)
        goto func_end;
    
    rc = read_uint_from_file(file, &tmp_year);
    if (rc != OK)
        goto func_end;
    
    rc = film_init(pfilm, tmp_title, tmp_name, tmp_year);

    func_end:
        free(tmp_name);
    free(tmp_title);
    return rc;
}

int film_print(FILE *file, const film_t *pfilm)
{
    assert(file);

    if (fprintf(file, "%s\n%s\n%d\n", pfilm->title, pfilm->name, pfilm->year) < 0)
        return ERR_IO;
    return OK;
}

int film_cmp_by_title(const film_t *pfirst, const film_t *psecond)
{
    assert(pfirst);
    assert(psecond);

    return strcmp(pfirst->title, psecond->title);
}
int film_cmp_by_name(const film_t *pfirst, const film_t *psecond)
{
    assert(pfirst);
    assert(psecond);

    return strcmp(pfirst->name, psecond->name);
}

int film_cmp_by_year(const film_t *pfirst, const film_t *psecond)
{
    assert(pfirst);
    assert(psecond);

    return pfirst->year - psecond->year;
}
