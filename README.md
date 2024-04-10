# C utils

Some utilities in C that i want to have in a single, no dependency, header file.

Files (complete/incomplete):
- [ ] list.h    - proper array-lists (cpp vectors)
- [ ] da.h - macros for easier dynamic arrays
- [ ] hashmap.h - hash maps (python dictionary)
- [ ] bstr.h    - better strings


### Description:

It's not a stb-like library, you don't have to #define X_IMPLEMENTATION, just include the file.

Not sure if this is a good way to do it, but some of the libs use macros to generate all of the functions and structs. This is done because i have no idea how to do all of it with just macros in c. For example, when you include list.h, you have to call the macro INIT_LIST(name, type), where the name is the prefix the functions will have, and the type is the type the list stores (eg. INIT_LIST(IntList, int) will make the functions IntList_make, IntList_add, IntList_insert...), and also because of the limitations, some functions (in this case the quicksort implementation) are behind another macro, so to generate those you have to also use INIT_LIST_SORT(name, type), but to generate all of the functions for types that support sorting (builtins basically) there is the macro INIT_LIST_ALL(name, type).
