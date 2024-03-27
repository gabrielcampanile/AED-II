#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max 10

int particion(int V[], int p, int r)
{
    int x = V[r]; // obtem o pivo x
    int i = p - 1;

    for (int j = p; j < r; j++)
    {
        if (V[j] <= x)
        {
            i++;
            int aux = V[i];
            V[i] = V[j];
            V[j] = aux;
        }
    }

    int aux = V[i + 1];
    V[i + 1] = V[r];
    V[r] = aux;

    return i + 1;
}

void quick_sort(int V[], int p, int r)
{
    if (p < r)
    {
        int q = particion(V, p, r);
        printf("%i\n", q);
        quick_sort(V, p, q-1);
        quick_sort(V, q+1, r);
    }
}

int main()
{
    int V[max];

    for (int i = 0; i < max; i++)
    {
        scanf("%i", &V[i]);
    }

    for (int i = 0; i < max; i++)
    {
        printf("%i ", V[i]);
    }

    quick_sort(V, 0, max-1);
    printf("\n");

    for (int i = 0; i < max; i++)
    {
        printf("%i ", V[i]);
    }

    return 0;
}