#include <stdio.h>
#include <stdlib.h>

// Estrutura que representa um elemento com um valor inteiro
typedef struct {
    int valor;
} Elemento;

// Índice para navegação na árvore
typedef int Indice;

// Estrutura de um nó na árvore-B
typedef struct Nodo *ArvoreB;

typedef struct Nodo {
    Elemento *elementos; // Array de elementos do nó
    ArvoreB *filhos;     // Ponteiros para os filhos do nó
    Indice quantidade;   // Número de elementos no nó
} Nodo;

// Função para buscar um elemento na árvore-B
int *buscar_elemento(ArvoreB arvore, int valor, int verifica_raiz, int i) {
    if (arvore == NULL) {
        printf("Valor nao encontrado\n");
        return NULL;
    }

    // Verifica se deve imprimir o número de elementos na raiz
    if (verifica_raiz) {
        printf("%d\n", arvore->quantidade);
    }

    // Navega pelos elementos do nó até encontrar a posição correta ou o fim
    while (i < arvore->quantidade && valor > arvore->elementos[i].valor) {
        i++;
    }

    // Se o valor for encontrado, imprime os elementos do nó
    if (i < arvore->quantidade && valor == arvore->elementos[i].valor) {
        printf("%d\n", arvore->quantidade);

        for (int j = 0; j < arvore->quantidade; j++) {
            printf("%d ", arvore->elementos[j].valor);
        }
        printf("\n");

        return &arvore->elementos[i].valor;
    }

    // Se o nó não tiver filhos, o valor não está na árvore
    if (arvore->filhos == NULL) {
        printf("Valor nao encontrado\n");
        return NULL;
    }

    // Continua a busca no filho correspondente
    return buscar_elemento(arvore->filhos[i], valor, 0, 0);
}

// Função para inserir um elemento em uma página específica
void inserir_na_pagina(ArvoreB arvore, Elemento chave, ArvoreB filho_direito) {
    int k = arvore->quantidade;
    int verifica_posicao = (k > 0);

    // Encontra a posição correta para inserir o novo elemento, deslocando os existentes
    while (verifica_posicao) {
        if (chave.valor >= arvore->elementos[k - 1].valor) {
            verifica_posicao = 0;
            break;
        }

        arvore->elementos[k] = arvore->elementos[k - 1];
        arvore->filhos[k + 1] = arvore->filhos[k];
        k--;

        verifica_posicao = (k >= 1);
    }

    // Insere o novo elemento e ajusta o ponteiro para o filho à direita
    arvore->elementos[k] = chave;
    arvore->filhos[k + 1] = filho_direito;
    arvore->quantidade++;
}

// Função auxiliar para tratar a inserção de um novo elemento na árvore
void auxiliar_insercao(Elemento chave, ArvoreB arvore, int *cresceu, Elemento *chave_retorno, ArvoreB *filho_retorno, int M, int MM) {
    int i = 1;

    // Se a árvore estiver vazia, cria um novo nó com o elemento
    if (arvore == NULL) {
        *cresceu = 1;
        *chave_retorno = chave;
        *filho_retorno = NULL;
        return;
    }

    // Encontra a posição para o novo elemento ou verifica se já existe
    while (i < arvore->quantidade && chave.valor > arvore->elementos[i - 1].valor) {
        i++;
    }

    // Se o elemento já existir, a inserção é cancelada
    if (chave.valor == arvore->elementos[i - 1].valor) {
        *cresceu = 0;
        return;
    }

    if (chave.valor < arvore->elementos[i - 1].valor) {
        i--;
    }

    // Continua a inserção recursivamente no filho adequado
    auxiliar_insercao(chave, arvore->filhos[i], cresceu, chave_retorno, filho_retorno, M, MM);

    if (!*cresceu) {
        return;
    }

    // Se o nó não estiver cheio, insere o novo elemento diretamente
    if (arvore->quantidade < MM) {
        inserir_na_pagina(arvore, *chave_retorno, *filho_retorno);
        *cresceu = 0;
        return;
    }

    // Se o nó estiver cheio, realiza a divisão do nó
    ArvoreB nova_arvore = (ArvoreB)malloc(sizeof(Nodo));
    nova_arvore->elementos = (Elemento *)malloc(MM * sizeof(Elemento));
    nova_arvore->filhos = (ArvoreB *)malloc((MM + 1) * sizeof(ArvoreB));
    nova_arvore->quantidade = 0;
    nova_arvore->filhos[0] = NULL;

    if (i <= M + 1) {
        inserir_na_pagina(nova_arvore, arvore->elementos[MM - 1], arvore->filhos[MM]);
        arvore->quantidade--;
        inserir_na_pagina(arvore, *chave_retorno, *filho_retorno);
    } else {
        inserir_na_pagina(nova_arvore, *chave_retorno, *filho_retorno);
    }

    // Move os elementos do nó original para a nova árvore após a divisão
    for (int j = M + 2; j <= MM; j++) {
        inserir_na_pagina(nova_arvore, arvore->elementos[j - 1], arvore->filhos[j]);
        arvore->quantidade--;
    }

    arvore->quantidade--;
    nova_arvore->filhos[0] = arvore->filhos[M + 1];
    *chave_retorno = arvore->elementos[M];
    *filho_retorno = nova_arvore;
}

// Função principal para inserir um novo elemento na árvore-B
void inserir_elemento(Elemento chave, ArvoreB *arvore, int M, int MM) {
    int cresceu;
    Elemento chave_retorno;
    ArvoreB filho_retorno = NULL;

    // Chama a função auxiliar para realizar a inserção
    auxiliar_insercao(chave, *arvore, &cresceu, &chave_retorno, &filho_retorno, M, MM);

    // Se o nó raiz tiver crescido após a inserção, cria uma nova raiz
    if (cresceu) {
        Nodo *nova_arvore = (Nodo *)malloc(sizeof(Nodo));
        nova_arvore->elementos = (Elemento *)malloc(MM * sizeof(Elemento));
        nova_arvore->filhos = (ArvoreB *)malloc((MM + 1) * sizeof(ArvoreB));
        nova_arvore->quantidade = 1;
        nova_arvore->elementos[0] = chave_retorno;
        nova_arvore->filhos[1] = filho_retorno;
        nova_arvore->filhos[0] = *arvore;
        *arvore = nova_arvore;
    }
}

// Função principal
int main() {
    ArvoreB arvore = NULL;
    int chave = 0;
    int M, MM;

    // Lê o valor de M e calcula o dobro (MM)
    scanf("%d", &M);
    MM = M * 2;

    // Insere elementos na árvore até encontrar -1
    while (1) {
        scanf("%d", &chave);
        if (chave == -1) break;
        Elemento elemento;
        elemento.valor = chave;
        inserir_elemento(elemento, &arvore, M, MM);
    }

    // Lê o valor a ser buscado
    int buscado;
    scanf("%d", &buscado);

    // Realiza a busca na árvore
    buscar_elemento(arvore, buscado, 1, 0);

    return 0;
}
