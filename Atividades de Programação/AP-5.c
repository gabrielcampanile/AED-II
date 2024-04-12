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
    int e = 2 * i;
    int d = 2 * i + 1;
    int maior = i;

    if (e <= n && strcmp(A[e], A[i]) > 0)
    {
        maior = e;
    }
    if (d <= n && strcmp(A[d], A[maior]) > 0)
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
    for (int i = n / 2; i > 0; i--)
        MaxHeapify(A, n, i);
}

char **HeapSort(char **A, int n)
{
    buildHeap(A, n);

    char **V = (char **)malloc((n + 1) * sizeof(char *));

    while (n > 0)
    {
        V[n] = A[1];
        A[1] = A[n];
        n--;
        MaxHeapify(A, n, 1);
    }

    return V;
}

int main()
{
    int N, M;
    // printf("Digite a quantidade total de palavras: ");
    scanf("%d", &N);

    char **V = (char **)malloc((N + 1) * sizeof(char *));
    // printf("Digite as palavras separadas por espaço: ");
    for (int i = 1; i <= N; i++)
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

    char **A = (char **)malloc((M + 1) * sizeof(char *));
    printf("build_heap: ");
    for (int i = 0; i < M; i++)
    {
        A[i + 1] = V[indices[i] + 1]; // +1 pois o vetor de palavras começa em 1
        printf("%s ", A[i + 1]);
    }
    printf("\n");

    A = HeapSort(A, M);

    printf("palavras: ");
    for (int i = 1; i <= M; i++)
    {
        printf("%s ", A[i]);
    }
    printf("\n");

    // Liberar memória alocada
    for (int i = 1; i <= N; i++)
    {
        free(V[i]);
    }
    free(V);
    free(A);
    free(indices);

    return 0;
}
