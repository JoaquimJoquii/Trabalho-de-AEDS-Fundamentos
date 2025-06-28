#include "compradores.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct endereco{
    char rua[30];
    char bairro[30];
    char cidade[30];
    char estado[30];
    int cep;
}endereco;

typedef struct compradores{
    int id;
    char nome[100];
    int cpf;
    char email[100];
    endereco endEntrega; //endereco de entrega do comprador
}compradores;

void apresentarCompradores(){

}

void deletarCompradore(int id){

}

void cadastrarCompradores(int quant){

}

void editarCompradores(int id){

}