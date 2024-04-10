#include <stdio.h>
#include "../list.h"
#include "../hashmap.h"
#include "../bstr.h"

INIT_LIST_ALL(IntList, int)
INIT_LIST_ALL(DoubleList, double)

double t(double x){return x*x;}

void double_test(){
    DoubleList fl = DoubleList_make();
    DoubleList_add(&fl, 1.562456);
    DoubleList_add(&fl, 2.565);
    double arr[] = {17364.44, 2.3};
    DoubleList_add_array(&fl, arr, 2);
    print_list(fl, "%lf\n");
    DoubleList_remove(&fl, 0);
    printf("\n --- \n");
    DoubleList_quicksort(&fl);
    print_list(fl, "%lf\n");
}

void int_test(){
    IntList list = IntList_make();
    IntList_add(&list, 5);
    IntList_add(&list, 9);
    IntList_add(&list, 6527);
    int arr[] = {6, 4, 6, 9, 19, 384, 23, 84, 79, 38};
    IntList_add_array(&list, arr, sizeof(arr) / sizeof(int));
    print_list(list, "%d\n");
    IntList_quicksort(&list);
    printf("\n");
    print_list(list, "%d\n");
}

INIT_HASHMAP(MapII, int, int)

void hash_test(){
    MapII map = MapII_make();
    MapII_insert(&map, 69, 90);
    MapII_insert(&map, 1, 7367);
    MapII_insert(&map, 7, 68736);
    MapII_insert(&map, 0, 38678);
    MapII_insert(&map, -5, 387);
    print_hashmap(map, "%d, ", "%d\n");
    MapII_remove(&map, -5);
    printf("---\n");
    print_hashmap(map, "%d, ", "%d\n");
    MapII_clear(&map);
    printf("---\n");
    print_hashmap(map, "%d, ", "%d\n");
    MapII_insert(&map, 0, 38678);
}

typedef struct{
    int a;
    float b;
}cool;

INIT_LIST(CoolL, cool)

void struct_list_test(){
    CoolL cl = CoolL_make();
    CoolL_add(&cl, (cool){.a = 12, .b = 34.5});
    CoolL_add(&cl, (cool){.a = -65, .b = -365.348765});
    CoolL_add(&cl, (cool){.a = 14678, .b = -584.65});
    CoolL_add(&cl, (cool){.a = 15782, .b = 4.5768});

    foreach(cool, c, CoolL, cl,
        printf("\t%d, \t%f\n", c.a, c.b);
    )
}

void bstr_test(){
    char *s = "hello my name is";
    bstr split_test = bstr_make(s, strlen(s));

    while(!(bstr_equal(split_test, bstr_empty))){
        bstr_println(bstr_split(&split_test, ' '));
    }

    char *a = "    hello everyone!  ";
    bstr trim = bstr_make(a, strlen(a));

    printf(".%s.\n", trim.content);
    bstr_trim(&trim, ' ');
    printf(".%s.\n", trim.content);
}

int main(){
    bstr_test();
}
