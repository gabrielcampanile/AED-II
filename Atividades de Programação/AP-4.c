#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int particion(int V[], int p, int r)
{
    int x = V[r]; // obtem o pivo x
    int i = p - 1;
 
    for (int j = p; j < r; j++)
    {
        if (V[j] < x)
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
 
void quick_sort(int V[], int p, int r, int *min_height, int *max_height, int atual, int mode)
{
    if (mode == 1)
    {
        int mid = (p + r) / 2;
        // printf("meio %i\n", V[mid]);
        int aux;
 
        if (V[p] < V[r] && V[p] < V[mid])
        {
            if (V[mid] < V[r])
            {
                aux = V[mid];
                V[mid] = V[r];
                V[r] = aux;
            }
        }
        else if (V[mid] < V[p] && V[mid] < V[r])
        {
            if (V[p] < V[r])
            {
                aux = V[p];
                V[p] = V[r];
                V[r] = aux;
            }
        }
        else if (V[r] < V[p] && V[r] < V[mid])
        {
            if (V[p] < V[mid])
            {
                aux = V[p];
                V[p] = V[r];
                V[r] = aux;
            }
            else
            {
                aux = V[mid];
                V[mid] = V[r];
                V[r] = aux;
            }
        }
    }
 
    if (p >= r)
    {
        if (atual > *max_height)
            *max_height = atual;
        if (atual < *min_height)
            *min_height = atual;
 
        return;
    }
 
    int q = particion(V, p, r);
    quick_sort(V, p, q - 1, min_height, max_height, atual + 1, mode);
    quick_sort(V, q + 1, r, min_height, max_height, atual + 1, mode);
}
 
int main()
{
    int n;
    scanf("%i", &n);
 
    // Vetores Dinâmicos
    int *V, *aux;
    V = (int *)malloc(sizeof(int) * n);
    aux = (int *)malloc(sizeof(int) * n);
 
    for (int i = 0; i < n; i++)
    {
        scanf("%i", &V[i]);
        aux[i] = V[i];
    }
 
    int min_height = n;
    int max_height = 0;
 
    quick_sort(V, 0, n - 1, &min_height, &max_height, 0, 0);
    // printf("%i\n", max_height);
    // printf("%i\n", min_height);
    printf("%i\n", max_height - min_height);
 
    // for (int i = 0; i < n; i++)
    // {
    //     printf("%i ", V[i]);
    // }
 
    min_height = n;
    max_height = 0;
 
    quick_sort(aux, 0, n - 1, &min_height, &max_height, 0, 1);
    // printf("%i\n", max_height);
    // printf("%i\n", min_height);
    printf("%i\n", max_height - min_height);
 
    // for (int i = 0; i < n; i++)
    // {
    //     printf("%i ", aux[i]);
    // }
 
    free(V);
    free(aux);
 
    return 0;
}