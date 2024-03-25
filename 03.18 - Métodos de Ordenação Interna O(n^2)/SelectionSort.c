#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define max 10

void selection_sort(int V[], int n) {
    for(int i=0; i<n-1; i++) {
        int posMenor = i;
        for(int j=i+1; j<n; j++) {
            if(V[j] < V[posMenor]) {
                posMenor = j;
            }
        }
        if(V[posMenor] < V[i]) {
            int aux = V[i];
            V[i] = V[posMenor];
            V[posMenor] = aux;
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

    selection_sort(V, max);

    for(int i=0; i<max; i++) {
        printf("%i ", V[i]);
    }

    return 0;
}