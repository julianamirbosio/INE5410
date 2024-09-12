#include <stdio.h>

/*
Faça um programa que leia 2 valores inteiros e chame uma função que receba 
essas 2 variáveis e troque o seu conteúdo. Ou seja, essa função é 
chamada passando duas variáveis, por exemplo, A e B, e, após a execução da função,
A conterá o valor de B e B terá o valor de A.

*/

void TrocaValores(int *A, int *B) {

    int temp = *A;
    *A = *B;
    *B = temp;

}

void main() {

    int A, B;
    printf("Escreva dois inteiros separados por espaço: \n");
    scanf("%d %d", &A, &B);

    TrocaValores(&A, &B);

    printf("Valor de A: %d\n", A);
    printf("Valor de B: %d\n", B);
    
}