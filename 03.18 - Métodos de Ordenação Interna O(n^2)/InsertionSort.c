#include <stdio.h>
#include <stdlib.h>

#define max 10

void insertion_sort(int V[], int n) {
    for(int i=1; i<n; i++) {
        int aux = V[i];
        int j = i;
        while((j > 0) && (aux < V[j-1])) {
            V[j] = V[j-1];
            j--;
        }
        V[j] = aux;
    }
}

int main() {
    int V[max];

    for(int i=0; i<max; i++) {
        scanf("%i", &V[i]);
    }

    for(int i=0; i<max; i++) {
        printf("%i ", V[i]);
    }

    printf("\n");

    insertion_sort(V, max);

    for(int i=0; i<max; i++) {
        printf("%i ", V[i]);
    }

    return 0;
}