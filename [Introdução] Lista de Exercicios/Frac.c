#include <stdio.h>
#include <math.h>

/*

Escreva uma função que, dado um número real passado como parâmetro, retorne a parte inteira e a parte 
fracionária deste número.
*/

void frac(double num, int* inteiro, double* fracao) {

    *inteiro = (int) trunc(num);
    *fracao = num - *inteiro;

}

void main() {

    double num;
    int inteiro;
    double fracao;

    printf("Digite número real: \n");
    scanf("%lf", &num);

    frac(num, &inteiro, &fracao);

    printf("Valor: %f\n", num);
    printf("Parte inteira: %d\n", inteiro);
    printf("Parte fracionária: %f\n", fracao);

}