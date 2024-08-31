#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_NUMEROS 100
#define TAMANHO_MEMORIA 10

void gera_numeros_aleatorios(char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (!arquivo) {
        printf("Erro ao criar o arquivo %s.\n", nome_arquivo);
        return;
    }

    srand(time(NULL));
    for (int i = 0; i < NUM_NUMEROS; i++) {
        int num = rand() % 1000; // Gera números aleatórios entre 0 e 999
        fprintf(arquivo, "%d ", num);
    }

    fclose(arquivo);
    printf("Arquivo %s criado com números aleatórios.\n", nome_arquivo);
}

void ajusta_heap(int arr[], int n, int i) {
    int menor = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    if (esquerda < n && arr[esquerda] < arr[menor])
        menor = esquerda;

    if (direita < n && arr[direita] < arr[menor])
        menor = direita;

    if (menor != i) {
        int temp = arr[i];
        arr[i] = arr[menor];
        arr[menor] = temp;

        ajusta_heap(arr, n, menor);
    }
}

void heap_sort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        ajusta_heap(arr, n, i);

    for (int i = n - 1; i >= 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        ajusta_heap(arr, i, 0);
    }
}

void splitFile(char *inputFile, int runSize) {
    FILE *inFile = fopen(inputFile, "r");
    if (!inFile) {
        printf("Erro ao abrir o arquivo de entrada: %s\n", inputFile);
        return;
    }

    int runCount = 0;
    int buffer[runSize];
    int i;

    while (!feof(inFile)) {
        for (i = 0; i < runSize && fscanf(inFile, "%d", &buffer[i]) == 1; i++)
            ;
        heap_sort(buffer, i);

        char outFileName[20];
        sprintf(outFileName, "run%d.txt", runCount++);
        FILE *outFile = fopen(outFileName, "w");
        if (!outFile) {
            printf("Erro ao criar o arquivo %s.\n", outFileName);
            continue;
        }

        for (int j = 0; j < i; j++) {
            fprintf(outFile, "%d ", buffer[j]);
        }

        fclose(outFile);
        printf("Arquivo %s criado com sucesso.\n", outFileName);

        outFile = fopen(outFileName, "r");
        if (outFile) {
            printf("Conteúdo de %s: ", outFileName);
            int num;
            while (fscanf(outFile, "%d", &num) == 1) {
                printf("%d ", num);
            }
            printf("\n");
            fclose(outFile);
        }
    }

    fclose(inFile);
}

void mergeFiles(FILE *fp1, FILE *fp2, FILE *outFile) {
    int a, b;

    if (fscanf(fp1, "%d", &a) != 1)
        a = EOF;
    if (fscanf(fp2, "%d", &b) != 1)
        b = EOF;

    while (a != EOF && b != EOF) {
        if (a < b) {
            fprintf(outFile, "%d ", a);
            if (fscanf(fp1, "%d", &a) != 1)
                a = EOF;
        } else {
            fprintf(outFile, "%d ", b);
            if (fscanf(fp2, "%d", &b) != 1)
                b = EOF;
        }
    }

    while (a != EOF) {
        fprintf(outFile, "%d ", a);
        if (fscanf(fp1, "%d", &a) != 1)
            a = EOF;
    }

    while (b != EOF) {
        fprintf(outFile, "%d ", b);
        if (fscanf(fp2, "%d", &b) != 1)
            b = EOF;
    }
}

void mergeSortedRuns(int runCount) {
    char outFileName[20];
    char runFileName1[20];
    char runFileName2[20];

    for (int i = 1; i < runCount; i *= 2) {
        for (int j = 0; j < runCount; j += 2 * i) {
            sprintf(runFileName1, "run%d.txt", j);
            sprintf(runFileName2, "run%d.txt", j + i);
            if (i * 2 >= runCount && j + 2 * i >= runCount) {
                sprintf(outFileName, "sorted_output.txt");
            } else {
                sprintf(outFileName, "run%d.txt", j / 2);
            }

            FILE *runFile1 = fopen(runFileName1, "r");
            FILE *runFile2 = fopen(runFileName2, "r");
            FILE *outFile = fopen(outFileName, "w");

            if (runFile1 && runFile2) {
                mergeFiles(runFile1, runFile2, outFile);
                printf("Arquivos %s e %s intercalados em %s.\n", runFileName1, runFileName2, outFileName);
            } else if (runFile1) {
                while (!feof(runFile1)) {
                    int n;
                    if (fscanf(runFile1, "%d", &n) == 1)
                        fprintf(outFile, "%d ", n);
                }
                printf("Arquivo %s copiado para %s.\n", runFileName1, outFileName);
            }

            if (runFile1) fclose(runFile1);
            if (runFile2) fclose(runFile2);
            fclose(outFile);

            outFile = fopen(outFileName, "r");
            if (outFile) {
                printf("Conteúdo de %s: ", outFileName);
                int num;
                while (fscanf(outFile, "%d", &num) == 1) {
                    printf("%d ", num);
                }
                printf("\n");
                fclose(outFile);
            }
        }
    }
}

int main() {
    char inputFile[] = "input.txt";
    gera_numeros_aleatorios(inputFile);

    splitFile(inputFile, TAMANHO_MEMORIA);

    int runCount = (NUM_NUMEROS + TAMANHO_MEMORIA - 1) / TAMANHO_MEMORIA;
    mergeSortedRuns(runCount);

    printf("Arquivo ordenado gerado com sucesso.\n");
    return 0;
}