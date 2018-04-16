/*
    Файл реализации двусвязного списка c_list
    Разработка, отладка и сборка производилась в:
    ОС: Windows 10/x64
    IDE: Code::Blocks 17.12
    Компилятор: default Code::Blocks 17.12 MinGW

    Разработчик: Глухманюк Максим
    Эл. почта: mgneo@yandex.ru
    Место: Российская Федерация, Самарская область, Сызрань
    Дата: 16.03.2018
    Лицензия: GPLv3
*/

#include "c_list.h"

// Компаратор для сортировки массива с индексами узлов, которые необходимо удалить.
static int comp_sort(const void *const _a,
                    const void *const _b)
{
    const size_t a = *((size_t*)_a);
    const size_t b = *((size_t*)_b);
    if (a > b)
    {
        return 1;
    } else {
        if (a == b)
        {
            return 0;
        } else {
            return -1;
        }
    }
}

// Создает новый двусвязный список.
// В случае ошибки возвращает NULL.
c_list *c_list_create(void)
{
    c_list *const new_list = (c_list*)malloc(sizeof(c_list));
    if (new_list == NULL) return NULL;

    new_list->first = NULL;
    new_list->last = NULL;
    new_list->nodes_count = 0;

    return new_list;
}

// Удаляет двусвязный список.
// В случае успеха возвращает > 0, иначе < 0.
ptrdiff_t c_list_delete(c_list *const _list,
                        void (*const _del_func)(void *const _data))
{
    if (c_list_clear(_list, _del_func) < 0)
    {
        return -1;
    }

    free(_list);

    return 1;
}

// Вставляет новый узел в начало двусвязного списка.
// Не позволяет вставлять узел с указателем на NULL.
// В случае успеха возвращает > 0, иначе < 0.
ptrdiff_t c_list_push_front(c_list *const _list,
                            const void *const _data)
{
    if (_list == NULL) return -1;
    if (_data == NULL) return -2;
    if (_list->nodes_count == SIZE_MAX) return -3;// Не, ну а вдруг...)

    c_list_node *const new_node = (c_list_node*)malloc(sizeof(c_list_node));
    if (new_node == NULL) return NULL;

    new_node->next = _list->first;
    new_node->prev = NULL;
    new_node->data = (void*)_data;

    if (_list->nodes_count == 0)
    {
        _list->last = new_node;
    } else {
        _list->first->prev = new_node;
    }

    _list->first = new_node;

    ++_list->nodes_count;

    return 1;
}

// Уничтожает первый узел списка.
// В случае успешного уничтожения возвращает > 0.
// Если уничтожать нечего, возвращает 0.
// В случае ошибки возвращает < 0.
ptrdiff_t c_list_pop_front(c_list *const _list,
                           void (*const _del_func)(void *const _data))
{
    if (_list == NULL) return -1;
    if (_list->nodes_count == 0) return 0;

    c_list_node *delete_node = _list->first;

    _list->first = _list->first->next;
    if (_list->first != NULL)
    {
        _list->first->prev = NULL;
    } else {
        _list->last = NULL;
    }

    if (_del_func != NULL)
    {
        _del_func( delete_node->data );
    }

    free(delete_node);

    --_list->nodes_count;

    return 1;
}

// Вставляет новый узел в конец двусвязного списка.
// Не позволяет вставлять узел с указателем на NULL.
// В случае успеха возвращает > 0, иначе < 0.
ptrdiff_t c_list_push_back(c_list *const _list,
                           const void *const _data)
{
    if (_list == NULL) return -1;
    if (_data == NULL) return -2;
    if (_list->nodes_count == SIZE_MAX) return -3;// Не, ну а вдруг...)

    c_list_node *const new_node = (c_list_node*)malloc(sizeof(c_list_node));
    if (new_node == NULL) return NULL;

    new_node->next = NULL;
    new_node->prev = _list->last;
    new_node->data = (void*)_data;

    if (_list->nodes_count == 0)
    {
        _list->first = new_node;
    } else {
        _list->last->next = new_node;
    }

    _list->last = new_node;

    ++_list->nodes_count;

    return 1;
}

// Уничтожает последний узел двусвязного списка.
// В случае успешного уничтожения возвращает > 0.
// Если уничтожать нечего, возвращает 0.
// В случае ошибки возвращает < 0.
ptrdiff_t c_list_pop_back(c_list *const _list,
                          void (*const _del_func)(void *const _data))
{
    if (_list == NULL) return -1;
    if (_list->nodes_count == 0) return 0;

    c_list_node *delete_node = _list->last;

    _list->last = _list->last->prev;
    if (_list->last != NULL)
    {
        _list->last->next = NULL;
    } else {
        _list->first = NULL;
    }

    if (_del_func != NULL)
    {
        _del_func(delete_node->data);
    }

    free(delete_node);

    --_list->nodes_count;

    return 1;
}

// Вставка нового узла в заданную позицию.
// В случае успеха возвращает > 0.
// В случае ошибки возвращает < 0.
// Не позволяет вставлять узел с указателем на NULL.
// Позволяет вставлять в пустой список, если _index = 0.
ptrdiff_t c_list_insert(c_list *const _list,
                    const void *const _data,
                    const size_t _index)
{
    if (_list == NULL) return -1;
    if (_data == NULL) return -2;
    if (_list->nodes_count == SIZE_MAX) return -3;// Не, ну а вдруг...)
    if (_index > _list->nodes_count) return -4;

    c_list_node *const new_node = (c_list_node*)malloc(sizeof(c_list_node));
    if (new_node == NULL) return -5;

    // Если список пуст.
    if (_list->nodes_count == 0)
    {
        new_node->next = NULL;
        new_node->prev = NULL;
        new_node->data = (void*)_data;

        _list->first = new_node;
        _list->last = new_node;

        ++_list->nodes_count;

        return 1;
    } else {
        // Вставка в начало.
        if (_index == 0)
        {
            new_node->next = _list->first;
            new_node->prev = NULL;
            new_node->data = (void*)_data;

            _list->first->prev = new_node;
            _list->first = new_node;

            ++_list->nodes_count;

            return 2;
        }
        // Вставка в конец.
        if (_index == _list->nodes_count)
        {
            new_node->next = NULL;
            new_node->prev = _list->last;

            _list->last->next = new_node;
            _list->last = new_node;

            ++_list->nodes_count;

            return 3;
        }
        // Вставка в первую половину (не в начало и не в конец).
        if (_index <= _list->nodes_count / 2)
        {
            c_list_node *prev_node = _list->first;
            for (size_t i = 0; i < _index - 1; ++i)
            {
                prev_node = prev_node->next;
            }

            new_node->next = prev_node->next;
            new_node->prev = prev_node;

            prev_node->next = new_node;
            prev_node->next->prev = new_node;

            ++_list->nodes_count;

            return 4;
        } else {
            // Вставка во вторую половину (не в начало и не в конец).
            c_list_node *next_node = _list->last;
            for (size_t i = _list->nodes_count - 1; i > _index; --i)
            {
                next_node = next_node->prev;
            }

            new_node->next = next_node;
            new_node->prev = next_node->prev;

            next_node->prev = new_node;
            next_node->prev->next = new_node;

            ++_list->nodes_count;

            return 5;
        }
    }
}

// Удаление узла с заданным индексом.
// В случае успеха возвращает > 0, иначе < 0.
ptrdiff_t c_list_erase(c_list *const _list,
                       const size_t _index,
                       void (*const _del_func)(void *const _data))
{
    if (_list == NULL) return -1;
    if (_index >= _list->nodes_count) return -2;

    c_list_node *delete_node;

    // Удаление из начала.
    if (_index == 0)
    {
        delete_node = _list->first;

        _list->first = _list->first->next;
        if (_list->first != NULL)
        {
            _list->first->prev = NULL;
        } else {
            _list->last = NULL;
        }

        if (_del_func != NULL)
        {
            _del_func( delete_node->data );
        }
        free(delete_node);

        --_list->nodes_count;

        return 1;
    }

    // Удаление из конца.
    if (_index == _list->nodes_count - 1)
    {
        delete_node = _list->last;

        _list->last = _list->last->prev;
        if (_list->last != NULL)
        {
            _list->last->next = NULL;
        } else {
            _list->first = NULL;
        }

        if (_del_func != NULL)
        {
            _del_func( delete_node->data );
        }
        free(delete_node);

        --_list->nodes_count;

        return 2;
    }

    // Удаление из первой половины (не из конца и не из начала).
    if (_index <= _list->nodes_count / 2)
    {
        delete_node = _list->first;
        for (size_t i = 0; i < _index; ++i)
        {
            delete_node = delete_node->next;
        }

        delete_node->prev->next = delete_node->next;
        delete_node->next->prev = delete_node->prev;

        if (_del_func != NULL)
        {
            _del_func( delete_node->data );
        }
        free(delete_node);

        --_list->nodes_count;

        return 3;
    } else {
        // Удаление из второй половины (не из начала и не из конца).
        delete_node = _list->last;
        for (size_t i = _list->nodes_count - 1; i > _index; --i)
        {
            delete_node = delete_node->prev;
        }

        delete_node->prev->next = delete_node->next;
        delete_node->next->prev = delete_node->prev;

        if (_del_func != NULL)
        {
            _del_func( delete_node->data );
        }
        free(delete_node);

        --_list->nodes_count;

        return 4;
    }
}

// Удаляет несколько узлов с заданными индексами.
// Массив, на который указывает _indexes, сортируется.
// Наличие несуществующих или одинаковых индексов не считается ошибкой.
// В случае успешного удаления возвращает количество удаленных узлов
// В случае ошибки возвращает < 0.
size_t c_list_erase_few(c_list *const _list,
                        size_t *const _indexes,
                        const size_t _indexes_count,
                        void (*const _del_func)(void *const _data))
{
    if (_list == NULL) return 0;
    if (_indexes == NULL) return 0;
    if (_indexes_count == 0) return 0;
    if (_list->nodes_count == 0) return 0;

    // Сортируем массив индексов.
    qsort(_indexes, _indexes_count, sizeof(size_t), comp_sort);

    // Если корректных индексов нет, то завершаем.
    if (_indexes[0] >= _list->nodes_count) return 0;

    // Избавимся от повторяющихся индексов.
    size_t i_index = 0;
    for (size_t i = 1; (i < _indexes_count) && (_indexes[i] < _list->nodes_count); ++i)
    {
        if (_indexes[i] != _indexes[i - 1])
        {
            _indexes[++i_index] = _indexes[i];
        }
    }

    // Теперь i_index == количеству корректных индексов.
    i_index += 1;
    // Контроль переполнения.
    if (i_index < i_index - 1) return NULL;// Не, ну а вдруг...)

    // Удалим узлы с заданными индексами и сошьем образовавшиеся в списке разрывы.
    size_t count = 0;

    c_list_node *select_node = _list->first,
                *last_not_deleted_node = NULL,
                *delete_node;

    size_t del_flag = 0;

    if (_del_func == NULL)
    {
        Тщательно проверить и протестировать ветку !=, а затем скопипастить сюда.
    } else {
        // Дублирование кода для повышения производительности,
        // чтобы при каждом переходе к новому узлу
        // не проверять _del_func == NULL.
        for (size_t i = 0; (i < _list->nodes_count) && (count < i_index); ++i)
        {
            if (i == _indexes[count])
            {
                if (del_flag == 0)
                {
                    del_flag = 1;
                    last_not_deleted_node = select_node->prev;

                    if (i == 0)
                    {
                        _list->first = NULL;
                    }
                }

                if (i == _list->nodes_count - 1)
                {
                    _list->last = NULL;
                }

                delete_node = select_node;
                select_node = select_node->next;

                _del_func( delete_node->data );
                free(delete_node);

                ++count;
            } else {
                if (del_flag == 1)
                {
                    select_node->prev = last_not_deleted_node;
                    if (last_not_deleted_node != NULL)
                    {
                        last_not_deleted_node->next = select_node;
                    }
                    del_flag = 0;
                }

                if (_list->first == NULL)
                {
                    _list->first = select_node;
                }

                select_node = select_node->next;
            }
        }
        // Контроль указателя на первый узел.
        if (_list->first == NULL)
        {
            _list->first = select_node;
            if (select_node != NULL)
            {
                _list->first->prev = NULL;
            }
        }
        // Контроль указателя на последний узел.
        if (_list->last == NULL)
        {
            _list->last = last_not_deleted_node;
            if (last_not_deleted_node != NULL)
            {
                _list->last->next = NULL;
            }
        }
        // Сшивание дыры, если вдруг она осталась.
        if (del_flag == 1)
        {
            if (last_not_deleted_node != NULL)
            {
                last_not_deleted_node->next = select_node;
            }
            if (select_node != NULL)
            {
                select_node->prev = last_not_deleted_node;
            }
        }
    }

    _list->nodes_count -= count;

    return count;
}

// Удаляет из двусвязного списка все узлы, для данных которых _comp возвращает > 0.
// Возвращает количество удаленных узлов.
// В случае ошибки возвращает 0.
size_t c_list_remove_few(c_list *const _list,
                         size_t (*const _comp)(void *const _data),
                         void (*const _del_func)(void *const _data))
{
    if (_list == NULL) return 0;
    if (_comp == NULL) return 0;
    if (_list->nodes_count == 0) return 0;

    size_t count = 0;

    c_list_node *select_node = _list->first,
                *last_not_deleted_node = NULL,
                *delete_node;

    size_t del_flag = 0;

    if (_del_func == NULL)
    {
        for (size_t i = 0; i < _list->nodes_count; ++i)
        {
            if (_comp(select_node->data) > 0)
            {
                if (del_flag == 0)
                {
                    del_flag = 1;
                    last_not_deleted_node = select_node->prev;

                    if (i == 0)
                    {
                        _list->first = NULL;
                    }
                }

                delete_node = select_node;
                select_node = select_node->next;

                free(delete_node);

                ++count;
            } else {
                if (del_flag == 1)
                {
                    select_node->prev = last_not_deleted_node;
                    if (last_not_deleted_node != NULL)
                    {
                        last_not_deleted_node->next = select_node;
                    }
                    del_flag = 0;
                }

                if (_list->first == NULL)
                {
                    _list->first = select_node;
                    _list->first->prev = NULL;
                }

                select_node = select_node->next;
            }
        }

        _list->last = last_not_deleted_node;
        _list->last->next = NULL;

        // Дублирование кода ради повышения производительности,
        // для того, чтобы при каждом переходе к следующему узлу не
        // проверять if (_del_func == NULL).
    } else {
        for (size_t i = 0; i < _list->nodes_count; ++i)
        {
            if (_comp(select_node->data) > 0)
            {
                if (del_flag == 0)
                {
                    del_flag = 1;
                    last_not_deleted_node = select_node->prev;

                    if (i == 0)
                    {
                        _list->first = NULL;
                    }
                }

                delete_node = select_node;
                select_node = select_node->next;

                _del_func(delete_node->data);
                free(delete_node);

                ++count;
            } else {
                if (del_flag == 1)
                {
                    select_node->prev = last_not_deleted_node;
                    if (last_not_deleted_node != NULL)
                    {
                        last_not_deleted_node->next = select_node;
                    }
                    del_flag = 0;
                }

                if (_list->first == NULL)
                {
                    _list->first = select_node;
                    _list->first->prev = NULL;
                }

                select_node = select_node->next;
            }
        }

        _list->last = last_not_deleted_node;
        _list->last->next = NULL;
    }

    _list->nodes_count -= count;

    return count;
}

// Возвращает указатель на данные, связанные с первым узлом.
// В случае ошибки возвращает NULL.
void *c_list_front(c_list *const _list)
{
    if (_list == NULL) return NULL;
    if (_list->nodes_count == 0) return NULL;

    return _list->first->data;
}

// Возвращает указатель на данные, связанные с узлом с заданным индексом.
// В случае ошибки возвращает NULL.
void *c_list_at(c_list *const _list,
                const size_t _index)
{
    if (_list == NULL) return NULL;
    if (_index >= _list->nodes_count) return NULL;

    c_list_node *select_node;

    if (_index <= _list->nodes_count / 2)
    {
        select_node = _list->first;
        for (size_t i = 0; i < _index; ++i)
        {
            select_node = select_node->next;
        }

        return select_node->data;
    } else {
        select_node = _list->last;
        for (size_t i = _list->nodes_count - 1; i > _index; --i)
        {
            select_node = select_node->prev;
        }

        return select_node->data;
    }
}

// Возвращает указатель на данные, связанные с последним узлом двусвязного списка.
// В случае ошибки возвращает NULL.
void *c_list_back(c_list *const _list)
{
    if (_list == NULL) return NULL;
    if (_list->nodes_count == 0) return NULL;

    return _list->last->data;
}

// Проходит по всему списку и выполненяет над данными каждого узла двусвязного списка функцию _func.
// В случае успешного выполнения возвращает > 0.
// Если двусвязный список пуст, возвращает 0.
// В случае ошибки возвращает < 0.
ptrdiff_t c_list_for_each(c_list *const _list,
                          void (*const _func)(void *const _data))
{
    if (_list == NULL) return -1;
    if (_func == NULL) return -2;
    if (_list->nodes_count == 0) return 0;

    c_list_node *select_node = _list->first;
    while (select_node != NULL)
    {
        _func( select_node->data );

        select_node = select_node->next;
    }

    return 1;
}

// Очищает список ото всех узлов.
// В случае успешного очищения возвращает > 0.
// Если элементов в списке не было, возвращает 0.
// В случае ошибки возвращает < 0.
ptrdiff_t c_list_clear(c_list *const _list,
                       void (*const _del_func)(void* const _data))
{
    if (_list == NULL) return -1;
    if (_list->nodes_count == 0) return 0;

    c_list_node *select_node = _list->first,
                *delete_node;

    if (_del_func != NULL)
    {
        while (select_node != NULL)
        {
            delete_node = select_node;
            select_node = select_node->next;

            _del_func( delete_node->data );
            free(delete_node);
        }
    } else {
        // Дублирование кода, чтобы на каждом узле не проверять,
        // задана ли функция удаления.
        while (select_node != NULL)
        {
            delete_node = select_node;
            select_node = select_node->next;

            free(delete_node);
        }
    }

    _list->first = NULL;
    _list->last = NULL;
    _list->nodes_count = 0;

    return 1;
}
