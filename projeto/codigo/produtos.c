#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produtos.h"

#define CAMINHO_ARQUIVO_PRODUTOS "../arquivos/produtos.txt"

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

// Função para salvar produtos em arquivo
void salvarProdutosEmArquivo(Produto produtos[], int qtdProdutos) {
    FILE *fp = fopen(CAMINHO_ARQUIVO_PRODUTOS, "w");
    if (!fp) {
        printf("Erro ao abrir arquivo para salvar produtos!\n");
        return;
    }
    for (int i = 0; i < qtdProdutos; i++) {
        fprintf(fp, "%d;%s;%d;%.2f\n", produtos[i].codigo, produtos[i].nome, produtos[i].quantidade, produtos[i].preco);
    }
    fclose(fp);
}

// Função para carregar produtos do arquivo
int carregarProdutosDeArquivo(Produto produtos[], int *qtdProdutos) {
    FILE *fp = fopen(CAMINHO_ARQUIVO_PRODUTOS, "r");
    if (!fp) {
        *qtdProdutos = 0;
        return 0;
    }
    int count = 0;
    while (fscanf(fp, "%d;%99[^;];%d;%f\n", &produtos[count].codigo, produtos[count].nome, &produtos[count].quantidade, &produtos[count].preco) == 4) {
        count++;
    }
    fclose(fp);
    *qtdProdutos = count;
    return 1;
}

void menuProdutos() {
    Produto produtos[100];
    int qtdProdutos = 0;
    carregarProdutosDeArquivo(produtos, &qtdProdutos);
    int opcao;
    do {
        // Exibe o menu
        printf("\n===== MENU =====\n");
        printf("1. Editar produtos\n");
        printf("2. Deletar produtos\n");
        printf("3. Listar produtos\n");
        printf("4. Novo produto\n");
        printf("5. Emitir nota fiscal\n");
        printf("0. Sair\n");
        printf("=================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        switch(opcao) {
            case 1: {
                Produto p;
                printf("Digite o codigo do produto a editar: ");
                scanf("%d", &p.codigo);
                printf("Novo nome: ");
                scanf("%99s", p.nome);
                printf("Nova quantidade: ");
                scanf("%d", &p.quantidade);
                printf("Novo preco: ");
                scanf("%f", &p.preco);
                if (alterarProduto(produtos, qtdProdutos, p)) {
                    printf("Produto alterado com sucesso!\n");
                    salvarProdutosEmArquivo(produtos, qtdProdutos);
                } else {
                    printf("Produto nao encontrado!\n");
                }
                break;
            }
            case 2: {
                int codigo;
                printf("Digite o codigo do produto a excluir: ");
                scanf("%d", &codigo);
                if (excluirProduto(produtos, &qtdProdutos, codigo)) {
                    printf("Produto excluido com sucesso!\n");
                    salvarProdutosEmArquivo(produtos, qtdProdutos);
                } else {
                    printf("Produto nao encontrado!\n");
                }
                break;
            }
            case 3: {
                listarProdutos(produtos, qtdProdutos);
                break;
            }
            case 4: {
                Produto p;
                printf("Codigo: ");
                scanf("%d", &p.codigo);
                printf("Nome: ");
                scanf("%99s", p.nome);
                printf("Quantidade: ");
                scanf("%d", &p.quantidade);
                printf("Preco: ");
                scanf("%f", &p.preco);
                if (cadastrarProduto(produtos, &qtdProdutos, p)) {
                    printf("Produto cadastrado com sucesso!\n");
                    salvarProdutosEmArquivo(produtos, qtdProdutos);
                }
                break;
            }
            case 5:
                // emitirNota(); // Implementar se necessário
                printf("Funcao emitir nota ainda nao implementada.\n");
                break;
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);
}