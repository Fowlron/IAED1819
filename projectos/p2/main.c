#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "contact_manager.h"
#include "contact_list.h" /* nao exatamente necessario (ja incluido em contact_manager.h), mas mantido por clareza */


void main_loop() {
    char command;
    ContactList *contact_list = make_contact_list();

    /* Loop principal do programa, em que se recebe cada comando */
    while ((command = getchar()) != 'x' && command != EOF) {
        if (command == '\n')
            continue; /* para simplificar utilizacao, no caso de se colocar uma newline extra sem querer */
        /* remover ' ' ou o fim de linha do buffer, dependendo do commando */
        getchar();
        switch (command) {
            case 'a':
                command_add_contact(contact_list);
                break;
            case 'l':
                command_print_contact_list(contact_list);
                break;
            case 'p':
                command_find_contact(contact_list);
                break;
            case 'r':
                command_remove_contact(contact_list);
                break;
            case 'e':
                command_change_email(contact_list);
                break;
            case 'c':
                command_count_email_domain(contact_list);
        }
    }

    /* libertar a memoria no fim */
    destroy_contact_list(contact_list);
}

int main() {
    main_loop();
    return 0;
}