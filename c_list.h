﻿#ifndef C_LIST_H
#define C_LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

typedef struct s_c_list
{
    void *first;
    void *last;
    size_t nodes_count;
} c_list;

/* Формат узла двусвязного списка:
 *                                  |___void *next___|___void *prev___|___uint8_t data[_data_size]___|
 * Указатель на узел указывает сюда ^
 */

c_list *c_list_create(void);

ptrdiff_t c_list_delete(c_list *const _list,
                        void (*const _del_func)(void *const _data));

void *c_list_push_front(c_list *const _list,
                        const size_t _data_size);

ptrdiff_t c_list_pop_front(c_list *const _list,
                           void (*const _del_func)(void *const _data));

void *c_list_push_back(c_list *const _list,
                       const size_t _data_size);

ptrdiff_t c_list_pop_back(c_list *const _list,
                          void (*const _del_func)(void *const _data));

void *c_list_insert(c_list *const _list,
                    const size_t _data_size,
                    const size_t _index);

ptrdiff_t c_list_erase(c_list *const _list,
                       const size_t _index,
                       void (*const _del_func)(void *const _data));

size_t c_list_erase_few(c_list *const _list,
                        size_t *const _indexes,
                        const size_t _indexes_count,
                        void (*const _del_func)(void *const _data));

size_t c_list_remove_few(c_list *const _list,
                         size_t (*const _comp)(void *const _data),
                         void (*const _del_func)(void *const _data));

void *c_list_front(c_list *const _list);

void *c_list_at(c_list *const _list,
                const size_t _index);

void *c_list_back(c_list *const _list);

ptrdiff_t c_list_for_each(c_list *const _list,
                          void (*const _func(void *const _data)));

ptrdiff_t c_list_clear(c_list *const _list,
                       void (*const _del_func)(void* const _data));

#endif
