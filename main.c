#include <stdio.h>
#include <stdlib.h>
#include "contact.h"

void freeContacts(Contacts *contacts, int totalContacts) {
    if (contacts == NULL) return;
    for (int i = 0; i < totalContacts; i++) {
        for (int j = 0; j < contacts[i].qtdInfos; j++) {
            free(contacts[i].infos[j].key);
            free(contacts[i].infos[j].value);
        }
        free(contacts[i].infos);
    }
    free(contacts);
}

int main() {
    Contacts *contacts = NULL;
    int option = 0;
    int optionUpdate = 0;
    int totalContacts = 0;
    
    do {
        printf("Menu:\n");
        printf("1 - Incluir Contato\n");
        printf("2 - Listar Contatos\n");
        printf("3 - Consultar Contato\n");
        printf("4 - Excluir Contato\n");
        printf("5 - Atualizar Contato\n");
        printf("6 - Sair\n");
        printf("Escolha uma opção:");
        scanf("%d", &option);

        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        switch (option) {
            case 1:
                totalContacts++;
                contacts = realloc(contacts, totalContacts * sizeof(Contacts));
                contacts[totalContacts - 1].infos = create(&contacts[totalContacts - 1].qtdInfos);
                saveContacts(contacts, totalContacts);
                break;
            case 2:
                freeContacts(contacts, totalContacts);
                contacts = loadContacts(&totalContacts);
                read(contacts, totalContacts);
                break;
            case 3:
                freeContacts(contacts, totalContacts);
                contacts = loadContacts(&totalContacts);
                search(contacts, totalContacts);
                break;
            case 4:
                freeContacts(contacts, totalContacts);
                contacts = loadContacts(&totalContacts);
                totalContacts = delete(contacts, totalContacts);
                if (totalContacts > 0){
                    contacts = realloc(contacts, totalContacts * sizeof(Contacts));
                } else {
                    free(contacts);
                    contacts = NULL;
                }
                saveContacts(contacts, totalContacts);
                break;
            case 5: 
                freeContacts(contacts, totalContacts);
                contacts = loadContacts(&totalContacts);
                if(totalContacts > 0){
                    printf("\n ======= Contatos ====== \n");
                    for (int i = 0; i < totalContacts; i++){
                        printf("%i - %s\n", i + 1, contacts[i].infos[0].value);
                    }
                        printf("escolha uma opcao: ");
                    if (scanf("%i", &optionUpdate) != 1) {
                        int c;
                        while ((c = getchar()) != '\n' && c != EOF);
                        printf("entrada inválida. operação cancelada.\n");
                        break;
                    }
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);
                    if (optionUpdate < 1 || optionUpdate > totalContacts) {
                        printf("Contato inválido.\n");
                        break;
                    }
                    update(&contacts[optionUpdate - 1]);
                    saveContacts(contacts, totalContacts);
                }
                else{
                    printf("nenhum contato para atualizar\n");
                }
                break;
            case 6:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (option != 6);

    freeContacts(contacts, totalContacts);
    return 0;
}