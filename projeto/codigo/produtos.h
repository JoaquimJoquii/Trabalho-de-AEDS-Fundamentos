// produtos.h

#ifndef PRODUTOS_H
#define PRODUTOS_H

#include <stdio.h>

// Definição da estrutura Produto
typedef struct {
    char nome[100];
    int codigo;
    int quantidade;
    float preco;
} Produto;

// Protótipos das funções
int cadastrarProduto(Produto produtos[], int *qtdProdutos, Produto novoProduto);
int consultarProduto(Produto produtos[], int qtdProdutos, int codigo);
int alterarProduto(Produto produtos[], int qtdProdutos, Produto produtoAtualizado);
int excluirProduto(Produto produtos[], int *qtdProdutos, int codigo);
void listarProdutos(Produto produtos[], int qtdProdutos);

#endif // PRODUTOS_H