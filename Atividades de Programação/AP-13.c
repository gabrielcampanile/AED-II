#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 101
#define INFINITO INT_MAX

// Estrutura para representar uma aresta
typedef struct {
    int origem, destino, peso;
} Aresta;

// Estrutura para representar um nó na lista de adjacência
typedef struct No {
    int vertice, peso;
    struct No* prox;
} No;

// Estrutura para representar uma lista de adjacência
typedef struct {
    No* cab;
} ListaAdjacencia;

// Estrutura para representar um grafo
typedef struct {
    int vertices;
    ListaAdjacencia adj[MAX_VERTICES];
} Grafo;

// Função para inicializar o grafo
void inicializarGrafo(Grafo* grafo, int vertices) {
    grafo->vertices = vertices;
    for (int i = 0; i < vertices; i++) {
        grafo->adj[i].cab = NULL;
    }
}

// Função para inserir uma aresta no grafo
void inserirAresta(Grafo* grafo, int origem, int destino, int peso) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->vertice = destino;
    novoNo->peso = peso;
    novoNo->prox = grafo->adj[origem].cab;
    grafo->adj[origem].cab = novoNo;
}

// Função para relaxar uma aresta
void relaxar(int distancia[], int u, int v, int peso, int restricao) {
    if (peso <= restricao && distancia[u] != INFINITO && distancia[u] + peso < distancia[v]) {
        distancia[v] = distancia[u] + peso;
    }
}

// Função para executar o algoritmo de Bellman-Ford
void bellmanFord(Grafo* grafo, int verticeInicial, int restricao) {
    int distancia[MAX_VERTICES];
    
    // Inicializa as distâncias com infinito
    for (int i = 0; i < grafo->vertices; i++) {
        distancia[i] = INFINITO;
    }
    distancia[verticeInicial] = 0;
    
    // Relaxamento das arestas (N-2) vezes
    for (int i = 1; i < grafo->vertices - 1; i++) {
        for (int u = 0; u < grafo->vertices; u++) {
            No* ad = grafo->adj[u].cab;
            while (ad) {
                relaxar(distancia, u, ad->vertice, ad->peso, restricao);
                ad = ad->prox;
            }
        }
    }
    
    // Exibe as distâncias mínimas do nó inicial para todos os outros nós
    for (int i = 0; i < grafo->vertices; i++) {
        if (distancia[i] == INFINITO) {
            printf("INF ");
        } else {
            printf("%d ", distancia[i]);
        }
    }
    printf("\n");
}

int main() {
    int verticeInicial, restricao, vertices, arestas;
    
    // Entrada dos dados
    scanf("%d", &verticeInicial);
    scanf("%d", &restricao);
    scanf("%d %d", &vertices, &arestas);
    
    Grafo grafo;
    inicializarGrafo(&grafo, vertices);
    
    // Lê as arestas do grafo
    for (int i = 0; i < arestas; i++) {
        int origem, destino, peso;
        scanf("%d %d %d", &origem, &destino, &peso);
        inserirAresta(&grafo, origem, destino, peso);
    }
    
    // Executa o algoritmo de Bellman-Ford com a restrição
    bellmanFord(&grafo, verticeInicial, restricao);
    
    return 0;
}