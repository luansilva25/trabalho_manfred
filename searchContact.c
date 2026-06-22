#include <stdio.h>
#include <string.h>
#include "contact.h"

void search(Contacts *contacts, int totalContacts) {
    //verifica o contador de contatos pra ver se tem algum cadastrado, se não tiver mostra a msg
    if (totalContacts == 0) {
        printf("\n============================\n Nenhum contato cadastrado. \n============================\n\n");
        return;
    }

    //parte de pedir o nome pro usuario digitar e fazer a consulta
    char name [50];
    printf("Digite o nome para consultar: ");
    scanf(" %49[^\n]", name);

    //limpa o buffer do teclado
    int c;
    while ((c = getchar()) != '\n' && c != EOF);


    // percorre o vetor procurando
    int found = 0; // aqui indica se achou alguma string que bate como o que o usuario digitou
    for (int i = 0; i < totalContacts; i++) {
        // contacts[i].infos[0] é o nome de contato cadastrado
        // o strstr faz a busca parcial, se um Mar for digitado ja bate com Marcia, Marli, Marcelo e etc
        if (strstr(contacts[i].infos[0].value, name) != NULL) {
            // se encontrar, retorna o contato encontrado com todas as infos do ctt
            printf("\n====== Contato %i ======\n", i + 1);
            for (int j = 0; j < contacts[i].qtdInfos; j++){
                printf("%s: %s\n", contacts[i].infos[j].key, contacts[i].infos[j].value);
            }
            found = 1;
        }
    }
    // caso nao encontre ninguem ele só avisa e encerra a busca
    if (!found){
        printf("\n nenhum contato encontrado com esse nome.\n");
    }
}