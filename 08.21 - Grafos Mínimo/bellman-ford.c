/*
 Algoritmo de Bellman-Ford:
 Inicialização: As distâncias de todos os vértices a partir da origem são inicializadas como infinito, exceto a distância da origem para si mesma, que é 0.
 Relaxação: Cada aresta é relaxada V-1 vezes. Se a distância para o vértice de destino puder ser reduzida, ela é atualizada.
 Verificação de Ciclos Negativos: Após a relaxação, uma verificação é feita para detectar ciclos de peso negativo. Se o algoritmo encontrar um ciclo, ele avisa o usuário.
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Estrutura para representar uma aresta
struct Edge {
    int src, dest, weight;
};

// Estrutura para representar um grafo
struct Graph {
    int V, E;
    struct Edge* edge;
};

// Função para criar um grafo com V vértices e E arestas
struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (struct Edge*) malloc(E * sizeof(struct Edge));
    return graph;
}

// Função para imprimir a solução
void printArr(int dist[], int n) {
    printf("Vértice   Distância da Origem\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}

// Função principal que implementa o algoritmo de Bellman-Ford
void BellmanFord(struct Graph* graph, int src) {
    int V = graph->V;
    int E = graph->E;
    int dist[V];

    // Passo 1: Inicializa as distâncias da origem para todos os outros vértices como infinito
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;
    dist[src] = 0;

    // Passo 2: Relaxa todas as arestas |V| - 1 vezes
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph->edge[j].src;
            int v = graph->edge[j].dest;
            int weight = graph->edge[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }

    // Passo 3: Verifica se há ciclos de peso negativo
    for (int i = 0; i < E; i++) {
        int u = graph->edge[i].src;
        int v = graph->edge[i].dest;
        int weight = graph->edge[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            printf("Grafo contém ciclo de peso negativo\n");
            return;
        }
    }

    // Imprime a solução
    printArr(dist, V);

    return;
}

// Função principal
int main() {
    int V = 5;  // Número de vértices no grafo
    int E = 8;  // Número de arestas no grafo
    struct Graph* graph = createGraph(V, E);

    // Adicionando arestas ao grafo
    graph->edge[0].src = 0;
    graph->edge[0].dest = 1;
    graph->edge[0].weight = -1;

    graph->edge[1].src = 0;
    graph->edge[1].dest = 2;
    graph->edge[1].weight = 4;

    graph->edge[2].src = 1;
    graph->edge[2].dest = 2;
    graph->edge[2].weight = 3;

    graph->edge[3].src = 1;
    graph->edge[3].dest = 3;
    graph->edge[3].weight = 2;

    graph->edge[4].src = 1;
    graph->edge[4].dest = 4;
    graph->edge[4].weight = 2;

    graph->edge[5].src = 3;
    graph->edge[5].dest = 2;
    graph->edge[5].weight = 5;

    graph->edge[6].src = 3;
    graph->edge[6].dest = 1;
    graph->edge[6].weight = 1;

    graph->edge[7].src = 4;
    graph->edge[7].dest = 3;
    graph->edge[7].weight = -3;

    BellmanFord(graph, 0);

    return 0;
}
