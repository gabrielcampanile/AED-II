#include <stdio.h>
#include <stdlib.h>

// Definindo um tipo genérico para as chaves na árvore-B.
typedef int TipoChave;

// Estrutura para armazenar elementos (chaves) da árvore-B.
typedef struct {
    TipoChave chave;
    // Outros campos podem ser adicionados conforme necessário.
} Elemento;

// Estrutura de um nó da árvore-B.
typedef struct Nodo {
    Elemento *elementos;  // Array de elementos (chaves) no nó.
    struct Nodo **filhos; // Ponteiros para os filhos do nó.
    int quantidade;       // Número de elementos no nó.
    int eh_folha;         // 1 se for folha, 0 se não for.
} Nodo;

typedef Nodo* ArvoreB;

// Função para criar um novo nó na árvore-B.
ArvoreB criar_nodo(int ordem, int eh_folha) {
    ArvoreB nodo = (ArvoreB)malloc(sizeof(Nodo));
    nodo->elementos = (Elemento *)malloc((2 * ordem - 1) * sizeof(Elemento));
    nodo->filhos = (ArvoreB *)malloc(2 * ordem * sizeof(ArvoreB));
    nodo->quantidade = 0;
    nodo->eh_folha = eh_folha;
    return nodo;
}

// Função para dividir um nó filho que está cheio.
void dividir_filho(ArvoreB pai, int indice, int ordem) {
    int i;
    ArvoreB filho_cheio = pai->filhos[indice];
    ArvoreB novo_filho = criar_nodo(ordem, filho_cheio->eh_folha);
    novo_filho->quantidade = ordem - 1;

    // Copia a segunda metade dos elementos do filho cheio para o novo filho.
    for (i = 0; i < ordem - 1; i++) {
        novo_filho->elementos[i] = filho_cheio->elementos[i + ordem];
    }

    // Se o filho cheio não for uma folha, copie a segunda metade dos filhos para o novo filho.
    if (!filho_cheio->eh_folha) {
        for (i = 0; i < ordem; i++) {
            novo_filho->filhos[i] = filho_cheio->filhos[i + ordem];
        }
    }

    filho_cheio->quantidade = ordem - 1;

    // Move os filhos do pai para a direita para abrir espaço para o novo filho.
    for (i = pai->quantidade; i >= indice + 1; i--) {
        pai->filhos[i + 1] = pai->filhos[i];
    }

    // Insere o novo filho no pai.
    pai->filhos[indice + 1] = novo_filho;

    // Move os elementos do pai para a direita para abrir espaço para a chave que sobe.
    for (i = pai->quantidade - 1; i >= indice; i--) {
        pai->elementos[i + 1] = pai->elementos[i];
    }

    // A chave do meio do filho cheio sobe para o pai.
    pai->elementos[indice] = filho_cheio->elementos[ordem - 1];
    pai->quantidade++;
}

// Função para inserir uma nova chave na árvore-B.
void inserir_nao_cheio(ArvoreB nodo, TipoChave chave, int ordem) {
    int i = nodo->quantidade - 1;

    if (nodo->eh_folha) {
        // Desloca as chaves para a direita até encontrar a posição correta para a nova chave.
        while (i >= 0 && nodo->elementos[i].chave > chave) {
            nodo->elementos[i + 1] = nodo->elementos[i];
            i--;
        }

        // Insere a nova chave na posição correta.
        nodo->elementos[i + 1].chave = chave;
        nodo->quantidade++;
    } else {
        // Encontra o filho que será responsável pela nova chave.
        while (i >= 0 && nodo->elementos[i].chave > chave) {
            i--;
        }
        i++;

        // Se o filho estiver cheio, divide-o.
        if (nodo->filhos[i]->quantidade == 2 * ordem - 1) {
            dividir_filho(nodo, i, ordem);

            // Após a divisão, decide para qual dos dois filhos a nova chave vai.
            if (nodo->elementos[i].chave < chave) {
                i++;
            }
        }
        inserir_nao_cheio(nodo->filhos[i], chave, ordem);
    }
}

// Função principal para inserir uma nova chave na árvore-B.
void inserir(ArvoreB *arvore, TipoChave chave, int ordem) {
    ArvoreB raiz = *arvore;

    if (raiz->quantidade == 2 * ordem - 1) {
        // Se a raiz estiver cheia, cria uma nova raiz e divide a antiga.
        ArvoreB nova_raiz = criar_nodo(ordem, 0);
        nova_raiz->filhos[0] = raiz;
        dividir_filho(nova_raiz, 0, ordem);
        inserir_nao_cheio(nova_raiz, chave, ordem);
        *arvore = nova_raiz;
    } else {
        inserir_nao_cheio(raiz, chave, ordem);
    }
}

// Função para imprimir a árvore-B (apenas para verificação).
void imprimir_arvore(ArvoreB nodo, int nivel) {
    int i;
    if (nodo != NULL) {
        for (i = 0; i < nodo->quantidade; i++) {
            if (!nodo->eh_folha) {
                imprimir_arvore(nodo->filhos[i], nivel + 1);
            }
            printf("Nivel %d, Chave %d\n", nivel, nodo->elementos[i].chave);
        }
        if (!nodo->eh_folha) {
            imprimir_arvore(nodo->filhos[i], nivel + 1);
        }
    }
}

int main() {
    int ordem;  // Ordem da árvore-B.
    scanf("%d", &ordem);
    ArvoreB arvore = criar_nodo(ordem, 1);

    // Inserir chaves na árvore.
    int chave = 0;
    while (chave >= 0) {
        scanf("%d", &chave);
        if (chave >= 0) {
            inserir(&arvore, chave, ordem);
        }
    }
    // inserir(&arvore, 10, ordem);
    // inserir(&arvore, 20, ordem);
    // inserir(&arvore, 5, ordem);
    // inserir(&arvore, 6, ordem);
    // inserir(&arvore, 12, ordem);
    // inserir(&arvore, 30, ordem);
    // inserir(&arvore, 7, ordem);
    // inserir(&arvore, 17, ordem);

    // Imprimir a árvore-B.
    imprimir_arvore(arvore, 0);

    return 0;
}
