/*
    Название задачи: Продуктовый магазин

    Условие:
    В файле хранятся пары: "продукт цена" 
    В зависимости от переданных ключей программа должна выполнить разные действия

    Параметры запуска:
    app.exe [pb, rv, s] file_in file_out

    [pb, rv, s] - опции
    - pb -- Удаляет элемент в "хвосте" списка
    - rv -- Разварачивает список рекурсией
    - s -- Сортировка списка методом вставок
*/
#include <stdio.h>

#include "products_array.h"
#include "errors.h"
#include "list.h"
#include "macro.h"

#define POP_BACK "pb"
#define REVERSE "rv"
#define SORT "s"
#define PRINT "p"

typedef enum
{
    ACT_POP_BACK,
    ACT_REVERSE,
    ACT_SORT,
} action_e;

int check_args(const int argc, char **argv, action_e *act);

int main(int argc, char **argv)
{
    PRINT_TABLE_HEADER();

    action_e act;              //Выполняемое действие
    product_t *arr = NULL;     //Массив продуктов
    size_t length = 0;         //Длина массива продуктов
    int rc = OK;               //Код ошибки
    char *file_in = argv[2];   //Файл для чтения продуктов
    char *file_out = argv[3];  //Файл для вывода продуктов

    void *data = NULL;
    node_t *head = NULL;

    rc = check_args(argc, argv, &act);

    if (rc != OK)
    {
        LOG_PRINT_ERR("app.exe [pb, rv, s] file_in file_out");
        goto func_end;
    }

    rc = products_create_ex(file_in, &arr, &length);
    if (rc != OK)
    {
        LOG_PRINT_ERR("Ошибка при заполнении массива, rc = %d", rc);
        goto free_products;
    }

    LOG_PRINT_OK("Массив успешно заполнен");
        
    rc = list_create(&head, arr, length);
    if (rc != OK)
    {
        LOG_PRINT_ERR("Ошибка при заполнении списка, rc = %d", rc);
        goto free_list;
    }

    LOG_PRINT_OK("Список успешно заполнен");

    switch (act)
    {
        case ACT_POP_BACK:
            data = pop_back(&head);
            LOG_PRINT_OK("Последний элемент списка был удален");
            break;
        case ACT_REVERSE:
            head = reverse(head);
            LOG_PRINT_OK("Список был реверснут");
            break;
        case ACT_SORT:
            head = sort(head, cmp_products_by_name);
            LOG_PRINT_OK("Список был отсортирован");
            break;
    }

    (void) data;
    rc = print_list_ex(file_out, head);
    if (rc == OK)
        LOG_PRINT_OK("Список успешно выведен");
    else 
        LOG_PRINT_ERR("Ошибка при выводе списка, rc = %d", rc);
    
    free_list:
        free_list(&head);
    LOG_PRINT_OK("Список очищен");
    
    free_products:
        free_products(&arr, &length);
    LOG_PRINT_OK("Массив очищен");

    func_end:
    (rc == OK) ? LOG_PRINT_OK("Код ошибки: %d", rc) : LOG_PRINT_ERR("Код ошибки: %d", rc);
    
    PRINT_END_TABLE();
    return rc;
}

int check_args(const int argc, char **argv, action_e *act)
{   
    if (argc != 4)
        return ERR_ARGS;

    action_e tmp_act;

    if (strcmp(argv[1], POP_BACK) == 0)
        tmp_act = ACT_POP_BACK;
    else if (strcmp(argv[1], REVERSE) == 0)
        tmp_act = ACT_REVERSE;
    else if (strcmp(argv[1], SORT) == 0)
        tmp_act = ACT_SORT;
    else 
        return ERR_ARGS;

    *act = tmp_act;
    
    return OK;
}
