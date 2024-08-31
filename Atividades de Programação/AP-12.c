#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 101

// Estrutura para representar um nó na lista de adjacência
typedef struct No {
    int vertice;
    struct No* proximo;
} No;

// Estrutura para representar uma lista de adjacência
typedef struct {
    No* cabeca;
} ListaAdjacencia;

// Estrutura para representar um grafo
typedef struct {
    ListaAdjacencia lista[MAX_VERTICES];
    int visitado[MAX_VERTICES];
} Grafo;

// Função para inicializar o grafo
void inicializarGrafo(Grafo* grafo, int vertices) {
    for (int i = 0; i < vertices; i++) {
        grafo->lista[i].cabeca = NULL;
        grafo->visitado[i] = 0;
    }
}

// Função para inserir uma aresta no grafo
void inserirAresta(Grafo* grafo, int origem, int destino) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->vertice = destino;
    novoNo->proximo = NULL;

    if (grafo->lista[origem].cabeca == NULL || grafo->lista[origem].cabeca->vertice > destino) {
        novoNo->proximo = grafo->lista[origem].cabeca;
        grafo->lista[origem].cabeca = novoNo;
    } else {
        No* temp = grafo->lista[origem].cabeca;
        while (temp->proximo != NULL && temp->proximo->vertice < destino) {
            temp = temp->proximo;
        }
        novoNo->proximo = temp->proximo;
        temp->proximo = novoNo;
    }
}

// Função para realizar a busca em largura (BFS) no grafo
void buscaEmLargura(Grafo* grafo, int inicio) {
    int fila[MAX_VERTICES], frente = 0, tras = 0;
    int visitado[MAX_VERTICES] = {0};

    fila[tras++] = inicio;
    visitado[inicio] = 1;

    while (frente < tras) {
        int verticeAtual = fila[frente++];
        printf("%d ", verticeAtual);

        No* temp = grafo->lista[verticeAtual].cabeca;
        while (temp) {
            int verticeAdjacente = temp->vertice;
            if (!visitado[verticeAdjacente]) {
                fila[tras++] = verticeAdjacente;
                visitado[verticeAdjacente] = 1;
            }
            temp = temp->proximo;
        }
    }
    printf("\n");
}

// Função auxiliar para realizar a busca em profundidade (DFS) no grafo
void buscaEmProfundidadeUtil(Grafo* grafo, int vertice) {
    grafo->visitado[vertice] = 1;
    printf("%d ", vertice);

    No* temp = grafo->lista[vertice].cabeca;
    while (temp) {
        int verticeAdjacente = temp->vertice;
        if (!grafo->visitado[verticeAdjacente]) {
            buscaEmProfundidadeUtil(grafo, verticeAdjacente);
        }
        temp = temp->proximo;
    }
}

// Função para realizar a busca em profundidade (DFS) no grafo
void buscaEmProfundidade(Grafo* grafo, int inicio) {
    for (int i = 0; i < MAX_VERTICES; i++) {
        grafo->visitado[i] = 0;
    }
    buscaEmProfundidadeUtil(grafo, inicio);
    printf("\n");
}

int main() {
    int verticeInicial, N, M;
    
    // Lê o vértice inicial, o número de vértices e o número de arestas
    scanf("%d", &verticeInicial);
    scanf("%d %d", &N, &M);

    Grafo grafo;
    inicializarGrafo(&grafo, N);

    // Lê as arestas e as insere no grafo
    for (int i = 0; i < M; i++) {
        int origem, destino;
        scanf("%d %d", &origem, &destino);
        inserirAresta(&grafo, origem, destino);
    }

    // Realiza a busca em largura (BFS) e a busca em profundidade (DFS)
    buscaEmLargura(&grafo, verticeInicial);
    buscaEmProfundidade(&grafo, verticeInicial);

    return 0;
}