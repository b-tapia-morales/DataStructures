#ifndef NODE_H
#define NODE_H

#endif //NODE_H

#include <stdlib.h>
#include <assert.h>

typedef struct Node {
    int element;
    struct Node *prev;
    struct Node *next;
} Node;

/**
 * Crea un nuevo nodo que contiene el elemento especificado.
 * @param element El elemento.
 * @return El nodo creado
 */
Node* createNode(int element);

/**
 * Elimina el nodo, liberando el bloque de memoria previamente asignado al mismo.
 * @param node El nodo.
 */
void deleteNode(Node* node);

Node *createNode(int element) {
    Node *node = (Node *) malloc(sizeof(Node));
    assert((node != NULL) && ("Attempt to allocate memory for Node was unsuccessful"));
    node->element = element;
    node->prev = node->next = NULL;
    return node;
}

void deleteNode(Node *node) {
    free(node);
}