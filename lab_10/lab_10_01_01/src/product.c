#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "product.h"
#include "errors.h"
#include "macro.h"

static int read_str(FILE *file, char **str)
{
    int rc = ERR_IO;
    size_t length;
    ssize_t read;
    char *buf = NULL;

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

static int read_uint(FILE *file, int *price)
{
    int tmp;
    if (fscanf(file, "%d\n", &tmp) != 1)
        return ERR_IO;
    
    if (tmp < 0)
        return ERR_RANGE;
    
    *price = tmp;
    return OK;
}

int product_init(product_t *pelem, char *name, int price)
{
    assert(pelem);
    assert(name);

    char *pname = NULL;

    pname = strdup(name);
    
    if (pname)
    {
        product_free_content(pelem);
        pelem->name = pname;
        pelem->price = price;
        
        return OK;
    }

    return ERR_MEMORY;
}


int product_copy(product_t *pdst, product_t *psrc)
{
    return product_init(pdst, psrc->name, psrc->price);
}

int product_read(FILE *file, product_t *pelem)
{
    assert(file);

    int rc = OK;
    char *tmp_name = NULL;
    int tmp_price;

    rc = read_str(file, &tmp_name);
    if (rc != OK)
    {
        LOG_PRINT_ERR("Ошибка при чтении строки из файла, rc = %d", rc);
        goto func_end;
    }

    rc = read_uint(file, &tmp_price);
    if (rc != OK)
    {
        LOG_PRINT_ERR("Ошибка при чтении числа из файла, rc = %d", rc);
        goto func_end;
    }

    rc = product_init(pelem, tmp_name, tmp_price);

    func_end:
        free(tmp_name);
    return rc;
}

void product_free_content(product_t *pelem)
{
    if (!pelem)
        return;

    free(pelem->name);
    pelem->name = NULL;
}

int product_print(FILE *file, const product_t *elem)
{
    assert(elem);
    assert(file);

    int rc = OK;
    if (fprintf(file, "%s\n%d\n", elem->name, elem->price) < 0)
        rc = ERR_IO;
    
    return rc;
}

int cmp_products_by_name(const void *pleft, const void *pright)
{
    const product_t *left = pleft;
    const product_t *right = pright;
    
    return strcmp(left->name, right->name);
}

int cmp_products_by_price(const void *pleft, const void *pright)
{
    const product_t *left = pleft;
    const product_t *right = pright;
    
    return left->price - right->price;
}
