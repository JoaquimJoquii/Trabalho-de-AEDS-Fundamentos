#include <stdio.h>
#include <stdlib.h>
#include "../codigo/compradores.h"
#define MUNIT_ENABLE_ASSERT_ALIASES
#define GENERICO "123456789\n"
#define NOME "teste\n"
#include "./munit/munit.h"

//casos de teste deletar
static MunitResult exemplo(const MunitParameter params[], void* fixture) {
    //preparação
    //execução
    //verificação
    return MUNIT_OK;
}
static MunitResult deletar_arquivo_vazio(const MunitParameter params[], void* fixture) {
    //cria um arquivo em branco
    FILE *ptr = fopen("../../arquivos/compradores.txt", "w");
    fclose(ptr);

    //chama a função dando como parametro uma constante
    deletarCompradores(NOME);

    //verificando se o arquivo continua vazio
    ptr = fopen("../../arquivos/compradores.txt", "r");
    int c = fgetc(ptr);
    fclose(ptr);

    assert_int(c, ==, EOF);

    return MUNIT_OK;
}
static MunitResult deletar_sucesso(const MunitParameter params[], void* fixture){
    //abrindo um arquivo em branco e preenchendo ele com um comprador generico
    FILE *ptr = fopen("../../arquivos/compradores.txt", "w");
    munit_assert_not_null(ptr);

    fprintf(ptr, "%s", NOME);
    for(int i=0; i<7; i++){
        fprintf(ptr, "%s", GENERICO);
    }
    fclose(ptr);
    
    //chamando a função
    deletarCompradores(NOME);
    
    //verificando se o nome ainda esta no arquivo
    ptr = fopen("../../arquivos/compradores.txt", "r");
    munit_assert_not_null(ptr);
    
    char linha[MAX_NOME];
    while(fgets(linha, sizeof(linha), ptr) != NULL){
        assert_string_not_equal(linha, NOME);
    }
    fclose(ptr);

    return MUNIT_OK;
}
static MunitResult deletar_inexistente(const MunitParameter params[], void* fixture) {
    //abrindo um arquivo em branco e preenchendo com um comprador generico
    FILE *ptr = fopen("../../arquivos/compradores.txt", "w");
    munit_assert_not_null(ptr);
    
    fprintf(ptr, "Joao Carlos\n");  // Nome diferente do que será buscado
    for(int i = 0; i < 7; i++) {
        fprintf(ptr, "%s", GENERICO); 
    }
    fclose(ptr);

    //Redirecionamento de saída e execução
    FILE *temp_out = freopen("output.txt", "w", stdout);
    munit_assert_not_null(temp_out);
    
    deletarCompradores(NOME);// Nome que não existe no arquivo
    FILE *con_out = freopen("CON", "w", stdout);  // Restauração para Windows
    munit_assert_not_null(con_out);

    //Verificação da mensagem impressa no arquivo
    ptr = fopen("output.txt", "r");
    munit_assert_not_null(ptr);
    
    char mensagem[100];
    fgets(mensagem, sizeof(mensagem), ptr);
    fclose(ptr);
    
    mensagem[strcspn(mensagem, "\n")] = '\0';
    munit_assert_string_equal(mensagem, "Comprador nao encontrado!");
    remove("output.txt");

    //Verifica se o arquivo compradores continua igual
    ptr = fopen("../../arquivos/compradores.txt", "r");
    munit_assert_not_null(ptr);
    
    int linhas = 0;
    char linha[MAX_NOME];
    while(fgets(linha, sizeof(linha), ptr) != NULL) {
        linhas++;
    }
    fclose(ptr);

    munit_assert_int(linhas, ==, 8);  // Deve manter 1 registro completo (8 linhas)

    return MUNIT_OK;
}

//casos de teste de edição
static MunitResult editar_arquivo_vazio(const MunitParameter params[], void* fixture) {
    //cria um arquivo em branco
    FILE *ptr = fopen("../../arquivos/compradores.txt", "w");
    fclose(ptr);

    //chama a função dando como parametro uma constante
    deletarCompradores(NOME);

    //verificando se o arquivo continua vazio
    ptr = fopen("../../arquivos/compradores.txt", "r");
    int c = fgetc(ptr);
    fclose(ptr);

    assert_int(c, ==, EOF);

    return MUNIT_OK;
}
static MunitResult editar_sucesso(const MunitParameter params[], void* fixture){
    //abrindo um arquivo em branco e preenchendo ele com um comprador generico
    FILE *ptr = fopen("../../arquivos/compradores.txt", "w");
    munit_assert_not_null(ptr);

    fprintf(ptr, "%s", NOME);
    for(int i=0; i<7; i++){
        fprintf(ptr, "%s", GENERICO);
    }
    fclose(ptr);
    
    //chamando a função
    editarCompradores(NOME);
    //verificando se o nome ainda esta no arquivo
    ptr = fopen("../../arquivos/compradores.txt", "r");
    munit_assert_not_null(ptr);
    
    char linha[MAX_NOME];
    while(fgets(linha, sizeof(linha), ptr) != NULL){
        assert_string_not_equal(linha, NOME);
    }
    fclose(ptr);

    return MUNIT_OK;
}
static MunitResult editar_inexistente(const MunitParameter params[], void* fixture) {
    //Cria arquivo com dados de teste 
    FILE *ptr = fopen("../../arquivos/compradores.txt", "w");
    munit_assert_not_null(ptr);
    
    for (int i=0; i<2; i++){
        fprintf(ptr, "%s", NOME);
        for(int j=0; j<7; j++){
        fprintf(ptr, "%s", GENERICO);
        }
    }
    fclose(ptr);

    freopen("output.txt", "w", stdout);
    editarCompradores("Marco Julio");  // Nome que não existe
    freopen("CON", "w", stdout);  // Restaura stdout (Windows)
    ptr = fopen("output.txt", "r");
    munit_assert_not_null(ptr);
    
    char mensagem[100];
    fgets(mensagem, sizeof(mensagem), ptr);
    fclose(ptr);
    
    // Normaliza quebras de linha (Windows/Linux)
    mensagem[strcspn(mensagem, "\n")] = '\0';
    munit_assert_string_equal(mensagem, "Comprador nao encontrado!");
    remove("output.txt");

    //Verifica se o arquivo original permanece intacto
    ptr = fopen("../../arquivos/compradores.txt", "r");
    munit_assert_not_null(ptr);
    
    int linhas = 0;
    char linha[MAX_NOME];
    while(fgets(linha, sizeof(linha), ptr) != NULL) linhas++;
    fclose(ptr);
    
    munit_assert_int(linhas, ==, 16);  // 2 registros completos (8 linhas cada)

    return MUNIT_OK;
}








//array de casos de teste editar
static MunitTest editar_testes[] = {
    {
        "/editar_arquivo_vazio",   // Nome do teste
        editar_arquivo_vazio,      // Função de teste
        NULL,                       // Setup (opcional)
        NULL,                       // Teardown (opcional)
        MUNIT_TEST_OPTION_NONE     // Opções
    },
    {
        "/editar_inexistente",
        editar_inexistente,
        NULL, 
        NULL, 
        MUNIT_TEST_OPTION_NONE
    },
    {
        "/editar_sucesso",  
        editar_sucesso,   
        NULL,                   
        NULL,                     
        MUNIT_TEST_OPTION_NONE    
    },
    { NULL, NULL, NULL, 0, 0}
};

//array de casos de teste deletar
static MunitTest deletar_testes[] = {
    {
        "/deletar_arquivo_vazio",   // Nome do teste
        deletar_arquivo_vazio,      // Função de teste
        NULL,                       // Setup (opcional)
        NULL,                       // Teardown (opcional)
        MUNIT_TEST_OPTION_NONE     // Opções                   
    },
    {
        "/deletar_sucesso",
        deletar_sucesso,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE
    },
    {
        "/deletar_inexistente",
        deletar_inexistente,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE
    },

    { NULL, NULL, NULL, 0, 0, NULL }
};

// Suíte subsidiaria
static MunitSuite suite[] = {
    {
        "/compradores_testes_deletar",  
        deletar_testes,                        
        NULL,                          
        1,                             
        MUNIT_SUITE_OPTION_NONE
    },
    {
        "/compradores_testes_editar",  
        editar_testes,                        
        NULL,                          
        1,                             
        MUNIT_SUITE_OPTION_NONE
    },
    {NULL, NULL, NULL, 0, 0}
};

//suite principal
static const MunitSuite main_suite = {
    "/meu_programa",
    NULL,
    suite,
    1,
    MUNIT_SUITE_OPTION_NONE
};


// Ponto de entrada
int main(int argc, char* argv[]) {
    
    return munit_suite_main(&main_suite, NULL, argc, argv);
}