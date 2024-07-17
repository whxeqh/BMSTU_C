#include <stdio.h>
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2

// функция получает число и номер позиции в которой возвращает бит
uint32_t get_bit(uint32_t number, int pos)
{
    return (number >> pos) & 1;
}

// функция получает число source, количество сдвигов n и возвращает число, которое было сдвинуто на n бит вправо
uint32_t shift(uint32_t source, int n)
{
    n %= 32;
    if (n == 0)
        return source;
    size_t nbits = sizeof(uint32_t) * CHAR_BIT;
    return source = (source >> n) | (source << (nbits - n)); 
}

// функция, которая выводит в консоль все биты числа a;
void to_second(uint32_t a)
{
    size_t nbits = sizeof(uint32_t) * CHAR_BIT;
    for (int i = nbits - 1; i >= 0; i--)
    {
        printf("%d", get_bit(a, i));
    }
    printf("\n");
}

int main(void)
{
    int n;
    uint32_t a;

    printf("Введите беззнаковое число a и натуральное число n: ");
    if (scanf("%" SCNu32 " %d", &a, &n) != 2)
    {
        printf("Error: некорректный ввод");
        return ERR_IO;
    }
    if (n < 0)
    {
        printf("Error: число должно быть натуральным\n");
        return ERR_RANGE;
    }

    a = shift(a, n);
    printf("Result: ");
    to_second(a);

    return OK;
}

