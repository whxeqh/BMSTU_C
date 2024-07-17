/*Выполнил: Палладий Евгений, ИУ7-21Б

Условие: С клавиатуры задаются координаты точек q, r, отрезка qr и координаты произвольной
точки p. Определить, не принадлежил или принадлежит точка отрезку, и вывести на экран 0 или 1 соответственно
*/

#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define INSIDE true
#define OUTSIDE false

#define OK 0
#define ERR_IO 1
#define EPS 1e-8
/*
  Функция, которая проверяет нахождение точки с координатами (px, py) на отрезке qr
  Выводит 1 в случае нахождения на отрезке и 0 в случае не нахождения на отрезке
*/
bool is_point_on_line(double qx, double qy, double rx, double ry, double px, double py)
{
    bool bool_inside = INSIDE;
    double x_min, x_max, y_min, y_max;
    x_min = fmin(qx, rx);
    y_min = fmin(qy, ry);
    x_max = fmax(qx, rx);
    y_max = fmax(qy, ry);
    // проверка, что точка лежит в пределах отрезка по оси X и Y
    if (px < x_min || px > x_max || py < y_min || py > y_max)
        bool_inside = OUTSIDE;
    // псевдоскалярное произведение должно быть равно 0
    if (bool_inside && fabs((px - qx) * (ry - qy) - (rx - qx) * (py - qy)) <= EPS)
        return INSIDE;
    return OUTSIDE;
}

int main(void)
{
    double qx, qy, rx, ry, px, py;
    bool ans;

    printf("Введите координаты точки q (сначала х, потом y): ");
    if (scanf("%lf%lf", &qx, &qy) != 2)
    {
        printf("Некорректный ввод");
        return ERR_IO;
    }

    printf("Введите координаты точки r (сначала х, потом y): ");
    if (scanf("%lf%lf", &rx, &ry) != 2)
    {
        printf("Некорректный ввод");
        return ERR_IO;
    }

    printf("Введите координаты точки p (сначала х, потом y): ");
    if (scanf("%lf%lf", &px, &py) != 2)
    {
        printf("Некорректный ввод");
        return ERR_IO;
    }
    
    if (fabs(qx - rx) < EPS && fabs(qy - ry) < EPS)
    {
        printf("Некорректный ввод");
        return ERR_IO;
    }

    ans = is_point_on_line(qx, qy, rx, ry, px, py);
    if (ans)
        printf("Точка лежит на прямой 1");
    else
        printf("Точка не лежит на прямой 0");

    return OK;
}
