#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vendas.h"

FILE *vendas;

float calcularFrete(float valor){
    float frete;
    if(valor<0){
        printf("erro, valor invalido!");
        return 0;
    }
    if (valor <= 100)
        return 30;
    else if (valor <= 300)
        return 20;
    else
        return 0;
}

int gerarCodigo() {
    FILE *arquivo = fopen("c../../arquivos/codigo.txt", "r+");  // abre para leitura/escrita
    int codigo;

    // Se o arquivo não existe, cria e começa do 1
    if (arquivo == NULL) {
        arquivo = fopen("../../arquivos/codigo.txt", "w");
        if (arquivo == NULL) {
            printf("Erro ao criar arquivo!\n");
            return -1;
        }
        codigo = 1;
    } else {
        fscanf(arquivo, "%d", &codigo);
        codigo++;  // incrementa o último código
    }

    // Reabre o arquivo para sobrescrever com o novo valor
    freopen("../../arquivos/codigo.txt", "w", arquivo);
    fprintf(arquivo, "%d", codigo);
    fclose(arquivo);

    return codigo;
}

void alterarVenda() {
    int codigoAlvo;
    printf("Digite o codigo da venda que deseja editar: ");
    // Solicita o código da venda a ser editada
    scanf("%d", &codigoAlvo);
    // Abre o arquivo original e um temporário para escrita
    FILE *temp = fopen("../../arquivos/temp.txt", "w");
    FILE *original = fopen("../../arquivos/vendas.txt", "r");

    if (original == NULL || temp == NULL) {
        printf("Erro ao abrir os arquivos!\n");
        return;
    }

    char linha[512];
    int ignorar = 0;
    int vendaEncontrada = 0;
    // Lê o arquivo original linha por linha
    while (fgets(linha, sizeof(linha), original)) {
        if (strstr(linha, "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=")) {
            ignorar = 0;
        }
        // Verifica se a linha contém o código da venda
        // Se o código for igual ao código alvo, ignora a venda e marca que a venda foi encontrada
        if (strstr(linha, "codigo:")) {
            int codigo;
            sscanf(linha, "codigo: %d", &codigo);
            if (codigo == codigoAlvo) {
                ignorar = 1;
                vendaEncontrada = 1;
            }
        }
        // Se a linha não for ignorada, escreve no arquivo temporário
        if (!ignorar) {
            fputs(linha, temp);
        }
    }
    // Fecha os arquivos temporário e original
    // Remove o arquivo original e renomeia o temporário para o nome original
    fclose(original);
    fclose(temp);
    remove("../../arquivos/vendas.txt");
    rename("../../arquivos/temp.txt", "../../arquivos/vendas.txt");
    // Se a venda foi encontrada, solicita os novos dados e escreve no arquivo
    // Se não, informa que a venda não foi encontrada
    if (!vendaEncontrada) {
        printf("Venda com o codigo %d nao encontrada.\n", codigoAlvo);
        system("pause");
        return;
    }

    // Recria a venda com mesmo código
    printf("Insira os novos dados para a venda de codigo %d.\n", codigoAlvo);

    FILE *vendasAtualizadas = fopen("../../arquivos/vendas.txt", "a");

    if (vendasAtualizadas == NULL) {
        printf("Erro ao abrir arquivo para escrita.\n");
        return;
    }

    char vendedor[100];
    char comprador[100];
    int cod, qnt, maisItens;
    char nome[100];
    float un, total, totalItens = 0, frete;

    printf("Digite o nome do vendedor: ");
    scanf(" %[^\n]", vendedor);
    printf("Digite o nome do comprador: ");
    scanf(" %[^\n]", comprador);

    fprintf(vendasAtualizadas, "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    fprintf(vendasAtualizadas, "codigo: %d\n", codigoAlvo);
    fprintf(vendasAtualizadas, "vendedor: %s\n", vendedor);
    fprintf(vendasAtualizadas, "comprador: %s\n", comprador);
    fprintf(vendasAtualizadas, "itens:{\n");

    do {
        printf("Digite o codigo do item: ");
        scanf("%d", &cod);
        printf("Digite o nome do item: ");
        scanf(" %[^\n]", nome);
        do{// Loop para garantir que o valor unitário e a quantidade sejam positivos
            un = -1; // Inicializa un com um valor negativo para entrar no loop
            qnt = -1; // Inicializa qnt com um valor negativo para entrar no loop
            printf("Digite o valor unitario do item: ");
            scanf("%f", &un);
            printf("Digite a quantidade do item: ");
            scanf("%d", &qnt);
                if(un < 0 || qnt < 0) {
                    printf("Erro: valor unitario e quantidade devem ser positivos.\n");
                }
        }while ((qnt < 0)||(un < 0));
        
        total = un * qnt;
        totalItens += total;

        fprintf(vendasAtualizadas, "    cod:%d nome:%s un:%.2f qnt:%d total:%.2f\n", cod, nome, un, qnt, total);

        printf("Deseja adicionar mais itens? (1 - Sim / 0 - Não): ");
        scanf("%d", &maisItens);
    } while (maisItens == 1);

    frete = calcularFrete(totalItens);

    fprintf(vendasAtualizadas, "}\n");
    fprintf(vendasAtualizadas, "total dos itens:%.2f frete:%.2f \n", totalItens, frete);
    fprintf(vendasAtualizadas, "total da compra=%.2f\n", totalItens + frete);
    fprintf(vendasAtualizadas, "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");

    fclose(vendasAtualizadas);
    printf("Venda atualizada com sucesso.\n");
    system("pause");
}

void deletarVenda() {
    int codigoAlvo;
    // Solicita o código da venda a ser deletada
    printf("Digite o codigo da venda que deseja deletar: ");
    scanf("%d", &codigoAlvo);

    FILE *temp = fopen("../../arquivos/temp.txt", "w");
    FILE *original = fopen("../../arquivos/vendas.txt", "r");

    if (original == NULL || temp == NULL) {
        printf("Erro ao abrir os arquivos!\n");
        return;
    }

    char linha[512];
    int ignorar = 0;
    int vendaEncontrada = 0;
    // Lê o arquivo original linha por linha
    // Se a linha contém o separador, reseta a flag de ignorar 
    while (fgets(linha, sizeof(linha), original)) {
        if (strstr(linha, "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=")) {
            ignorar = 0;
        }

        if (strstr(linha, "codigo:")) {
            int codigo;
            sscanf(linha, "codigo: %d", &codigo);
            if (codigo == codigoAlvo) {
                ignorar = 1;
                vendaEncontrada = 1;
            }
        }
        // Se a linha não for ignorada, escreve no arquivo temporário
        if (!ignorar) {
            fputs(linha, temp);
        }
    }
    // Fecha os arquivos temporário e original
    // Remove o arquivo original e renomeia o temporário para o nome original
    fclose(original);
    fclose(temp);
    remove("../../arquivos/vendas.txt");
    rename("../../arquivos/temp.txt", "../../arquivos/vendas.txt");
    // Informa se a venda foi encontrada e removida ou não
    if (vendaEncontrada)
        printf("Venda removida com sucesso.\n");
    else
        printf("Venda com o código %d não encontrada.\n", codigoAlvo);

    system("pause");
}

void listarVendas() {
    vendas = fopen("../../arquivos/vendas.txt", "r");
    if (vendas == NULL) {
        printf("Erro ao abrir o arquivo de vendas.\n");
        return;
    }
    char linha[256];// Buffer para armazenar cada linha lida do arquivo
    // Lê e exibe cada linha do arquivo
    printf("\n===== LISTA DE VENDAS =====\n");
    while (fgets(linha, sizeof(linha), vendas) != NULL) {
        printf("%s", linha);
    }
    fclose(vendas);
    printf("============================\n");
    system("pause");
}

void emitirNota(){
    int codigoVenda;
    printf("Digite o codigo da venda para emitir a nota: ");
    scanf("%d", &codigoVenda);

    vendas = fopen("../../arquivos/vendas.txt", "r");
    if (vendas == NULL) {
        printf("Erro ao abrir o arquivo de vendas.\n");
        return;
    }

    char linha[256];
    int vendaEncontrada = 0;
    FILE *notaFiscal;
    notaFiscal = fopen("../../arquivos/nota_fiscal.txt", "w");
    if (notaFiscal == NULL) {
        printf("Erro ao criar o arquivo de nota fiscal.\n");
        fclose(vendas);
        return;
    }
    while (fgets(linha, sizeof(linha), vendas) != NULL) {
        if (strstr(linha, "codigo:")) {
            int codigo;
            sscanf(linha, "codigo: %d", &codigo);
            if (codigo == codigoVenda) {
                vendaEncontrada = 1;
                fprintf(notaFiscal,"\n===== NOTA FISCAL =====\n");
                fprintf(notaFiscal,"%s", linha);
                while (fgets(linha, sizeof(linha), vendas) != NULL && !strstr(linha, "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=")) {
                    fprintf(notaFiscal,"%s", linha);
                }
                fprintf(notaFiscal,"\n========================\n");
                break;
            }
        }
    }
    fclose(notaFiscal);
    fclose(vendas);

    if (!vendaEncontrada) {
        printf("Venda com o codigo %d nao encontrada.\n", codigoVenda);
    }
    printf("nota fiscal emitida com sucesso!\n");
    system("pause");
    return;
}

void novaVenda(){
    int codigoVenda;
    char vendedor[256];
    char comprador[256];
    
    // Itens
    char nome[256];
    float un;
    int qnt,r,cod;
    float total = un * qnt;

    float totalItens = 0;
    float frete;

    // Abrindo o arquivo para escrita
    vendas = fopen("vendas.txt", "a");
    if (vendas == NULL) {
        printf("Erro ao criar o arquivo!\n");
        return 0;
    }
    // Coletando dados da venda
    printf("Digite o codigo da venda: ");
    scanf("%d", &codigoVenda);
    printf("Digite o nome do vendedor: ");
    scanf(" %s", vendedor);
    printf("Digite o nome do comprador: ");
    scanf(" %s", comprador);

    // Escrevendo no arquivo
    fprintf(vendas, "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    fprintf(vendas, "codigo: %d\n", codigoVenda);
    fprintf(vendas, "vendedor: %s\n", vendedor);
    fprintf(vendas, "comprador: %s\n", comprador);
    // Coletando dados dos itens e salvando no arquivo
    do{
        printf("Digite o codigo do item: ");
        scanf("%d", &cod);
        printf("Digite o nome do item: ");
        scanf(" %s", nome);
        printf("Digite o valor unitario do item: ");
        scanf("%f", &un);
        printf("Digite a quantidade do item: ");
        scanf("%d", &qnt);
        
        total = un * qnt;
        totalItens += total;

        fprintf(vendas, "itens:{\n");
        fprintf(vendas, "    cod:%d nome:%s un:%.2f qnt:%d total:%.2f\n", cod, nome, un, qnt, total);
        fprintf(vendas, "}\n");

        printf("Deseja adicionar mais itens? (1-sim/0-nao): ");
        scanf("%d", &r);
    } while(r == 1);
    //calculando o frete
    frete = calcularFrete(totalItens);
    fprintf(vendas, "total dos itens:%.2f frete:%.2f \n", totalItens, frete);
    fprintf(vendas, "total da compra=%.2f\n", totalItens + frete);
    fprintf(vendas, "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");

    fclose(vendas);

    printf("venda salva com sucesso!\n");
    system("pause"); 
    return 0;
}

void menuVendas(void) {
    int opcao;
    do {
        // Exibe o menu
        printf("\n===== MENU =====\n");
        printf("1. Editar Vendas\n");
        printf("2. Deletar vendas\n");
        printf("3. Listar vendas\n");
        printf("4. Nova venda\n");
        printf("5. Emitir nota fiscal\n");
        printf("0. Sair\n");
        printf("=================\n");
        printf("Escolha uma opcao: ");
        // Lê a opção do usuário
        scanf("%d", &opcao);
        switch(opcao) {
            case 1: {
                alterarVenda();
                break;
            }
            case 2: {
                detetarVenda();
                break;
            }
            case 3: {
                listarVendas();
                break;
            }
            case 4:
                novaVenda();
                break;
            case 5:
                emitirNota();
                break;
            case 0:
                printf("Saindo do programa...\n");
                break;
            }
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}