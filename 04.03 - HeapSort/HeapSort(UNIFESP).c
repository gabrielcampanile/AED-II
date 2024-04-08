#include <stdio.h>
#include <stdlib.h>

void swap(int *A, int i, int j)
{
    int temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}

void MaxHeapify(int *A, int n, int i)
{
    int e = 2 * i;
    int d = 2 * i + 1;
    int maior = i;

    if (e <= n && A[e] > A[i])
    {
        maior = e;
        // printf("esquerda\n");
    }
    else
        maior = i;
    if (d <= n && A[d] > A[maior])
    {
        maior = d;
        // printf("direita\n");
    }
    // printf("maior = %i\n", i);
    if (maior != i)
    {
        swap(A, i, maior);
        MaxHeapify(A, n, maior);
    }
}

void buildHeap(int *A, int n)
{
    for (int i = n / 2; i > 0; i--)
    {
        // printf("%i\n", i);
        MaxHeapify(A, n, i);
    }
}

int HeapExtraxtMax(int *A, int n)
{
    int max = A[1];
    A[1] = A[n];
    n--;

    MaxHeapify(A, n, 1);

    return max;
}

int *HeapSort(int *A, int n)
{
    int *V = (int *)malloc((n + 1) * sizeof(int)); // Allocate memory for V starting from index 1

    while (n > 0)
    {
        V[n] = HeapExtraxtMax(A, n);
        n--;
    }

    return V;
}

int main()
{
    int n;
    printf("Digite o tamanho do array: ");
    scanf("%d", &n);

    int *V = (int *)malloc((n + 1) * sizeof(int)); // Allocate memory for V starting from index 1

    for (int i = 1; i <= n; i++)
        scanf("%i", &V[i]);

    buildHeap(V, n);

    printf("V:\n");
    for (int i = 1; i <= n; i++)
    {
        printf("%d ", V[i]);
    }
    printf("\n");

    int *A = HeapSort(V, n);

    printf("A:\n");
    for (int i = 1; i <= n; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");

    free(V);
    free(A); // Free the allocated memory for A

    return 0;
}
