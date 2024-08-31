#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para intercalação de dois arquivos
void mergeFiles(FILE *fp1, FILE *fp2, FILE *outFile)
{
    int a, b;

    // Lê o primeiro elemento de cada arquivo
    if (fscanf(fp1, "%d", &a) != 1) a = EOF;
    if (fscanf(fp2, "%d", &b) != 1) b = EOF;

    while (a != EOF && b != EOF)
    {
        if (a < b)
        {
            fprintf(outFile, "%d ", a);
            if (fscanf(fp1, "%d", &a) != 1) a = EOF;
        }
        else
        {
            fprintf(outFile, "%d ", b);
            if (fscanf(fp2, "%d", &b) != 1) b = EOF;
        }
    }

    // Copia o restante do arquivo que ainda não foi completamente lido
    while (a != EOF)
    {
        fprintf(outFile, "%d ", a);
        if (fscanf(fp1, "%d", &a) != 1) a = EOF;
    }

    while (b != EOF)
    {
        fprintf(outFile, "%d ", b);
        if (fscanf(fp2, "%d", &b) != 1) b = EOF;
    }
}

// Função para comparar inteiros para qsort
int compareInt(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

// Função para dividir o arquivo grande em arquivos menores
int splitFile(char *inputFile, int runSize)
{
    FILE *inFile = fopen(inputFile, "r");
    if (!inFile) {
        printf("Erro ao abrir o arquivo de entrada: %s\n", inputFile);
        return -1;
    }

    int runCount = 0;
    int buffer[runSize];
    int i;

    while (!feof(inFile))
    {
        for (i = 0; i < runSize && fscanf(inFile, "%d", &buffer[i]) == 1; i++);

        if (i == 0) break; // Nenhum dado lido

        qsort(buffer, i, sizeof(int), compareInt);

        char outFileName[20];
        sprintf(outFileName, "run%d.txt", runCount++);
        FILE *outFile = fopen(outFileName, "w");
        if (!outFile) {
            printf("Erro ao criar o arquivo %s.\n", outFileName);
            continue;
        }

        for (int j = 0; j < i; j++)
        {
            fprintf(outFile, "%d ", buffer[j]);
        }

        fclose(outFile);
        printf("Arquivo %s criado com sucesso.\n", outFileName);
    }

    fclose(inFile);
    return runCount;
}

// Função para fazer a intercalação de runs
void mergeSortedRuns(int runCount)
{
    int currentRunCount = runCount;
    int newRunCount = 0;
    int i, j;

    while (currentRunCount > 1)
    {
        for (i = 0, newRunCount = 0; i < currentRunCount; i += 2)
        {
            char runFileName1[20];
            char runFileName2[20];
            char outFileName[20];

            sprintf(runFileName1, "run%d.txt", i);
            sprintf(runFileName2, "run%d.txt", i + 1);

            if (i + 1 < currentRunCount) {
                sprintf(outFileName, "run%d.txt", newRunCount++);
                FILE *runFile1 = fopen(runFileName1, "r");
                FILE *runFile2 = fopen(runFileName2, "r");
                FILE *outFile = fopen(outFileName, "w");

                if (runFile1 && runFile2)
                {
                    mergeFiles(runFile1, runFile2, outFile);
                    printf("Arquivos %s e %s intercalados em %s.\n", runFileName1, runFileName2, outFileName);
                }

                fclose(runFile1);
                fclose(runFile2);
                fclose(outFile);
            }
            else {
                // Apenas copia o último arquivo, caso não haja par para intercalar
                sprintf(outFileName, "run%d.txt", newRunCount++);
                rename(runFileName1, outFileName);
            }
        }

        currentRunCount = newRunCount;
    }

    // Renomeia o arquivo final
    rename("run0.txt", "sorted_output.txt");
}

int main()
{
    char inputFile[] = "C:/entrada/input.txt";
    int runSize = 10; // Tamanho do bloco que cabe em memória

    int runCount = splitFile(inputFile, runSize);

    if (runCount > 0) {
        mergeSortedRuns(runCount);
        printf("Arquivo ordenado gerado com sucesso.\n");
    } else {
        printf("Nenhum bloco foi criado.\n");
    }

    return 0;
}
