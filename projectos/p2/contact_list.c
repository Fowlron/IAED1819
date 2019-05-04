#include <stdlib.h>
#include <stdio.h>

#include "contact_manager.h"


void print_contact(Contact c) {
    printf("%s %s %s\n", c.name, c.email, c.tel);
}


ContactList *make_contact_list() {
    ContactList *cl = malloc(sizeof(ContactList));
    cl->head = NULL;
    cl->tail = NULL;
    return cl;
}


void destroy_node(Node *node) {
    free(node->c.name);
    free(node->c.email);
    free(node->c.tel);
    free(node);
}


void destroy_contact_list(ContactList *cl) {
    Node *next;
    while (cl->head != NULL) {
        /* guardar o proximo elemento para usar depois de libertar a head */
        next = cl->head->next;

        /* libertar o contacto antes da head */
        destroy_node(cl->head);
        cl->head = next;
    }
    free(cl);
}


void append_to_contact_list(ContactList *cl, Contact c) {
    /* a nova tail e criada e recebe os valores necessarios */
    Node *new_tail = malloc(sizeof(Node));
    new_tail->next = NULL;
    new_tail->previous = cl->tail;
    new_tail->c = c;

    /* se a lista e vazia, a nova tail tambem e a head */
    if (cl->head == NULL) 
        cl->head = new_tail;
    else /* caso contrario, atualizar a tail antiga */
        cl->tail->next = new_tail;
    
    cl->tail = new_tail;
}
