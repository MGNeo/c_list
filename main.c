#include <stdio.h>
#include <stdlib.h>

#include "c_vector.h"

// Проверка возвращаемых значений не выполняется для упрощения.

void print_func(void *const _data)
{
    if (_data == NULL) return;

    uint8_t *data = _data;
    printf("%Iu\n", (size_t)(*data));

    return;
}

int main(int agrc, char **argv)
{
    // Создадим вектор для хранения в нем объектов типа (размера) uint8_t.
    // Начальная емкость вектора = 10.
    c_vector *vector = c_vector_create(sizeof(uint8_t), 10);

    // Заполним вектор.
    for (size_t i = 0; i < 10; ++i)
    {
        uint8_t *data = c_vector_push_back(vector);
        *data = i;
    }

    // Выведем содержимое вектора.
    printf("vector:\n");
    c_vector_for_each(vector, print_func);
    printf("\n");

    // Сформируем массив удаляемых индексов.
    size_t indexes[9] = {8, 0, 10009090, 1, 8, 11, 8, 7, 1};

    // Отобразим  его.
    printf("indexes:\n");
    for (size_t i = 0; i < 9; ++i)
    {
        printf("%Iu\n", indexes[i]);
    }
    printf("\n");

    // Удалим элементы с заданными индексами.
    c_vector_erase_few(vector, indexes, 9, NULL);

    // Выведем содержимое вектора.
    printf("vector:\n");
    c_vector_for_each(vector, print_func);
    printf("\n");

    // Выведем содержимое индексов.
    printf("indexes: \n");
    for (size_t i = 0; i < 9; ++i)
    {
        printf("%Iu\n",indexes[i]);
    }
    printf("\n");

    // Вставим данные по заданному индексу.
    size_t index = 5;
    uint8_t *data = c_vector_insert(vector, index);
    *data = 100;

    // Выведем содержимое вектора.
    printf("vector:\n");
    c_vector_for_each(vector, print_func);
    printf("\n");

    getchar();
    return 0;
}
