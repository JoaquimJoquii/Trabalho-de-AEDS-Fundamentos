#include "munit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Inclui o arquivo que será testado
#include "../codigo/vendedores.h"

// Torna as variáveis globais do módulo visíveis para os testes
extern struct vendedores lista[];
extern int qtd;
extern int proximo_numero;

#define TMP_IN "entrada.txt"
#define TMP_OUT "saida.txt"

// Helpers
void limparArquivo() {
    // Limpa o arquivo de dados dos vendedores
    FILE *f = fopen("../../arquivos/vendedores.txt", "w");
    if (f) fclose(f);
    // Zera as variáveis globais
    qtd = 0;
    proximo_numero = 1;
}

// Simula entrada e redireciona saída para evitar `printf` poluir o terminal
void simularEntrada(const char *input) {
    FILE *in = fopen(TMP_IN, "w");
    fputs(input, in);
    fclose(in);
    freopen(TMP_IN, "r", stdin);

    FILE *out = fopen(TMP_OUT, "w");
    fclose(out);
    freopen(TMP_OUT, "w", stdout);
}

// -------- TESTES --------

MunitResult test_inserir(void *udata) {
    (void)udata;
    limparArquivo();
    simularEntrada("1\nJoao\n2500.50\n");

    inserir();

    munit_assert_int(qtd, ==, 1);
    munit_assert_string_equal(lista[0].nome, "Joao");
    munit_assert_float(lista[0].salario_fixo, ==, 2500.50);
    return MUNIT_OK;
}

MunitResult test_consultar(void *udata) {
    (void)udata;
    limparArquivo();
    lista[0].numero = 7;
    strcpy(lista[0].nome, "Paula");
    lista[0].salario_fixo = 4000;
    qtd = 1;

    simularEntrada("7\n");
    consultar();

    return MUNIT_OK;
}

MunitResult test_alterar(void *udata) {
    (void)udata;
    limparArquivo();
    lista[0].numero = 3;
    strcpy(lista[0].nome, "Antigo");
    lista[0].salario_fixo = 3000;
    qtd = 1;

    simularEntrada("3\nNovoNome\n3500\n");
    alterar();

    munit_assert_string_equal(lista[0].nome, "NovoNome");
    munit_assert_float(lista[0].salario_fixo, ==, 3500);
    return MUNIT_OK;
}

MunitResult test_excluir(void *udata) {
    (void)udata;
    limparArquivo();
    lista[0].numero = 1;
    strcpy(lista[0].nome, "Excluir");
    lista[0].salario_fixo = 1000;
    qtd = 1;

    simularEntrada("1\n");
    excluir();

    munit_assert_int(qtd, ==, 0);
    return MUNIT_OK;
}

MunitResult test_registrar_venda(void *udata) {
    (void)udata;
    limparArquivo();
    lista[0].numero = 2;
    strcpy(lista[0].nome, "Vendedor");
    lista[0].salario_fixo = 1000;
    qtd = 1;

    simularEntrada("2\n200\n");
    registrar_venda();

    munit_assert_float(lista[0].salario_fixo, ==, 1000 + (200 * 0.03));
    return MUNIT_OK;
}

MunitResult test_buscar(void *udata) {
    (void)udata;
    limparArquivo();
    lista[0].numero = 99;
    qtd = 1;

    int achou = buscar(99);
    munit_assert_int(achou, ==, 0);

    int naoAchou = buscar(1);
    munit_assert_int(naoAchou, ==, -1);
    return MUNIT_OK;
}

MunitResult test_salvar_carregar(void *udata) {
    (void)udata;
    limparArquivo();

    lista[0].numero = 5;
    strcpy(lista[0].nome, "Teste");
    lista[0].salario_fixo = 1999.90;
    qtd = 1;

    salvarVendedoresEmArquivo();
    qtd = 0;
    carregarVendedoresDeArquivo();

    munit_assert_int(qtd, ==, 1);
    munit_assert_string_equal(lista[0].nome, "Teste");
    return MUNIT_OK;
}

// -------- SUITE --------

static MunitTest tests[] = {
    { "/inserir", test_inserir, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/consultar", test_consultar, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/alterar", test_alterar, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/excluir", test_excluir, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/registrar_venda", test_registrar_venda, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/buscar", test_buscar, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/salvar_carregar", test_salvar_carregar, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
    "/vendedores", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
