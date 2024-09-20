#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


//                          (principal)
//                               |
//              +----------------+--------------+
//              |                               |
//           filho_1                         filho_2
//              |                               |
//    +---------+-----------+          +--------+--------+
//    |         |           |          |        |        |
// neto_1_1  neto_1_2  neto_1_3     neto_2_1 neto_2_2 neto_2_3

// ~~~ printfs  ~~~
//      principal (ao finalizar): "Processo principal %d finalizado\n"
// filhos e netos (ao finalizar): "Processo %d finalizado\n"
//    filhos e netos (ao inciar): "Processo %d, filho de %d\n"

// Obs:
// - netos devem esperar 5 segundos antes de imprmir a mensagem de finalizado (e terminar)
// - pais devem esperar pelos seu descendentes diretos antes de terminar

int ProcessoNetos(int n) { // n = 3
    pid_t pid;
    // criar netos
    for (int j = 0; j < n; j++) {
        fflush(stdout); // antes do fork
        pid = fork();
        if (pid == 0) {
            printf("Processo %d filho de %d\n", getpid(), getppid());
            return 0;
        }
    }
    
    exit(0);
}

int ProcessoFilhos(int n, int k) { // n = 2, k = 3
    pid_t pid;
    // criar netos
    for (int j = 0; j < n; j++) {
        fflush(stdout); // antes do fork
        pid = fork();
        if (pid == 0) {
            printf("Processo %d filho de %d\n", getpid(), getppid());
            ProcessoNetos(k);
            return 0;
        }
    }
    
    while(wait(NULL) >= 0);    
    printf("Processo %d finalizado\n", getpid());
    exit(0);
}

int main(int argc, char** argv) {

    /*************************************************
     * Dicas:                                        *
     * 1. Leia as intruções antes do main().         *
     * 2. Faça os prints exatamente como solicitado. *
     * 3. Espere o término dos filhos                *
     *************************************************/

    ProcessoFilhos(2, 3); // filhos, netos
    while(wait(NULL) >= 0);    
    printf("Processo principal %d finalizado\n", getpid());    
    return 0;
}
