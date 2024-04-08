#include <stdio.h>
#include <stdlib.h>

void swap(int *A, int i, int j) {
    int temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}

void maxHeap(int *A, int n, int i) {
    int e = 2 * i;
    int d = 2 * i + 1;
    int maior = i;

    if (e < n && A[e] > A[i])
        maior = e;
    if (d < n && A[d] > A[maior])
        maior = d;
    if (maior != i) {
        swap(A, i, maior);
        maxHeap(A, n, maior);
    }
}

void buildHeap(int *A, int n) {
    for(int i = n / 2 - 1; i >= 0; i--) 
        maxHeap(A, n, i);
}

void heapsort(int *A, int n) {
    buildHeap(A, n);
    for (int i = n - 1; i > 0; i--) {
        swap(A, 0, i);
        maxHeap(A, i, 0);
    }
}

int main() {
    int n;
    printf("Digite o tamanho do array: ");
    scanf("%d", &n);

    int *V;
    V = (int *)malloc(n * sizeof(int));
 
    printf("Digite os elementos do array:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &V[i]);

    heapsort(V, n);

    printf("Array ordenado:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", V[i]);
    }
    printf("\n");

    free(V);

    return 0;
}
