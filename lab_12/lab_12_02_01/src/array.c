#include "array.h"

#include <stdbool.h>
#include <math.h>
#include <assert.h>

static void swap_int(int *l, int *r)
{
    int tmp = *l;
    *l = *r;
    *r = tmp;
}

static void reverse(int *arr, int start, int end)
{
    while (start < end)
    {
        swap_int(&arr[start], &arr[end]);
        start++;
        end--;
    }
}

void cyclic_shift(int *arr, const size_t len, const size_t k)
{
    assert(arr);
    assert(len);

    size_t shift = k % len; 

    reverse(arr, 0, shift - 1);
    reverse(arr, shift, len - 1);
    reverse(arr, 0, len - 1);
}

static bool check_sqrt(const int num)
{
    if (num < 0)
        return false;

    for (int i = 0; i * i <= num; i++)
    {
        if (i * i == num)
            return true;
    }

    return false;
}



int filter(const int *src, size_t src_len, int *dst, size_t *dst_len)
{
    assert(src);
    assert(dst_len);

    size_t n = 0;

    for (size_t i = 0; i < src_len; i++)
    {
        if (check_sqrt(src[i]))
            n++;
    }

    if (n > *dst_len)
    {
        *dst_len = n;
        return FILTER_NEW_DST_LENGTH;
    }

    n = 0;
    for (size_t i = 0; i < src_len; i++)
    {
        if (check_sqrt(src[i]))
        {
            dst[n++] = src[i];
        }
    }
    
    *dst_len = n;

    return FILTER_SUCCESS;
}
