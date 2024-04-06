/*
 * QUICKSTART
 *
 * To make a bstr, use the bstr_make function or make an empty bstr
 * with the bstr_empty macro and then change it.
 *
 * Example with the c string:
 *   char *s = "hello world!!!";
 *   bstr split_test = bstr_make(s, strlen(s));
 *
 * */

#ifndef BSTR_H_
#define BSTR_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define BSTR_ASSERT_MSG(cond, print_msg) if(!(cond)) { print_msg; exit(0); };

typedef struct{
    char *content;
    int len;
}bstr;

bstr bstr_make(char *cstr, int len);
char* bstr_to_cstr(bstr bstr);
bstr bstr_cstr_cat(bstr bstr, char *cstr, int len);
bstr bstr_cat(bstr a, bstr b);
int bstr_cmp(bstr a, bstr b);
void bstr_append(bstr *str, char chr);
bstr bstr_until(bstr str, char end);
void bstr_remove(bstr *str, int idx);
void bstr_trim_before(bstr *str, char chr);
void bstr_trim_after(bstr *str, char chr);
bstr bstr_split(bstr *str, char delim);
int bstr_equal(bstr a, bstr b);

#define bstr_print(bstr) printf("%s", bstr_to_cstr(bstr))
#define bstr_println(bstr) printf("%s\n", bstr_to_cstr(bstr))

#define bstr_empty bstr_make("", 0)

bstr bstr_make(char *cstr, int len){
    bstr bs;
    bs.content = (char*)malloc(len);
    strcpy(bs.content, cstr);
    bs.len = len;
    return bs;
}

char* bstr_to_cstr(bstr bstr){
    char* cstr = (char*)malloc(bstr.len);
    strcpy(cstr, bstr.content);
    return cstr;
}

bstr bstr_cstr_cat(bstr str, char *cstr, int len){
    bstr res;
    res.content = (char*)malloc(str.len + len);
    strcat(res.content, cstr);
    res.len = str.len + len;
    return res;
}

bstr bstr_cat(bstr a, bstr b){
    bstr res;
    res.content = (char*)malloc(a.len + b.len);
    strcpy(res.content, a.content);
    strcat(res.content, b.content);
    res.len = a.len + b.len;
    return res;
}

int bstr_cmp(bstr a, bstr b){
    return strcmp(a.content, b.content);
}

void bstr_append(bstr *str, char chr){
    char* res = (char*)realloc(str->content, str->len + 1);
    BSTR_ASSERT_MSG(res != NULL, printf("Could not reallocate memory for bstr_add\n"))
    str->content = res;
    str->content[str->len] = chr;
    str->len++;
}

bstr bstr_until(bstr str, char end){
    bstr res = bstr_empty;
    for(int i = 0; i < str.len && str.content[i] != end; i++){
        bstr_append(&res, str.content[i]);
    }
    return res;
}

void bstr_remove(bstr *str, int idx){
    for(int i = idx; i < str->len; i++){
        str->content[i] = str->content[i+1];
    }
    str->len--;
    if(str->len != 0){
        char* res = (char*)realloc(str->content, str->len);
        BSTR_ASSERT_MSG(res != NULL, printf("Could not reallocate memory for bstr_remove\n"))
        str->content = res;
    } else {
        str->content = (char*)malloc(0);
        str->len = 0;
    }
}

void bstr_trim_before(bstr *str, char chr){
    while(str->content[0] == chr){
        bstr_remove(str, 0);
    }
}

void bstr_trim_after(bstr *str, char chr){
    for(int i = str->len; str->content[i] == chr; i--){
        bstr_remove(str, i);
    }
}

bstr bstr_split(bstr *str, char delim){
    bstr res = bstr_until(*str, delim);
    for(int i = 0; i < res.len; i++){
        bstr_remove(str, 0);
    }
    if(str->len > 0) bstr_remove(str, 0);
    return res;
}

int bstr_equal(bstr a, bstr b){
    return (a.len == b.len) && bstr_cmp(a, b) == 0;
}

#endif //BSTR_H_
