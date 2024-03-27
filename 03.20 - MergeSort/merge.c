#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void Merge(int *A, int p, int q, int r){
    int n1 = q - p + 1;
    int n2 = r - q;

    int *L = malloc((n1+1)*sizeof(int));
    int *R = malloc((n2+1)*sizeof(int));

    for (int i = 0; i < n1 + 1; i++)
        L[i] = A[p + i - 1];
    for (int j = 0; j < n2 + 1; j++)
        R[j] = A[q + j];

    L[n1 + 1] = INT_MAX;
    R[n2 + 1] = INT_MAX;

    int i = 0;
    int j = 0;

    for (int k = p; k < r + 1; k++){
        if (L[i] <= R[i]){
            A[k] = L[i];
            i += 1;
        }
        else{
            A[k] = R[i];
            j += 1;
        }
    }
}

void Merge_Sort(int *A, int p, int r){
    int q;
    
    if (p < r){
        q = (p + r)/2;
        Merge_Sort(A, p, q);
        Merge_Sort(A, q+1, r);
        Merge(A, p, q, r);
    }
}