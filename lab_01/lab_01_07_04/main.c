/*
Выполнил: Палладий Евгений, ИУ7-21Б

Условие: Приняв с клавиаутуры x и eps, 0 < eps <= 1, вывеси на экран вычисленной с точностью eps приближенное
значение s(x) и точное значение f(x) функции f, абсолютную и относительную погрешности
*/

#include <stdio.h>
#include <math.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2


/*
  Функция принимает точность вычисления (eps) и заданную неизвестную (x)
  и возвращает вычисленное с точностью eps приближенное значение функции s(x)

             2*3*x   3*4*x^2   4*5*x^3   5*6*x^4
  s(x) = 1 - ----- + ------- - ------- + ------- + ...
               2        2         2         2
*/
double func(double eps, double x)
{
    int i = 2;
    double stepen = x, current, s = 1;
    int sign = -1; // Переменная для хранения текущего знака
    current = sign * (i * (i + 1) * x) / 2;
    while (fabs(current) > eps)
    {
        s += current;
        x *= stepen;
        i++;
        sign *= -1;
        current = sign * (i * (i + 1) * x) / 2;
    }
    return s;
}

int main(void)
{
    double x, eps;
    double s = 1, delta, f, epsilon;

    printf("Введите x и eps по очереди: ");
    if (scanf("%lf %lf", &x, &eps) != 2)
    {
        printf("Некорректный ввод");
        return ERR_IO;
    }
    if (fabs(x) >= 1 || eps <= 0 || eps > 1)
    {
        printf("Некорректный диапазон");
        return ERR_RANGE;
    }
    f = 1 / ((1 + x) * (1 + x) * (1 + x));
    s = func(eps, x);
    delta = fabs(f - s);
    epsilon = delta / fabs(f);

    printf("Приближенное значение s(x) = %lf , точное значение f(x) = %lf\n", s, f);
    printf("Абсолютная погрешность равна %lf , относительная погрешность равна %lf\n", delta, epsilon);

    return OK;
}
