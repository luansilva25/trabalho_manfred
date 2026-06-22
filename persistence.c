#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"

#define ARQUIVO_CONTATOS "contatos.txt"

/*
 * Formato do arquivo (texto, um contato por bloco):
 *
 * QTDINFOS;<numero de campos do contato>
 * <key1>;<value1>
 * <key2>;<value2>
 * ...
 * FIM
 */

void saveContacts(Contacts *contacts, int totalContacts) {
    FILE *file = fopen(ARQUIVO_CONTATOS, "w");
    if (file == NULL) {
        fprintf(stderr, "erro ao abrir arquivo para gravacao.\n");
        return;
    }

    for (int i = 0; i < totalContacts; i++) {
        fprintf(file, "QTDINFOS;%d\n", contacts[i].qtdInfos);
        for (int j = 0; j < contacts[i].qtdInfos; j++) {
            fprintf(file, "%s;%s\n", contacts[i].infos[j].key, contacts[i].infos[j].value);
        }
        fprintf(file, "FIM\n");
    }

    fclose(file);
}

static char *readLineTrimmed(FILE *file) {
    static char buffer[256];

    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        return NULL;
    }

    size_t length = strlen(buffer);
    if (length > 0 && buffer[length - 1] == '\n') {
        buffer[length - 1] = '\0';
    }

    return buffer;
}

Contacts *loadContacts(int *totalContacts) {
    *totalContacts = 0;

    FILE *file = fopen(ARQUIVO_CONTATOS, "r");
    if (file == NULL) {
        return NULL;
    }

    Contacts *contacts = NULL;
    char *line;

    while ((line = readLineTrimmed(file)) != NULL) {
        int qtdInfos = 0;

        if (sscanf(line, "QTDINFOS;%d", &qtdInfos) != 1) {
            continue;
        }

        (*totalContacts)++;
        Contacts *newContacts = realloc(contacts, (*totalContacts) * sizeof(Contacts));
        if (newContacts == NULL) {
            fprintf(stderr, "erro ao realocar memoria ao carregar contatos.\n");
            fclose(file);
            return contacts;
        }
        contacts = newContacts;

        Contacts *current = &contacts[*totalContacts - 1];
        current->qtdInfos = qtdInfos;
        current->infos = malloc(qtdInfos * sizeof(Contact));

        for (int j = 0; j < qtdInfos; j++) {
            line = readLineTrimmed(file);
            if (line == NULL) {
                break;
            }

            char key[50] = "";
            char value[50] = "";
            char *separator = strchr(line, ';');

            if (separator != NULL) {
                size_t keyLength = (size_t)(separator - line);
                if (keyLength > 49) keyLength = 49;
                strncpy(key, line, keyLength);
                key[keyLength] = '\0';
                strncpy(value, separator + 1, 49);
                value[49] = '\0';
            }

            current->infos[j].key = malloc(50);
            current->infos[j].value = malloc(50);
            strcpy(current->infos[j].key, key);
            strcpy(current->infos[j].value, value);
        }

        readLineTrimmed(file); /* consome a linha "FIM" */
    }

    fclose(file);
    return contacts;
}
