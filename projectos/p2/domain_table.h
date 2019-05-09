/*******************************************************************************
* Projeto 2 IAED1819: domain_table.h                                           *
* Neste projeto tenciona-se criar um sistema de gestao de contactos, com o     *
* qual se interage atraves de comandos.                                        *
*                                                                              *
*                                                 Pedro Godinho - 93608 - LETI *
********************************************************************************
* Este ficheiro contem a declaracao das estruturas e funcoes necessarias para  *
* a implementacao de uma hashtable de dominios, bem como as respetivas         *
* documentacoes.                                                               *
*******************************************************************************/

#ifndef DOMAIN_TABLE_H
#define DOMAIN_TABLE_H

#define DT_SIZE 503 /* size da hashtable de domains - primo proximo de 500 */

/*******************************************************************************
* Estrutura Item:                                                              *
* Um item individual da hashtable de domains, com o a string do dominio em     *
* questao e o numero de vezes que ele ocorreu (e um ponteiro para a proxima    *
* colisao de hashes, se houver).                                               *
*******************************************************************************/
typedef struct struct_item {
    int num;
    char* domain;
    struct struct_item *next_collision;
} Item;

/*******************************************************************************
* Estrutura DomainHashTable:                                                   *
* Uma estrutura que contem uma lista de ponteiros para cada bucket na          *
* hashtable de domains.                                                        *
*******************************************************************************/
typedef struct {
    Item **items;
} DomainHashTable;


/*******************************************************************************
* Funcao que gera uma hash de uma string dada. O algoritmo usado e             *
* Fowler-Noll-Vol.                                                             *
*                                                                              *
********************************************************************************
* Args:                                                                        *
*     Char *str: A string para criar a hash                                    * 
*                                                                              *
* Returns:                                                                     *
*     ContactList*: a hashtable criada                                         *
*******************************************************************************/
unsigned int hash(char *str);


/*******************************************************************************
* Funcao que gera uma hashtable de dominios vazia.                             *
*                                                                              *
********************************************************************************
* Returns:                                                                     *
*     ContactList*: a hashtable criada                                         *
*******************************************************************************/
DomainHashTable *make_domain_hash_table();


/*******************************************************************************
* Funcao que encontra um dominio na hashtable.                                 *
*                                                                              *
********************************************************************************
* Args:                                                                        *
*     DomainHashTable *table: A table onde procurar                            *
*     Char *str: O dominio a procurar                                          * 
*                                                                              *
* Returns:                                                                     *
*     ContactList*: o numero de ocurrencias do dominio registadas na           *
*                   hashtable                                                  *
*******************************************************************************/
int get_from_domain_table(DomainHashTable *table, char *domain);


/*******************************************************************************
* Funcao que incrementa o numero de ocurrencias de um dominio registadas na    *
* hashtable.                                                                   *
*                                                                              *
********************************************************************************
* Args:                                                                        *
*     DomainHashTable *table: A table onde incrementar                         *
*     Char *str: O dominio a incrementar                                       * 
*******************************************************************************/
void increment_in_domain_table(DomainHashTable *table, char *domain);


/*******************************************************************************
* Funcao que decrementa o numero de ocurrencias de um dominio registadas na    *
* hashtable.                                                                   *
*                                                                              *
********************************************************************************
* Args:                                                                        *
*     DomainHashTable *table: A table onde decrementar                         *
*     Char *str: O dominio a decrementar                                       * 
*******************************************************************************/
void decrement_in_domain_table(DomainHashTable *table, char *domain);


/*******************************************************************************
* Funcao que liberta toda a memoria relacionada com uma hashtable.             *
*                                                                              *
********************************************************************************
* Args:                                                                        *
*     DomainHashTable *cl: o ponteiro para a hashtable a destruir              *
*******************************************************************************/
void destroy_domain_hash_table(DomainHashTable *dt);

#endif