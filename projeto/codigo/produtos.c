#include <stdio.h>
#include <string.h>
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

// Função: consultarProduto
int consultarProduto(Produto produtos[], int qtdProdutos, int codigo) {
    for (int i = 0; i < qtdProdutos; i++) {
        if (produtos[i].codigo == codigo) {
            printf("Produto encontrado:\n");
            printf("Nome: %s\n", produtos[i].nome);
            printf("Código: %d\n", produtos[i].codigo);
            printf("Quantidade: %d\n", produtos[i].quantidade);
            printf("Preço: %.2f\n", produtos[i].preco);
            return 1;
        }
    }
    printf("Produto não encontrado.\n");
    return 0;
}

// Função: alterarProduto
int alterarProduto(Produto produtos[], int qtdProdutos, Produto produtoAtualizado) {
    int indice = -1;
    for (int i = 0; i < qtdProdutos; i++) {
        if (produtos[i].codigo == produtoAtualizado.codigo) {
            indice = i;
            break;
        }
    }

    if (indice == -1) return 0;
    strcpy(produtos[indice].nome, produtoAtualizado.nome);
    produtos[indice].quantidade = produtoAtualizado.quantidade;
    produtos[indice].preco = produtoAtualizado.preco;
    return 1;
}

// Função: excluirProduto
int excluirProduto(Produto produtos[], int *qtdProdutos, int codigo) {
    int indice = -1;
    for (int i = 0; i < *qtdProdutos; i++) {
        if (produtos[i].codigo == codigo) {
            indice = i;
            break;
        }
    }

    if (indice == -1) return 0;

    for (int i = indice; i < *qtdProdutos - 1; i++) {
        produtos[i] = produtos[i + 1];
    }

    (*qtdProdutos)--;
    return 1;
}

// Função: listarProdutos
void listarProdutos(Produto produtos[], int qtdProdutos) {
    if (qtdProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    printf("\n=== Lista de Produtos ===\n");
    for (int i = 0; i < qtdProdutos; i++) {
        printf("Nome: %s | Código: %d | Quantidade: %d | Preço: R$%.2f\n",
               produtos[i].nome, produtos[i].codigo,
               produtos[i].quantidade, produtos[i].preco);
    }
}