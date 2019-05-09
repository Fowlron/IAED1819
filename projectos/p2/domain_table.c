#include <string.h>
#include <stdlib.h>

#include "domain_table.h"

unsigned int hash(char *str)
{
    unsigned int hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}


DomainHashTable *make_domain_hash_table() {
    int i;
    DomainHashTable *ht = malloc(sizeof(DomainHashTable));
    ht->items = malloc(sizeof(Item) * DT_SIZE);
    for (i = 0; i < DT_SIZE; i++) {
        *(ht->items+i) = NULL;
    }
    return ht;
}


int get_from_domain_table(DomainHashTable *ht, char *domain) {
    Item *item;
    int hash_index = hash(domain) % DT_SIZE;

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
        item = malloc(sizeof(Item));
        item->domain = malloc(sizeof(char) * (strlen(domain) + 1));
        strcpy(item->domain, domain);
        item->num = 1;
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
            next = current->next_collision;
            free(current->domain);
            free(current);
            current = next;
        }
    }
    
    free(dt->items);
    free(dt);
}