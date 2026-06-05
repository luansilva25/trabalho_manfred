#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"

static void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void update(Contacts *contacts) {
    int qtdInfos = contacts->qtdInfos;
    char oneMoreExtra;
    char updateField;

    while (1) {
        printf("voce deseja adicionar uma nova informação extra (s/n): ");
        if (scanf(" %c", &oneMoreExtra) != 1) {
            clearInputBuffer();
            printf("valor inválido. digite só 's' ou 'n'\n");
            continue;
        }
        clearInputBuffer();

        if (oneMoreExtra == 's') {
            Contact *newInfos = realloc(contacts->infos, (qtdInfos + 1) * sizeof(Contact));
            if (newInfos == NULL) {
                printf("erro ao realocar memoria.\n");
                return;
            }
            contacts->infos = newInfos;
            contacts->infos[qtdInfos].key = malloc(50);
            contacts->infos[qtdInfos].value = malloc(50);
            if (contacts->infos[qtdInfos].key == NULL || contacts->infos[qtdInfos].value == NULL) {
                printf("erro ao alocar memoria.\n");
                return;
            }

            printf("qual o nome da nova informação extra: ");
            if (scanf(" %49[^\n]", contacts->infos[qtdInfos].key) != 1) {
                clearInputBuffer();
                printf("entrada inválida.\n");
                continue;
            }
            clearInputBuffer();

            printf("digite o valor da nova informação extra: ");
            if (scanf(" %49[^\n]", contacts->infos[qtdInfos].value) != 1) {
                clearInputBuffer();
                printf("entrada inválida.\n");
                continue;
            }
            clearInputBuffer();

            printf("novo dado adicionado com sucesso -> %s: %s\n", contacts->infos[qtdInfos].key, contacts->infos[qtdInfos].value);
            qtdInfos++;
        } else if (oneMoreExtra == 'n') {
            break;
        } else {
            printf("valor inválido. digite só 's' ou 'n'\n");
        }
    }

    contacts->qtdInfos = qtdInfos;

    while (1) {
        printf("voce deseja atualizar algum dado do contato: %s (s/n): ", contacts->infos[0].value);
        if (scanf(" %c", &updateField) != 1) {
            clearInputBuffer();
            printf("valor inválido. digite só 's' ou 'n'\n");
            continue;
        }
        clearInputBuffer();

        if (updateField == 's') {
            int fieldIndex = -1;
            char newVal[50];

            printf("qual campo deseja atualizar de %s:\n", contacts->infos[0].value);
            for (int i = 0; i < qtdInfos; i++) {
                printf("%i - %s\n", i + 1, contacts->infos[i].key);
            }
            printf("escolha um campo para ser atualizado: ");
            if (scanf("%i", &fieldIndex) != 1) {
                clearInputBuffer();
                printf("entrada inválida. operação cancelada.\n");
                continue;
            }
            clearInputBuffer();

            if (fieldIndex < 1 || fieldIndex > qtdInfos) {
                printf("campo inválido.\n");
                continue;
            }

            printf("digite o novo valor de %s: ", contacts->infos[fieldIndex - 1].key);
            if (scanf(" %49[^\n]", newVal) != 1) {
                clearInputBuffer();
                printf("entrada inválida.\n");
                continue;
            }
            clearInputBuffer();

            strcpy(contacts->infos[fieldIndex - 1].value, newVal);
            printf("campo atualizado com sucesso!\n");
        } else if (updateField == 'n') {
            break;
        } else {
            printf("valor inválido. digite só 's' ou 'n'\n");
        }
    }
}