#include "munit.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../codigo/vendas.h"

// Cria arquivos simulados para testes
void setup_mock_files() {
    // vendedores.txt
    FILE *f = fopen("../../arquivos/vendedores.txt", "w");
    fprintf(f, "1;Joao;3000.00\n");
    fclose(f);

    // compradores.txt
    f = fopen("../../arquivos/compradores.txt", "w");
    fprintf(f, "ID: 1\nNome: Maria\nCPF: 123.456.789-00\nEmail: maria@email.com\nRua: Rua A\nBairro: Centro\nCidade: Cidade\nEstado: Estado\nCEP: 00000-000\n\n");
    fclose(f);

    // produtos.txt
    f = fopen("../../arquivos/produtos.txt", "w");
    fprintf(f, "10;Caneta Azul;100;2.50\n");
    fclose(f);

    // vendas.txt
    f = fopen("../../arquivos/vendas.txt", "w");
    fprintf(f, "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    fprintf(f, "codigo: 1\nvendedor: Joao\ncomprador: Maria\n");
    fprintf(f, "itens:{\n    cod:10 nome:Caneta Azul un:2.50 qnt:2 total:5.00\n}\n");
    fprintf(f, "total dos itens:5.00 frete:30.00 \ntotal da compra=35.00\n");
    fprintf(f, "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    fclose(f);

    // codigo.txt
    f = fopen("../../arquivos/codigo.txt", "w");
    fprintf(f, "10");
    fclose(f);
}

// ---------- TESTES ----------

MunitResult test_calcular_frete(void *udata) {
    (void)udata;
    munit_assert_float(calcularFrete(50.0), ==, 30.0);
    munit_assert_float(calcularFrete(150.0), ==, 20.0);
    munit_assert_float(calcularFrete(500.0), ==, 0.0);
    munit_assert_float(calcularFrete(-10.0), ==, 0.0);
    return MUNIT_OK;
}

MunitResult test_gerar_codigo(void *udata) {
    (void)udata;
    setup_mock_files();
    int c1 = gerarCodigo();
    int c2 = gerarCodigo();
    munit_assert_int(c2, ==, c1 + 1);
    return MUNIT_OK;
}

MunitResult test_buscar_vendedor(void *udata) {
    (void)udata;
    setup_mock_files();
    char nome[100];
    int achou = buscarVendedorPorCodigo(1, nome);
    munit_assert_int(achou, ==, 1);
    munit_assert_string_equal(nome, "Joao");
    return MUNIT_OK;
}

MunitResult test_buscar_comprador(void *udata) {
    (void)udata;
    setup_mock_files();
    char nome[100];
    int achou = buscarCompradorPorNome("Maria", nome);
    munit_assert_int(achou, ==, 1);
    munit_assert_string_equal(nome, "Maria");
    return MUNIT_OK;
}

MunitResult test_buscar_produto(void *udata) {
    (void)udata;
    setup_mock_files();
    char nome[100];
    float preco;
    int estoque;
    int achou = buscarProdutoPorCodigo(10, nome, &preco, &estoque);
    munit_assert_int(achou, ==, 1);
    munit_assert_string_equal(nome, "Caneta Azul");
    munit_assert_float(preco, ==, 2.5);
    munit_assert_int(estoque, ==, 100);
    return MUNIT_OK;
}

MunitResult test_emitir_nota(void *udata) {
    (void)udata;
    setup_mock_files();

    // redireciona entrada simulada
    FILE *input = fopen("input.txt", "w");
    fprintf(input, "1\n");
    fclose(input);
    freopen("input.txt", "r", stdin);

    emitirNota();

    // verifica se nota_fiscal.txt foi criada
    FILE *f = fopen("../../arquivos/nota_fiscal.txt", "r");
    munit_assert_not_null(f);
    fclose(f);
    return MUNIT_OK;
}

// ---------- SUITE ----------

static MunitTest tests[] = {
    { "/calcular_frete", test_calcular_frete, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/gerar_codigo", test_gerar_codigo, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/buscar_vendedor", test_buscar_vendedor, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/buscar_comprador", test_buscar_comprador, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/buscar_produto", test_buscar_produto, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/emitir_nota", test_emitir_nota, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
    "/vendas", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}