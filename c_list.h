/*
    Заголовочный файл односвязного списка c_forward_list
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

#ifndef C_LIST_H
#define C_LIST_H

#include <stddef.h>

typedef struct s_c_list c_list;

c_list *c_list_create(size_t *const _error);

ptrdiff_t c_list_delete(c_list *const _list,
                        void (*const _del_data)(void *const _data));

ptrdiff_t c_list_push_front(c_list *const _list,
                            const void *const _data);

ptrdiff_t c_list_pop_front(c_list *const _list,
                           void (*const _del_data)(void *const _data));

ptrdiff_t c_list_push_back(c_list *const _list,
                           const void *const _data);

ptrdiff_t c_list_pop_back(c_list *const _list,
                          void (*const _del_data)(void *const _data));

ptrdiff_t c_list_insert(c_list *const _list,
                        const void *const _data,
                        const size_t _index);

ptrdiff_t c_list_erase(c_list *const _list,
                       const size_t _index,
                       void (*const _del_data)(void *const _data));

size_t c_list_erase_few(c_list *const _list,
                        size_t *const _indexes,
                        const size_t _indexes_count,
                        void (*const _del_data)(void *const _data),
                        size_t *const _error);

size_t c_list_remove_few(c_list *const _list,
                         size_t (*const _comp_data)(const void *const _data),
                         void (*const _del_data)(void *const _data),
                         size_t *const _error);

void *c_list_front(c_list *const _list,
                   size_t *const _error);

void *c_list_at(c_list *const _list,
                const size_t _index,
                size_t *const _error);

void *c_list_back(c_list *const _list,
                  size_t *const _error);

ptrdiff_t c_list_for_each(c_list *const _list,
                          void (*const _action_data)(void *const _data));

ptrdiff_t c_list_clear(c_list *const _list,
                       void (*const _del_data)(void* const _data));

size_t c_list_nodes_count(const c_list *const _list);

#endif
