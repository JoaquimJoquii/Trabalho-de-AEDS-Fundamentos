#ifndef VENDEDORES_H
#define VENDEDORES_H

int buscar(int numero);
void inserir();
void consultar();
void alterar();
void excluir();
void registrar_venda();
void menuVendedores();

struct vendedores
{
    int numero;
    char nome[50];
    float salario_fixo;
};
#endif