#include "c_list.h"

// ������� ����� ���������� ������.
// � ������ ������ ���������� NULL.
c_list *c_list_create(void)
{
    c_list *new_list = (c_list*)malloc(sizeof(c_list));
    if (new_list == NULL) return NULL;

    new_list->first = NULL;
    new_list->last = NULL;
    new_list->nodes_count = 0;

    return new_list;
}

// ������� ���������� ������.
// � ������ ������ ���������� > 0, ����� < 0.
ptrdiff_t c_list_delete(c_list *const _list,
                        void (*const _del_func)(void *const _data))
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

                _del_func((void**)delete_node + 2);
                free(delete_node);
            }
        } else {
            while(select_node != NULL)
            {
                delete_node = select_node;
                select_node = *((void**)select_node);

                free(delete_node);
            }
        }
    }

    free(_list);

    return 1;
}

// ��������� ����� ���� � ������ ����������� ������.
// � ������ ������ ���������� ��������� �� �������������������� ������ ������������ ����.
// � ������ ������ ���������� NULL.
void *c_list_push_front(c_list *const _list,
                        const size_t _data_size)
{
    if (_list == NULL) return NULL;
    if (_data_size == 0) return NULL;

    // �������� ������������.
    const size_t new_node_size = 2 * sizeof(void*) + _data_size;
    if (new_node_size < _data_size) return NULL;

    void *new_node = malloc(new_node_size);
    if (new_node == NULL) return NULL;

    *((void**)new_node) = _list->first;
    *(((void**)new_node) + 1) = NULL;

    if (_list->nodes_count == 0)
    {
        _list->last = new_node;
    } else {
        *(((void**)_list->first) + 1) = new_node;
    }

    _list->first = new_node;

    ++_list->nodes_count;

    return (void**)_list->first + 2;
}

// ������� ���� �� ������ ����������� ������.
// � ������ ������ ���������� > 0, ����� < 0.
ptrdiff_t c_list_pop_front(c_list *const _list,
                           void (*const _del_func)(void *const _data))
{
    if (_list == NULL) return -1;
    if (_list->nodes_count == 0) return -2;

    void *delete_node = _list->first;

    _list->first = *((void**)_list->first);
    if (_list->first != NULL)
    {
        *(((void**)_list->first) + 1) = NULL;
    } else {
        _list->last = NULL;
    }

    if (_del_func != NULL)
    {
        _del_func((void**)delete_node + 2);
    }

    free(delete_node);

    --_list->nodes_count;

    return 1;
}

// ��������� ����� ���� � ����� ����������� ������.
// � ������ ������ ���������� ��������� �� �������������������� ������ ������������ ����.
// � ������ ������ ���������� NULL.
void *c_list_push_back(c_list *const _list,
                       const size_t _data_size)
{
    if (_list == NULL) return NULL;
    if (_data_size == 0) return NULL;

    // �������� ������������.
    const size_t new_node_size = 2 * sizeof(void*) + _data_size;
    if (new_node_size < _data_size) return NULL;

    void *new_node = malloc(new_node_size);
    if (new_node == NULL) return NULL;

    *((void**)new_node) = NULL;
    *(((void**)new_node) + 1) = _list->last;

    if (_list->nodes_count == 0)
    {
        _list->first = new_node;
    } else {
        *((void**)_list->last) = new_node;
    }

    _list->last = new_node;

    ++_list->nodes_count;

    return (void**)_list->last + 2;
}

// ������� ���� � ����� ����������� ������.
// � ������ ������ ���������� > 0, ����� < 0.
ptrdiff_t c_list_pop_back(c_list *const _list,
                          void (*const _del_func)(void *const _data))
{
    if (_list == NULL) return -1;
    if (_list->nodes_count == 0) return -2;

    void *delete_node = _list->last;

    _list->last = *((void**)_list->last + 1);
    if (_list->last != NULL)
    {
        *((void**)_list->last) = NULL;
    } else {
        _list->first = NULL;
    }

    if (_del_func != NULL)
    {
        _del_func((void**)delete_node + 2);
    }

    free(delete_node);

    --_list->nodes_count;

    return 1;
}

// ������� ������ ���� � �������� �������.
// � ������ ������ ���������� ��������� �� �������������������� ������ ������ ����.
// � ������ ������ ���������� NULL.
// ��������� ��������� � ������ ������, ���� _index = 0.
void *c_list_insert(c_list *const _list,
                    const size_t _data_size,
                    const size_t _index)
{
    if (_list == NULL) return NULL;
    if (_data_size == 0) return NULL;
    if (_index > _list->nodes_count) return NULL;

    // �������� ������������.
    const size_t new_node_size = 2 * sizeof(void*) + _data_size;
    if (new_node_size < _data_size) return NULL;

    void *new_node = malloc(new_node_size);
    if (new_node == NULL) return NULL;

    // ���� ������ ����.
    if (_list->nodes_count == 0)
    {
        *((void**)new_node) = NULL;
        *((void**)new_node + 1) = NULL;

        _list->first = new_node;
        _list->last = new_node;

        ++_list->nodes_count;

        return (void**)new_node + 2;
    } else {
        // ������� � ������.
        if (_index == 0)
        {
            *((void**)new_node) = _list->first;
            *((void**)new_node + 1) = NULL;

            *((void**)_list->first + 1) = new_node;
            _list->first = new_node;

            ++_list->nodes_count;

            return (void**)new_node + 2;
        }
        // ������� � �����.
        if (_index == _list->nodes_count)
        {
            *((void**)new_node) = NULL;
            *((void**)new_node + 1) = _list->last;

            *((void**)_list->last) = new_node;
            _list->last = new_node;

            ++_list->nodes_count;

            return (void**)new_node + 2;
        }
        // ������� � ��������.
        if (_index <= _list->nodes_count / 2)
        {
            void *prev_node = _list->first;
            for (size_t i = 0; i < _index - 1; ++i)
            {
                prev_node = *((void**)prev_node);
            }

            *((void**)new_node) = *((void**)prev_node);
            *((void**)new_node + 1) = prev_node;

            *( ( (void**) ( *((void**)prev_node) ) ) + 1 ) = new_node;
            *((void**)prev_node) = new_node;

            ++_list->nodes_count;

            return (void**)new_node + 2;
        } else {
            void *next_node = _list->last;
            for (size_t i = _list->nodes_count - 1; i > _index; --i)
            {
                next_node = *((void**)next_node + 1);
            }

            *((void**)new_node) = next_node;
            *((void**)new_node + 1) = *((void**)next_node + 1);

            *( (void**) ( *((void**)next_node + 1) ) ) = new_node;
            *((void**)next_node + 1) = new_node;

            ++_list->nodes_count;

            return (void**)new_node + 2;
        }
    }
}

// �������� ���� � �������� ��������.
// � ������ ������ ���������� > 0, ����� < 0.
ptrdiff_t c_list_erase(c_list *const _list,
                       const size_t _index,
                       void (*const _del_func)(void *const _data))
{
    if (_list == NULL) return -1;
    if (_index >= _list->nodes_count) return -2;

    void *delete_node;

    // �������� �� ������.
    if (_index == 0)
    {
        delete_node = _list->first;

        _list->first = *((void**)_list->first);
        if (_list->first != NULL)
        {
            *((void**)_list->first + 1) = NULL;
        } else {
            _list->last = NULL;
        }

        if (_del_func != NULL)
        {
            _del_func((void**)delete_node + 2);
        }
        free(delete_node);

        --_list->nodes_count;

        return 1;
    }

    // �������� �� �����.
    if (_index == _list->nodes_count - 1)
    {
        delete_node = _list->last;

        _list->last = *((void**)_list->last + 1);
        if (_list->last != NULL)
        {
            *((void**)_list->last) = NULL;
        } else {
            _list->first = NULL;
        }

        if (_del_func != NULL)
        {
            _del_func((void**)delete_node + 2);
        }
        free(delete_node);

        --_list->nodes_count;

        return 2;
    }

    // �������� �� �� ����� � �� �� ������.
    if (_index <= _list->nodes_count / 2)
    {
        delete_node = _list->first;
        for (size_t i = 0; i < _index; ++i)
        {
            delete_node = *((void**)delete_node);
        }

        *((void**)(*((void**)delete_node + 1))) = *((void**)delete_node);
        *(((void**)(*((void**)delete_node))) + 1) = *((void**)delete_node + 1);

        if (_del_func != NULL)
        {
            _del_func((void**)delete_node + 2);
        }
        free(delete_node);

        --_list->nodes_count;

        return 3;
    } else {
        delete_node = _list->last;
        for (size_t i = _list->nodes_count - 1; i > _index; --i)
        {
            delete_node = *((void**)delete_node + 1);
        }

        *((void**)(*((void**)delete_node + 1))) = *((void**)delete_node);
        *(((void**)(*((void**)delete_node))) + 1) = *((void**)delete_node + 1);

        if (_del_func != NULL)
        {
            _del_func((void**)delete_node + 2);
        }
        free(delete_node);

        --_list->nodes_count;

        return 4;
    }
}

// ������� ��������� ����� � ��������� ���������.
// ������, �� ������� ��������� _indexes, �����������.
// ������� �������������� ��� ���������� �������� �� ��������� �������.
// � ������ ������ ������� ���������� ���-�� ��������� �����.
// � ������ ������ 0.
size_t c_list_erase_few(c_list *const _list,
                        size_t *const _indexes,
                        const size_t _indexes_count,
                        void (*const _del_func)(void *const _data))
{
    if (_list == NULL) return 0;
    if (_indexes == NULL) return 0;
    if (_indexes_count == 0) return 0;
    if (_list->nodes_count == 0) return 0;

    // ���������� ��� ���������� �������.
    ptrdiff_t comp_sort(const void *const _a,
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

    // ��������� ������ ��������.
    qsort(_indexes, _indexes_count, sizeof(size_t), comp_sort);

    // ���� ���������� �������� ���, �� ���������.
    if (_indexes[0] > _list->nodes_count) return 0;

    // ��������� �� ������������� ��������.
    size_t i_index = 0;
    for (size_t i = 1; (i < _indexes_count) && (_indexes[i] < _list->nodes_count); ++i)
    {
        if (_indexes[i] != _indexes[i - 1])
        {
            _indexes[++i_index] = _indexes[i];
        }
    }

    // ������ i_index == ���������� ���������� ��������.
    i_index += 1;

    // ������ ���� � ��������� ��������� � ������ �������������� � ������ �������.
    size_t count = 0;

    void *select_node = _list->first,
         *last_not_deleted_node = NULL,
         *delete_node;

    size_t del_flag = 0;

    if (_del_func == NULL)
    {
        for (size_t i = 0; (i < _list->nodes_count) && (count < i_index); ++i)
        {
            if (i == _indexes[count])
            {
                if (del_flag == 0)
                {
                    del_flag = 1;
                    last_not_deleted_node = *((void**)select_node + 1);

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
                select_node = *((void**)select_node);

                free(delete_node);

                ++count;
            } else {
                if (del_flag == 1)
                {
                    *((void**)select_node + 1) = last_not_deleted_node;
                    if (last_not_deleted_node != NULL)
                    {
                        *((void**)last_not_deleted_node) = select_node;
                    }
                    del_flag = 0;
                }

                if (_list->first == NULL)
                {
                    _list->first = select_node;
                }

                select_node = *((void**)select_node);
            }
        }
        if (_list->first == NULL)
        {
            _list->first = select_node;
            *((void**)_list->first + 1) = NULL;
        }

        if (_list->last == NULL)
        {
            _list->last = last_not_deleted_node;
            *((void**)_list->last) = NULL;
        }
        // ������������ ���� ��� ��������� ������������������,
        // ����� ��� ������ �������� � ������ ����
        // �� ��������� _del_func == NULL.
    } else {
        for (size_t i = 0; (i < _list->nodes_count) && (count < i_index); ++i)
        {
            if (i == _indexes[count])
            {
                if (del_flag == 0)
                {
                    del_flag = 1;
                    last_not_deleted_node = *((void**)select_node + 1);

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
                select_node = *((void**)select_node);

                _del_func((void**)delete_node + 2);
                free(delete_node);

                ++count;
            } else {
                if (del_flag == 1)
                {
                    *((void**)select_node + 1) = last_not_deleted_node;
                    if (last_not_deleted_node != NULL)
                    {
                        *((void**)last_not_deleted_node) = select_node;
                    }
                    del_flag = 0;
                }

                if (_list->first == NULL)
                {
                    _list->first = select_node;
                }

                select_node = *((void**)select_node);
            }
        }
        if (_list->first == NULL)
        {
            _list->first = select_node;
            *((void**)_list->first + 1) = NULL;
        }

        if (_list->last == NULL)
        {
            _list->last = last_not_deleted_node;
            *((void**)_list->last) = NULL;
        }
    }

    _list->nodes_count -= count;

    return count;
}

// ������� �� ����������� ������ ��� ����, ��� ������ ������� _comp ���������� > 0.
// ���������� ���������� ��������� �����.
// � ������ ������ ���������� 0.
size_t c_list_remove_few(c_list *const _list,
                         size_t (*const _comp)(void *const _data),
                         void (*const _del_func)(void *const _data))
{
    if (_list == NULL) return 0;
    if (_comp == NULL) return 0;
    if (_list->nodes_count == 0) return 0;

    size_t count = 0;

    void *select_node = _list->first,
         *last_not_deleted_node = NULL,
         *delete_node;

    size_t del_flag = 0;

    if (_del_func == NULL)
    {
        for (size_t i = 0; i < _list->nodes_count; ++i)
        {
            if (_comp((void**)select_node + 2) > 0)
            {
                if (del_flag == 0)
                {
                    del_flag = 1;
                    last_not_deleted_node = *((void**)select_node + 1);

                    if (i == 0)
                    {
                        _list->first = NULL;
                    }
                }

                delete_node = select_node;
                select_node = *((void**)select_node);

                free(delete_node);

                ++count;
            } else {
                if (del_flag == 1)
                {
                    *((void**)select_node + 1) = last_not_deleted_node;
                    if (last_not_deleted_node != NULL)
                    {
                        *((void**)last_not_deleted_node) = select_node;
                    }
                    del_flag = 0;
                }

                if (_list->first == NULL)
                {
                    _list->first = select_node;
                    *((void**)_list->first + 1) = NULL;
                }

                select_node = *((void**)select_node);
            }
        }

        _list->last = last_not_deleted_node;
        *((void**)_list->last) = NULL;

        // ������������ ���� ���� ��������� ������������������,
        // ��� ����, ����� ��� ������ �������� � ���������� ���� ��
        // ��������� if (_del_func == NULL).
    } else {
        for (size_t i = 0; i < _list->nodes_count; ++i)
        {
            if (_comp((void**)select_node + 2) > 0)
            {
                if (del_flag == 0)
                {
                    del_flag = 1;
                    last_not_deleted_node = *((void**)select_node + 1);

                    if (i == 0)
                    {
                        _list->first = NULL;
                    }
                }

                delete_node = select_node;
                select_node = *((void**)select_node);

                _del_func((void**)delete_node + 2);
                free(delete_node);

                ++count;
            } else {
                if (del_flag == 1)
                {
                    *((void**)select_node + 1) = last_not_deleted_node;
                    if (last_not_deleted_node != NULL)
                    {
                        *((void**)last_not_deleted_node) = select_node;
                    }
                    del_flag = 0;
                }

                if (_list->first == NULL)
                {
                    _list->first = select_node;
                    *((void**)_list->first + 1) = NULL;
                }

                select_node = *((void**)select_node);
            }
        }

        _list->last = last_not_deleted_node;
        *((void**)_list->last) = NULL;
    }

    _list->nodes_count -= count;

    return count;
}

// ���������� ��������� �� ������ ������� ���� ����������� ������.
// � ������ ������ ���������� NULL.
void *c_list_front(c_list *const _list)
{
    if (_list == NULL) return NULL;
    if (_list->nodes_count == 0) return NULL;

    return (void**)_list->first + 2;
}

// ���������� ��������� �� ������ ���� ����������� ������ � �������� ��������.
// � ������ ������ ���������� NULL.
void *c_list_at(c_list *const _list,
                const size_t _index)
{
    if (_list == NULL) return NULL;
    if (_index >= _list->nodes_count) return NULL;

    void *select_node;

    if (_index <= _list->nodes_count / 2)
    {
        select_node = _list->first;
        for (size_t i = 0; i < _index; ++i)
        {
            select_node = *((void**)select_node);
        }

        return (void**)select_node + 2;
    } else {
        select_node = _list->last;
        for (size_t i = _list->nodes_count - 1; i > _index; --i)
        {
            select_node = *((void**)select_node + 1);
        }

        return (void**)select_node + 2;
    }
}

// ���������� ��������� �� ������ ���������� ���� ����������� ������.
// � ������ ������ ���������� NULL.
void *c_list_back(c_list *const _list)
{
    if (_list == NULL) return NULL;
    if (_list->nodes_count == 0) return NULL;

    return (void**)_list->last + 2;
}

// ������ �� ����� ������ � ���������� ��� ������� ������� ���� ����������� ������ ������� _func.
// � ������ ������ ���������� > 0, � ������ ������ < 0.
ptrdiff_t c_list_for_each(c_list *const _list,
                          void (*const _func(void *const _data)))
{
    if (_list == NULL) return -1;
    if (_func == NULL) return -2;
    if (_list->nodes_count == 0) return 1;

    void *select_node = _list->first;
    while(select_node != NULL)
    {
        _func((void**)select_node + 2);

        select_node = *((void**)select_node);
    }

    return 2;
}

// ������� ������ ��� ���� �����.
// � ������ ������ ���������� > 0, � ������ ������ < 0.
ptrdiff_t c_list_clear(c_list *const _list,
                       void (*const _del_func)(void* const _data))
{
    if (_list == NULL) return -1;
    if (_list->nodes_count == 0) return 1;

    void *select_node = _list->first,
         *delete_node;

    if (_del_func != NULL)
    {
        while(select_node != NULL)
        {
            delete_node = select_node;
            select_node = *((void**)select_node);

            _del_func((void**)delete_node + 2);
            free(delete_node);
        }
    } else {
        while(select_node != NULL)
        {
            delete_node = select_node;
            select_node = *((void**)select_node);

            free(delete_node);
        }
    }

    _list->first = NULL;
    _list->last = NULL;
    _list->nodes_count = NULL;

    return 1;
}
