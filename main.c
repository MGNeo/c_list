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

// Функция оценки критения удаления по данным узла.
size_t comp_func_f(const void *const _data)
{
    if (_data == NULL) return 0;
    float data = *((float*)_data);
    if (data < 3.f)
    {
        return 1;
    }
    return 0;
}

int main()
{
    srand(time(NULL));

    // Создание двусвязного списка.
    c_list *list = c_list_create();

    // Вставка в начало.
    float *data = (float*)malloc(sizeof(float));
    *data = 3.1415f;
    c_list_push_front(list, data);

    // Удаление из конца.
    c_list_pop_back(list, del_func_f);

    // Вставка десяти элементов в позицию с индексом 0 (начало).
    const size_t count = 10;
    for (size_t i = 0; i < count; ++i)
    {
        data = (float*)malloc(sizeof(float));
        *data = 1.1f * i;
        c_list_insert(list, data, 0);
    }

    // Вывод содержимого списка.
    c_list_for_each(list, print_func_f);
    printf("\n");

    // Удаление сразу нескольких узлов с заданными индексами.
    const size_t indexes_count = 4;
    size_t indexes[indexes_count];
    indexes[0] = 3;
    indexes[1] = 19;// Узла с таким индексом в сипске нет.
    indexes[2] = 9;
    indexes[3] = 1;
    c_list_erase_few(list, indexes, indexes_count, del_func_f);
    // Почему индексы узлов начинаютяс с 1!?

    // Вывод содержимого списка.
    c_list_for_each(list, print_func_f);
    printf("\n");

    // Удаление всех узлов, данные которых < 3.f;
    c_list_remove_few(list, comp_func_f, del_func_f);

    // Вывод содержимого списка.
    c_list_for_each(list, print_func_f);
    printf("\n");

    // Удаление списка.
    c_list_delete(list, del_func_f);

    getchar();
    return 0;
}
