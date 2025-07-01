#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "vendas.h"

FILE *vendas;

float calcularFrete(float valor){
    float frete;
    if(valor<0){
        printf("erro, valor invalido!");
        return 0;
    }
    if(valor<=100){
        frete=30;
    }
    else if((valor>100)&&(valor<=300)){
        frete=20;
    }
    else {
        frete=0;
    }
    return frete;
}

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
    int codigoVenda;
    char vendedor[256];
    char comprador[256];
    
    // Itens
    char nome[256];
    float un;
    int qnt,r,cod;
    float total = un * qnt;

    float totalItens = 0;
    float frete;

    // Abrindo o arquivo para escrita
    vendas = fopen("vendas.txt", "a");
    if (vendas == NULL) {
        printf("Erro ao criar o arquivo!\n");
        return 0;
    }
    // Coletando dados da venda
    printf("Digite o codigo da venda: ");
    scanf("%d", &codigoVenda);
    printf("Digite o nome do vendedor: ");
    scanf(" %s", vendedor);
    printf("Digite o nome do comprador: ");
    scanf(" %s", comprador);

    // Escrevendo no arquivo
    fprintf(vendas, "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    fprintf(vendas, "codigo: %d\n", codigoVenda);
    fprintf(vendas, "vendedor: %s\n", vendedor);
    fprintf(vendas, "comprador: %s\n", comprador);
    // Coletando dados dos itens e salvando no arquivo
    do{
        printf("Digite o codigo do item: ");
        scanf("%d", &cod);
        printf("Digite o nome do item: ");
        scanf(" %s", nome);
        printf("Digite o valor unitario do item: ");
        scanf("%f", &un);
        printf("Digite a quantidade do item: ");
        scanf("%d", &qnt);
        
        total = un * qnt;
        totalItens += total;

        fprintf(vendas, "itens:{\n");
        fprintf(vendas, "    cod:%d nome:%s un:%.2f qnt:%d total:%.2f\n", cod, nome, un, qnt, total);
        fprintf(vendas, "}\n");

        printf("Deseja adicionar mais itens? (1-sim/0-nao): ");
        scanf("%d", &r);
    } while(r == 1);
    //calculando o frete
    frete = calcularFrete(totalItens);
    fprintf(vendas, "total dos itens:%.2f frete:%.2f \n", totalItens, frete);
    fprintf(vendas, "total da compra=%.2f\n", totalItens + frete);
    fprintf(vendas, "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");

    fclose(vendas);

    printf("venda salva com sucesso!\n");
    system("pause"); 
    return 0;
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