#include <stdio.h>
#include <stdlib.h>

#include "c_list.h"

// В целях упрощения - првоерка возвращаемых значений не выполняется.

// Функция печати содержимого узла.
void print_float(void *const _data)
{
    if (_data == 0)
    {
        return;
    }

    float *data = (float*)_data;

    printf("%f\n", *data);

    return;
}

// Функция удаления содержимого узла.
void del_float(void *const _data)
{
    if (_data == NULL)
    {
        return;
    }

    free(_data);

    return;
}

int main(int agrc, char **argv)
{
    // Создание списка.
    c_list *list = c_list_create();

    // Заполнение списка.
    for (size_t i = 0; i < 10; ++i)
    {
        float *data = (float*)malloc(sizeof(float));
        *data = 3.14f + i;

        c_list_push_front(list, data);
    }

    // Вывод содержимого списка.
    c_list_for_each(list, print_float);

    // Удаление списка и всех данных в нем.
    c_list_delete(list, del_float);

    getchar();

    return 0;
}
