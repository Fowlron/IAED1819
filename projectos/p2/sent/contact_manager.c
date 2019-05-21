/*******************************************************************************
* Projeto 2 IAED1819: contact_manager.c                                        *
* Neste projeto tenciona-se criar um sistema de gestao de contactos, com o     *
* qual se interage atraves de comandos.                                        *
*                                                                              *
*                                                 Pedro Godinho - 93608 - LETI *
********************************************************************************
* Este ficheiro contem a implementacao das funcoes declaradas no ficheiro      *
* contact_manager.h                                                            *
*******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "contact_manager.h"


void get_domain_from_email(char *email, char *domain) {
    int i;
    for (i = 0; email[i] != '@'; i++); /* procurar @ */
    strcpy(domain, email+i+1); /* copiar o que vem a frente do arroba para domain */
}


void command_add_contact(HashedContactList *cl, DomainHashTable *dt) {
    /* o tamanho maximo da linha e o tamanho maximo das 3 strings, mais um por espaço, mais 2 para "\n\0" no fim */
    char line[MAX_STR_NAME + 1 + MAX_STR_EMAIL + 1 + MAX_STR_TEL + 2];
    char name[MAX_STR_NAME + 1], email[MAX_STR_EMAIL + 1], tel[MAX_STR_TEL + 1];
    char domain[MAX_STR_EMAIL + 1];

    Contact contact;

    /* ler linha do standard input com fgets */
    if (fgets(line, sizeof(line), stdin)) {
        /* formatar a linha para as tres variaveis */
        if (sscanf(line, "%s %s %s", name, email, tel) != 3) {
            printf("Erro ao adicionar contacto (linha mal formatada?)\n");
            return;
        }
    } else {
        printf("Erro a ler do standard input. \n");
        return;
    }

    /* procurar um contacto com o mesmo nome e dar erro se encontrado */
    if (get_node_by_name(cl, name)) {
        printf("Nome existente.\n");
        return;
    }

    /* reservar apenas a memoria necessaria */
    contact.name = malloc(sizeof(char) * (strlen(name) + 1));
    contact.email = malloc(sizeof(char) * (strlen(email) + 1));
    contact.tel = malloc(sizeof(char) * (strlen(tel) + 1));

    strcpy(contact.name, name);
    strcpy(contact.email, email);
    strcpy(contact.tel, tel);


    append_to_contact_list(cl, contact);
    get_domain_from_email(email, domain);
    increment_in_domain_table(dt, domain);
}


void command_print_contact_list(HashedContactList *cl) {
    Node *current;
    for (current = cl->head; current; current = current->next) {
        print_contact(current->c);
    }
}


void command_find_contact(HashedContactList *cl) {
    char name[MAX_STR_NAME + 1];
    Node *node;

    /* ler linha do standard input com fgets */
    if (fgets(name, sizeof(name), stdin)) {
        /* remover o '\n' */
        name[strlen(name) - 1] = '\0';
    } else {
        printf("Erro a ler do standard input. \n");
        return;
    }

    if ((node = get_node_by_name(cl, name))) 
        print_contact(node->c);
    else
        printf("Nome inexistente.\n");
}


void command_remove_contact(HashedContactList *cl, DomainHashTable *dt) {
    char name[MAX_STR_NAME + 2];
    char domain[MAX_STR_EMAIL + 1];
    Node *node;

    /* ler linha do standard input com fgets */
    if (fgets(name, sizeof(name), stdin)) {
        /* remover o '\n' */
        name[strlen(name) - 1] = '\0';
    } else {
        printf("Erro a ler do standard input. \n");
        return;
    }

    if (!(node = get_node_by_name(cl, name))) {
        printf("Nome inexistente.\n");
        return;
    }

    get_domain_from_email(node->c.email, domain);
    remove_node_from_list(cl, name);
    decrement_in_domain_table(dt, domain);
}


void command_change_email(HashedContactList *cl, DomainHashTable *dt) {
    char line[MAX_STR_NAME + MAX_STR_EMAIL + 1];
    char name[MAX_STR_NAME + 1], email[MAX_STR_EMAIL + 1];
    char domain[MAX_STR_EMAIL + 1];
    Node *node;

    /* ler linha do standard input com fgets */
    if (fgets(line, sizeof(line), stdin)) {
        /* formatar a linha para as duas variaveis */
        if (sscanf(line, "%s %s", name, email) != 2) {
            printf("Erro ao mudar o email de um contacto (linha mal formatada?)\n");
            return;
        }
    } else {
        printf("Erro a ler do standard input. \n");
        return;
    }

    /* verificar se o contacto existe */
    if (!(node = get_node_by_name(cl, name))) {
        printf("Nome inexistente.\n");
        return;
    }

    get_domain_from_email(node->c.email, domain);
    decrement_in_domain_table(dt, domain);

    /* temos de realocar a memoria do email do contacto, ja que o numero de caracteres pode variar */
    node->c.email = realloc(node->c.email, sizeof(char) * strlen(email) + 1);
    strcpy(node->c.email, email);

    get_domain_from_email(email, domain);
    increment_in_domain_table(dt, domain);
}


void command_count_email_domain(DomainHashTable *dt) {
    /* o tamanho maximo de um dominio e MAX_STR_EMAIL - 1 (@) - 1 (caracter minimo do local) + 1 ('\0') */
    char domain[MAX_STR_EMAIL + 1];

    /* ler linha do standard input com fgets */
    if (fgets(domain, sizeof(domain), stdin)) {
        /* remover o '\n' */
        domain[strlen(domain) - 1] = '\0';
    } else {
        printf("Erro a ler do standard input. \n");
        return;
    }

    printf("%s:%d\n", domain, get_from_domain_table(dt, domain));
}