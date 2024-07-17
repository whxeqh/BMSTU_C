#include <stdio.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define ERR_NO_ELEMENTS 3 //Если в массиве нет отрицательных или положительных элементов

#define N 10

int input(int *pbeg, int **pend);
int calc_value(const int *p_begin, const int *p_end);
void print_error(const int rc);

int main(void) 
{
    int ans = 0, rc = OK, a[N];
    int *pbeg = a, *pend = a;

    rc = input(pbeg, &pend);
    if (rc == OK)    
        ans = calc_value(pbeg, pend);
    if (rc == OK && ans == 0)
        rc = ERR_NO_ELEMENTS;
    if (rc != OK) 
        print_error(rc);
    else 
        printf("Ответ: %d\n", ans);

    return rc;
}

/*
  Функция обработки ввода.
  Принимает указатель на первый элемент массива и указатель на указатель
  элемнта, расположенного за последним элементом массива.
  Возвращает код ошибки
*/
int input(int *pbeg, int **pend)
{
    int size = -1;
    printf("Введите размер массива: ");
    if (scanf("%d", &size) != 1)
        return ERR_IO;
    else if (size <= 0 || size > N)
        return ERR_RANGE;

    *pend = pbeg + size;
    printf("Вводите элементы массива: ");
    for (int *ptr = pbeg; ptr < *pend; ptr++) 
        if (scanf("%d", ptr) != 1)
            return ERR_IO;
    return OK;
}

/*
  Функция вычисления суммы произведений. 
  Принимает указатели на константы (на первый элемент и элемент за последним)
  Возвращает сумму: X[0]*Y[0] + X[1]*Y[1] +...+ X[k-1]*Y[k-1]. X - отрицательные эл. массива, Y - положительные 
  k = min(p, q), p - кол-во положительных элементов, q - кол-во отрицательных
*/
int calc_value(const int *p_begin, const int *p_end)
{
    int ans = 0;
    const int *start = p_begin, *end = p_end - 1;
    while (end > (p_begin - 1) && start < p_end)
    {
        if (*start < 0 && *end > 0)
        {
            ans += (*start) * (*end);
            start++;
            end--;
        }
        else 
        {
            if (*start >= 0)
                start++;
            if (*end <= 0)
                end--;
        }
    }
    return ans;
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
    else if (rc == ERR_NO_ELEMENTS)
        printf("В массиве нет отрицательных или положительных элементов\n");
    else
        printf("Неизвестная ошибка (%d)\n", rc);
}
