#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TAMANHO_MEMORIA 1000000 // Define o tamanho da memória para 1.000.000 de elementos

// Função para ajustar a heap mínima
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

// Função principal de seleção por substituição
void selecao_por_substituicao(FILE *entrada, FILE *saida) {
    int *memoria = (int *)malloc(TAMANHO_MEMORIA * sizeof(int));
    int i, num_elementos, proximo_elemento;
    int fim_arquivo = 0;

    // Carrega a memória inicial
    for (i = 0; i < TAMANHO_MEMORIA; i++) {
        if (fscanf(entrada, "%d", &memoria[i]) != 1) {
            fim_arquivo = 1;
            break;
        }
    }
    num_elementos = i;

    // Constrói a heap mínima inicial
    for (i = num_elementos / 2 - 1; i >= 0; i--) {
        ajusta_heap(memoria, num_elementos, i);
    }

    int tamanho_corrente_run = 0;

    while (!fim_arquivo || num_elementos > 0) {
        // Escreve o menor elemento no arquivo de saída
        fprintf(saida, "%d ", memoria[0]);
        tamanho_corrente_run++;

        if (!fim_arquivo) {
            // Carrega o próximo elemento do arquivo de entrada
            if (fscanf(entrada, "%d", &proximo_elemento) != 1) {
                fim_arquivo = 1;
                proximo_elemento = INT_MAX; // Marca como "infinito"
            }
        } else {
            proximo_elemento = INT_MAX;
        }

        if (proximo_elemento >= memoria[0]) {
            memoria[0] = proximo_elemento;
        } else {
            memoria[0] = memoria[num_elementos - 1];
            memoria[num_elementos - 1] = proximo_elemento;
            num_elementos--;
        }

        ajusta_heap(memoria, num_elementos, 0);

        // Se a memória estiver vazia, finalize o run atual e inicie um novo
        if (num_elementos == 0 && tamanho_corrente_run > 0) {
            fprintf(saida, "\n"); // Novo run no arquivo de saída
            tamanho_corrente_run = 0;

            // Recarrega a memória
            for (i = 0; i < TAMANHO_MEMORIA; i++) {
                if (fscanf(entrada, "%d", &memoria[i]) != 1) {
                    fim_arquivo = 1;
                    break;
                }
            }
            num_elementos = i;
            for (i = num_elementos / 2 - 1; i >= 0; i--) {
                ajusta_heap(memoria, num_elementos, i);
            }
        }
    }

    free(memoria);
}

// Função principal
int main() {
    FILE *entrada = fopen("C:/entrada/arq15M/entrada.txt", "r");
    FILE *saida = fopen("C:/entrada/arq15M/saida.txt", "w");

    if (entrada == NULL || saida == NULL) {
        printf("Erro ao abrir arquivos.\n");
        return 1;
    }

    selecao_por_substituicao(entrada, saida);

    fclose(entrada);
    fclose(saida);

    printf("Ordenação concluída. Verifique o arquivo saida.txt para os dados ordenados.\n");
    return 0;
}
