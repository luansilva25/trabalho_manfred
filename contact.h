#ifndef CONTACT_H
#define CONTACT_H

typedef struct {
    char *key;
    char *value;
} Contact;

typedef struct {
    Contact *infos;
    int qtdInfos;
} Contacts;

Contact *create(int *qtdInfos);
void read(Contacts *contacts, int totalContacts);
void update(Contacts *contacts);
void search(Contacts *contacts, int totalContacts);
int delete(Contacts *contacts, int totalContacts);

#endif