#include "frete.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
float valor=4;
float calcularFrete(float valor){
    float total;
    if(valor<0){
        printf("erro, valor invalido!");
        return 0;
    }
    if(valor<=100){
        total=valor+30;
    }
    else if((valor>100)&&(valor<=300)){
        total=valor+20;
    }
    else {
        total=valor;
    }
    printf("O valor do frete e: %.2f\n", total);
    return total;
}