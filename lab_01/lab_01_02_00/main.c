/*
Выполнил: Палладий Евгений, ИУ7-21Б

Условие: Принять с клавиатуры величины оснований a и b и высоты h
равнобедренной трапеции. Найти и вывести на экран периметр P трапеции
*/

#include <stdio.h>
#include <math.h>

int main(void)
{
    double a, b, c, t, h, perimetr;

    printf("Введите нижнее, верхнее основание и высоту: ");
    scanf("%lf%lf%lf", &a, &b, &h);

    t = (a - b) / 2.0;
    c = sqrt(t * t + h * h);
    perimetr = a + b + 2 * c;

    printf("Периметр равнобедренной трапеции = %f", perimetr);
    
    return 0;
}
