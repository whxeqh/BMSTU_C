#include "calculations.h"
#include "errors.h"
#include "constants.h"

/** 
 * @brief Функция для нахождения первой цифры числа
 * @param[in] num Целое число
 * @return Первая цифра числа num
*/
int first_digit(int num)
{
    if (num < 0)
        num = -num;
    return num % BASE;
}

/** 
 * @brief Функция для нахождения последней цифры числа
 * @param[in] num Целое число
 * @return Последняя цифра числа num
*/
int last_digit(int num)
{
    int digit;
    if (num < 0)
        num = -num;
    do 
    {
        digit = num % BASE;
        num /= BASE;
    } while (num);

    return digit;
}

/**
 * @brief Функция проверки равенства количества элементов, начинающихся или заканчивающихся на заданную цифру.
 * 
 * @param[in] arr_size Размер массива.
 * @param[out] array Указатель на исходный массив.
 * @param[in] digit Заданная цифра для проверки.
 * @return true, если количество чисел, начинающихся на заданную цифру, равно количеству чисел, заканчивающихся на неё, иначе false.
 */
bool is_equal_count(const size_t arr_size, int *array, const short digit)
{
    size_t count_begin = 0, count_end = 0;
    for (size_t i = 0; i < arr_size; i++)
    {
        if (first_digit(array[i]) == digit)
            count_begin++;
        if (last_digit(array[i]) == digit)
            count_end++;
    }

    return count_begin != 0 && count_begin == count_end;
}

//Изменненные функции для защиты

/**
 * @brief Функция заполняет каждый элемент массива числом num
 * 
 * @param[in] a_m Размер массива.
 * @param[out] arr Указатель на исходный массив.
 * @param[in] num Число, которым будут заполнять строку.
*/
void fill_string(const size_t a_m, int *arr, const int num)
{
    for (size_t i = 0; i < a_m; i++)
        arr[i] = num;
}

/**
 * @brief Функция присваивает элемнты массива source соответствующим элементам массива target 
 * 
 * @param[out] target_arr Массив, который будет заполнен элементами массива source.
 * @param[out] source_arr Масив.
 * @param[in] size Размерность обоих массивов.
*/
void assign_arrays(int *target_arr, const int *source_arr, const size_t size)
{
    for (size_t i = 0; i < size; i++)
        target_arr[i] = source_arr[i];
}

/**
 * @brief Функция добавляет массив arr в матрицу по позиции строки
 * 
 * @param[out] a_n Кол-во строк в матрице
 * @param[in] a_m Кол-во столбцов в матрице.
 * @param[out] matrix Исходная матрица.
 * @param[in] arr Массив для добавления
 * @param[in] pos Позиция добавления
 * 
 * @return Код ошибки
*/
int new_insert_string(size_t *a_n, const size_t a_m, int (*matrix)[M], const int *arr, const size_t pos)
{
    if (pos >= *a_n + 1)
        return ERR_RANGE;

    (*a_n)++;

    for (size_t i = *a_n; i > pos; i--)
        assign_arrays(matrix[i], matrix[i - 1], a_m);

    assign_arrays(matrix[pos], arr, a_m); // Добавляет массив arr по индексу. В контексте задачи arr состоит только из элементов 100

    return OK;
}

//Функция изменяет матрицу путем вставления строк из чисел 100
/**
 * @brief Функция редактироания матрицы
 * 
 * При одинаковом количестве элементов, начинающихся и заканчивающихся на заданную цифру,
 * вызывается функцию new_insert_string(), которая добавляет массив arr по позиции строки в матрицу.
 * 
 * @param[out] a_n Кол-во строк в матрице
 * @param[in] a_m Кол-во столбцов в матрице.
 * @param[out] matrix Исходная матрица.
 * @param[in] digit Цифра для проверки
 * 
 * @return Код ошибки
*/
int new_edit_matrix(size_t *a_n, const size_t a_m, int (*matrix)[M], const short digit)
{
    size_t new_row = *a_n;
    int arr[M], rc = OK;
    fill_string(a_m, arr, 100); //Массив из чисел 100

    for (size_t i = 0; i < new_row; i++)
        if (is_equal_count(a_m, matrix[i], digit))
        {
            rc = new_insert_string(&new_row, a_m, matrix, arr, ++i); 
            if (rc != OK)
                return rc;
        }

    *a_n = new_row;
    return rc;
}



/**
 * @brief Функция вставки строки из чисел 100 в матрицу 
 * 
 * @param[in] a_n Количество строк
 * @param[in] a_m Количество столбцов
 * @param[out] matrix Матрица
 * @param[in] pos Индекс, в который нужно вставить строку из чисел 100
*/
// void insert_string(const size_t a_n, const size_t a_m, int (*matrix)[M], const size_t pos)
// {
//     for (size_t i = a_n; i > pos; i--)
//         for (size_t j = 0; j < a_m; j++)
//             matrix[i][j] = matrix[i - 1][j];

//     for (size_t j = 0; j < a_m; j++)
//         matrix[pos][j] = 100;
// }


/** 
 * @brief Функция редактирования матрицы.
 * 
 * При одинаковом количестве элементов, начинающихся и заканчивающихся на заданную цифру,
 * вызывается функцию insert_string(), которая добавляет строку из чисел 100.
 * 
 * @param[in] a_n Количество строк  
 * @param[in] a_m Количество столбцов
 * @param[out] matrix Матрица
 * @param[in] digit Цифра для проверки
 * 
 * @return Новая длина матрицы
*/
// size_t edit_matrix(size_t a_n, const size_t a_m, int (*matrix)[M], const short digit)
// {
//     int arr[M];
//     fill_string(a_m, arr, 100);

//     for (size_t i = 0; i < a_n; i++)
//         if (is_equal_count(a_m, matrix[i], digit))
//             insert_string(++a_n, a_m, matrix, ++i);
            
//     return a_n;
// }
