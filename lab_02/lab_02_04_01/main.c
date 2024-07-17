#include <stdio.h>

#define OK 0
#define ERR_EMPTY_ARRAY 1
#define SPECIAL_CODE 100

#define N 10

int input_array(size_t *arr_size, int *a);
void insertion_sort(const size_t arr_size, int *a);
void swap(int *a, int *b);
void selection_sort(const size_t arr_size, int *a);
void print_err(const int rc);
void print_array(const size_t arr_size, const int *a);

int main(void) 
{
    size_t arr_size = 0;
    int rc, arr[N];
    rc = input_array(&arr_size, arr);
    selection_sort(arr_size, arr);
    if (rc == OK || rc == SPECIAL_CODE)
        print_array(arr_size, arr);
    else
        print_err(rc);
    
    return rc;
}

/*
  Функция ввода массива.
  Принимает указатель на первый элемент.
  Возвращает возвращает код ошибки.
*/
int input_array(size_t *arr_size, int *arr)
{
    printf("Вводите элементы массива по концевому признаку:\n");
    int rc = OK, temp;
    size_t i;
    for (i = 0; i < N && (scanf("%d", &arr[i]) == 1); i++);
    *arr_size = i;
    if (scanf("%d", &temp) == 1)
        rc = SPECIAL_CODE;
    if (i == 0)
        rc = ERR_EMPTY_ARRAY;
    return rc;
}

/*
  Функция сортировки вставками. 
  Принимает длину массива и указатель на первый элемент
  Изменяет массив
*/
/*void insertion_sort(const size_t arr_size, int *arr)
{
    int j;
    for (size_t i = 1; i < arr_size; i++)
    {
        int temp = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > temp)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}*/

/*
  Функция обмена значениями двух переменных по указателю
*/
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/*
  Функция сортировки выбором. Принимает длину массива и сам массив
*/
void selection_sort(const size_t arr_size, int *arr)
{
    for (size_t i = 0; i < arr_size; i++)
    {
        int min_elem = arr[i];
        size_t new_id = i;
        for (size_t j = i + 1; j < arr_size; j++)
        {
            if (arr[j] < min_elem)
            {
                min_elem = arr[j];
                new_id = j;
            }
        }
        if (i != new_id)
            swap(&arr[i], &arr[new_id]);
    }
}

/*
  Функция вывода сообщений об ошибки в консоль.
  Принимает код ошибки.
  Ничего не возвращает. 
*/
void print_err(const int rc)
{
    if (rc == ERR_EMPTY_ARRAY)
        printf("Массив пустой\n");
    else
        printf("Неизвестная ошибка (%d)\n", rc);
}

/*
  Функция вывода массива в консоль.
  Принимает длину и указатель на первый элемент.
  Ничего не возвращает. 
*/
void print_array(const size_t arr_size, const int *arr)
{
    printf("Отсортированный массив:\n");
    for (size_t i = 0; i < arr_size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
