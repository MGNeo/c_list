#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "c_list.h"

void del_func(void *const _data)
{
    free( *((void**)_data) );
}

size_t comp(void *const _data)
{
    float f = *((float*)_data);
    float r = ( rand() % RAND_MAX ) * pow(-1, rand() % 2);
    if (f > r)
    {
        return 1;
    }
    return 0;
}

int main()
{
    size_t iteration = 0;

    srand(time(NULL));

    const size_t INSERT_COUNT = 1E4;

    AGAIN:;

    ++iteration;
    printf("Iteration: %Iu\n", iteration);

    // �������� ����������� ������.
    c_list *list = c_list_create();

    // ������� � ������.
    c_list_push_back(list, sizeof(void*));

    // ������� � ��������� �������.
    for (size_t i = 0; i < INSERT_COUNT; ++i)
    {
        const size_t index = rand() % list->nodes_count;
        void *data = c_list_insert(list, sizeof(void*), index);
        *((void**)data) = malloc(sizeof(float));
        *((float*)*((void**)data)) = ( rand() % RAND_MAX ) * pow(-1, rand() % 2);
    }

    // �������� �� ���������� �������� ������.
    c_list_remove_few(list, comp, del_func);
    printf("nodes count after delete: %Iu\n", list->nodes_count);
    printf("first: %Iu\n", (size_t)list->first);
    printf("last: %Iu\n", (size_t)list->last);

    // �������� ����� � ��������� ���������.
    size_t indexes[] = {0, 1};
    c_list_erase_few(list, indexes, 2, del_func);// �������� ������ ������.
    printf("nodes count after delete: %Iu\n", list->nodes_count);
    printf("first: %Iu\n", (size_t)list->first);
    printf("last: %Iu\n", (size_t)list->last);

    // �������� ������.
    c_list_delete(list, del_func);

    // ������ ������������.
    goto AGAIN;
    return 0;
}

/*

2) ������� �������� � �������� ����������� first � c_list_erase_few.

*/
