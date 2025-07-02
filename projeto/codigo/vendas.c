#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vendas.h"

FILE *vendas;

float calcularFrete(float valor){
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
        if (!ignorar) {
            fputs(linha, temp);
        }
    }
    fclose(original);
    fclose(temp);
    remove("../../arquivos/vendas.txt");
    rename("../../arquivos/temp.txt", "../../arquivos/vendas.txt");
    if (!vendaEncontrada) {
        printf("Venda com o codigo %d nao encontrada.\n", codigoAlvo);
        system("pause");
        return;
    }
    printf("Insira os novos dados para a venda de codigo %d.\n", codigoAlvo);
    FILE *vendasAtualizadas = fopen("../../arquivos/vendas.txt", "a");
    if (vendasAtualizadas == NULL) {
        printf("Erro ao abrir arquivo para escrita.\n");
        return;
    }
    int codVendedor;
    char vendedor[100];
    char comprador[100];
    char compradorEncontrado[100];
    int cod, qnt, maisItens, estoque;
    char nomeProduto[100];
    float precoUnit, total, totalItens = 0, frete;
    // Busca vendedor pelo código
    printf("Digite o codigo do vendedor: ");
    scanf("%d", &codVendedor);
    if (!buscarVendedorPorCodigo(codVendedor, vendedor)) {
        printf("Vendedor nao encontrado no arquivo!\n");
        fclose(vendasAtualizadas);
        return;
    }
    printf("Vendedor: %s\n", vendedor);
    // Busca comprador pelo nome
    printf("Digite o nome do comprador: ");
    scanf(" %[^\n]", comprador);
    if (!buscarCompradorPorNome(comprador, compradorEncontrado)) {
        printf("Comprador nao encontrado no arquivo!\n");
        fclose(vendasAtualizadas);
        return;
    }
    fprintf(vendasAtualizadas, "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    fprintf(vendasAtualizadas, "codigo: %d\n", codigoAlvo);
    fprintf(vendasAtualizadas, "vendedor: %s\n", vendedor);
    fprintf(vendasAtualizadas, "comprador: %s\n", compradorEncontrado);
    do {
        printf("Digite o codigo do item: ");
        scanf("%d", &cod);
        if (!buscarProdutoPorCodigo(cod, nomeProduto, &precoUnit, &estoque)) {
            printf("Produto nao encontrado!\n");
            printf("Deseja tentar outro produto? (1-sim/0-nao): ");
            scanf("%d", &maisItens);
            if (maisItens == 1) continue;
            else break;
        }
        printf("Produto: %s | Preco unitario: %.2f | Estoque: %d\n", nomeProduto, precoUnit, estoque);
        printf("Digite a quantidade do item: ");
        scanf("%d", &qnt);
        if (qnt > estoque) {
            printf("Estoque insuficiente!\n");
            printf("Deseja tentar outra quantidade ou produto? (1-sim/0-nao): ");
            scanf("%d", &maisItens);
            if (maisItens == 1) continue;
            else break;
        }
        total = precoUnit * qnt;
        totalItens += total;
        fprintf(vendasAtualizadas, "itens:{\n");
        fprintf(vendasAtualizadas, "    cod:%d nome:%s un:%.2f qnt:%d total:%.2f\n", cod, nomeProduto, precoUnit, qnt, total);
        fprintf(vendasAtualizadas, "}\n");
        printf("Deseja adicionar mais itens? (1-sim/0-nao): ");
        scanf("%d", &maisItens);
    } while(maisItens == 1);
    frete = calcularFrete(totalItens);
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
    char compradorNome[100] = "";
    // Busca a venda e extrai o nome do comprador
    while (fgets(linha, sizeof(linha), vendas) != NULL) {
        if (strstr(linha, "codigo:")) {
            int codigo;
            sscanf(linha, "codigo: %d", &codigo);
            if (codigo == codigoVenda) {
                vendaEncontrada = 1;
                // Avança até achar o comprador
                while (fgets(linha, sizeof(linha), vendas) != NULL) {
                    if (strstr(linha, "comprador:")) {
                        sscanf(linha, "comprador: %[^\n]", compradorNome);
                        break;
                    }
                }
                break;
            }
        }
    }
    fclose(vendas);
    if (!vendaEncontrada) {
        printf("Venda com o codigo %d nao encontrada.\n", codigoVenda);
        return;
    }
    // Busca os dados completos do comprador
    FILE *compradores = fopen("../../arquivos/compradores.txt", "r");
    if (!compradores) {
        printf("Erro ao abrir compradores.txt!\n");
        return;
    }
    char nome[100] = "", cpf[30] = "", email[100] = "", rua[100] = "", bairro[100] = "", cidade[100] = "", estado[100] = "", cep[100] = "";
    int id = 0;
    int achou = 0;
    while (fgets(linha, sizeof(linha), compradores)) {
        if (strncmp(linha, "ID:", 3) == 0) {
            sscanf(linha, "ID: %d", &id);
        } else if (strncmp(linha, "Nome:", 5) == 0) {
            sscanf(linha, "Nome: %[^\n]", nome);
        } else if (strncmp(linha, "CPF:", 4) == 0) {
            sscanf(linha, "CPF: %[^\n]", cpf);
        } else if (strncmp(linha, "Email:", 6) == 0) {
            sscanf(linha, "Email: %[^\n]", email);
        } else if (strncmp(linha, "Rua:", 4) == 0) {
            sscanf(linha, "Rua: %[^\n]", rua);
        } else if (strncmp(linha, "Bairro:", 7) == 0) {
            sscanf(linha, "Bairro: %[^\n]", bairro);
        } else if (strncmp(linha, "Cidade:", 7) == 0) {
            sscanf(linha, "Cidade: %[^\n]", cidade);
        } else if (strncmp(linha, "Estado:", 7) == 0) {
            sscanf(linha, "Estado: %[^\n]", estado);
        } else if (strncmp(linha, "CEP:", 4) == 0) {
            sscanf(linha, "CEP: %[^\n]", cep);
        }
        // Quando terminar um bloco de comprador, verifica se é o certo
        if (linha[0] == '\n' || feof(compradores)) {
            if (strcmp(nome, compradorNome) == 0) {
                achou = 1;
                break;
            }
            // Limpa para o próximo
            nome[0] = cpf[0] = email[0] = rua[0] = bairro[0] = cidade[0] = estado[0] = cep[0] = '\0';
            id = 0;
        }
    }
    fclose(compradores);
    // Gera a nota fiscal
    FILE *notaFiscal = fopen("../../arquivos/nota_fiscal.txt", "w");
    if (!notaFiscal) {
        printf("Erro ao criar o arquivo de nota fiscal.\n");
        return;
    }
    fprintf(notaFiscal, "===== NOTA FISCAL =====\n");
    fprintf(notaFiscal, "Comprador: %s\nCPF: %s\nEmail: %s\nEndereco: %s, %s, %s, %s, %s\n",
        nome, cpf, email, rua, bairro, cidade, estado, cep);
    // Agora copia os dados da venda para a nota
    vendas = fopen("../../arquivos/vendas.txt", "r");
    int dentroVenda = 0;
    while (fgets(linha, sizeof(linha), vendas)) {
        if (strstr(linha, "codigo:")) {
            int codigo;
            sscanf(linha, "codigo: %d", &codigo);
            dentroVenda = (codigo == codigoVenda);
        }
        if (dentroVenda) {
            fprintf(notaFiscal, "%s", linha);
            if (strstr(linha, "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=")) {
                break;
            }
        }
    }
    fclose(vendas);
    fclose(notaFiscal);
    printf("Nota fiscal emitida com sucesso!\n");
    system("pause");
}

// Função auxiliar para buscar comprador pelo nome
int buscarCompradorPorNome(const char *nomeBuscado, char *saida) {
    FILE *fp = fopen("../../arquivos/compradores.txt", "r");
    if (!fp) {
        printf("Erro ao abrir compradores.txt!\n");
        return 0;
    }
    char linha[256];
    int encontrado = 0;
    while (fgets(linha, sizeof(linha), fp)) {
        char nome[100];
        // Supondo que o nome esteja na linha como: Nome: <nome>
if (sscanf(linha, "Nome: %[^\n]", nome) == 1) {
    if (strcmp(nome, nomeBuscado) == 0) {
        encontrado = 1;
        strcpy(saida, nome);
        break;
    }
}
    }
    fclose(fp);
    return encontrado;
}

// Função para buscar produto no arquivo produtos.txt pelo código
// Retorna 1 se encontrou, 0 se não encontrou
int buscarProdutoPorCodigo(int codigoBuscado, char *nome, float *preco, int *quantidade) {
    FILE *fp = fopen("../../arquivos/produtos.txt", "r");
    if (!fp) {
        printf("Erro ao abrir produtos.txt!\n");
        return 0;
    }
    int codigoLido, qtdLida;
    char nomeLido[100];
    float precoLido;
    int encontrado = 0;
    while (fscanf(fp, "%d;%99[^;];%d;%f\n", &codigoLido, nomeLido, &qtdLida, &precoLido) == 4) {
        if (codigoLido == codigoBuscado) {
            if (nome) strcpy(nome, nomeLido);
            if (preco) *preco = precoLido;
            if (quantidade) *quantidade = qtdLida;
            encontrado = 1;
            break;
        }
    }
    fclose(fp);
    return encontrado;
}

// Função para buscar vendedor no arquivo vendedores.txt pelo código
// Retorna 1 se encontrou, 0 se não encontrou
int buscarVendedorPorCodigo(int codigoBuscado, char *nome) {
    FILE *fp = fopen("../../arquivos/vendedores.txt", "r");
    if (!fp) {
        printf("Erro ao abrir vendedores.txt!\n");
        return 0;
    }
    int codigoLido;
    char nomeLido[100];
    float salario;
    int encontrado = 0;
    while (fscanf(fp, "%d;%99[^;];%f\n", &codigoLido, nomeLido, &salario) == 3) {
        if (codigoLido == codigoBuscado) {
            if (nome) strcpy(nome, nomeLido);
            encontrado = 1;
            break;
        }
    }
    fclose(fp);
    return encontrado;
}

void novaVenda(){
    int codigoVenda;
    int codVendedor;
    char vendedor[256];
    char comprador[256];
    char compradorEncontrado[256];
    // Itens
    char nome[256];
    float un;
    int qnt,r,cod;
    float total;
    float totalItens = 0;
    float frete;
    // Abrindo o arquivo para escrita
    vendas = fopen("../../arquivos/vendas.txt", "a");
    if (vendas == NULL) {
        printf("Erro ao criar o arquivo!\n");
        return;
    }
    // Coletando dados da venda
    codigoVenda = gerarCodigo();
    // Busca vendedor pelo código
    printf("Digite o codigo do vendedor: ");
    scanf("%d", &codVendedor);
    if (!buscarVendedorPorCodigo(codVendedor, vendedor)) {
        printf("Vendedor nao encontrado no arquivo!\n");
        fclose(vendas);
        return;
    }
    printf("Vendedor: %s\n", vendedor);
    // Busca comprador pelo nome
    printf("Digite o nome do comprador: ");
    scanf(" %[^\n]", comprador);
    if (!buscarCompradorPorNome(comprador, compradorEncontrado)) {
        printf("Comprador nao encontrado no arquivo!\n");
        fclose(vendas);
        return;
    }
    // Escrevendo no arquivo
    fprintf(vendas, "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    fprintf(vendas, "codigo: %d\n", codigoVenda);
    fprintf(vendas, "vendedor: %s\n", vendedor);
    fprintf(vendas, "comprador: %s\n", compradorEncontrado);
    // Coletando dados dos itens e salvando no arquivo
    do{
        printf("Digite o codigo do item: ");
        scanf("%d", &cod);
        // Buscar produto no arquivo
        int estoque;
        float precoUnit;
        char nomeProduto[100];
        if (!buscarProdutoPorCodigo(cod, nomeProduto, &precoUnit, &estoque)) {
            printf("Produto nao encontrado!\n");
            printf("Deseja tentar outro produto? (1-sim/0-nao): ");
            scanf("%d", &r);
            if (r == 1) continue;
            else break;
        }
        printf("Produto: %s | Preco unitario: %.2f | Estoque: %d\n", nomeProduto, precoUnit, estoque);
        printf("Digite a quantidade do item: ");
        scanf("%d", &qnt);
        if (qnt > estoque) {
            printf("Estoque insuficiente!\n");
            printf("Deseja tentar outra quantidade ou produto? (1-sim/0-nao): ");
            scanf("%d", &r);
            if (r == 1) continue;
            else break;
        }
        total = precoUnit * qnt;
        totalItens += total;
        fprintf(vendas, "itens:{\n");
        fprintf(vendas, "    cod:%d nome:%s un:%.2f qnt:%d total:%.2f\n", cod, nomeProduto, precoUnit, qnt, total);
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
                deletarVenda();
                break;
            }
            case 3: {
                listarVendas();
                break;
            }
            case 4:{
                novaVenda();
                break;
            }
            case 5:{
                emitirNota();
                break;
            }
            case 0:{
                printf("Saindo do programa...\n");
                break;
            }
            default:{
                printf("Opcao invalida! Tente novamente.\n");
            }
        }
    } while (opcao != 0);
}