#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "compradores.h"
#include "vendas.h"
#include "vendedores.h"


int main(){    
    char nome[100];
    scanf("%s", nome);
    deletarCompradores(nome);
    return 0;
}