#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void validarPalavra(char *palavra)
{
    int i = 0;
    while (palavra[i] != '\0')
    {
        if (palavra[i] >= 65 && palavra[i] <= 90)
        {
            palavra[i] = palavra[i] + 32;
        }
        i++;
    }
}

void imprimir(char A[][21], int n, int x)
{
    for (int i = 0; i < n; i++)
    {
        if (x)
            printf("%s\n", A[i]);
        else
            printf("%s.\n", A[i]);
    }
}

int tamMax(char A[][21], int n)
{
    int max = strlen(A[0]);

    for (int i = 0; i < n; i++)
    {
        if (strlen(A[i]) > max)
        {
            max = strlen(A[i]);
        }
    }

    return max;
}

void completar(char A[][21], int n, int maxLem)
{
    for (int i = 0; i < n; i++)
    {
        if (strlen(A[i]) < maxLem)
        {
            for (int j = strlen(A[i]); j < maxLem; j++)
            {
                A[i][j] = ' ';
            }
        }
        A[i][maxLem] = '\0';
    }
}

int indice(char c, char chave[])
{
    for (int i = 0; i < 26; i++)
    {
        if (c == chave[i])
        {
            return i+1;
        }
    }
    return 0;
}

void radixSort(char A[][21], char B[][21], int n, int k, int maiorPalavra, char chave[])
{
    int v;

    for (v = maiorPalavra - 1; v >= 0; v--)
    {
        int i, j;

        int C[k+1];

        for (i = 0; i <= k; i++)
        {
            C[i] = 0;
        }

        for (j = 0; j < n; j++)
        {
            C[indice(A[j][v], chave)] = C[indice(A[j][v], chave)] + 1; // núm.elem.de tamanho i
        }

        for (int a = 1; a <= k; a++)
        {
            C[a] = C[a] + C[a - 1]; // soma prefixa
        }

        // Imprimir C
        for (int a = 0; a < k; a++)
        {
            printf("%i ", C[a]);
        }
        printf("\n");

        for (j = n-1; j >= 0; j--)
        {
            strcpy(B[C[indice(A[j][v], chave)] - 1], A[j]);
            C[indice(A[j][v], chave)] = C[indice(A[j][v], chave)] - 1;
        }

        for (j = 0; j < n; j++)
            strcpy(A[j], B[j]);
    }
}

int main()
{
    int n;
    scanf("%i", &n);

    int k = 27;
    char chave[k];
    scanf("%s", chave);
    // for (int i = 0; i < k; i++)
    // {
    //     printf("%c", chave[i]);
    // }

    char A[n][21];
    char B[n][21];

    for (int i = 0; i < n; i++)
    {
        scanf("%s", A[i]);
        validarPalavra(A[i]);
    }

    imprimir(A, n, 0);

    int d = tamMax(A, n);
    printf("%i\n", d);

    completar(A, n, d);

    radixSort(A, B, n, k, d, chave);

    imprimir(A, n, 1);

    return 0;
}