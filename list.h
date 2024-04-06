/*
 * QUICKSTART
 * 
 * To start using a list, you first need to generate the functions
 * for the specific types. To do this use the INIT_LIST macro.
 *
 * Example (list that contains ints):
 *   INIT_LIST(IntList, int)
 *
 *
 * When you've generated the functions with the macro, you can initialize
 * it with the `name`_make function, where the name is the first argument
 * in the INIT_LIST macro.
 *
 * Example (using previous declarations):
 *   IntList list = IntList_make();
 *
 *
 * If the provided type is comperable, you can also generate the sorting
 * functions. To do that use the INIT_LIST_SORT(name, type) macro after
 * the INIT_LIST macro or just use the INIT_LIST_ALL macro, as for now all
 * that there is for lists is basic functionality and a quicksort
 * implementation.
 * 
 * Example:
 *   INIT_LIST_ALL(DoubleList, double)
 *
 * */

#ifndef LIST_H_
#define LIST_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LIST_ASSERT_MSG(cond, print_msg) if(!(cond)) { print_msg; exit(0); };

#define DEFAULT_SIZE 32

#define INIT_LIST(name, type)   \
typedef struct{                 \
    type *content; \
    int count;                  \
    int capacity; \
}name;                          \
                                \
name name ## _make(){           \
    name list;                  \
    list.content = malloc(DEFAULT_SIZE * sizeof(type)); \
    list.count = 0;             \
    list.capacity = DEFAULT_SIZE;\
    return list;                \
}                               \
                                \
void name ## _add(name *list, type el){                                 \
    if(list->capacity <= list->count){                                  \
        list->capacity *= 2;                                            \
        type *n = realloc(list->content, list->capacity * sizeof(type));\
        LIST_ASSERT_MSG(!n, printf("Could not reallocate memory"))      \
        list->content = n;                                              \
    }                                                                   \
    list->content[list->count++] = el;                                  \
}                                                                       \
                                                                        \
type name ## _get(name list, int index){                                \
    LIST_ASSERT_MSG(index < list.count, printf("Cannot access element at index %d, count is %d\n", index, list.count));\
    return list.content[index];                                         \
}                                                                       \
                                                                        \
void name ## _add_array(name *list, type *arr, int arr_len){            \
    for(int i = 0; i < arr_len; i++){                                   \
        name ## _add(list, arr[i]);                                     \
    }                                                                   \
}                                                                       \
                                                            \
void name ## _insert(name *list, type el, int idx){         \
    LIST_ASSERT_MSG(idx < 0 || idx > list->count,                \
            printf("Cannot insert element at index %d, count is %d\n", idx, list->count));  \
    name ## _add(list, el);                                 \
    for(int i = list->count - 1; i > idx -1; i--){          \
        list->content[i+1] = list->content[i];              \
    }                                                       \
    list->content[idx] = el;                                \
}                                                           \
                                                            \
void name ## _remove(name *list, int idx){                  \
    LIST_ASSERT_MSG(idx >= 0 && idx < list->count,              \
            printf("Cannot remove element at index %d, count is %d\n", idx, list->count));  \
    for(int i = idx; i < list->count; i++){                 \
        list->content[i] = list->content[i+1];              \
    }                                                       \
    list->count--;                                          \
}                                                           \
                                                            \
void name ## _set(name *list, type el, int idx){            \
    LIST_ASSERT_MSG(idx < list->count, printf("Cannot set element at index %d, count is %d\n", idx, list->count));\
    list->content[idx] = el;                                \
}                                                           \


#define INIT_LIST_SORT(name, type)  \
int name ## _partition(name *list, int p, int r){           \
    type x = name ## _get(*list, r);                        \
    int i = p - 1;                                          \
    for(int j = p; j <= r - 1; j++){                        \
        if(name ## _get(*list, j) <= x){                    \
            i++;                                            \
            type old = name ## _get(*list, i);              \
            name ## _set(list, name ## _get(*list, j), i);  \
            name ## _set(list, old, j);                     \
        }                                                   \
    }                                                       \
    type old = name ## _get(*list, i + 1);                  \
    name ## _set(list, name ## _get(*list, r), i + 1);      \
    name ## _set(list, old, r);                             \
    return i + 1;                                           \
}                                                           \
                                                            \
void name ## _quicksort_rec(name *list, int p, int r){      \
    if(p < r){                                              \
        int q = name ## _partition(list, p, r);             \
        name ## _quicksort_rec(list, p, q - 1);             \
        name ## _quicksort_rec(list, q + 1, r);             \
    }                                                       \
}                                                           \
                                                            \
void name ## _quicksort(name *list){                        \
    name ## _quicksort_rec(list, 0, list->count - 1);       \
}                                                           \


#define INIT_LIST_ALL(name, type)\
    INIT_LIST(name, type)\
    INIT_LIST_SORT(name, type)


#define foreach(val_type, name, list_type, list, block) \
{   int name ## _i = 0;                                 \
    val_type name = list_type ## _get(list, 0);         \
    for(; name ## _i < list.count -1; name ## _i++, name = list_type ## _get(list, name ## _i)) {block} block }\

#define print_list(list, fmt) \
    do{ for(int i = 0; i < list.count; i++) printf(fmt, list.content[i]); }while(0)

#endif //LIST_H_
