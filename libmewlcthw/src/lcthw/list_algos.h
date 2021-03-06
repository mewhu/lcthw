#ifndef lcthw_List_algos_h
#define lcthw_List_algos_h

#include <lcthw/list.h>

typedef int (*List_compare)(char *a, char *b);

int List_bubble_sort(List *list, List_compare cmp);
List *List_merge_sort(List *list, List_compare cmp);

#endif
