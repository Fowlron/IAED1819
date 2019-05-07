/*******************************************************************************
* Projeto 2 IAED1819: main.c                                                   *
* Neste projeto tenciona-se criar um sistema de gestao de contactos, com o     *
* qual se interage atraves de comandos.                                        *
*                                                                              *
*                                                 Pedro Godinho - 93608 - LETI *
********************************************************************************
* Este ficheiro contem as funcoes main() e main_loop(), responsaveis pelo      *
* inicio do programa, bem como pelo loop principal, no qual o utilizador       *
* inseres os comandos a usar.                                                  *
*                                                                              *
*******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "contact_manager.h"
#include "contact_list.h"


/*******************************************************************************
* Funcao responsavel pelo loop principal do programa. A cada iteracao, a       *
* funcao respetiva ao comando dado e chamada.                                  *
*******************************************************************************/
void main_loop() {    
    char command;
    ContactList *contact_list = make_contact_list();

    /* Loop principal do programa, em que se recebe cada comando */
    while ((command = getchar()) != 'x' && command != EOF) {
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

/*******************************************************************************
* Ponto de entrada no programa.                                                *
*******************************************************************************/
int main() {
    main_loop();
    return 0;
}