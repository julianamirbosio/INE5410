#include <stdio.h>
#include <math.h> 

/*
Implemente uma funcao que calcule a area da superfıcie e o volume de uma esfera de raio R.
*/

void calc_esfera(float R, float *area, float *volume) {
    *area = 4 * M_PI * pow(R, 2);
    *volume = (4/3) * M_PI * pow(R, 3);
}

void main () {
    float R, area, volume;
    printf("Digite o raio da esfera: ");
    scanf("%f", &R);

    calc_esfera(R, &area, &volume);
    printf("Área: %.2f\n", area);
    printf("Volume: %.2f\n", volume);

}