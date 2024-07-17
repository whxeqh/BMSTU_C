/*
Выполнил: Палладий Евгений, ИУ7-21Б

Условие: По введёным с клавиатуры росту человека в сантиметрах, обхвату грудной клетки в сантиметрах
и массе тела в килограммах определить и вывести на экран нормальный веч человека и индекс массы его тела 
*/

#include <stdio.h>

#define COUNT_OF_CENTIMETERS 100

int main(void)
{
    float rost_cm, rost_m, obhvat, massa, m_normal, bmi;

    printf("Введите рост в сантиметрах, обхват грудной клетки в сантиметрах и массу в килограммах: ");
    scanf("%f%f%f", &rost_cm, &obhvat, &massa);

    rost_m = rost_cm / COUNT_OF_CENTIMETERS;
    m_normal = (rost_cm * obhvat) / 240;
    bmi = massa / (rost_m * rost_m);

    printf("Нормальная масса = %f , BMI = %f", m_normal, bmi);
    
    return 0;
}
