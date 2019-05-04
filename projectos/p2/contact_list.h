#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct {
    char *name, *email, *tel;
} Contact;

typedef struct struct_node {
    struct struct_node *next, *previous;
    Contact c;
} Node;

typedef struct {
    struct struct_node *head, *tail;
} ContactList;

void print_contact(Contact c);

ContactList *make_contact_list();

void destroy_node(Node *node);

void destroy_contact_list(ContactList *cl);

void append_to_contact_list(ContactList *cl, Contact c);

Contact *find_contact_by_name(ContactList *cl, char *name);

#endif