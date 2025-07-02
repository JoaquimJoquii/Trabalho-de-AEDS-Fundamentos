#ifndef COMPRADORES_H
#define COMPRADORES_H
#define MAX_ENDERECO 30
#define MAX_NOME 100
#define MAX_CPF 12

int apresentarCompradores();

int deletarCompradores(char nome[100]);

int cadastrarCompradores(int quant);

int editarCompradores(char nome[100]);

int menuCompradores();
#endif