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


Contact *find_contact_by_name(ContactList *cl, char *name) {
    Node *current;
    /* percorrer a lista, e retornar um ponteiro para o contacto, caso encontrado */
    for (current = cl->head; current != NULL; current = current->next) {
        if (strcmp(current->c.name, name) == 0)
            return &(current->c);
    }
    return NULL;
}


void get_domain_from_email(char *email, char *domain) {
    int i;
    for (i = 0; email[i] != '@'; i++); /* procurar @ */
    strcpy(domain, email+i+1); /* copiar o que vem a frente do arroba para domain */
}


void command_add_contact(ContactList *cl) {
    /* o tamanho maximo da linha e o tamanho maximo das 3 strings + 1 para '\0' */
    char line[MAX_STR_NAME + MAX_STR_EMAIL + MAX_STR_TEL + 1];
    char name[MAX_STR_NAME + 1], email[MAX_STR_EMAIL + 1], tel[MAX_STR_TEL + 1];

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
    }

    /* procurar um contacto com o mesmo nome e dar erro se encontrado */
    if (find_contact_by_name(cl, name)) {
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
}


void command_print_contact_list(ContactList *cl) {
    Node *current;
    for (current = cl->head; current != NULL; current = current->next) {
        print_contact(current->c);
    }
}


void command_find_contact(ContactList *cl) {
    char line[MAX_STR_NAME + 1], name[MAX_STR_NAME + 1];
    Contact *contact;

    /* ler linha do standard input com fgets */
    if (fgets(line, sizeof(line), stdin)) {
        /* formatar a linha para a variavel */
        if (sscanf(line, "%s", name) != 1) {
            printf("Erro ao procurar contacto (linha mal formatada?)\n");
            return;
        }
    } else {
        printf("Erro a ler do standard input. \n");
    }

    if ((contact = find_contact_by_name(cl, name))) 
        print_contact(*contact);
    else
        printf("Nome inexistente.\n");
}


void command_remove_contact(ContactList *cl) {
    char line[MAX_STR_NAME + 1], name[MAX_STR_NAME + 1];
    Node *current;

    /* ler linha do standard input com fgets */
    if (fgets(line, sizeof(line), stdin)) {
        /* formatar a linha para a variavel */
        if (sscanf(line, "%s", name) != 1) {
            printf("Erro ao remover contacto (linha mal formatada?)\n");
            return;
        }
    } else {
        printf("Erro a ler do standard input. \n");
    }

    if (!find_contact_by_name(cl, name)) {
        printf("Nome inexistente.\n");
        return;
    }

    /* iterar a lista ate encontrar o que corresponde */
    for (current = cl->head; current != NULL; current = current->next) {
        if (strcmp(current->c.name, name) == 0) {
            /* remover o node da lista, alterando o next e previous dos nodes circundantes */
            if (current->previous != NULL)
                current->previous->next = current->next;
            if (current->next != NULL)
                current->next->previous = current->previous;

            /* se o node for a head ou a tail, atualizar a estrutura da lista */
            if (current == cl->head)
                cl->head = current->next;
            if (current == cl->tail)
                cl->tail = current->previous;

            /* libertar a memoria do node */
            
            destroy_node(current); /* quebra o for loop, ja que perdemos o current->next, mas fazemos return a seguir */
            return;
        }
    }
}


void command_change_email(ContactList *cl) {
    char line[MAX_STR_NAME + MAX_STR_EMAIL + 1];
    char name[MAX_STR_NAME + 1], email[MAX_STR_EMAIL + 1];
    Contact *contact;

    /* ler linha do standard input com fgets */
    if (fgets(line, sizeof(line), stdin)) {
        /* formatar a linha para as duas variaveis */
        if (sscanf(line, "%s %s", name, email) != 2) {
            printf("Erro ao mudar o email de um contacto (linha mal formatada?)\n");
            return;
        }
    } else {
        printf("Erro a ler do standard input. \n");
    }

    /* verificar se o contacto existe */
    if (!(contact = find_contact_by_name(cl, name))) {
        printf("Nome inexistente.\n");
        return;
    }

    /* temos de realocar a memoria do email do contacto, ja que o numero de caracteres pode variar */
    free(contact->email);
    contact->email = malloc(sizeof(char) * (strlen(email) + 1));
    strcpy(contact->email, email);
}


void command_count_email_domain(ContactList *cl) {
    /* o tamanho maximo de um dominio e MAX_STR_EMAIL - 1 (@) - 1 (caracter minimo do local) + 1 ('\0') */
    char line[MAX_STR_EMAIL+1], domain_to_count[MAX_STR_EMAIL + 1], domain[MAX_STR_EMAIL - 1];
    Node *current;
    int counter = 0;

    /* ler linha do standard input com fgets */
    if (fgets(line, sizeof(line), stdin)) {
        /* formatar a linha para a variavel */
        if (sscanf(line, "%s", domain_to_count) != 1) {
            printf("Erro ao contar dominios de email (linha mal formatada?)\n");
            return;
        }
    } else {
        printf("Erro a ler do standard input. \n");
    }


    /* iterar os nodes com os contactos */
    for (current = cl->head; current != NULL; current = current->next) {
        get_domain_from_email(current->c.email, domain);
        if (strcmp(domain, domain_to_count) == 0) {
            counter++;
        }
    }
    printf("%s:%d\n", domain_to_count, counter);
}