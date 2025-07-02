#include <stdio.h>
#include <string.h>
#include "vendedores.h"

#define MAX 100 


struct vendedores {
    int numero;
    char nome[50];
    float salario_fixo;
};

struct vendedores lista[MAX]; 
int qtd = 0; 
int proximo_numero = 1; 

int buscar(int numero) {
    for (int i = 0; i < qtd; i++) {
    if (lista[i].numero == numero) {
    return i;
    }
    }
    return -1; 
}

void inserir() {
    if (qtd >= MAX) {
    printf("Cadastro cheio.\n");
    return;
    }
    int numero;
    printf("Deseja gerar o numero automaticamente? (1-Sim, 0-Nao): ");
    int opc;
    scanf("%d", &opc);
    if (opc == 1) {
    numero = proximo_numero++;
    } else {
    printf("Digite o numero do vendedor: ");
    scanf("%d", &numero);
if (buscar(numero) != -1) {
 printf("Numero ja cadastrado.\n");
            return;
        }
    }
    lista[qtd].numero = numero;
    printf("Digite o nome do vendedor: ");
    getchar(); 
    fgets(lista[qtd].nome, 50, stdin); // 
    lista[qtd].nome[strcspn(lista[qtd].nome, "\n")] = '\0'; 
    printf("Digite o salario fixo: ");
    scanf("%f", &lista[qtd].salario_fixo);
    qtd++;
    printf("Vendedor cadastrado com sucesso!\n");
}
void consultar() {
    int numero;
    printf("Digite o numero do vendedor para consulta: ");
    scanf("%d", &numero);
    int pos = buscar(numero);
    if (pos != -1) {
    printf("Numero: %d\n", lista[pos].numero);
    printf("Nome: %s\n", lista[pos].nome);
    printf("Salario: %.2f\n", lista[pos].salario_fixo);
    } else {
    printf("Vendedor nao encontrado.\n");
    }
}
void alterar() {
    int numero;
    printf("Digite o numero do vendedor para alterar: ");
    scanf("%d", &numero);
    int pos = buscar(numero);
    if (pos != -1) {
    printf("Digite o novo nome: ");
    getchar(); 
    fgets(lista[pos].nome, 50, stdin);
    lista[pos].nome[strcspn(lista[pos].nome, "\n")] = '\0'; 
    printf("Digite o novo salario fixo: ");
    scanf("%f", &lista[pos].salario_fixo);
    printf("Dados alterados com sucesso!\n");
    } else {
        printf("Vendedor nao encontrado.\n");
    }
}
void excluir() {
 int numero;
 printf("Digite o numero do vendedor para excluir: ");
 scanf("%d", &numero);
 int pos = buscar(numero);
 if (pos != -1) {
 for (int i = pos; i < qtd - 1; i++) {
lista[i] = lista[i + 1]; 
 }
qtd--; 
printf("Vendedor excluido com sucesso.\n");
} else {
printf("Vendedor nao encontrado.\n");
 }
}
void registrar_venda() {
int numero;
float valor;
printf("Digite o numero do vendedor para registrar a venda do mesmo: ");
scanf("%d", &numero);
int pos = buscar(numero);
if (pos != -1) {
printf("Digite o valor da venda: ");
scanf("%f", &valor);
float comissao = valor * 0.03;
lista[pos].salario_fixo += comissao; 
printf("Venda registrada! Comissao de %.2f adicionada ao salario.\n", comissao);
} else {
printf("Vendedor nao encontrado.\n");
    }
}
int menuVendedores() {
int opcao;
do {
printf("\n--- Menu Vendedores ---\n");
printf("1 - Inserir vendedor\n");
printf("2 - Consultar vendedor\n");
printf("3 - Alterar vendedor\n");
printf("4 - Excluir vendedor\n");
printf("5 - Registrar venda\n");
printf("0 - Sair\n");
printf("Escolha: ");
scanf("%d", &opcao);

    
switch (opcao) {
case 1: inserir(); break;
case 2: consultar(); break;
case 3: alterar(); break;
case 4: excluir(); break;
case 5: registrar_venda(); break;
case 0: printf("Saindo...\n"); break;
default: printf("Opcao invalida.\n");
}
} while (opcao != 0); 
    return 0;
}