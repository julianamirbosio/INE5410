#include <stdio.h>
#include <stdlib.h>

// Bubblesort - complexidade O(n²)
void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

//Lê valores do array via terminal
void inputArray(int * arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("Digite o valor de arr[%d]: ", i);
        scanf("%d", &arr[i]);
    }
}

//Imprime o conteúdo do vetor arr com tamanho size
void printArray(int * arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

//Função que compara dois inteiros. A função retorna a diferença entre o primeiro e o segundo
int sortAscending(int * num1, int * num2) {
    return *num1 - *num2;
}

//Função que compara dois inteiros. A função retorna a diferença entre o segundo e o primeiro
int sortDescending(int * num1, int * num2) {
    return *num2 - *num1;
}

//Função que realizada a ordenação. O terceiro argumento é um ponteiro para função que realiza a comparação entre dois inteiros do vetor (funções sortAscending ou sortDescending)
void sort(int * arr, int size, int (* compare)(int *, int *)) {
    int i, j, t;

    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {

            if (compare(&arr[j], &arr[j + 1]) > 0) {
                t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
        }
    }
}

int main() {
    int size;

    // Tamanho do array
    printf("Digite o tamanho do array: ");
    scanf("%d", &size);

    // Alocação dinâmica do array
    int *arr = (int *)malloc(size * sizeof(int));

    if (arr == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    inputArray(arr, size);

    printf("Escolha o tipo de ordenação (1 para crescente, 2 para decrescente): ");
    int c;
    scanf("%d", &c);

    if (c == 1) {
        sort(arr, size, sortAscending);
        printf("Array ordenado em ordem crescente: \n");
    } else if (c == 2) {
        sort(arr, size, sortDescending);
        printf("Array ordenado em ordem decrescente: \n");
    } else {
        printf("Escolha inválida!\n");
        free(arr);
        return 1;
    }

    // Imprimir o array ordenado
    printArray(arr, size);

    // Desalocar a memória
    free(arr);

    return 0;
}

