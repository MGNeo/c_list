#include "c_list.h"

// Создает новый двусвязный список.
// В случае ошибки возвращает NULL.
c_list *c_list_create(void)
{
    c_list *new_list = (c_list*)malloc(sizeof(c_list));
    if (new_list == NULL) return NULL;

    new_list->first = NULL;
    new_list->last = NULL;
    new_list->nodes_count = 0;

    return new_list;
}

// Удаляет двусвязный список.
// В случае успеха возвращает > 0, иначе < 0.
ptrdiff_t c_list_delete(c_list *const _list, void (*const _del_func)(void *const _data))
{
    if (_list == NULL) return -1;

    if (_list->nodes_count > 0)
    {
        void *select_node = _list->first,
             *delete_node;

        if (_del_func != NULL)
        {
            while(select_node != NULL)
            {
                delete_node = select_node;
                select_node = *((void**)select_node);

                _del_func((uint8_t*)delete_node + 2 * sizeof(void*));

                free(delete_node);
            }
        } else {
            delete_node = select_node;
            select_node = *((void**)select_node);

            free(delete_node);
        }
    }

    free(_list);

    return 1;
}

// Вставляет в начало списка новый узел.
// В случае успеха возвращает указатель на неинициализированные данные.
// В случае ошибки возвращает NULL.
void *c_list_push_front(c_list *const _list, const size_t _data_size)
{
    if (_list == NULL) return NULL;
    if (_data_size == 0) return NULL;

    void *new_node = malloc(2 * sizeof(void*) + _data_size);
    if (new_node == NULL) return NULL;

    *((void**)new_node) = _list->first;
    *(((void**)new_node) + 1) = NULL;

    _list->first = new_node;
    if (_list->nodes_count == 0)
    {
        _list->last = new_node;
    }

    ++_list->nodes_count;

    return (uint8_t*)_list->first + 2 * sizeof(void*);
}



