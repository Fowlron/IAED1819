/*******************************************************************************
* Projeto 2 IAED1819: contact_list.c                                           *
* Neste projeto tenciona-se criar um sistema de gestao de contactos, com o     *
* qual se interage atraves de comandos.                                        *
*                                                                              *
*                                                 Pedro Godinho - 93608 - LETI *
********************************************************************************
* Este fincheiro contem a implementacao das funcoes definidas em               *
* contact_list.h                                                               *
*******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "contact_manager.h"
#include "domain_table.h"


void print_contact(Contact c) {
    printf("%s %s %s\n", c.name, c.email, c.tel);
}


HashedContactList *make_contact_list() {
    int i;
    HashedContactList *cl = malloc(sizeof(HashedContactList));
    cl->head = NULL;
    cl->tail = NULL;
    cl->hashtable = malloc(sizeof(Node) * CL_SIZE);
    /* Inicializar cada ponteiro como NULL */
    for (i = 0; i < CL_SIZE; i++) 
        *(cl->hashtable + i) = NULL;
    return cl;
}


void destroy_node(Node *node) {
    free(node->c.name);
    free(node->c.email);
    free(node->c.tel);
    free(node);
}


void destroy_contact_list(HashedContactList *cl) {
    Node *next;
    while (cl->head) {
        /* guardar o proximo elemento para usar depois de libertar a head */
        next = cl->head->next;

        destroy_node(cl->head);
        cl->head = next;
    }
    free(cl->hashtable);
    free(cl);
}


void append_to_contact_list(HashedContactList *cl, Contact c) {
    int hash_index;

    /****** gerir doubly linked list ******/
    Node *new_tail = malloc(sizeof(Node));
    new_tail->next = NULL;
    new_tail->previous = cl->tail;
    new_tail->c = c;

    if (!cl->head) /* lista vazia */
        cl->head = new_tail;
    else           /* lista nao vazia */
        cl->tail->next = new_tail;
    
    cl->tail = new_tail;

    /****** gerir hash table ******/
    new_tail->next_collision = NULL;
    hash_index = hash(new_tail->c.name) % CL_SIZE;

    new_tail->next_collision = *(cl->hashtable + hash_index);
    *(cl->hashtable + hash_index) = new_tail;
}


void remove_node_from_list(HashedContactList *cl, char *name) {
    int hash_index;
    Node *current;
    Node *node = get_node_by_name(cl, name);

    /* remover o node da lista, alterando o next e previous dos nodes circundantes */
    if (node->previous)
        node->previous->next = node->next;
    if (node->next)
        node->next->previous = node->previous;

    /* se o node for a head ou a tail, atualizar a estrutura da lista */
    if (node == cl->head)
        cl->head = node->next;
    if (node == cl->tail)
        cl->tail = node->previous;

    /* remover da hashtable */
    hash_index = hash(name) % CL_SIZE;

    current = *(cl->hashtable + hash_index);
    if (strcmp(current->c.name, name) == 0) {
        *(cl->hashtable + hash_index) = current->next_collision;
    } else {
        for (; strcmp(current->next_collision->c.name, name) != 0; current = current->next_collision);
        current->next_collision = current->next_collision->next_collision;
    }

    /* libertar a memoria do node */
    destroy_node(node);
    return;
}


Node *get_node_by_name(HashedContactList *cl, char *name) {
    Node *current;
    int hash_index = hash(name) % CL_SIZE;
    
    for (current = *(cl->hashtable + hash_index); 
         current && strcmp(current->c.name, name); 
         current = current->next_collision);
    return current;
}


void print_hash_table(HashedContactList *cl) {
    int i;
    Node *current;
    for (i = 0; i < CL_SIZE; i++) {
        if (*(cl->hashtable + i))
            printf("Hash: %d | ", i);
        for (current = *(cl->hashtable + i); current; current = current->next_collision) {
            printf("%s ", current->c.name);
        }
        if (*(cl->hashtable + i))
            printf("\n");
    }
}