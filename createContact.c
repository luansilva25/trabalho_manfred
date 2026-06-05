#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"

static void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

Contact* create(int *qtdInfos) {
    *qtdInfos = 2;

    Contact *contact = malloc(*qtdInfos * sizeof(Contact));
    if (contact == NULL) {
        fprintf(stderr, "erro ao alocar memoria.\n");
        return NULL;
    }

    for (int i = 0; i < *qtdInfos; i++) {
        contact[i].key = malloc(50);
        contact[i].value = malloc(50);
        if (contact[i].key == NULL || contact[i].value == NULL) {
            fprintf(stderr, "erro ao alocar memoria.\n");
            return NULL;
        }
    }

    strcpy(contact[0].key, "nome");
    printf("Digite o nome: ");
    if (scanf(" %49[^\n]", contact[0].value) != 1) {
        clearInputBuffer();
        printf("entrada inválida.\n");
    }
    clearInputBuffer();

    strcpy(contact[1].key, "telefone");
    printf("Digite o telefone: ");
    if (scanf(" %49[^\n]", contact[1].value) != 1) {
        clearInputBuffer();
        printf("entrada inválida.\n");
    }
    clearInputBuffer();

    while (1) {
        char answer;
        printf("Deseja adicionar informações extras? (s/n): ");
        if (scanf(" %c", &answer) != 1) {
            clearInputBuffer();
            printf("valor inválido. digite só 's' ou 'n'\n");
            continue;
        }
        clearInputBuffer();

        if (answer == 'n') {
            break;
        } else if (answer == 's') {
            (*qtdInfos)++;
            Contact *newContact = realloc(contact, *qtdInfos * sizeof(Contact));
            if (newContact == NULL) {
                fprintf(stderr, "erro ao realocar memoria.\n");
                free(contact);
                return NULL;
            }
            contact = newContact;

            contact[*qtdInfos - 1].key = malloc(50);
            contact[*qtdInfos - 1].value = malloc(50);
            if (contact[*qtdInfos - 1].key == NULL || contact[*qtdInfos - 1].value == NULL) {
                fprintf(stderr, "erro ao alocar memoria.\n");
                return NULL;
            }

            printf("Digite a informação extra: ");
            if (scanf(" %49[^\n]", contact[*qtdInfos - 1].key) != 1) {
                clearInputBuffer();
                printf("entrada inválida.\n");
                continue;
            }
            clearInputBuffer();

            printf("Digite o valor da informação extra: ");
            if (scanf(" %49[^\n]", contact[*qtdInfos - 1].value) != 1) {
                clearInputBuffer();
                printf("entrada inválida.\n");
                continue;
            }
            clearInputBuffer();

            printf("Informação extra adicionada com sucesso!\n");
        } else {
            printf("valor inválido. digite só 's' ou 'n'\n");
        }
    }

    printf("Informações do contato:\n");
    for (int i = 0; i < *qtdInfos; i++) {
        printf("%s: %s\n", contact[i].key, contact[i].value);
    }

    printf("contato criado com sucesso!\n\n");
    return contact;
}
