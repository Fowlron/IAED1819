/*******************************************************************************
* Projeto 2 IAED1819: domain_table.c                                           *
* Neste projeto tenciona-se criar um sistema de gestao de contactos, com o     *
* qual se interage atraves de comandos.                                        *
*                                                                              *
*                                                 Pedro Godinho - 93608 - LETI *
********************************************************************************
* Este fincheiro contem a implementacao das funcoes definidas em               *
* domain_table.h                                                               *
*******************************************************************************/

#include <string.h>
#include <stdlib.h>

#include "domain_table.h"

unsigned int hash(char* str) {
	unsigned int hash = 16777619;
    while (*str) {
        hash = (hash * 0x811C9DC5) ^ *str++;
    }
	return hash;
}


DomainHashTable *make_domain_hash_table() {
    int i;
    DomainHashTable *ht = malloc(sizeof(DomainHashTable));
    ht->items = malloc(sizeof(Item) * DT_SIZE);
    /* inicializar os ponteiros como nulos */
    for (i = 0; i < DT_SIZE; i++) {
        *(ht->items+i) = NULL;
    }
    return ht;
}


int get_from_domain_table(DomainHashTable *ht, char *domain) {
    Item *item;
    int hash_index = hash(domain) % DT_SIZE;

    /* avanca para o proximo item no bucket de hashes ate encontrar um nulo ou com o nome pretendido */
    for (item = *(ht->items + hash_index); item && strcmp(item->domain, domain) != 0; item = item->next_collision);
    return item ? item->num : 0;
}


void increment_in_domain_table(DomainHashTable *ht, char *domain) {
    Item *item;
    int hash_index = hash(domain) % DT_SIZE;

    for (item = *(ht->items + hash_index); item && strcmp(item->domain, domain) != 0; item = item->next_collision);
    if (item) {
        item->num++;
    } else {
        /* Se o item pretendido nao foi encontrado, criar um novo com essa key */
        item = malloc(sizeof(Item));
        item->domain = malloc(sizeof(char) * (strlen(domain) + 1));
        strcpy(item->domain, domain);
        item->num = 1;
        /* coloca-lo como nova head desse bucket */
        item->next_collision = *(ht->items + hash_index);
        *(ht->items + hash_index) = item;
    }
}


void decrement_in_domain_table(DomainHashTable *ht, char *domain) {
    Item *item;
    int hash_index = hash(domain) % DT_SIZE;

    for (item = *(ht->items + hash_index); item && strcmp(item->domain, domain) != 0; item = item->next_collision);
    if (item && item->num > 0) {
        item->num--;
    }
}


void destroy_domain_hash_table(DomainHashTable *dt) {
    int i;
    Item *current, *next;

    for (i = 0; i < DT_SIZE; i++) {
        current = *(dt->items + i);
        while (current) {
            /* guardar o next do bucket para nao perder o depois do free */
            next = current->next_collision;
            free(current->domain);
            free(current);
            current = next;
        }
    }
    
    free(dt->items);
    free(dt);
}