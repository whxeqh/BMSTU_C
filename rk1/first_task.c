#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2

//Функция обработки ввода
int input(int *n, int*m)
{
    int new_n, new_m;
    if (scanf("%d%d", &new_n, &new_m) != 2)
        return ERR_IO;
    if (new_m <= 0)
        return ERR_RANGE;
    *n = new_n;
    *m = new_m;
    return OK;
}

/*
  Функция для подсчёта суммы цифр в числе
  Принимает числа n, m и указатель ans. Возвращает код ошибки
*/
int summ(int n, int m, int *ans)
{
    int rc = OK;
    do
    {
        *ans += (n % 10);
        n /= 10;
        m--;
    } while (n && m);

    //Если в числе n было меньше m разрядов, то возвращаем ошибку
    if (n == 0 && m)
        rc = ERR_IO;
    
    return rc;
}

int main(void)
{
    int n, m, rc = OK, ans = 0;

    rc = input(&n, &m);
    
    if (rc != OK)
    {
        printf("Ошибка ввода\n");
        return rc;
    }
    if (n < 0)
        n = abs(n);
    
    rc = summ(n, m, &ans);

    if (rc == OK)
        printf("Ответ: %d\n", ans);
    else
        printf("Ошибка, в числе меньше разрядов\n");

    return OK;
}