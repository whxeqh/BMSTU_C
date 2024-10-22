/*
Выполнил: Палладий Евгений, ИУ7-21Б

Условие: Составить программу для печати разложения на простые множитеи заданного
натурального числа n. Если n равно 1, печатать ничего не надо
*/

#include <stdio.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2

// Прототипы функций
int input(int *a, int *n);
int binpow(int a, int n);
void print(const int rc);

int main(void) 
{
    int rc, a, n, ans = 0;
    rc = input(&a, &n);
    if (rc == OK)   
    {
        ans = binpow(a, n);
        printf("Быстрое возведение a^n = %d\n", ans);
    }
    else 
        print(rc);

    return rc;
}

//Функция проверки ввода. Возвращает код возврата
int input(int *a, int *n)
{
    int rc = OK, a_input, n_input;
    printf("Введите целое число а и целое положительное число n: ");
    if (scanf("%d%d", &a_input, &n_input) != 2)
        rc = ERR_IO;
    else if (n_input <= 0)
        rc = ERR_RANGE;
    else
    {
        *a = a_input;
        *n = n_input;
    }
    return rc;
}

/*
  Функция быстрого возведения в степень. Принимает указатель на код возврата, который изменится при вызове
  функции validate_input(). На каждой итерации проверяется младший бит числа n с помощью побитового И. 
  Если младший бит равен 1, то это означает, что текущая степень является нечетной, поэтому к результату res 
  умножается текущее значение a. Если младший бит равен 0, то это означает, что текущая степень является четной, 
  поэтому a возводится в квадрат. n на каждой итерации делится на два с помощью сдвига вправо на 1 бит.
*/
int binpow(int a, int n)
{
    int ans = 1;
    while (n) 
    {
        if (n & 1)
            ans *= a;
        a *= a;
        n >>= 1;
    }
    return ans;
}

//Функция вывода сообений об ошибке в консоль
void print(int rc)
{
    if (rc == ERR_IO)
        printf("Должны быть введены два целых числа!");
    else
        printf("Степень должна быть положительной");
}
