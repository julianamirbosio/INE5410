#include <stdio.h>

/*
Elaborar um programa que leia dois valores inteiros (A e B). Em seguida, faça uma função
que retorne a soma do dobro dos dois números lidos. A função deverá armazenar o 
dobro de A na própria variável A e o dobro de B na própria variável B.
*/

int SomaDoDobro(int *A, int *B) {
    *A *= 2;
    *B *= 2;
    return *A + *B;
}

void main() {

    int A, B;
    printf("Escreva dois inteiros separados por espaço: \n");
    scanf("%d %d", &A, &B);

    int soma = SomaDoDobro(&A, &B);
    printf("Soma: %d\n", soma);

}