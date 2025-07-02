#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "compradores.h"
#include "vendas.h"
#include "vendedores.h"
#include "produtos.h"

int main() {
    int opcao;
    do {
        // Exibe o menu
        printf("\n===== MENU =====\n");
        printf("1. Produtos\n");
        printf("2. Compradores\n");
        printf("3. Vendas e nota fiscal\n");
        printf("4. Vendedores\n");
        printf("0. Sair\n");
        printf("=================\n");
        printf("Escolha uma opcao: ");
        // Lê a opção do usuário
        scanf("%d", &opcao);
        switch(opcao) {
            case 1: {
                menuProdutos();
                break;
            }
            case 2: {
                menuCompradores();
                break;
            }
            case 3: {
                menuVendas();
                break;
            }
            case 4:
                menuVendedores();
                break;
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

