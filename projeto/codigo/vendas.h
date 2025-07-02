#ifndef VENDAS_H
#define VENDAS_H

float calcularFrete(float valor);

void alterarVenda();

void deletarVenda();

void listarVendas();

void novaVenda();

int gerarCodigo();

void menuVendas();

int buscarVendedorPorCodigo(int codigoBuscado, char *nome);

int buscarCompradorPorNome(const char *nome, char *saida);

int buscarProdutoPorCodigo(int codigoBuscado, char *nome, float *preco, int *quantidade);

void emitirNota();
#endif