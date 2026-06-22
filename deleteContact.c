#include <stdio.h>
#include <stdlib.h>
#include "contact.h"

//verifica se tem contatos, se nao tiver, a um aviso e retorna pro menu
int delete(Contacts *contacts, int totalContacts) {
    if (totalContacts == 0) {
        printf("Nenhum contato para excluir.\n");
        return totalContacts;
    }


    //lista os ctts pro usuario escolher o que quer excluir
    printf("\n======= Contatos =======\n");
    for (int i = 0; i < totalContacts; i++) {
        printf("%i - %s\n", i + 1, contacts[i].infos[0].value);
    }


    //escolha de qual o ctt a ser excluido
    int option;
    printf("Escolha o contato para excluir: ");
    if(scanf("%i", &option) != 1) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        printf("Entrada invalida. \n");
        return totalContacts;
    }
    int c;
    while ((c = getchar()) != '\n' && c != EOF);


    // valida a escolha do usuario
    if (option < 1 || option > totalContacts) {
        printf("Contato invalido.\n");
        printf("\nO total de contatos é 0 até %i\n", totalContacts);
        return totalContacts;
    }

    int index = option - 1; // converter pra indice do vetor, pois o vetor começa em 0 e a listagem que aparece para o usuario começa em 1


    //libera a memoria do ctt que vai ser excluido
    for (int j = 0; j < contacts[index].qtdInfos; j++) {
        free(contacts[index].infos[j].key);
        free(contacts[index].infos[j].value);
    }
    free(contacts[index].infos);

    //move todos os contatos a frente do excluido, uma posição pra tras
    for (int i = index; i < totalContacts - 1; i++) {
        contacts[i] = contacts[i + 1];
    }
    
    printf("\nContato excluido com sucesso\n");

    //retorna o novo total de ctts
    return totalContacts - 1;
}
