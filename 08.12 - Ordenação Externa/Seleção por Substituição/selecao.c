#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definindo o tamanho da memória que podemos carregar de uma vez
#define TAMANHO_MEMORIA 10

// Função para ajustar a heap mínima
void ajusta_heap(int arr[], int n, int i) {
    int menor = i; // Inicializa o menor como a raiz
    int esquerda = 2 * i + 1; // Filho à esquerda
    int direita = 2 * i + 2; // Filho à direita
  
    // Se o filho à esquerda for menor que a raiz
    if (esquerda < n && arr[esquerda] < arr[menor])
        menor = esquerda;
  
    // Se o filho à direita for menor que o menor elemento atual
    if (direita < n && arr[direita] < arr[menor])
        menor = direita;
  
    // Se o menor não for a raiz, troque e continue ajustando
    if (menor != i) {
        int temp = arr[i];
        arr[i] = arr[menor];
        arr[menor] = temp;
        ajusta_heap(arr, n, menor);
    }
}

// Função principal de ordenação por seleção por substituição
void selecao_por_substituicao(FILE *entrada, FILE *saida) {
    int memoria[TAMANHO_MEMORIA];
    int i, j, num_elementos;
    
    // Carrega a memória inicial com os elementos do arquivo de entrada
    for (i = 0; i < TAMANHO_MEMORIA; i++) {
        if (fscanf(entrada, "%d", &memoria[i]) != 1)
            break; // Se não conseguir ler mais elementos, pare
    }
    num_elementos = i; // Número de elementos carregados
    
    // Constrói a heap mínima inicial
    for (i = num_elementos / 2 - 1; i >= 0; i--) {
        ajusta_heap(memoria, num_elementos, i);
    }
    
    int tamanho_corrente_run = 0;
    int proximo_elemento;
    
    // Enquanto houver elementos na memória
    while (num_elementos > 0) {
        // Escreve o menor elemento (raiz da heap) no arquivo de saída
        fprintf(saida, "%d ", memoria[0]);
        tamanho_corrente_run++;
        
        // Tenta carregar o próximo elemento do arquivo de entrada
        if (fscanf(entrada, "%d", &proximo_elemento) == 1) {
            // Se o próximo elemento for maior ou igual à raiz da heap
            if (proximo_elemento >= memoria[0]) {
                memoria[0] = proximo_elemento;
            } else {
                // Se o próximo elemento for menor, ele vai para o próximo run
                memoria[0] = memoria[num_elementos - 1];
                memoria[num_elementos - 1] = proximo_elemento;
                num_elementos--;
            }
        } else {
            // Se não houver mais elementos para carregar
            memoria[0] = memoria[num_elementos - 1];
            num_elementos--;
        }
        
        // Reajusta a heap mínima após a substituição
        ajusta_heap(memoria, num_elementos, 0);
        
        // Se a memória estiver vazia, finalize o run atual e inicie um novo
        if (num_elementos == 0 && tamanho_corrente_run > 0) {
            fprintf(saida, "\n"); // Novo run no arquivo de saída
            tamanho_corrente_run = 0;
            
            // Recarrega a memória com novos elementos do arquivo de entrada
            for (i = 0; i < TAMANHO_MEMORIA; i++) {
                if (fscanf(entrada, "%d", &memoria[i]) != 1)
                    break; // Pare se não houver mais elementos
            }
            num_elementos = i; // Atualiza o número de elementos carregados
            
            // Reconstrói a heap mínima
            for (i = num_elementos / 2 - 1; i >= 0; i--) {
                ajusta_heap(memoria, num_elementos, i);
            }
        }
    }
}

// Função principal
int main() {
    // Abre os arquivos de entrada e saída
    FILE *entrada = fopen("C:/entrada/entrada.txt", "r");
    FILE *saida = fopen("C:/entrada/saida.txt", "w");
    
    // Verifica se os arquivos foram abertos corretamente
    if (entrada == NULL || saida == NULL) {
        printf("Erro ao abrir arquivos.\n");
        return 1;
    }
    
    // Executa a ordenação por seleção por substituição
    selecao_por_substituicao(entrada, saida);
    
    // Fecha os arquivos
    fclose(entrada);
    fclose(saida);
    
    return 0;
}
