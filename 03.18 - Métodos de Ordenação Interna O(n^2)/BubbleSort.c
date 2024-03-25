#include <stdio.h>
#include <stdlib.h>

#define max 10

void bubble_sort(int V[], int n) {
    for(int i=0; i<n-1; i++) {
        for(int j=0; j<n-1-i; j++) {
            if(V[j] > V[j+1]) {
                int aux = V[j+1];
                V[j+1] = V[j];
                V[j] = aux;
            }
        }
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

    bubble_sort(V, max);

    for(int i=0; i<max; i++) {
        printf("%i ", V[i]);
    }

    return 0;
}