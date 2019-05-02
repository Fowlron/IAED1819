#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTR 1024

typedef struct stru_node {
    struct stru_node *next;
    char * s;
} node;

/* remove the first element of the list and return the new head */
node * pop(node * head);
/* add integer e as the first element of the list and return the new head */
node * push(node * head, char * s);
/* frees all memory associated with the list and returns NULL */
node * destroy(node * head);
/* print the elements of the integers in the list, one per line */
void print(node * head);

int main() {
    node * head = NULL;
    char * s = malloc(sizeof(char) * MAXSTR);
    for (scanf("%s", s); strcmp(s, "x") != 0; scanf("%s", s)) {
        head = push(head, s);
    }
    print(head);
    free(s);
    destroy(head);
    return 0;
}

node * pop(node * head) {
    node * next = head->next;
    free(head->s);
    free(head);
    return next;
}

node * push(node * head, char * s) {
    node * new_head = malloc(sizeof(node));
    new_head->next = head;
    new_head->s = malloc(sizeof(char) * strlen(s)+1);
    strcpy(new_head->s, s);
    return new_head;
}

void print(node * head) {
    while (head != NULL) {
        printf("%s\n", head->s);
        head = head->next;
    }
}

node * destroy(node * head) {
    while (head != NULL)
        head = pop(head);
    return NULL;
}
