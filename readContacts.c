#include <stdio.h>
#include "contact.h"


void read(Contacts *contacts, int totalContacts){
    if(totalContacts == 0){
        printf("nenhum contato cadastrado.\n");
        return;
    }

    for (int i = 0; i < totalContacts; i++){
        printf("\n======= Contato %i =====\n", i + 1);

        for (int j = 0; j < contacts[i].qtdInfos; j++){
            printf("%s: %s\n", contacts[i].infos[j].key, contacts[i].infos[j].value);
        }
    }
}