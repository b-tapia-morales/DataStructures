#include <stdio.h>
#include "list.h"

int main() {
    List* list = createList();
    addLast(list, 0);
    addLast(list, 3);
    addLast(list, 6);
    addLast(list, 9);
    addLast(list, 15);
    showList(list);
    add(list, 12, 4);
    showList(list);
    int i = indexOf(list, 9);
    printf("%d\n", i);
    addFirst(list, 0);
    showList(list);
    add(list, 18, 6);
    showList(list);
    int element = delete(list, 5);
    printf("%d\n", element);
    showList(list);
    deleteList(list);
}
