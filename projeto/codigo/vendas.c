#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "vendas.h"

FILE *vendas;

void alterarVenda(){

}

void detetarVenda(){

}

void listarVendas(){
    // Abre o arquivo de vendas para leitura
    vendas = fopen("vendas.txt", "r");
    // Verifica se o arquivo foi aberto corretamente
    if (vendas == NULL) {
        printf("Erro ao abrir o arquivo de vendas.\n");
        return;
    }
    char linha[256];// Buffer para armazenar cada linha lida do arquivo
    // Lê e exibe cada linha do arquivo
    printf("\n===== LISTA DE VENDAS =====\n");
    while (fgets(linha, sizeof(linha), vendas) != NULL) {
        printf("%s", linha);
    }
    // Fecha o arquivo após a leitura
    fclose(vendas);
    printf("\n============================\n");
    system("pause"); // Aguarda o usuário pressionar Enter
}

void novaVenda(){

}

void menuVendas(void) {
    int opcao;
    do {
        // Exibe o menu
        printf("\n===== MENU =====\n");
        printf("1. Editar Vendas\n");
        printf("2. Deletar vendas\n");
        printf("3. Listar vendas\n");
        printf("4. Nova venda\n");
        printf("5. sair\n");
        printf("=================\n");
        printf("Escolha uma opcao: ");
        // Lê a opção do usuário
        scanf("%d", &opcao);
        switch(opcao) {
            case 1: {
                alterarVenda();
                break;
            }
            case 2: {
                detetarVenda();
                break;
            }
            case 3: {
                listarVendas();
                break;
            }
            case 4:
                novaVenda();
                break;
            case 5:{
                printf("Saindo do programa...\n");
                break;
            }
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while(opcao != 5);
}