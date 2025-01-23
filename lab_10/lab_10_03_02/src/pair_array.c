#define _POSIX_C_SOURCE 200809L

#include "pair_array.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>

void pair_free_content(pair_t *elem)
{
    free(elem->key);
    elem->key = NULL;
}

assoc_array_error_t pair_dup_data(pair_t *elem, const char *key, int value)
{
    assert(elem);

    elem->key = strdup(key);
    if (!elem->key)
        return ASSOC_ARRAY_MEM;
    
    elem->value = value;

    return ASSOC_ARRAY_OK;
}

pair_array_t *pair_array_create(void)
{
    pair_array_t *arr = malloc(sizeof(pair_array_t));
    if (!arr)
        return NULL;
    
    pair_array_init(arr);

    return arr;
}

void pair_array_init(pair_array_t *parr)
{
    assert(parr);

    parr->data = NULL;
    parr->length = 0;
    parr->allocated = 0;
}

assoc_array_error_t pair_array_push_back(pair_array_t *parr, pair_t *elem)
{
    assert(elem);

    if (!parr->data)
    {
        parr->data = malloc(sizeof(pair_t) * DA_INIT_SIZE);
        if (!parr->data)
            return ASSOC_ARRAY_MEM;
        parr->allocated = DA_INIT_SIZE;
    }

    if (parr->length >= parr->allocated)
    {
        void *tmp = realloc(parr->data, parr->allocated * DA_STEP * sizeof(pair_t));
        if (!tmp)
            return ASSOC_ARRAY_MEM;
        parr->data = tmp;
        parr->allocated *= DA_STEP;
    }
    parr->data[parr->length] = *elem;
    parr->length++;
    
    return ASSOC_ARRAY_OK;
}

void pair_array_delete(pair_array_t *parr, int index)
{
    assert(parr);
    assert(index != -1);

    pair_free_content(&parr->data[index]);
    
    memmove(parr->data + index, parr->data + index + 1, (parr->length - index - 1) * sizeof(pair_t));
    
    parr->length--;
}

int pair_array_search(pair_array_t *parr, const char *key)
{
    if (!parr)
        return -1;
        
    for (size_t i = 0; i < parr->length; i++)
        if (strcmp(parr->data[i].key, key) == 0)
            return i;
    
    return -1;
}

void pair_array_clear(pair_array_t *parr)
{
    if (!parr)
        return; 
    for (size_t i = 0; i < parr->length; i++)
    {
        pair_free_content(&parr->data[i]);
    }
    
    parr->length = 0;
    parr->allocated = 0;

    free(parr->data);
    parr->data = NULL;
}

void pair_array_destroy(pair_array_t **parr)
{
    if (!parr || !*parr)
        return; 

    pair_array_clear(*parr);

    free(*parr);
    *parr = NULL;
}

void pair_array_apply(pair_array_t *parr, void (*action)(const char *key, int *num, void *param), void *param)
{
    assert(parr);
    assert(action);

    for (size_t i = 0; i < parr->length; i++)
        action(parr->data[i].key, &parr->data[i].value, param);
}

pair_t *pair_array_search_min(pair_array_t *parr)
{
    assert(parr);

    if (!parr->length)
        return NULL;

    pair_t *min = &parr->data[0];

    for (size_t i = 1; i < parr->length; i++)
    {
        if (strcmp(parr->data[i].key, min->key) < 0)
            min = &parr->data[i];
    }

    return min;
}

pair_t *pair_array_search_max(pair_array_t *parr)
{
    assert(parr);

    if (!parr->length)
        return NULL;

    pair_t *max = &parr->data[0];

    for (size_t i = 1; i < parr->length; i++)
    {
        if (strcmp(parr->data[i].key, max->key) > 0)
            max = &parr->data[i];
    }

    return max;
}