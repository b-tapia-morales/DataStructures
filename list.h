#include <stdio.h>
#include <stdbool.h>
#include "node.h"

#ifndef LIST_H
#define LIST_H

#endif //LIST_H

typedef struct List {
    int size;
    Node *first;
    Node *last;
} List;

/**
 * Crea una nueva lista vacía.
 * @return La lista
 */
List *createList();

/**
 * Añade el elemento como el primer elemento en lista.
 * @param list La lista
 * @param element El elemento a añadir
 */
void addFirst(List *list, int element);

/**
 * Añade el elemento como el último elemento en lista.
 * @param list La lista
 * @param element El elemento a añadir
 */
void addLast(List *list, int element);

/**
 * Inserta el elemento en la posición especificada en lista, desplazando el elemento que está ocupando actualmente esa
 * posición (si lo hay) y cualquier elemento posterior hacia la derecha.
 * @param list La lista
 * @param element El elemento a añadir
 * @param index La posición en la que será añadido el elemento
 */
void add(List *list, int element, int index);

/**
 * Añade todos los elementos de la segunda lista al final de la primera lista
 * @param this La lista a la que se le añadirán los elementos
 * @param other La lista que contiene los elementos a añadir
 */
void addAll(List *this, List *other);

/**
 * Elimina el primer elemento en lista, y lo devuelve.
 * @param list La lista
 * @return El primer elemento en lista
 */
int deleteFirst(List *list);

/**
 * Elimina el último elemento en lista, y lo devuelve.
 * @param list La lista
 * @return El último elemento en lista
 */
int deleteLast(List *list);

/**
 * Elimina el elemento en la posición especificada en lista, desplazando cualquier elemento posterior hacia la
 * izquierda. Devuelve el elemento eliminado de la lista.
 * @param list La lista
 * @param index El índice del elemento a eliminar
 */
int delete(List *list, int index);

/**
 * Devuelve el índice de la primera vez que aparece el elemento en la lista, o -1 si ésta no contiene el elemento.
 * @param list La lista
 * @param element El elemento a buscar
 * @return El índice de la primera vez que aparece el elemento en lista, o -1
 */
int indexOf(List *list, int element);

/**
 * Determina si la lista contiene el elemento especificado.
 * @param list La lista
 * @param element El elemento a buscar
 * @return true si la lista contiene el elemento; de lo contrario, false.
 */
bool contains(List *list, int element);

/**
 * Elimina todos los elementos en la lista, liberando los bloques de memoria previamente asignados a cada uno de ellos.
 * La lista quedará vacía después de que este método haya sido llamado.
 * @param list La lista
 */
void clearList(List *list);

/**
 * Elimina la lista, liberando tanto el bloque de memoria previamente asignada a ella como los bloques de memoria
 * correspondientes a todos los elementos en lista. La lista será una referencia nula después de que este método haya
 * sido llamado.
 * @param list La lista
 */
void deleteList(List *list);

void addToEmptyList__(List *list, Node *node);

void addInMiddle__(List *list, Node *node, Node *prev, Node *next);

int deleteInMiddle__(List *list, Node *node, Node *prev, Node *next);

List *createList() {
    List *list = (List *) malloc(sizeof(List));
    assert((list != NULL) && ("Attempt to allocate memory for List was unsuccessful"));
    list->size = 0;
    list->first = list->last = NULL;
    return list;
}

void addFirst(List *list, int element) {
    assert((list != NULL) && ("Provided List is null"));
    Node *node = createNode(element);
    assert((node != NULL) && ("Attempt to allocate memory for Node was unsuccessful"));
    if (list->size == 0) {
        addToEmptyList__(list, node);
        return;
    }
    node->next = list->first;
    list->first->prev = node;
    list->first = node;
    list->size++;
}

void addLast(List *list, int element) {
    assert((list != NULL) && ("Provided List is null"));
    Node *node = createNode(element);
    assert((node != NULL) && ("Attempt to allocate memory for Node was unsuccessful"));
    if (list->size == 0) {
        addToEmptyList__(list, node);
        return;
    }
    node->prev = list->last;
    list->last->next = node;
    list->last = node;
    list->size++;
}

void add(List *list, int element, int index) {
    assert((list != NULL) && ("Provided List is null"));
    assert((index >= 0 && index <= list->size) && ("Index can't be lesser than 0 or greater than size"));
    if (index == 0) {
        addFirst(list, element);
        return;
    }
    if (index == list->size) {
        addLast(list, element);
        return;
    }
    Node *node = createNode(element);
    assert((node != NULL) && ("Attempt to allocate memory for Node was unsuccessful"));
    Node *prev = list->first;
    Node *next = prev->next;
    for (int i = 1; i < list->size; i++) {
        if (i == index) {
            addInMiddle__(list, node, prev, next);
            return;
        }
        prev = prev->next;
        next = prev->next;
    }
}

void addToEmptyList__(List *list, Node *node) {
    list->first = list->last = node;
    list->size = 1;
}

void addInMiddle__(List *list, Node *node, Node *prev, Node *next) {
    node->prev = prev;
    node->next = next;
    prev->next = node;
    next->prev = node;
    list->size++;
}

int deleteFirst(List *list) {
    assert((list != NULL) && ("Provided List is null"));
    assert((list->size != 0) && ("Attempted to delete elements from an empty list"));
    Node *node = list->first;
    int element = node->element;
    list->first = list->first->next;
    list->first->prev = NULL;
    deleteNode(node);
    list->size--;
    return element;
}

int deleteLast(List *list) {
    assert((list != NULL) && ("Provided List is null"));
    assert((list->size != 0) && ("Attempted to delete elements from an empty list"));
    Node *node = list->last;
    int element = node->element;
    list->last = list->last->prev;
    list->last->next = NULL;
    deleteNode(node);
    list->size--;
    return element;
}

int delete(List *list, int index) {
    assert((list != NULL) && ("Provided List is null"));
    assert((list->size != 0) && ("Attempted to delete elements from an empty list"));
    assert((index <= list->size - 1) && ("Attempted to delete from an index greater than list size"));
    if (index == 0) {
        int element = deleteFirst(list);
        return element;
    }
    if (index == list->size - 1) {
        int element = deleteFirst(list);
        return element;
    }
    Node *prev = list->first;
    Node *node = list->first->next;
    Node *next = list->first->next->next;
    int element = 0;
    for (int i = 1; i < list->size - 1; i++) {
        if (i == index) {
            element = deleteInMiddle__(list, node, prev, next);
            break;
        }
        prev = prev->next;
        node = prev->next;
        next = node->next;
    }
    return element;
}

int deleteInMiddle__(List *list, Node *node, Node *prev, Node *next) {
    int element = node->element;
    prev->next = next;
    next->prev = prev;
    free(node);
    list->size--;
    return element;
}

int indexOf(List *list, int element) {
    assert((list != NULL) && ("Provided List is null"));
    if (list->size == 0) {
        return -1;
    }
    Node *iterator = list->first;
    for (int i = 0; i < list->size; i++) {
        if (iterator->element == element) {
            return i;
        }
        iterator = iterator->next;
    }
    return -1;
}

bool contains(List *list, int element) {
    return indexOf(list, element) != -1;
}

void addAll(List *this, List *other) {
    assert((this != NULL && other != NULL) && ("One of the provided Lists is null"));
    Node *iterator = other->first;
    for (int i = 0; i < other->size; i++) {
        addLast(this, iterator->element);
        iterator = iterator->next;
    }
}

void showList(List *list) {
    assert((list != NULL) && ("Provided List is null"));
    Node *iterator = list->first;
    printf("[");
    for (int i = 0; i < list->size; i++) {
        printf("%d", iterator->element);
        if (i != list->size - 1) {
            printf(", ");
        }
        iterator = iterator->next;
    }
    printf("]\n");
}

void clearList(List *list) {
    assert((list != NULL) && ("Provided List is null"));
    if (list->size == 0) {
        return;
    }
    Node *iterator = list->first;
    while (iterator->next != NULL) {
        list->first = iterator->next;
        deleteNode(iterator);
        iterator = list->first;
    }
    list->size = 0;
    list->first = list->last = NULL;
}

void deleteList(List *list) {
    assert((list != NULL) && ("Provided List is null"));
    clearList(list);
    free(list);
}
