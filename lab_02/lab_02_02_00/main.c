#include <stdio.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define ERR_EMPTY_ARRAY 3

#define N 10

int input_array_size(size_t *arr_size);
int input_array(const size_t arr_size, int *a);
size_t new_array(const size_t arr_size, const int *a, int *new_a, const float middle);
float mid_value_array(const size_t arr_size, const int *a);
void print_error(const int rc);
void print_array(const size_t arr_size, const int *a);

int main(void)
{
    int a[N], new_a[N];
    int rc = OK;
    float middle;
    size_t arr_size, new_arr_size;

    rc = input_array_size(&arr_size);
    if (rc == OK)
        rc = input_array(arr_size, a);
    if (rc == OK)
    {
        middle = mid_value_array(arr_size, a);
        new_arr_size = new_array(arr_size, a, new_a, middle);
        if (new_arr_size == 0)
            rc = ERR_EMPTY_ARRAY;
    }
    if (rc == OK)
        print_array(new_arr_size, new_a);
    else
        print_error(rc);

    return rc;
}

/*
  Функция ввода длины массива. 
  Принимает указатель на длину массива.
  Возвращает код ошибки
*/
int input_array_size(size_t *arr_size)
{
    int size;
    printf("Введите размер массива: ");
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
  Возвращает возвращает код ошибки.
*/
int input_array(const size_t arr_size, int *a)
{
    printf("Вводите элементы массива: ");
    for (size_t i = 0; i < arr_size; i++)
        if (scanf("%d", &a[i]) != 1)
            return ERR_IO;
    return OK;
}

/*
  Функция получения среднего арифметического числа массива
  Принимает длину массива и указатель на первый элемент массива
  Возвращает среднее арифметическое массива
*/
float mid_value_array(const size_t arr_size, const int *a)
{
    float middle = 0.0;
    for (size_t i = 0; i < arr_size; i++)
        middle += a[i];
    middle /= arr_size;

    return middle;
}
/*
  Функция формирует новый массив, в который попадают элементы из массива (a), 
  которые больше среднего арифметического (middle) этого массива
  Функция принимает длину массивов, сами массивы и среднее арифметическое
  Возвращает новую длину массива
*/
size_t new_array(const size_t arr_size, const int *a, int *new_a, const float middle)
{
    size_t new_arr_size = 0;
    for (size_t i = 0; i < arr_size; i++)
        if (a[i] > middle)
            new_a[new_arr_size++] = a[i];
    
    return new_arr_size;
}

/*
  Функция вывода сообщений об ошибки в консоль.
  Принимает код ошибки.
  Ничего не возвращает. 
*/
void print_error(const int rc)
{
    if (rc == ERR_IO)
        printf("Неверный ввод\n");
    else if (rc == ERR_RANGE)
        printf("Неверный диапазон\n");
    else if (rc == ERR_EMPTY_ARRAY)
        printf("Нет элементов, больших среднего арифметического\n");
    else
        printf("Неизвестная ошибка (%d)\n", rc);
}

/*
  Функция вывода массива в консоль.
  Принимает длину и указатель на первый элемент.
  Ничего не возвращает. 
*/
void print_array(const size_t arr_size, const int *a)
{
    printf("Элементы массива: ");
    for (size_t i = 0; i < arr_size; i++)
        printf("%d ", a[i]);
    printf("\n");
}
