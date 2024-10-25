#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <stdlib.h>

FILE* out;

// semáforos
sem_t semA;
sem_t semB;


void *thread_a(void *args) {
    for (int i = 0; i < *(int*)args; ++i) {
        sem_wait(&semA); // Espera pelo semáforo A

        fprintf(out, "A");
        fflush(stdout);

        sem_post(&semB); // Libera o semáforo B
    }
    return NULL;
}

void *thread_b(void *args) {
    for (int i = 0; i < *(int*)args; ++i) {
        sem_wait(&semB); // Espera pelo semáforo B

        
        fprintf(out, "B");
        fflush(stdout);
        
        sem_post(&semA); // Libera o semáforo A
    }
    return NULL;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Uso: %s [ITERAÇÕES]\n", argv[0]);
        return 1;
    }
    int iters = atoi(argv[1]);
    srand(time(NULL));
    out = fopen("result.txt", "w");

    pthread_t ta, tb;

    // Inicializa semáforos
    sem_init(&semA, 0, 1); // semA começa disponível
    sem_init(&semB, 0, 1); // semB começa indisponível

    // Cria threads
    pthread_create(&ta, NULL, thread_a, &iters);
    pthread_create(&tb, NULL, thread_b, &iters);

    // Espera pelas threads
    pthread_join(ta, NULL);
    pthread_join(tb, NULL);

    // Imprime quebra de linha e fecha arquivo
    fprintf(out, "\n");
    fclose(out);

    // Destrói semáforos
    sem_destroy(&semA);
    sem_destroy(&semB);

    return 0;
}
