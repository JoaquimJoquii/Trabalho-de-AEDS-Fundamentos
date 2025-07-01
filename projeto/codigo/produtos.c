#include <stdio.h>
#include "produtos.h"

// Função: cadastrarProduto
int cadastrarProduto(Produto produtos[], int *qtdProdutos, Produto novoProduto) {
    if (*qtdProdutos >= 100) {
        printf("Limite máximo de produtos atingido.\n");
        return 0;
    }

    for (int i = 0; i < *qtdProdutos; i++) {
        if (produtos[i].codigo == novoProduto.codigo) {
            printf("Erro: Código já existente.\n");
            return 0;
        }
    }

    produtos[*qtdProdutos] = novoProduto;
    (*qtdProdutos)++;
    return 1;
}
