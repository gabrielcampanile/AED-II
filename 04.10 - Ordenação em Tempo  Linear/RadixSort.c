#include <stdio.h>
#include <stdlib.h>

void radixSort(int *V, int d, int *A, int *B, int k, int n)
{
    int v;

    for (v = 0; v < d; v++)
    {
        int i, j;

        int *C = (int *)malloc((k + 1) * sizeof(int));

        for (i = 0; i <= k; i++)
        {
            C[i] = 0;
        }

        for (j = 1; j <= n; j++)
        {
            C[A[j]] = C[A[j]] + 1; // núm.elem.de tamanho i
        }

        printf("C array: ");
        for (int i = 0; i <= k; i++)
        {
            printf("%i ", C[i]);
        }
        printf("\n");

        for (int a = 1; a <= k; a++)
        {
            C[a] = C[a] + C[a - 1]; // soma prefixa
        }

        printf("C array: ");
        for (int i = 0; i <= k; i++)
        {
            printf("%i ", C[i]);
        }
        printf("\n");

        for (j = n; j >= 1; j--)
        {
            B[C[A[j]]] = A[j];
            C[A[j]] = C[A[j]] - 1;
        }
    }
}

int main()
{
    int n, k;
    printf("Size: ");
    scanf("%d", &n);

    int *A = (int *)malloc((n + 1) * sizeof(int));
    int *B = (int *)malloc((n + 1) * sizeof(int));

    printf("A: ");
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &A[i]);
        if (i == 1 || A[i] > k)
        {
            k = A[i];
        }
    }

    printf("k = %i\n", k);

    countingSort(A, B, k, n);

    printf("B: ");
    for (int i = 1; i <= n; i++)
    {
        printf("%i ", B[i]);
    }
    printf("\n");

    free(A);
    free(B);

    return 0;
}