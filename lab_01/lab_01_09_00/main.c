/*
Выполнил: Палладий Евгений, ИУ7-21Б
Приняв с клавиаутры по концевому признаку (до первого отрицательного числа) элементы непустой
последовательности неотрицательных чисел x, вычислить и вывести на экран значение g(x)
Условие:
*/

#include <stdio.h>
#include <math.h>

#define OK 0
#define ERR_IO 1
#define ERR_ZERO_NUMS 2

// Прототипы функций
int input(int i, double *x);
int func_sum(double *g);
void print(const int rc);

int main(void)
{
    int rc = OK;
    double g = 0.0;
    
    printf("Вводите значения x до первого отрицательного числа\n");
    rc = func_sum(&g);
    if (rc == OK) 
        printf("Значение функции g = %lf", g); 
    else
        print(rc);

    return rc;
}

//функция проверки ввода. Возвращает код возврата 
int input(int i, double *x)
{
    int rc;
    double input_x;
    if (scanf("%lf", &input_x) != 1)
        rc = ERR_IO;
    else if (i == 1 && input_x < 0) 
        rc = ERR_ZERO_NUMS;
    else
    {
        rc = OK;
        *x = input_x;
    }

    return rc;
}

/*
  Функция принимает указатель на до этого не инициализированную переменную g,
  которая в конце будет равна сумме функции по условию задачи.
*/
int func_sum(double *g)
{
    int i = 1, rc;
    double new_g = 0.0, x;  
    rc = input(i, &x);
    while (rc == OK && x >= 0)
    {
        new_g += x / i;
        i += 1;
        rc = input(i, &x);
    }
    if (rc == OK)
        new_g = sqrt(new_g);
    *g = new_g;
    
    return rc;
}

//функция вывода сообщений об ошибке в консоль
void print(const int rc)
{
    if (rc == ERR_IO)
        printf("Ошибка ввода");
    else
        printf("Должен быть хотя бы один положительный элемент");
}
