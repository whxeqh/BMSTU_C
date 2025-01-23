#include "measurement_functions.h"

unsigned long long calc_elapsed_time(const struct timespec *beg, const struct timespec *end)
{
    return ((unsigned long long)
        (end->tv_sec - beg->tv_sec) * 1000 * 1000 * 1000 + (end->tv_nsec - beg->tv_nsec)) / 1000; 
}

void init_random(const size_t size, int *arr)
{
    for (size_t i = 0; i < size; i++)
        arr[i] = rand() % 1000007;
}

void init_sorted(const size_t length, int *arr)
{
    for (size_t i = 0; i < length; ++i)
    {
        arr[i] = i;
    }
}

void init_reversed(const size_t length, int *arr)
{
    for (size_t i = 0; i < length; ++i)
    {
        arr[i] = length - i;
    }
}

void appropriate(const size_t size, int *arr, const int *src_arr)
{
    for (size_t i = 0; i < size; i++)
        arr[i] = src_arr[i];
}
