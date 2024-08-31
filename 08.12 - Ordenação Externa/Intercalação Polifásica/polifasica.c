#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_FITAS 3
#define TAMANHO_MEMORIA 100

void merge(int f1, int f2, int f3) {
    int num1, num2;
    FILE *fitas[NUM_FITAS];
    fitas[0] = fopen("fita1.txt", "r");
    fitas[1] = fopen("fita2.txt", "r");
    fitas[2] = fopen("fita3.txt", "w");

    fscanf(fitas[f1], "%d", &num1);
    fscanf(fitas[f2], "%d", &num2);

    while (!feof(fitas[f1]) && !feof(fitas[f2])) {
        if (num1 <= num2) {
            fprintf(fitas[f3], "%d ", num1);
            fscanf(fitas[f1], "%d", &num1);
        } else {
            fprintf(fitas[f3], "%d ", num2);
            fscanf(fitas[f2], "%d", &num2);
        }
    }

    while (!feof(fitas[f1])) {
        fprintf(fitas[f3], "%d ", num1);
        fscanf(fitas[f1], "%d", &num1);
    }

    while (!feof(fitas[f2])) {
        fprintf(fitas[f3], "%d ", num2);
        fscanf(fitas[f2], "%d", &num2);
    }

    fclose(fitas[0]);
    fclose(fitas[1]);
    fclose(fitas[2]);
}

void polifasico(FILE *entrada) {
    FILE *fitas[NUM_FITAS];
    int num, i = 0;

    // Divisão inicial: Divida o arquivo de entrada em runs ordenados
    fitas[0] = fopen("fita1.txt", "w");
    fitas[1] = fopen("fita2.txt", "w");
    int run[TAMANHO_MEMORIA];

    while (fscanf(entrada, "%d", &num) == 1) {
        run[i++] = num;
        if (i == TAMANHO_MEMORIA) {
            qsort(run, TAMANHO_MEMORIA, sizeof(int), (int(*)(const void*, const void*))strcmp);
            for (int j = 0; j < TAMANHO_MEMORIA; j++) {
                fprintf(fitas[0], "%d ", run[j]);
            }
            i = 0;
        }
    }

    if (i > 0) {
        qsort(run, i, sizeof(int), (int(*)(const void*, const void*))strcmp);
        for (int j = 0; j < i; j++) {
            fprintf(fitas[1], "%d ", run[j]);
        }
    }

    fclose(fitas[0]);
    fclose(fitas[1]);

    // Realizando a intercalação polifásica
    merge(0, 1, 2);
}

int main() {
    FILE *entrada = fopen("C:/entrada/entrada.txt", "r");

    if (entrada == NULL) {
        printf("Erro ao abrir arquivo de entrada.\n");
        return 1;
    }

    polifasico(entrada);
    fclose(entrada);

    printf("Ordenação concluída. Verifique o arquivo fita3.txt para os dados ordenados.\n");
    return 0;
}
