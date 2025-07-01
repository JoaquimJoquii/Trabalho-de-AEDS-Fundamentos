#include "frete.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
float valor=4;
float calcularFrete(float valor){
    float frete;
    if(valor<0){
        printf("erro, valor invalido!");
        return 0;
    }
    if(valor<=100){
        frete=30;
    }
    else if((valor>100)&&(valor<=300)){
        frete=20;
    }
    else {
        frete=0;
    }
    return frete;
}