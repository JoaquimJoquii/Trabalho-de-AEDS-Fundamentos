#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "compradores.h"

int main(){
    char nome[100];

    printf("Qual nome do comprador que deseja deletar? ");
    fgets(nome, MAX_NOME, stdin);
    deletarCompradores(nome);

    apresentarCompradores();
    

    return 0;
}