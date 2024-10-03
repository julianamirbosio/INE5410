#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>
#include "helper.h"

// Lê o conteúdo do arquivo filename e retorna um vetor E o tamanho dele
// Se filename for da forma "gen:%d", gera um vetor aleatório com %d elementos
//
// +-------> retorno da função, ponteiro para vetor malloc()ado e preenchido
// | 
// |         tamanho do vetor (usado <-----+
// |         como 2o retorno)              |
// v                                       v
double* load_vector(const char* filename, int* out_size);


// Avalia o resultado no vetor c. Assume-se que todos os ponteiros (a, b, e c)
// tenham tamanho size.
void avaliar(double* a, double* b, double* c, int size);


struct data {
double* a;
double* b;
double* c;

int inicio;
int fim;
};

void* soma_vetores(void* s) {

    struct data* vec = (struct data*) s;

    double* a = vec->a;
    double*b = vec->b;
    double* c = vec->c;

    int inicio = vec->inicio;
    int fim = vec->fim;

    for (int i = inicio; i < fim; ++i) {
        c[i] = a[i] + b[i];
        // printf("a = %f, b = %f, c = %f\n", a[i], b[i], c[i]);
    } 

    return 0;

}

int main(int argc, char* argv[]) {
    // Gera um resultado diferente a cada execução do programa
    // Se **para fins de teste** quiser gerar sempre o mesmo valor
    // descomente o srand(0)
    srand(time(NULL)); //valores diferentes
    //srand(0);        //sempre mesmo valor

    //Temos argumentos suficientes?
    if(argc < 4) {
        printf("Uso: %s n_threads a_file b_file\n"
               "    n_threads    número de threads a serem usadas na computação\n"
               "    *_file       caminho de arquivo ou uma expressão com a forma gen:N,\n"
               "                 representando um vetor aleatório de tamanho N\n",
               argv[0]);
        return 1;
    }
  
    //Quantas threads?
    int n_threads = atoi(argv[1]);
    if (!n_threads) {
        printf("Número de threads deve ser > 0\n");
        return 1;
    }
    //Lê números de arquivos para vetores alocados com malloc
    int a_size = 0, b_size = 0;
    double* a = load_vector(argv[2], &a_size);
    if (!a) {
        //load_vector não conseguiu abrir o arquivo
        printf("Erro ao ler arquivo %s\n", argv[2]);
        return 1;
    }
    double* b = load_vector(argv[3], &b_size);
    if (!b) {
        printf("Erro ao ler arquivo %s\n", argv[3]);
        return 1;
    }
    
    //Garante que entradas são compatíveis
    if (a_size != b_size) {
        printf("Vetores a e b tem tamanhos diferentes! (%d != %d)\n", a_size, b_size);
        return 1;
    }
    //Cria vetor do resultado 
    double* c = malloc(a_size*sizeof(double));

    // Calcula com uma thread só. Programador original só deixou a leitura 
    // do argumento e fugiu pro caribe. É essa computação que você precisa 
    // paralelizar

    // for (int i = 0; i < a_size; ++i) 
    //     c[i] = a[i] + b[i];

    //////////////

    // Excecoes

    if (n_threads > a_size) {
        n_threads = a_size;
    }

    pthread_t threads[n_threads];
    struct data s;

    int quantidade = a_size / n_threads;
    int resto = a_size % n_threads;

    for (int i = 0; i < n_threads; i++) {

        s[i].a = a;
        s[i].b = b;
        s[i].c = c;
        s[i].inicio = i*quantidade;
        s[i].fim = (i+1)*quantidade;

        if (i == n_threads - 1) {
            s[i].fim += resto;
        }

        pthread_create(&threads[i], NULL, soma_vetores, (void *)&s[i]);
    }

    for (int i = 0; i < n_threads; ++i)
        pthread_join(threads[i], NULL);

    //////////

    //    +---------------------------------+
    // ** | IMPORTANTE: avalia o resultado! | **
    //    +---------------------------------+
    avaliar(a, b, c, a_size);
    

    //Importante: libera memória
    free(a);
    free(b);
    free(c);

    return 0;
}