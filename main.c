#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "c_list.h"

// Проверка возвращаемых значений не выполняется для упрощения.

// Функция печати содержимого узла
void print_func_f(void *const _data)
{
    if (_data == NULL) return;

    const float data = *((float*)_data);
    printf("%f\n", data);
    return;
}

// Функция удаления данных узла
void del_func_f(void *const _data)
{
    if (_data == NULL) return;

    free(_data);
    return;
}

int main()
{
    // Создание двусвязного списка.
    c_list *list = c_list_create();

    // Добавление в конец десяти элементов.
    const size_t count = 10;
    float *data;
    for (size_t i = 0; i < count; ++i)
    {
        data = (float*)malloc(sizeof(float));
        *data = i * 1.1f;
        c_list_push_back(list, data);
    }



    // Вывод содержимого двусвязного списка.
    c_list_for_each(list, print_func_f);

    // Удаление нескольких узлов с заданными индексами,
    // индексы хранятся в неупорядоченном виде.
    const size_t indexes_count = 3;
    size_t indexes[indexes_count];
    indexes[0] = 7;
    indexes[1] = 1;
    indexes[2] = 4;
    c_list_erase_few(list, indexes, indexes_count, del_func_f);
///////////////////////////////////////////
c_list_node *select_node = list->first;
while (select_node != NULL)
{
    printf("node: %Iu\nprev: %Iu\nnext: %Iu\ndata: %f\n\n",
           (size_t)select_node,
           (size_t)select_node->prev,
           (size_t)select_node->next,
           *((float*)select_node->data));

    select_node = select_node->next;
}
///////////////////////////////////////////
    // Вывод содержимого двусвязного списка.
    c_list_for_each(list, print_func_f);

    getchar();
    return 0;
}
