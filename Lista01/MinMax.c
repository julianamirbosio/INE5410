#include <stdio.h>
#include <stdlib.h>

typedef struct MinMax {
    int min;
    int max;
} MinMax;

MinMax *getMinMax(int * array, const int SIZE) {

    MinMax *s = (MinMax *) malloc(sizeof(MinMax));
    
    int max = array[0];
    int min = max;

    for (int i = 0; i < SIZE; i++) {
        int val = array[i];
        if (val > max)
            max = val;
        if (val < min)
            min = val;
    }

    s->max = max;
    s->min = min;

    return s;

}

int main() {

    const int SIZE = 4;
    int array[] = {2, 20, 54, -78};

    MinMax* s = getMinMax(array, SIZE);
    printf("Max. value: %d\nMin. value: %d\n", s->max, s->min);

    // desalocação da memória
    free(s);

    return 0;
}