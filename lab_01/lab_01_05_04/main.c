/*
Выполнил: Палладий Евгений, ИУ7-21Б

Условие: Составить программу для печати разложения на простые множитеи заданного
натурального числа n. Если n равно 1, печатать ничего не надо
*/

#include <stdio.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2

/*
    Функция, которая принимает делимое (n) и делитель (d). Число n делится на d до тех пор,
    пока остаток от деления равен нулю. Выводит в консоль делители числа n. Число n изменяется по указателю
*/
void division(int *n, int d)
{
    int new_n = *n;
    while (new_n % d == 0)
    {
        new_n /= d;
        printf("%d ", d);
    }
    *n = new_n;
}

/* 
    Функция solve() проверяет деление числа n на делитель div. Сначала проверяется деление на 2, затем 
    перебираются нечетные числа, которые меньше n. Если деление происходит без остатка, то управление передается
    функции division(), которая выводит делители в консоль. 
*/
void solve(int n)
{
    int div = 3;
    if (n % 2 == 0)
        division(&n, 2);
    
    while (n > 1)
    {    
        if (n % div == 0)
            division(&n, div);
        div += 2;
    }
}

int main(void) 
{
    int n;
    printf("Введите натуральное число N: ");

    if (scanf("%d", &n) != 1)
    {
        printf("Некорректный ввод");
        return ERR_IO;
    }
    else if (n < 1)
    {
        printf("Некорректный диапазон");
        return ERR_RANGE; 
    }
    else
        solve(n);
    return OK;
}
