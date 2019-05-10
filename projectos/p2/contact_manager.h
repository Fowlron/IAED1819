/*******************************************************************************
* Projeto 2 IAED1819: contact_manager.h                                        *
* Neste projeto tenciona-se criar um sistema de gestao de contactos, com o     *
* qual se interage atraves de comandos.                                        *
*                                                                              *
*                                                 Pedro Godinho - 93608 - LETI *
********************************************************************************
* Este ficheiro contem a declaracao das funcoes necessarias para o             *
* funcionamento do sistema de gestao de contactos proposto, bem como as        *
* respetivas documentacoes.                                                    *
*******************************************************************************/

#ifndef CONTACT_MANAGER_H
#define CONTACT_MANAGER_H

#include "contact_list.h"
#include "domain_table.h"

#define MAX_STR_NAME 1023  /* tamanho maximo de cada nome */
#define MAX_STR_EMAIL 511  /* tamanho maximo de cada email */
#define MAX_STR_TEL 63     /* tamanho maximo de cada n de tel */


/*******************************************************************************
* Funcao que, dado um email, descobre o seu dominio.
*
********************************************************************************
* Args:
*     char *email: o email a analizar
*     char *domain: ponteiro para onde o domain vai ser escrito
*******************************************************************************/
void get_domain_from_email(char *email, char *domain);


/*******************************************************************************
* Funcao responsavel pelo comando a. Adiciona um contacto ao fim da lista.
*
********************************************************************************
* Args:
*     HashedContactList *cl: a lista que esta a ser trabalhada
*     DomainHashTable *dt: a hashtable que esta a ser trabalhada
*
* Errors:
*     Sao levantados erros caso nao seja possivel ler do stdin, o input esteja
* mal formatado, ou ja exista um nome com o contacto que se esta a tentar
*******************************************************************************/
void command_add_contact(HashedContactList *cl, DomainHashTable *dt);


/*******************************************************************************
* Funcao responsavel pelo comando l. Escreve no ecra a lista de contactos pela
* ordem em que foram adicionados.
*
********************************************************************************
* Args:
*     HashedContactList *cl: a lista que esta a ser trabalhada
*******************************************************************************/
void command_print_contact_list(HashedContactList *cl);


/*******************************************************************************
* Funcao responsavel pelo comando p. Procura um contacto com o nome dado.
*
********************************************************************************
* Args:
*     HashedContactList *cl: a lista que esta a ser trabalhada
*
* Errors:
*     Sao levantados erros caso nao seja possivel ler do stdin, o input esteja
*     mal formatado, ou nao existir nenhum contacto com o nome dado
*******************************************************************************/
void command_find_contact(HashedContactList *cl);


/*******************************************************************************
* Funcao responsavel pelo comando r. Procura e remove o contacto com o nome
* dado.
*
********************************************************************************
* Args:
*     HashedContactList *cl: a lista que esta a ser trabalhada
*     DomainHashTable *dt: a hashtable que esta a ser trabalhada
*
* Errors:
*     Sao levantados erros caso nao seja possivel ler do stdin, o input esteja
*     mal formatado, ou nao existir nenhum contacto com o nome dado
*******************************************************************************/
void command_remove_contact(HashedContactList *cl, DomainHashTable *dt);


/*******************************************************************************
* Funcao responsavel pelo comando e. Procura e altera o email do contacto com
* o nome dado.
*
********************************************************************************
* Args:
*     ContactList *cl: a lista que esta a ser trabalhada
*     DomainHashTable *dt: a hashtable que esta a ser trabalhada
*
* Errors:
*     Sao levantados erros caso nao seja possivel ler do stdin, o input esteja
*     mal formatado, ou nao existir nenhum contacto com o nome dado
*******************************************************************************/
void command_change_email(HashedContactList *cl, DomainHashTable *dt);


/*******************************************************************************
* Funcao responsavel pelo comando c. Procura e conta o numero de contactos
* cujo email esteja no dominio dado.
*
********************************************************************************
* Args:
*     DomainHashTable *dt: a hashtable que esta a ser trabalhada
*
* Errors:
*     Sao levantados erros caso nao seja possivel ler do stdin ou o input
*     esteja mal formatado.
*******************************************************************************/
void command_count_email_domain(DomainHashTable *dt);

#endif