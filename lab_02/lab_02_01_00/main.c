#include <stdio.h>
#include <stdbool.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define NO_ODD_ERROR 3

#define N 10

int input_array_size(size_t *arr_size);
int input_array(const size_t arr_size, int *a);
int arr_summ(const size_t arr_size, const int *a, int *ans);
void print_err(const int rc);

int main(void)
{
    int arr[N];
    int rc = OK, ans = 0;
    size_t arr_size;
    rc = input_array_size(&arr_size);
    if (rc == OK)
        rc = input_array(arr_size, arr);
    if (rc == OK)
        rc = arr_summ(arr_size, arr, &ans);
    if (rc == OK)
        printf("Сумма четных элементов массива равна: %d\n", ans);
    else
        print_err(rc);

    return rc;
}

/*
  Функция ввода длины массива. 
  Принимает указатель на длину массива.
  Возвращает код ошибки.
*/
int input_array_size(size_t *arr_size)
{
    int size;
    printf("Введите количество элементов массива: ");
    if (scanf("%d", &size) != 1)
        return ERR_IO;
    else if (size <= 0 || size > N)
        return ERR_RANGE;
    *arr_size = size;
    return OK;
}

/*
  Функция ввода массива.
  Принимает длину массива и указатель на его первый элемент.
  Возвращает код ошибки.
*/
int input_array(const size_t arr_size, int *arr)
{
    printf("Вводите элементы массива: ");
    for (size_t i = 0; i < arr_size; i++) 
        if (scanf("%d", &arr[i]) != 1)
            return ERR_IO;
    return OK;
}

/*
  Функция подсчёта суммы чётных элементов массива, кратных двум. 
  Принимает длину массива, указатель на первый элемент массива и указатель целое число.
  Возвращает код ошибки.
*/
int arr_summ(const size_t arr_size, const int *arr, int *ans)
{
    int rc = NO_ODD_ERROR;
    for (size_t i = 0; i < arr_size; i++)
        if (arr[i] % 2 == 0)
        {
            *ans += arr[i];
            rc = OK;
        }
    return rc;
}

/*
  Функция вывода сообщений об ошибке в консоль.
  Принимает код ошибки.
  Ничего не возвращает. 
*/
void print_err(const int rc)
{
    if (rc == ERR_IO)
        printf("Неверный ввод\n");
    else if (rc == ERR_RANGE)
        printf("Неверный диапазон\n");
    else if (rc == NO_ODD_ERROR)
        printf("Нет четных чисел\n");
    else 
        printf("Неизвестня ошибка (%d)\n", rc);
}
