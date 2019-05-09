/*******************************************************************************
* Projeto 2 IAED1819: contact_list.c                                           *
* Neste projeto tenciona-se criar um sistema de gestao de contactos, com o     *
* qual se interage atraves de comandos.                                        *
*                                                                              *
*                                                 Pedro Godinho - 93608 - LETI *
********************************************************************************
* Este fincheiro contem a implementacao das funcoes definidas em               *
*******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

    if (cl->head == NULL) /* se a lista e vazia, a nova tail tambem e a head */
        cl->head = new_tail;
    else /* caso contrario, atualizar a tail antiga */
        cl->tail->next = new_tail;
    
    cl->tail = new_tail;
}


void remove_node_from_list(ContactList *cl, char *name) {
    Node *node = get_node_by_name(cl, name);

    /* remover o node da lista, alterando o next e previous dos nodes circundantes */
    if (node->previous != NULL)
        node->previous->next = node->next;
    if (node->next != NULL)
        node->next->previous = node->previous;

    /* se o node for a head ou a tail, atualizar a estrutura da lista */
    if (node == cl->head)
        cl->head = node->next;
    if (node == cl->tail)
        cl->tail = node->previous;

    /* libertar a memoria do node */
    destroy_node(node);
    return;
}


Node *get_node_by_name(ContactList *cl, char *name) {
    Node *current;
    /* percorrer a lista, e retornar um ponteiro para o contacto, caso encontrado */
    for (current = cl->head; current != NULL; current = current->next) {
        if (strcmp(current->c.name, name) == 0)
            return current;
    }
    return NULL;
}
