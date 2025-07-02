#include <stdio.h>
#include <stdlib.h>
#include "../codigo/compradores.h"
#define MUNIT_ENABLE_ASSERT_ALIASES
#define GENERICO "123456789\n"
#define NOME "teste\n"
#include "./munit/munit.h"


//casos de teste deletar
/*static MunitResult exemplo(const MunitParameter params[], void* fixture) {
    //preparação
    //execução
    //verificação
    return MUNIT_OK;
}*/
static MunitResult deletar_arquivo_vazio(const MunitParameter params[], void* fixture) {
    //cria um arquivo em branco
    FILE *ptr = fopen("../../arquivos/compradores.txt", "w");
    fclose(ptr);

    //chama a função dando como parametro uma constante
    assert_int(deletarCompradores(NOME), ==, 1);

    return MUNIT_OK;
}
static MunitResult deletar_sucesso(const MunitParameter params[], void* fixture){
    //abrindo um arquivo em branco e preenchendo ele com um comprador generico
    FILE *ptr = fopen("../../arquivos/compradores.txt", "w");
    assert_not_null(ptr);

    fprintf(ptr, "%s", NOME);
    for(int i=0; i<7; i++){
        fprintf(ptr, "%s", GENERICO);
    }
    fclose(ptr);
    
    //chamando a função
    assert_int(deletarCompradores(NOME), ==, 0);

    return MUNIT_OK;
}
static MunitResult deletar_inexistente(const MunitParameter params[], void* fixture) {
    //abrindo um arquivo em branco e preenchendo com um comprador generico
    FILE *ptr = fopen("../../arquivos/compradores.txt", "w");
    assert_not_null(ptr);
    
    fprintf(ptr, "Joao Carlos\n");  // Nome diferente do que será buscado
    for(int i = 0; i < 7; i++) {
        fprintf(ptr, "%s", GENERICO); 
    }
    fclose(ptr);

    assert_int(deletarCompradores(NOME), ==, 1);
    return MUNIT_OK;
}

//casos de teste de edição
static MunitResult editar_arquivo_vazio(const MunitParameter params[], void* fixture) {
    //cria um arquivo em branco
    FILE *ptr = fopen("../../arquivos/compradores.txt", "w");
    fclose(ptr);

    assert_int( deletarCompradores(NOME), ==, 1);//compara o retorno da função com o resultado esperado
    return MUNIT_OK;
}
static MunitResult editar_sucesso(const MunitParameter params[], void* fixture){

    //abrindo um arquivo em branco e preenchendo ele com um comprador generico
    FILE *ptr = fopen("../../arquivos/compradores.txt", "w");
    assert_not_null(ptr);

    fprintf(ptr, "%s", NOME);
    for(int i=0; i<7; i++){
        fprintf(ptr, "%s", GENERICO);
    }
    fclose(ptr);

    int m = editarCompradores(NOME);

    assert_int(m, ==, 0);
    return MUNIT_OK;
}//------------------------->retirar a entrada de dados
static MunitResult editar_inexistente(const MunitParameter params[], void* fixture) {
    //Cria arquivo com dados de teste 
    FILE *ptr = fopen("../../arquivos/compradores.txt", "w");
    assert_not_null(ptr);
    
    for (int i=0; i<2; i++){
        fprintf(ptr, "%s", NOME);
        for(int j=0; j<7; j++){
        fprintf(ptr, "%s", GENERICO);
        }
    }
    fclose(ptr);

    assert_int(editarCompradores("marcos"), ==, 1);
    return MUNIT_OK;
}

//casos de teste de apresentação
static MunitResult apresentacao_arquivo_vazio(const MunitParameter params[], void* fixture) {
    //criando arquivos vazios
    FILE *ptr = fopen("../../arquivos/compradores.txt", "w");
    fclose(ptr);
    
    assert_int(apresentarCompradores(), ==, 1);
    return MUNIT_OK;
}
static MunitResult apresentacao_arquivo_populado(const MunitParameter params[], void* fixture) {
    //criando arquivos vazios
    FILE *ptr = fopen("../../arquivos/compradores.txt", "w");
    assert_not_null(ptr);
    //inserindo pessoas nos arquivos
    fprintf(ptr, "%s", NOME);
    for(int i=0; i<7; i++){
        fprintf(ptr, "%s", GENERICO);
    }
    fclose(ptr);

    assert_int(apresentarCompradores(), ==, 0);
    

    
    

    return MUNIT_OK;
}

//casos e teste de cadastro
static MunitResult cadastro_entrada_invalida(const MunitParameter params[], void* fixture) {

    assert_int(cadastrarCompradores(0), ==, 1);
    return MUNIT_OK;
}
static MunitResult cadastro_sucesso(const MunitParameter params[], void* fixture) {

    assert_int(cadastrarCompradores(1), ==, 0);
    return MUNIT_OK;
}//retirar a entrada de dados------------------------->

//array de cadastrar
static MunitTest cadastrar_testes[] = {
    {
        "/cadastro_entrada_invalida",   // Nome do teste
        cadastro_entrada_invalida,      // Função de teste
        NULL,                       // Setup (opcional)
        NULL,                       // Teardown (opcional)
        MUNIT_TEST_OPTION_NONE     // Opções
    },
    {
        "/cadastro_sucesso",
        cadastro_sucesso,
        NULL, 
        NULL, 
        MUNIT_TEST_OPTION_NONE
    },
    { NULL, NULL, NULL, 0, 0}
};
//array de apresentadores
static MunitTest apresentar_testes[] = {
    {
        "/apresentacao_arquivo_vazio",   // Nome do teste
        apresentacao_arquivo_vazio,      // Função de teste
        NULL,                       // Setup (opcional)
        NULL,                       // Teardown (opcional)
        MUNIT_TEST_OPTION_NONE     // Opções
    },
    {
        "/apresentacao_arquivo_populado",
        apresentacao_arquivo_populado,
        NULL, 
        NULL, 
        MUNIT_TEST_OPTION_NONE
    },
    { NULL, NULL, NULL, 0, 0}
};
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
        "/compradores_testes_cadastrar",  
        cadastrar_testes,                        
        NULL,                          
        1,                             
        MUNIT_SUITE_OPTION_NONE
    },
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
    {
        "/compradores_testes_apresentar",  
        apresentar_testes,                        
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