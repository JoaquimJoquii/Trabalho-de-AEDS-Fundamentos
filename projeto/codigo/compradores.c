#include "compradores.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct endereco{
    char rua[MAX_ENDERECO];
    char bairro[MAX_ENDERECO];
    char cidade[MAX_ENDERECO];
    char estado[MAX_ENDERECO];
    char cep[MAX_ENDERECO];
} endereco;

typedef struct compradores{
    int id;
    char nome[MAX_NOME];
    char cpf[MAX_CPF];
    char email[MAX_NOME];
    endereco endEntrega; // endereco de entrega do comprador
} compradores;

int cadastrarCompradores(int quant){
    int i, x;
    FILE *ptr = fopen("../../arquivos/compradores.txt", "a");
    if (ptr == NULL){
        printf("abertura falhou\n");
        exit(-1);
    }
    compradores clientes[quant];

    if(quant>0){
        while (getchar() != '\n');//limpa o \n do buffer de entrada
        // loop para a entrada de dados pelo usuario
        for (i = 0; i < quant; i++){
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
        for (i = 0; i < quant; i++){
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
    }else{
        printf("\nentrada invalida\n");
        return 1;
    }
    x = fclose(ptr);
    if (x == EOF){
        printf("\nfechamento falhou\n");
        exit(-1);
    }
    printf("\nCadastro concluido com sucesso\n");
    system("pause");
    return 0;
}

int apresentarCompradores(){
    FILE *ptr = fopen("../../arquivos/compradores.txt", "r");
    if (ptr == NULL){
        printf("abertura falhou\n");
        exit(-1);
    }

    int cont=0, x;
    compradores cliente;
    char linha[MAX_NOME];

    while (fgets(linha, sizeof(linha), ptr) != NULL){
        cont++;
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

        // imprimi os dados no arquivo
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
    if (x == EOF){
        printf("fechamento falhou\n");
        exit(-1);
    }

    if(cont==0){
        printf("\nNao existem compradores registrados no arquivo\n");
        system("pause");
        return 1;
    }else{
        printf("\nApresentação bem sucedida\n");
        system("pause");
        return 0;
    }
}

int editarCompradores(char nome[MAX_NOME]){
    FILE *ptr = fopen("../../arquivos/compradores.txt", "r");
    FILE *temp = fopen("../../arquivos/temp.txt", "w");

    if (ptr == NULL || temp == NULL){
        printf("Erro ao abrir arquivos\n");
        exit(-1);
    }

    compradores cliente;
    char linha[MAX_NOME];
    int find=0, cont=0;

    while(fgets(linha, sizeof(linha), ptr) != NULL){
        if (strcmp(linha, nome) == 0){
            cont++;
            find++;
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

            printf("Novo nome: ");
            fgets(alteracao, MAX_NOME, stdin);
            if (strlen(alteracao) > 1)
            { // caso haja algum caractere digitado pelo usuario o valor e substituido em cliente.nome
                strcpy(cliente.nome, alteracao);
            }
            printf("Novo CPF: ");
            fgets(alteracao, MAX_CPF, stdin);
            if (strlen(alteracao) > 1)//se o user nao entrar com valores o valor continua o mesmo
            {
                strcpy(cliente.cpf, alteracao);
            }
            printf("Novo email: ");
            fgets(alteracao, MAX_NOME, stdin);
            if (strlen(alteracao) > 1)
            {
                strcpy(cliente.email, alteracao);
            }
            printf("Novo Estado: ");
            fgets(alteracao, MAX_ENDERECO, stdin);
            if (strlen(alteracao) > 1)
            {
                strcpy(cliente.endEntrega.estado, alteracao);
            }
            printf("Nova cidade: ");
            fgets(alteracao, MAX_ENDERECO, stdin);
            if (strlen(alteracao) > 1)
            {
                strcpy(cliente.endEntrega.cidade, alteracao);
            }
            printf("Novo bairro: ");
            fgets(alteracao, MAX_ENDERECO, stdin);
            if (strlen(alteracao) > 1)
            {
                strcpy(cliente.endEntrega.bairro, alteracao);
            }
            printf("Nova rua: ");
            fgets(alteracao, MAX_ENDERECO, stdin);
            if (strlen(alteracao) > 1)
            {
                strcpy(cliente.endEntrega.rua, alteracao);
            }
            printf("Novo CEP: ");
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
        else{
            cont++;
            // Copia os dados originais para o arquivo temporário
            fprintf(temp, "%s", linha);

            // Copia as próximas 7 linhas
            for (int i = 0; i < 7; i++){
                if (fgets(linha, sizeof(linha), ptr) != NULL){
                    fprintf(temp, "%s", linha);
                }
            }
        }
    }

    fclose(ptr);
    fclose(temp);

    if(cont==0){
        printf("\nNao existem compradores registrados no arquivo\n");
        remove("../../arquivos/temp.txt");
        system("pause");
        return 1;
    }else{
        if (!find){
            printf("\nComprador nao encontrado!\n");
            remove("../../arquivos/temp.txt");
            system("pause");
            return 1;
        }else{
            remove("../../arquivos/compradores.txt");
            rename("../../arquivos/temp.txt", "../../arquivos/compradores.txt");
            printf("\nEdição concluida com sucesso!\n");
            system("pause");
            return 0;
        }
    }
}

int deletarCompradores(char nome[MAX_NOME]){
    FILE *ptr = fopen("../../arquivos/compradores.txt", "r");
    FILE *temp = fopen("../../arquivos/temp.txt", "w");

    if (ptr == NULL || temp == NULL){
        printf("Erro ao abrir arquivos\n");
        exit(-1);
    }

    char linha[MAX_NOME];
    int find=0, cont=0;

    while(fgets(linha, sizeof(linha), ptr) != NULL){
        if (strcmp(linha, nome) == 0){
            cont++;
            find++;
            fprintf(temp, "%s", "");
            for (int i=0; i<7; i++){
                if (fgets(linha, sizeof(linha), ptr) != NULL){
                    fprintf(temp, "%s", "");
                }
            }
        }else{
            fprintf(temp, "%s", linha);
            cont++;
            for (int i = 0; i < 7; i++){
                if (fgets(linha, sizeof(linha), ptr) != NULL){
                    fprintf(temp, "%s", linha);
                }
            }
        }
    }
    
    fclose(ptr);
    fclose(temp);

    if(cont==0){
        printf("\nNao existem compradores registrados neste arquivo\n");
        remove("../../arquivos/temp.txt");
        system("pause");
        return 1;
    }else{
        if(!find){
            printf("\nComprador nao encontrado!\n");
            remove("../../arquivos/temp.txt");
            system("pause");
            return 1;
        }
        else{
            remove("../../arquivos/compradores.txt");
            rename("../../arquivos/temp.txt", "../../arquivos/compradores.txt");
            printf("\nComprador deletado com sucesso!\n");
            system("pause");
            return 0;
        }
    }

}

int menuCompradores() {
    int opcao, i;
    char nome[MAX_NOME];
    do {
        system("cls");//limpa a tela
        // Exibe o menu
        printf("\n===== MENU =====\n");
        printf("1. Editar Compradores\n");
        printf("2. Deletar Compradores\n");
        printf("3. Apresentar Compradores\n");
        printf("4. Cadastrar Compradores\n");
        printf("0. Sair\n");
        printf("=================\n");
        printf("Escolha uma opcao: ");
        // Lê a opção do usuário
        scanf("%d", &opcao);
        switch(opcao) {
            case 1:
                while (getchar() != '\n');//limpa o \n do buffer de entrada deixado pelo scanf anterior
                printf("Digite o nome do comprador que deseja editar: ");
                fgets(nome, MAX_NOME, stdin);
                editarCompradores(nome);
                break;
            case 2: 
                while (getchar() != '\n');
                printf("Digite o nome do comprador que deseja deletar: ");
                fgets(nome, MAX_NOME, stdin);
                deletarCompradores(nome);
                break;
            case 3:
                apresentarCompradores();
                break;
            case 4:
                printf("Quantos compradores deseja cadastrar? ");
                scanf("%d", &i);
                cadastrarCompradores(i);
                break;
            case 0:
                printf("Saindo de compradores...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);
    return 0;
}