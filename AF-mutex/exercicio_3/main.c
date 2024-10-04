#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//int gValue = 0;
pthread_mutex_t gMtx;
pthread_mutex_t gMtx2;

// Função imprime resultados na correção do exercício -- definida em helper.c
void imprimir_resultados(int n, int** results);

// Função escrita por um engenheiro
// void compute(int arg) {
//     if (arg < 2) {
//         pthread_mutex_lock(&gMtx2);
//         gValue += arg;
//         pthread_mutex_unlock(&gMtx2);
//     } else {
//         compute(arg - 1);
//         compute(arg - 2);
//     }

//     // OUTRA FORMA
// }

int compute_2(int arg) {
    int gValue_local = 0;
    if (arg < 2) {
        gValue_local += arg;
    } else {
        gValue_local += compute_2(arg - 1);
        gValue_local += compute_2(arg - 2);
    }

    return gValue_local;
}

/*

ARG = 4

                   compute(3)                         compute (2)
            compute(2)     compute(1)              compute(1)    compute(0)
     compute(1)  compute(0)    gvalue = 1           gvalue = 2     gvalue += 0
     gvalue = 3   gvalue = 0

final = gvalue = 3



*/


// Função wrapper que pode ser usada com pthread_create() para criar uma 
// thread que retorna o resultado de compute(arg
void* compute_thread(void* arg) {


    int* ret = malloc(sizeof(int));
    int gValue = 0;
    gValue += compute_2(*((int*)arg));
    *ret = gValue;
    
    return ret;
}


int main(int argc, char** argv) {
    // Temos n_threads?
    if (argc < 2) {
        printf("Uso: %s n_threads x1 x2 ... xn\n", argv[0]);
        return 1;
    }
    // n_threads > 0 e foi dado um x para cada thread?
    int n_threads = atoi(argv[1]);
    if (!n_threads || argc < 2+n_threads) {
        printf("Uso: %s n_threads x1 x2 ... xn\n", argv[0]);
        return 1;
    }

    // MUTEX RECURSIVO
    // pthread_mutexattr_t attr;
    // pthread_mutexattr_init(&attr);
    // pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    // pthread_mutex_init(&gMtx, &attr);
    // pthread_mutexattr_destroy(&attr);

    //Inicializa o mutex
    pthread_mutex_init(&gMtx, NULL);

    int args[n_threads];
    int* results[n_threads];
    pthread_t threads[n_threads];
    //Cria threads repassando argv[] correspondente
    for (int i = 0; i < n_threads; ++i)  {
        args[i] = atoi(argv[2+i]);
        pthread_create(&threads[i], NULL, compute_thread, &args[i]);
    }
    // Faz join em todas as threads e salva resultados
    for (int i = 0; i < n_threads; ++i)
        pthread_join(threads[i], (void**)&results[i]);

    // Não usaremos mais o mutex
    pthread_mutex_destroy(&gMtx);
    pthread_mutex_destroy(&gMtx2);

    // Imprime resultados na tela
    // Importante: deve ser chamada para que a correção funcione
    imprimir_resultados(n_threads, results);

    // Faz o free para os resultados criados nas threads
    for (int i = 0; i < n_threads; ++i) 
        free(results[i]);
    
    return 0;
}