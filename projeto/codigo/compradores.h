#ifndef COMPRADORES_H
#define COMPRADORES_H
#define MAX_ENDERECO 30
#define MAX_NOME 100
#define MAX_CPF 12

void apresentarCompradores();

void deletarCompradores(char nome[100]);

void cadastrarCompradores(int quant);

void editarCompradores(char nome[100]);

#endif