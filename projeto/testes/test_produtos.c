#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "munit/munit.h"
#include "../codigo/produtos.h"

/* ---------- Fixture global ---------- */
static Produto buf[100];
static int qtd;

/* Executado antes de **cada** teste */
static void*
setup(const MunitParameter params[], void* user_data) {
  (void)params; (void)user_data;
  qtd = 0;                  /* zera contador           */
  return NULL;              /* µnit pode devolver ptr  */
}

/* Não precisamos de teardown, mas ele existe */
static void
teardown(void* fixture) {
  (void)fixture;
}

/* ---------- Casos de teste ---------- */

/* 1) Cadastro simples */
static MunitResult
test_cadastrar_sucesso(const MunitParameter params[], void* data) {
  (void)params; (void)data;

  Produto p = {"Arroz", 1, 50, 4.99f};
  int ok = cadastrarProduto(buf, &qtd, p);

  munit_assert_true(ok);
  munit_assert_int(qtd, ==, 1);
  munit_assert_string_equal(buf[0].nome, "Arroz");
  return MUNIT_OK;
}

/* 2) Código duplicado */
static MunitResult
test_cadastrar_duplicado(const MunitParameter params[], void* data) {
  (void)params; (void)data;

  Produto p1 = {"Arroz", 1, 50, 4.99f};
  Produto p2 = {"Feijao", 1, 30, 7.50f};

  cadastrarProduto(buf, &qtd, p1);
  int ok = cadastrarProduto(buf, &qtd, p2);

  munit_assert_false(ok);
  munit_assert_int(qtd, ==, 1);
  return MUNIT_OK;
}

/* 3) Alteração */
static MunitResult
test_alterar(const MunitParameter params[], void* data) {
  (void)params; (void)data;

  Produto p = {"Arroz", 1, 50, 4.99f};
  cadastrarProduto(buf, &qtd, p);

  Produto novo = {"ArrozIntegral", 1, 70, 5.99f};
  int ok = alterarProduto(buf, qtd, novo);

  munit_assert_true(ok);
  munit_assert_int(buf[0].quantidade, ==, 70);
  munit_assert_double(buf[0].preco, ==, 5.99f);
  return MUNIT_OK;
}

/* 4) Exclusão */
static MunitResult
test_excluir(const MunitParameter params[], void* data) {
  (void)params; (void)data;

  Produto p1 = {"Arroz", 1, 50, 4.99f};
  Produto p2 = {"Feijao", 2, 30, 7.50f};
  cadastrarProduto(buf, &qtd, p1);
  cadastrarProduto(buf, &qtd, p2);

  int ok = excluirProduto(buf, &qtd, 1);

  munit_assert_true(ok);
  munit_assert_int(qtd, ==, 1);
  munit_assert_int(buf[0].codigo, ==, 2);
  return MUNIT_OK;
}

/* 5) Consulta */
static MunitResult
test_consultar(const MunitParameter params[], void* data) {
  (void)params; (void)data;

  Produto p = {"Arroz", 1, 50, 4.99f};
  cadastrarProduto(buf, &qtd, p);

  munit_assert_true(consultarProduto(buf, qtd, 1));
  munit_assert_false(consultarProduto(buf, qtd, 99));
  return MUNIT_OK;
}

/* ---------- Tabela de testes ---------- */
static MunitTest tests[] = {
  { "/cadastrar_sucesso",  test_cadastrar_sucesso,  setup, teardown, MUNIT_TEST_OPTION_NONE, NULL },
  { "/cadastrar_duplicado", test_cadastrar_duplicado, setup, teardown, MUNIT_TEST_OPTION_NONE, NULL },
  { "/alterar",            test_alterar,            setup, teardown, MUNIT_TEST_OPTION_NONE, NULL },
  { "/excluir",            test_excluir,            setup, teardown, MUNIT_TEST_OPTION_NONE, NULL },
  { "/consultar",          test_consultar,          setup, teardown, MUNIT_TEST_OPTION_NONE, NULL },
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL } /* fim */
};

/* ---------- Suite ---------- */
static const MunitSuite suite = {
  "/produtos",  /* prefixo */
  tests,        /* array   */
  NULL,         /* sem sub‑suites */
  1,            /* nº de iterações */
  MUNIT_SUITE_OPTION_NONE
};

/* ---------- main ---------- */
int main(int argc, char* argv[]) {
  return munit_suite_main(&suite, NULL, argc, argv);
}
