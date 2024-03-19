#include <stdio.h>
#include <stdlib.h>

void bubbleSort(int *p, int n) {
    int i, j;
    for(i=0; i<n-1; i++) {
        for(j=0; j<n-1-i; j++) {
            if(p[j] > p[j+1]) {
                int aux;
                aux = p[j];
                p[j] = p[j+1];
                p[j+1] = aux;
            } 
        }
    }
}

int teste(int *p, int *d, int n) {
    int i;
    for(i=0; i<n; i++)
        if(p[i]>=d[i])
            return 0;

    return 1;
}

int main(){
    int N, i;
    scanf("%i", &N);

    int *pacientes, *doses;

    pacientes = (int*)malloc(N*sizeof(int));
    doses = (int*)malloc(N*sizeof(int));

    for(i=0; i<N; i++) {
        scanf("%i", &pacientes[i]);
    }

    for(i=0; i<N; i++) {
        scanf("%i", &doses[i]);
    }

    bubbleSort(pacientes, N);
    bubbleSort(doses, N);

    // for(i=0; i<N; i++) 
    //     printf("%i ", pacientes[i]);
    // printf("\n");
    // for(i=0; i<N; i++) 
    //         printf("%i ", doses[i]);      

    if(teste(pacientes, doses, N))
        printf("sim");
    else
        printf("nao");

    free(pacientes);
    free(doses);

    return 0;                                              
}