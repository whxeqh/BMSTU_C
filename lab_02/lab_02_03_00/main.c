#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define ERR_EMPTY_ARRAY 3

#define N 10

int input_array_size(size_t *arr_size);
int input_array(const size_t arr_size, int *arr);
bool is_palindrome(const int num);
void delete_elem(int *arr, size_t *arr_size, const size_t pos);
void edit_array(size_t *arr_size, int *arr);
void print_error(const int rc);
void print_array(const size_t arr_size, const int *arr);

int main(void) 
{
    size_t arr_size = 0;
    int rc = OK, arr[N];

    rc = input_array_size(&arr_size);
    if (rc == OK)
        rc = input_array(arr_size, arr);
    if (rc == OK)
        edit_array(&arr_size, arr);
    if (rc == OK && arr_size == 0)
        rc = ERR_EMPTY_ARRAY;
    if (rc == OK)
        print_array(arr_size, arr);
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
  Принимает указатель на первый элемент.
  Возвращает возвращает код ошибки.
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
  Функция определяет, является ли число палиндромом. 
  Принимает целое число 
  Возвращает true, если число палиндром и false в противоположном случае
*/
bool is_palindrome(const int num)
{    
    if (num < 0)
        return false;
        
    int j, b = 0, new_num = num;
    for (unsigned int i = new_num; i > 0; i /= 10) 
    {
        j = i % 10;
        b = b * 10 + j;
    }
    return new_num == b;
}

/*
  Функция удаления элемента по индексу. Сдвигает все элементы справа стоящие от pos влево на 1 позицию
  Принимает массив, длину массива и позицию для удаления
  Изменяет массив
*/
void delete_elem(int *arr, size_t *arr_size, const size_t pos)
{
    for (size_t i = pos; i < (*arr_size) - 1; i++)
        arr[i] = arr[i + 1];
    (*arr_size)--;
}

/*
  Функция удаляет из массива числа, являющиеся палиндромами. 
  Принимает длину массива и указатель на его первый элемент 
*/
void edit_array(size_t *arr_size, int *arr)
{
    size_t r = 0;
    while (r < *arr_size)
    {
        if (is_palindrome(arr[r]))
            delete_elem(arr, arr_size, r);
        else
            r++;
    }
}

/*
  Функция вывода сообщений об ошибки в консоль.
  Принимает код ошибки.
  Ничего не изменяет. 
*/
void print_error(const int rc)
{
    if (rc == ERR_IO)
        printf("Неверный ввод\n");
    else if (rc == ERR_RANGE)
        printf("Неверный диапазон\n");
    else if (rc == ERR_EMPTY_ARRAY)
        printf("Массив стал пустым\n");
    else
        printf("Неизвестная ошибка (%d)\n", rc);
}

/*
  Функция вывода массива в консоль.
  Принимает длину и указатель на первый элемент.
  Ничего не изменяет. 
*/
void print_array(const size_t arr_size, const int *arr)
{
    printf("Элементы массива: \n");
    for (size_t i = 0; i < arr_size; i++)
        printf("%d ", arr[i]);
}
