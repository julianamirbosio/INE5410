#include <stdio.h>

/*
Escreva um programa que contenha duas variáveis inteiras. Compare seus enderecos e
exiba o maior endereco.
*/

void MaiorEndereco(int A, int B) {

    int *ptr_A = &A;
    int *ptr_B = &B;

    unsigned long val_A = (unsigned long) ptr_A;
    unsigned long val_B = (unsigned long) ptr_B;

    if (val_A > val_B) {
        printf("O valor númerico do endereço de A é maior que o de B: %lu > %lu\n", val_A, val_B);
    } else {
        printf("O valor númerico do endereço de B é maior que o de A: %lu > %lu\n",  val_B, val_A);
    }

}

void main() {
    MaiorEndereco(210, 5000);
}