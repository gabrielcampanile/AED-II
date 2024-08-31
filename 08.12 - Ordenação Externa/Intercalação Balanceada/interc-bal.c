#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_FITAS_ENTRADA 3
#define NUM_FITAS_SAIDA 3
#define TAMANHO_MEMORIA 10

void intercalacao_balanceada(FILE *fitas_entrada[], FILE *fitas_saida[]) {
    int buffer[NUM_FITAS_ENTRADA];
    int i, menor, fim_run, fim_intercalacao = 0;

    // Carrega o primeiro número de cada fita de entrada para o buffer
    for (i = 0; i < NUM_FITAS_ENTRADA; i++) {
        if (fscanf(fitas_entrada[i], "%d", &buffer[i]) != 1) {
            buffer[i] = __INT_MAX__; // Marca como infinito se a fita estiver vazia
        }
    }

    while (!fim_intercalacao) {
        fim_run = 0;

        while (!fim_run) {
            // Encontra o menor valor no buffer
            menor = 0;
            for (i = 1; i < NUM_FITAS_ENTRADA; i++) {
                if (buffer[i] < buffer[menor]) {
                    menor = i;
                }
            }

            if (buffer[menor] == __INT_MAX__) {
                fim_intercalacao = 1; // Todos os runs foram processados
                break;
            }

            // Escreve o menor valor na fita de saída
            fprintf(fitas_saida[0], "%d ", buffer[menor]);

            // Lê o próximo valor da fita de onde o menor valor foi extraído
            if (fscanf(fitas_entrada[menor], "%d", &buffer[menor]) != 1) {
                buffer[menor] = __INT_MAX__; // Marca como infinito se não houver mais valores
            }

            // Checa se é o final do run
            for (i = 0; i < NUM_FITAS_ENTRADA; i++) {
                if (buffer[i] != __INT_MAX__ && buffer[i] < buffer[menor]) {
                    fim_run = 1; // Final do run detectado
                }
            }
        }

        fprintf(fitas_saida[0], "\n"); // Finaliza o run na fita de saída
    }
}

void criar_runs(FILE *entrada, FILE *fitas[]) {
    int run[TAMANHO_MEMORIA];
    int i, j, num;

    // Divide o arquivo de entrada em runs e armazena nas fitas
    for (i = 0; fscanf(entrada, "%d", &num) == 1; i = (i + 1) % NUM_FITAS_ENTRADA) {
        run[0] = num;
        for (j = 1; j < TAMANHO_MEMORIA && fscanf(entrada, "%d", &num) == 1; j++) {
            run[j] = num;
        }
        qsort(run, j, sizeof(int), (int(*)(const void*, const void*))strcmp);
        for (int k = 0; k < j; k++) {
            fprintf(fitas[i], "%d ", run[k]);
        }
        fprintf(fitas[i], "\n");
    }
}

int main() {
    FILE *entrada = fopen("C:/entrada/entrada.txt", "r");
    FILE *fitas_entrada[NUM_FITAS_ENTRADA];
    FILE *fitas_saida[NUM_FITAS_SAIDA];

    if (entrada == NULL) {
        printf("Erro ao abrir arquivo de entrada.\n");
        return 1;
    }

    // Abre as fitas de entrada e saída
    fitas_entrada[0] = fopen("fita1.txt", "w+");
    fitas_entrada[1] = fopen("fita2.txt", "w+");
    fitas_entrada[2] = fopen("fita3.txt", "w+");
    fitas_saida[0] = fopen("saida.txt", "w+");

    // Cria os runs a partir do arquivo de entrada
    criar_runs(entrada, fitas_entrada);

    // Reseta o ponteiro para o início das fitas de entrada
    for (int i = 0; i < NUM_FITAS_ENTRADA; i++) {
        rewind(fitas_entrada[i]);
    }

    // Realiza a intercalação balanceada
    intercalacao_balanceada(fitas_entrada, fitas_saida);

    // Fecha todos os arquivos
    fclose(entrada);
    for (int i = 0; i < NUM_FITAS_ENTRADA; i++) {
        fclose(fitas_entrada[i]);
    }
    fclose(fitas_saida[0]);

    printf("Ordenação concluída. Verifique o arquivo saida.txt para os dados ordenados.\n");
    return 0;
}
