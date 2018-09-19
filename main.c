#include <stdio.h>
#include <stdlib.h>

#include "c_list.h"

typedef struct s_object
{
    int i;
    float f;
} object;

// Функция вывода содержимого объекта типа object.
void print_object(void *const _data)
{
    if (_data == NULL)
    {
        return;
    }

    const object *const obj = (object*)_data;

    printf("i: %i, f: %f\n", obj->i, obj->f);
}

// Предикат удаления элемента типа object.
size_t pred_object(const void *const _data)
{
    if (_data == NULL)
    {
        return 0;
    }

    const object *const obj = (object*)_data;

    if (obj->f > 11)
    {
        return 1;
    }

    return 0;
}

int main(int agrc, char **argv)
{
    size_t error;
    c_list *list;

    // Пытаемся создать двусвязный список.
    list = c_list_create(&error);
    // Если произошла ошибка, покажем ее код.
    if (list == NULL)
    {
        printf("error: %Iu\n", error);
        printf("Program end.\n");
        getchar();
        return -1;
    }

    // Вставляем в двусвязный список 11 элементов типа object.
    for (size_t i = 0; i < 10; ++i)
    {
        // Пытаемся выделить память под объект.
        object *const obj = malloc(sizeof(object));
        // Если память выделить не удалось, покажем ошибку.
        if (obj == NULL)
        {
            printf("malloc(): NULL\n");
            printf("Program end.\n");
            getchar();
            return -2;
        }
        // Инициализируем объект.
        obj->i = i;
        obj->f = i + 3.14f;
        // Попытаемся вставить объект в конец двусвязного списка.
        const ptrdiff_t r_code = c_list_push_back(list, obj);
        // Если вставка не удалась, покажем причину.
        if (r_code < 0)
        {
            printf("push back error, r_code: %Id\n", r_code);
            printf("Program end.\n");
            getchar();
            return -3;
        }
    }

    // При помощи обхода всего списка выведем содержимое его узлов.
    {
        const ptrdiff_t r_code = c_list_for_each(list, print_object);
        // Если возникла ошибка, покажем ее.
        if (r_code < 0)
        {
            printf("for each error, r_code: %Id\n", r_code);
            printf("Program end.\n");
            getchar();
            return -4;
        }
    }

    // Удалим из списка элементы с индексами: 0, 1, 3, 2, 99
    {
        size_t indexes[5] = {0, 1, 3, 2, 99};
        error = 0;
        const size_t d_count = c_list_erase_few(list, indexes, 5, free, &error);
        // Если произошла ошибка, покажем ее.
        if ( (d_count == 0) && (error > 0) )
        {
            printf("erase few error: %Iu\n", error);
            printf("Program end.\n");
            getchar();
            return -5;
        }
        // Покажем, сколько элементов было удалено.
        printf("d_count: %Iu\n", d_count);
    }

    // При помощи обхода всего списка выведем содержимое его узлов.
    {
        const ptrdiff_t r_code = c_list_for_each(list, print_object);
        // Если возникла ошибка, покажем ее.
        if (r_code < 0)
        {
            printf("for each error, r_code: %Id\n", r_code);
            printf("Program end.\n");
            getchar();
            return -6;
        }
    }

    // Удалим из списка элементы, у которых f > 11.
    {
        error = 0;
        const size_t d_count = c_list_remove_few(list, pred_object, free, &error);
        // Если произошла ошибка, покажем ее.
        if ( (d_count == 0) && (error > 0) )
        {
            printf("remove few error: %Iu\n", error);
            printf("Program end.\n");
            getchar();
            return -7;
        }
        // Покажем, сколько элементов было удалено.
        printf("d_count: %Iu\n", d_count);
    }

    // При помощи обхода всего списка выведем содержимое его узлов.
    {
        const ptrdiff_t r_code = c_list_for_each(list, print_object);
        // Если возникла ошибка, покажем ее.
        if (r_code < 0)
        {
            printf("for each error, r_code: %Id\n", r_code);
            printf("Program end.\n");
            getchar();
            return -8;
        }
    }

    // Удалим двусвязный список.
    {
        const ptrdiff_t r_code = c_list_delete(list, free);
        // Если произошла ошибка, покажем ее.
        if (r_code < 0)
        {
            printf("delete error, r_code: %Id\n", r_code);
            printf("Program end.\n");
            getchar();
            return -9;
        }
    }

    getchar();
    return 0;
}
