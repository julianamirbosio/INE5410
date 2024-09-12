#include <stdio.h>

/*
Escreva um programa que declare um inteiro, um real e um char, 
e ponteiros para inteiro, real e char. Associe as variáveis aos ponteiros (use &). 
Modifique os valores de cada variável usando os ponteiros. 
Imprima os valores das variáveis antes e após a modificação.
*/

void main() {

    // variaveis
    int i;
    float r;
    char c;

    // valores arbitrários
    i = 10;
    r = 5.28;
    c = 'A';

    printf("Inteiro: %d\n", i);
    printf("Real: %f\n", r);
    printf("Char: %c\n", c);
    printf("\n");

    // ponteiros
    int *ptr_i;
    float *ptr_r;
    char *ptr_c;

    // associações
    ptr_i = &i;
    ptr_r = &r;
    ptr_c = &c;

    // alterações nos valores de i, r & c via ponteiros
    *ptr_i = 15;
    *ptr_r = 78.9; 
    *ptr_c = 'Z';

    printf("Inteiro: %d\n", i);
    printf("Real: %f\n", r);
    printf("Char: %c\n", c);
    
}