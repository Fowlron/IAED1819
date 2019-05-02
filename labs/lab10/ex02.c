#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct str_node  {
    struct str_node *next, *previous;
    char c;
} node;

typedef struct  {
    struct str_node *head, *last;
} list;

list *mk_list(); /* cria nova lista vazia */
void free_list(list *l); /* liberta toda a memoria associada a lista */
void add_last(list *l, char c); /* adiciona o char c como o ultimo elemento da lista */
int is_paly(const list *ls); /* calcula se a dada lista e um palindromo */
void print(list *l);

int main() {
    int i, len;
    list *lst;
    char *line = malloc(sizeof(char) * 1000);
    lst = mk_list();
    scanf("%s", line);
    len = strlen(line);
    for (i = 0; i < len; i++) {
        add_last(lst, *(line+i));
    }

    printf(is_paly(lst) ? "yes\n" : "no\n");

    free_list(lst);
    free(line);
    return 0;
}

list *mk_list() {
    list *l = malloc(sizeof(list));
    l->head = NULL;
    l->last = NULL;
    return l;
}

int is_paly(const list *l) {
    node *current_a, *current_b;
    for (current_a = l->head, current_b = l->last; current_a != NULL; current_a = current_a->next, current_b = current_b->previous) {
        if (current_a->c != current_b->c)
            return 0;
    }
    return 1;
}

void free_list(list *l) {
    node *next;
    while (l->head != NULL) {
        next = l->head->next;
        free(l->head);
        l->head = next;
    }
    free(l);
}

void add_last(list *l, char c) {
    node *new_last = malloc(sizeof(node));
    new_last->next = NULL;
    new_last->previous = l->last;
    new_last->c = c;

    if (l->head == NULL)
        l->head = new_last;
    else
        l->last->next = new_last;

    l->last = new_last;

}

void print(list *l) {
    node *current;
    for (current = l->head; current != NULL; current = current->next) {
        printf("%c\n", current->c);
    }
}