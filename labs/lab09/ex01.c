#include <stdio.h>
#include <stdlib.h>

typedef struct stru_node {
    struct stru_node *next;
    int v;
} node;

/* remove the first element of the list and return the new head */
node * pop(node * head);
/* add integer e as the first element of the list and return the new head */
node * push(node * head, int e);
/* frees all memory associated with the list and returns NULL */
node * destroy(node * head);
/* print the elements of the integers in the list, one per line */
void print(node * head);
/* compara duas listas */
int is_eq(node *h1, node *h2);
/* devolve uma nova lista que corresponda a lista dada invertida */
node * rev(node * head);

int main() {
    int i;
    node *head = NULL;
    for (scanf("%d", &i); i != 0; scanf("%d", &i)) {
        head = push(head, i);
    }
    print(head);
    destroy(head);
    return 0;
}

node *pop(node *head) {
    node *next = head->next;
    free(head);
    return next;
}

node *push(node *head, int e) {
    node *new_head = malloc(sizeof(node));
    new_head->next = head;
    new_head->v = e;
    return new_head;
}

void print(node * head) {
    while (head != NULL) {
        printf("%d\n", head->v);
        head = head->next;
    }
}

node * destroy(node * head) {
    while (head != NULL)
        head = pop(head);
    return NULL;
}

int is_eq(node *h1, node *h2) {
    if (h1 == NULL || h2 == NULL) {
        return h1 == NULL && h2 == NULL;
    }
    if (h1->v == h2->v) {
        if (h1->next == NULL && h2->next == NULL)
            return 1;
        return is_eq(h1->next, h2->next);
    }
    return 0;
}

node *rev(node * head) {
    node * new_head = NULL;
    while (head != NULL) {
        new_head = push(new_head, head->v);
        head = head->next;
    }
    return new_head;
}
