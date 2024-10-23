#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <stdlib.h>

FILE* out;

// semáforos
<<<<<<< HEAD
sem_t semA;
sem_t semB;


void *thread_a(void *args) {
    for (int i = 0; i < *(int*)args; ++i) {
        sem_wait(&semA); // Espera pelo semáforo A

        fprintf(out, "A");
        fflush(stdout);

        sem_post(&semB); // Libera o semáforo B
=======
sem_t sem_a, sem_b;

void *thread_a(void *args) {
    for (int i = 0; i < *(int*)args; ++i) {
        //      +---> arquivo (FILE*) destino
        //      |    +---> string a ser impressa
        //      v    v
        sem_wait(&sem_a); //libera a sessão critica para A escrever
        fprintf(out, "A");
        fflush(stdout);
        // Importante para que vocês vejam o progresso do programa
        // mesmo que o programa trave em um sem_wait().
        sem_post(&sem_b);
>>>>>>> 038f4f12a3a91480f48fb6e2d068e52e349e6e0d
    }
    return NULL;
}

void *thread_b(void *args) {
    for (int i = 0; i < *(int*)args; ++i) {
<<<<<<< HEAD
        sem_wait(&semB); // Espera pelo semáforo B

        
        fprintf(out, "B");
        fflush(stdout);
        
        sem_post(&semA); // Libera o semáforo A
=======
        sem_wait(&sem_b); //libera a sessão critica para B escrever
        fprintf(out, "B");
        fflush(stdout);
        sem_post(&sem_a);
>>>>>>> 038f4f12a3a91480f48fb6e2d068e52e349e6e0d
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

<<<<<<< HEAD
    // Inicializa semáforos
    sem_init(&semA, 0, 1); // semA começa disponível
    sem_init(&semB, 0, 1); // semB começa disponível
=======
    sem_init(&sem_a, 0, 1);
    sem_init(&sem_b, 0, 1);
>>>>>>> 038f4f12a3a91480f48fb6e2d068e52e349e6e0d

    // Cria threads
    pthread_create(&ta, NULL, thread_a, &iters);
    pthread_create(&tb, NULL, thread_b, &iters);

    // Espera pelas threads
    pthread_join(ta, NULL);
    pthread_join(tb, NULL);

<<<<<<< HEAD
    // Destrói semáforos
    sem_destroy(&semA);
    sem_destroy(&semB);

    // Imprime quebra de linha e fecha arquivo
    fprintf(out, "\n");
    fclose(out);

=======
    sem_destroy(&sem_a);
    sem_destroy(&sem_b);

    //Imprime quebra de linha e fecha arquivo
    fprintf(out, "\n");
    fclose(out);
  
>>>>>>> 038f4f12a3a91480f48fb6e2d068e52e349e6e0d
    return 0;
}
