#ifndef CONTACT_MANAGER_H
#define CONTACT_MANAGER_H


#include "contact_list.h"

#define MAX_STR_NAME 1023
#define MAX_STR_EMAIL 511
#define MAX_STR_TEL 63

Contact *get_contact_by_name(ContactList *cl, char *name);

void get_domain_from_email(char *email, char *domain);

void command_add_contact(ContactList *cl);

void command_print_contact_list(ContactList *cl);

void command_find_contact(ContactList *cl);

void command_remove_contact(ContactList *cl);

void command_change_email(ContactList *cl);

void command_count_email_domain(ContactList *cl);

#endif