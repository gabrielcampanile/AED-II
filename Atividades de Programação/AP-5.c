#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int validarPalavra(char *palavra) {
    int i = 0;
    while (palavra[i] != '\0') {
        if (palavra[i]<97 || palavra[i]>122) {
            printf("a palavra %s eh invalida\n", palavra);
            return 0;
        }
        i++;
    }
    return 1;
}

void swap(char **A, int i, int j)
{
    char *temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}

void MaxHeapify(char **A, int n, int i)
{
    int e = 2 * i + 1;
    int d = 2 * i + 2;
    int maior = i;

    if (e < n && strcmp(A[maior], A[e]) < 0)
    {
        maior = e;
    }
    if (d < n && strcmp(A[maior], A[d]) < 0)
    {
        maior = d;
    }
    if (maior != i)
    {
        swap(A, i, maior);
        MaxHeapify(A, n, maior);
    }
}

void buildHeap(char **A, int n)
{
    for (int i = n / 2 -1; i >= 0; i--)
        MaxHeapify(A, n, i);
}

char **HeapSort(char **A, int n)
{
    buildHeap(A, n);

    for (int i = 0; i < n; i++)
        printf("%s ", A[i]);

    char **V = (char **)malloc(n * sizeof(char *));

    while (n > 0)
    {
        V[n-1] = A[0];
        A[0] = A[n-1];
        n--;
        MaxHeapify(A, n, 0);
    }

    return V;
}

int main()
{
    int N, M;
    // printf("Digite a quantidade total de palavras: ");
    scanf("%d", &N);

    char **V = (char **)malloc(N * sizeof(char *));
    // printf("Digite as palavras separadas por espaço: ");
    for (int i = 0; i < N; i++)
    {
        V[i] = (char *)malloc(20 * sizeof(char));
        scanf("%s", V[i]);
        if (!validarPalavra(V[i])) {
            return 0;
        }
    }

    // printf("Digite a quantidade de palavras selecionadas: ");
    scanf("%d", &M);

    int *indices = (int *)malloc(M * sizeof(int));
    // printf("Digite as posições das palavras selecionadas separadas por espaço: ");
    for (int i = 0; i < M; i++)
    {
        scanf("%d", &indices[i]);
    }

    char **A = (char **)malloc(M * sizeof(char *));
    printf("build_heap: ");
    for (int i = 0; i < M; i++)
    {
        A[i] = V[indices[i]]; // +1 pois o vetor de palavras começa em 1
    }

    A = HeapSort(A, M);

    printf("\npalavras: ");
    for (int i = 0; i < M; i++)
    {
        printf("%s ", A[i]);
    }
    printf("\n");

    // Liberar memória alocada
    for (int i = 0; i < N; i++)
    {
        free(V[i]);
    }
    free(V);
    free(A);
    free(indices);

    return 0;
}
