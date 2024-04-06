/*
 * QUICKSTART
 * 
 * To start using a hashmap, you first need to generate the functions
 * for the specific types. To do this use the INIT_HASHMAP macro.
 *
 * Example (hashmap whose key is of type int, and value of type float):
 *   INIT_HASHMAP(HashMapIF, int, float)
 *
 *
 * When you've generated the functions with the macro, you can initialize
 * it with the `name`_make function, where the name is the first argument
 * in the INIT_HASHMAP macro.
 *
 * Example (using previous declarations):
 *   HashMapIF map = HashMapIF_make();
 *
 *
 * */

#ifndef HASHMAP_H_
#define HASHMAP_H_

#include <stdio.h>

#define HM_ASSERT_MSG(cond, print_msg) if(!(cond)) { print_msg; exit(0); };

#define HASHMAP_INIT_SIZE 32

#define INIT_HASHMAP(name, key_type, value_type)   \
typedef struct{                 \
    key_type key;               \
    value_type value;           \
}name ## _set;                  \
                                \
typedef struct{                 \
    name ## _set *content;      \
    int count;                  \
    int capacity;               \
}name;                          \
                                \
name name ## _make(){           \
    name map;                   \
    map.content = malloc(HASHMAP_INIT_SIZE * sizeof(name ## _set)); \
    map.count = 0;              \
    map.capacity = HASHMAP_INIT_SIZE;\
    return map;                 \
}                               \
                                \
int name ## _key_exists(name map, key_type key){ \
    for(int i = 0; i < map.count; i++){          \
        if(map.content[i].key == key) return 1;  \
    }                                            \
    return 0;                                    \
}                                                \
                                                 \
void name ## _insert(name *map, key_type key, value_type value){          \
    if(map->capacity <= map->count){                                      \
        map->capacity *= 2;                                               \
        name ## _set *n = realloc(map->content, map->capacity * sizeof(name ## _set));\
        HM_ASSERT_MSG(!n, printf("Could not reallocate memory");)         \
        map->content = n;                                                 \
    }                                                                     \
    HM_ASSERT_MSG(!(name ## _key_exists(*map, key)), printf("Tried adding a value, but key already exists"));\
    map->content[map->count] = (name ## _set){.key = key, .value = value};\
    map->count++;                                                         \
}                                                                         \
                                                                          \
value_type name ## _get(name map, key_type key){                          \
    for(int i = 0; i < map.count; i++){                                   \
        if(map.content[i].key == key) return map.content[i].value;        \
    }                                                                     \
    HM_ASSERT_MSG(0, printf("Tried getting value for non-existant key")); \
    return map.content[0].value;                                          \
}                                                                         \
                                                                          \
void name ## _remove(name *map, key_type key){                           \
    int idx = -1;                                                        \
    for(int i = 0; i < map->count; i++){                                 \
        if(map->content[i].key == key) {idx = i; break;}                 \
    }                                                                    \
    HM_ASSERT_MSG(idx != -1, printf("Tried removing value for non-existant key"));\
    for(int i = idx; i < map->count-1; i++){                             \
        map->content[i] = map->content[i+1];                             \
    }                                                                    \
    map->count--;                                                        \
}                                                                        \
                                                                         \
void name ## _assign(name map, key_type key, value_type value){          \
    for(int i = 0; i < map.count; i++){                                      \
        if(map.content[i].key == key) {map.content[i].value = value; return;}\
    }                                                                        \
    HM_ASSERT_MSG(0, printf("Tried getting value for non-existant key"));    \
}                                                                            \
                                                                     \
void name ## _clear(name *map){                                      \
    free(map->content);                                              \
    map->content = malloc(HASHMAP_INIT_SIZE * sizeof(name ## _set)); \
    map->count = 0;                                                  \
    map->capacity = HASHMAP_INIT_SIZE;                               \
}


#define print_hashmap(map, fmt1, fmt2)          \
    do { for(int i = 0; i < map.count; i++){    \
            printf(fmt1, map.content[i].key);   \
            printf(fmt2, map.content[i].value); \
        } } while(0)


#endif // HASHMAP_H_
