#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2

#define N 15

//Функция обработки ввода длина массива
int input_size(size_t *arr_size)
{
    int size;
    if (scanf("%d", &size) != 1)
        return ERR_IO;
    if (size <= 0 || size > N)
        return ERR_RANGE;
    *arr_size = size;
    return OK;
}

//Функция обработки ввода массива
int input_arr(int *a, const size_t arr_size)
{
    for (size_t i = 0; i < arr_size; i++)
        if (scanf("%d", &a[i]) != 1)
            return ERR_IO;
    return OK;
}

//Функция для обмена двух чисел по указателю
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

//Функция сортировки по условию задачи
void sort(int *a, const size_t arr_size)
{
    for (size_t i = 0; i < arr_size; i++)
    {
        for (size_t j = i + 1; j < arr_size; j++)
        {
            if (a[i] % 3 == 0 && a[j] % 3 == 0 && a[i] < a[j])
                swap(&a[i], &a[j]);
        }
    }
}

int main(void)
{
    
    int a[N], rc;
    size_t arr_size;

    rc = input_size(&arr_size);
    if (rc != OK)
        return rc;

    rc = input_arr(a, arr_size);
    if (rc != OK)
        return rc;

    sort(a, arr_size);

    printf("\n");
    for (size_t i = 0; i < arr_size; i++)
        printf("%d ", a[i]);


    return OK;
}
