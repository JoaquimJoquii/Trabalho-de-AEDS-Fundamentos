#include "compradores.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct endereco
{
    char rua[MAX_ENDERECO];
    char bairro[MAX_ENDERECO];
    char cidade[MAX_ENDERECO];
    char estado[MAX_ENDERECO];
    char cep[MAX_ENDERECO];
} endereco;

typedef struct compradores
{
    int id;
    char nome[MAX_NOME];
    char cpf[MAX_CPF];
    char email[MAX_NOME];
    endereco endEntrega; // endereco de entrega do comprador
} compradores;

void cadastrarCompradores(int quant){
    int i, x;
    FILE *ptr = fopen("../../arquivos/compradores.txt", "a");
    if (ptr == NULL)
    {
        printf("abertura falhou\n");
        exit(1);
    }
    compradores clientes[quant];

    // loop para a entrada de dados pelo usuario
    for (i = 0; i < quant; i++)
    {
        printf("digite o nome do %d comprador: ", i + 1);
        fgets(clientes[i].nome, MAX_NOME, stdin);

        printf("digite o cpf do %d comprador (apenas numeros): ", i + 1);
        fgets(clientes[i].cpf, MAX_CPF, stdin);

        printf("digite o email do %d comprador: ", i + 1);
        fgets(clientes[i].email, MAX_NOME, stdin);

        printf("digite o Estado do %d comprador: ", i + 1);
        fgets(clientes[i].endEntrega.estado, MAX_ENDERECO, stdin);

        printf("digite a cidade do %d comprador: ", i + 1);
        fgets(clientes[i].endEntrega.cidade, MAX_ENDERECO, stdin);

        printf("digite o bairro do %d comprador: ", i + 1);
        fgets(clientes[i].endEntrega.bairro, MAX_ENDERECO, stdin);

        printf("digite a rua do %d comprador: ", i + 1);
        fgets(clientes[i].endEntrega.rua, MAX_ENDERECO, stdin);

        printf("digite o cep do %d comprador: ", i + 1);
        fgets(clientes[i].endEntrega.cep, MAX_ENDERECO, stdin);
    }

    // loop para adicionar os dados recebidos no arquivo
    for (i = 0; i < quant; i++)
    {
        fprintf(ptr, "%s%s%s%s%s%s%s%s",
                clientes[i].nome,
                clientes[i].cpf,
                clientes[i].email,
                clientes[i].endEntrega.estado,
                clientes[i].endEntrega.cidade,
                clientes[i].endEntrega.bairro,
                clientes[i].endEntrega.rua,
                clientes[i].endEntrega.cep);
    }

    x = fclose(ptr);
    if (x == EOF)
    {
        printf("fechamento falhou\n");
        exit(1);
    }
}

void apresentarCompradores(){
    int x;
    FILE *ptr = fopen("../../arquivos/compradores.txt", "r");
    if (ptr == NULL)
    {
        printf("abertura falhou\n");
        exit(1);
    }

    compradores cliente;
    char linha[MAX_NOME];

    while (fgets(linha, sizeof(linha), ptr) != NULL)
    {

        strcpy(cliente.nome, linha);

        fgets(linha, sizeof(linha), ptr); // le o arquivo e passa pra variavel linha
        strcpy(cliente.cpf, linha);       // copia da variavel linha para a variavel cliente

        fgets(linha, sizeof(linha), ptr);
        strcpy(cliente.email, linha);

        fgets(linha, sizeof(linha), ptr);
        strcpy(cliente.endEntrega.estado, linha);

        fgets(linha, sizeof(linha), ptr);
        strcpy(cliente.endEntrega.cidade, linha);

        fgets(linha, sizeof(linha), ptr);
        strcpy(cliente.endEntrega.bairro, linha);

        fgets(linha, sizeof(linha), ptr);
        strcpy(cliente.endEntrega.rua, linha);

        fgets(linha, sizeof(linha), ptr);
        strcpy(cliente.endEntrega.cep, linha);

        // Apresenta os dados do arquivo
        printf("--------------------------------------\n");
        printf("Nome: %s", cliente.nome);
        printf("CPF: %s", cliente.cpf);
        printf("Email: %s", cliente.email);
        printf("Estado: %s", cliente.endEntrega.estado);
        printf("Cidade: %s", cliente.endEntrega.cidade);
        printf("Bairro: %s", cliente.endEntrega.bairro);
        printf("Rua: %s", cliente.endEntrega.rua);
        printf("CEP: %s", cliente.endEntrega.cep);
    }

    x = fclose(ptr);
    if (x == EOF)
    {
        printf("fechamento falhou\n");
        exit(1);
    }
}

void editarCompradores(char nome[MAX_NOME])
{
    FILE *ptr = fopen("../../arquivos/compradores.txt", "r");
    FILE *temp = fopen("../../arquivos/temp.txt", "w");

    if (ptr == NULL || temp == NULL)
    {
        printf("Erro ao abrir arquivos\n");
        exit(1);
    }

    compradores cliente;
    char linha[MAX_NOME];
    int find = 0;

    while(fgets(linha, sizeof(linha), ptr) != NULL)
    {
        if (strcmp(linha, nome) == 0){
            find = 1;
            strcpy(cliente.nome, linha); // copia o nome que esta em linha para cliente.nome

            fgets(linha, sizeof(linha), ptr);
            strcpy(cliente.cpf, linha);

            fgets(linha, sizeof(linha), ptr);
            strcpy(cliente.email, linha);

            fgets(linha, sizeof(linha), ptr);
            strcpy(cliente.endEntrega.estado, linha);

            fgets(linha, sizeof(linha), ptr);
            strcpy(cliente.endEntrega.cidade, linha);

            fgets(linha, sizeof(linha), ptr);
            strcpy(cliente.endEntrega.bairro, linha);

            fgets(linha, sizeof(linha), ptr);
            strcpy(cliente.endEntrega.rua, linha);

            fgets(linha, sizeof(linha), ptr);
            strcpy(cliente.endEntrega.cep, linha);

            // Solicita apenas as novas informações
            printf("\nEditando comprador: %s\n", cliente.nome);

            char alteracao[MAX_NOME];

            printf("Novo nome: ", cliente.nome);
            fgets(alteracao, MAX_NOME, stdin);
            if (strlen(alteracao) > 1)
            { // caso haja algum caractere digitado pelo usuario o valor e substituido em cliente.nome
                strcpy(cliente.nome, alteracao);
            }
            printf("Novo CPF: ", cliente.cpf);
            fgets(alteracao, MAX_CPF, stdin);
            if (strlen(alteracao) > 1)
            {
                strcpy(cliente.cpf, alteracao);
            }
            printf("Novo email: ", cliente.email);
            fgets(alteracao, MAX_NOME, stdin);
            if (strlen(alteracao) > 1)
            {
                strcpy(cliente.email, alteracao);
            }
            printf("Novo Estado: ", cliente.endEntrega.estado);
            fgets(alteracao, MAX_ENDERECO, stdin);
            if (strlen(alteracao) > 1)
            {
                strcpy(cliente.endEntrega.estado, alteracao);
            }
            printf("Nova cidade: ", cliente.endEntrega.cidade);
            fgets(alteracao, MAX_ENDERECO, stdin);
            if (strlen(alteracao) > 1)
            {
                strcpy(cliente.endEntrega.cidade, alteracao);
            }
            printf("Novo bairro: ", cliente.endEntrega.bairro);
            fgets(alteracao, MAX_ENDERECO, stdin);
            if (strlen(alteracao) > 1)
            {
                strcpy(cliente.endEntrega.bairro, alteracao);
            }
            printf("Nova rua: ", cliente.endEntrega.rua);
            fgets(alteracao, MAX_ENDERECO, stdin);
            if (strlen(alteracao) > 1)
            {
                strcpy(cliente.endEntrega.rua, alteracao);
            }
            printf("Novo CEP: ", cliente.endEntrega.cep);
            fgets(alteracao, MAX_ENDERECO, stdin);
            if (strlen(alteracao) > 1)
            {
                strcpy(cliente.endEntrega.cep, alteracao);
            }
            // Escreve os dados editados
            fprintf(temp, "%s%s%s%s%s%s%s%s",
                    cliente.nome,
                    cliente.cpf,
                    cliente.email,
                    cliente.endEntrega.estado,
                    cliente.endEntrega.cidade,
                    cliente.endEntrega.bairro,
                    cliente.endEntrega.rua,
                    cliente.endEntrega.cep);
        }
        else
        {
            // Copia os dados originais para o arquivo temporário
            fprintf(temp, "%s", linha);

            // Copia as próximas 7 linhas
            for (int i = 0; i < 7; i++)
            {
                if (fgets(linha, sizeof(linha), ptr) != NULL)
                {
                    fprintf(temp, "%s", linha);
                }
            }
        }
    }

    fclose(ptr);
    fclose(temp);

    if (!find)
    {
        printf("Comprador nao encontrado!\n");
        remove("../../arquivos/temp.txt");
    }
    else
    {
        remove("../../arquivos/compradores.txt");
        rename("../../arquivos/temp.txt", "../../arquivos/compradores.txt");
        printf("Comprador atualizado com sucesso!\n");
    }
}

void deletarCompradores(char nome[MAX_NOME])
{
    FILE *ptr = fopen("../../arquivos/compradores.txt", "r");
    FILE *temp = fopen("../../arquivos/temp.txt", "w");

    if (ptr == NULL || temp == NULL)
    {
        printf("Erro ao abrir arquivos\n");
        exit(1);
    }

    compradores cliente;
    char linha[MAX_NOME];
    int find=0;

    while(fgets(linha, sizeof(linha), ptr) != NULL){
        if (strcmp(linha, nome) == 0){
            find = 1;
            fprintf(temp, "%s", "");
            for (int i=0; i<7; i++){
                if (fgets(linha, sizeof(linha), ptr) != NULL){
                    fprintf(temp, "%s", "");
                }
            }
        }else{
            fprintf(temp, "%s", linha);
            for (int i = 0; i < 7; i++){
                if (fgets(linha, sizeof(linha), ptr) != NULL){
                    fprintf(temp, "%s", linha);
                }
            }
        }
    }

    fclose(ptr);
    fclose(temp);

    if (!find){
        printf("Comprador nao encontrado!\n");
        remove("../../arquivos/temp.txt");
    }
    else{
        remove("../../arquivos/compradores.txt");
        rename("../../arquivos/temp.txt", "../../arquivos/compradores.txt");
        printf("Comprador deletado com sucesso!\n");
    }
}