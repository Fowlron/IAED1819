#ifndef DOMAIN_TABLE_H
#define DOMAIN_TABLE_H

#define DT_SIZE 503

typedef struct struct_item {
    int num;
    char* domain;
    struct struct_item *next_collision;
} Item;


typedef struct {
    Item **items;
} DomainHashTable;

unsigned int hash(char *str);
DomainHashTable *make_domain_hash_table();
int get_from_domain_table(DomainHashTable *table, char *domain);
void increment_in_domain_table(DomainHashTable *table, char *domain);
void decrement_in_domain_table(DomainHashTable *table, char *domain);
void destroy_domain_hash_table(DomainHashTable *dt);

#endif