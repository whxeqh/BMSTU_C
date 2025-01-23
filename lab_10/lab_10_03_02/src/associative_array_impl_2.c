#include <stdlib.h>
#include <string.h>

#include "associative_array.h"
#include "pair_array.h"


struct assoc_array_type
{
    pair_array_t *parr;
};

assoc_array_t assoc_array_create(void)
{
    assoc_array_t assoc_array = malloc(sizeof(struct assoc_array_type));
    if (!assoc_array)
        return NULL;
    
    assoc_array->parr = pair_array_create();
    if (!assoc_array->parr)
    {
        free(assoc_array);
        return NULL;
    }

    return assoc_array;
}

void assoc_array_destroy(assoc_array_t *assoc_array)
{
    if (!assoc_array || !*assoc_array)
        return;

    assoc_array_clear(*assoc_array);

    free((*assoc_array)->parr);
    (*assoc_array)->parr = NULL;

    free(*assoc_array);
    *assoc_array = NULL;
}

assoc_array_error_t assoc_array_insert(assoc_array_t assoc_array, const char *key, int num)
{
    assoc_array_error_t rc = ASSOC_ARRAY_OK;
    if (!assoc_array || !key || !strlen(key))
    {
        rc = ASSOC_ARRAY_INVALID_PARAM;
        goto func_end;
    }

    pair_array_t *tmp_pair_array = assoc_array->parr;
    if (pair_array_search(tmp_pair_array, key) >= 0)
    {
        rc = ASSOC_ARRAY_KEY_EXISTS;
        goto func_end;
    }

    pair_t pair;

    rc = pair_dup_data(&pair, key, num);
    if (rc != ASSOC_ARRAY_OK)
        goto func_end;

    pair_array_push_back(tmp_pair_array, &pair);
    assoc_array->parr = tmp_pair_array;
    
    func_end:
        return rc;
}

assoc_array_error_t assoc_array_find(const assoc_array_t assoc_array, const char *key, int **num)
{
    if (!assoc_array || !key || !num || !strlen(key))
        return ASSOC_ARRAY_INVALID_PARAM;
    
    int index = pair_array_search(assoc_array->parr, key);
    if (index < 0)
        return ASSOC_ARRAY_NOT_FOUND;
    
    *num = &assoc_array->parr->data[index].value;

    return ASSOC_ARRAY_OK; 
}

assoc_array_error_t assoc_array_remove(assoc_array_t assoc_array, const char *key)
{
    if (!assoc_array || !key || !strlen(key))
        return ASSOC_ARRAY_INVALID_PARAM;
    
    int index = pair_array_search(assoc_array->parr, key);
    if (index < 0)
        return ASSOC_ARRAY_NOT_FOUND;
    
    pair_array_t *tmp_pair_array = assoc_array->parr;

    pair_array_delete(tmp_pair_array, index);

    assoc_array->parr = tmp_pair_array;

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_clear(assoc_array_t assoc_array)
{
    if (!assoc_array)
        return ASSOC_ARRAY_INVALID_PARAM;

    pair_array_t *pair_array = assoc_array->parr;

    pair_array_clear(pair_array);

    return ASSOC_ARRAY_OK;
}


assoc_array_error_t assoc_array_each(const assoc_array_t assoc_array, void (*action)(const char *key, int *num, void *param), void *param)
{  
    if (!assoc_array || !action)
        return ASSOC_ARRAY_INVALID_PARAM;
    
    pair_array_apply(assoc_array->parr, action, param);

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_min(const assoc_array_t assoc_array, int **num)
{
    if (!assoc_array || !num)
        return ASSOC_ARRAY_INVALID_PARAM;
    
    pair_t *pair = pair_array_search_min(assoc_array->parr);
    if (!pair)
        return ASSOC_ARRAY_NOT_FOUND;
    
    *num = &pair->value;

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_max(const assoc_array_t assoc_array, int **num)
{
    if (!assoc_array || !num)
        return ASSOC_ARRAY_INVALID_PARAM;
    
    pair_t *pair = pair_array_search_max(assoc_array->parr);
    if (!pair)
        return ASSOC_ARRAY_NOT_FOUND;
    
    *num = &pair->value;
    
    return ASSOC_ARRAY_OK;
}