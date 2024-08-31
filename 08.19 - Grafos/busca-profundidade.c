// Busca em Profundidade (DFS): A DFS começa por marcar o vértice inicial como visitado e, recursivamente, visita cada vértice adjacente que ainda não foi visitado. A recursão desce até o nível mais profundo antes de voltar e explorar outros caminhos.

#include <stdio.h>
#include <stdlib.h>

// Estrutura do Nó da Lista de Adjacência
struct Node {
    int vertex;
    struct Node* next;
};

// Estrutura do Grafo
struct Graph {
    int numVertices;
    struct Node** adjLists;
    int* visited;
};

// Função para Criar Nó
struct Node* createNode(int v) {
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Função para Criar Grafo
struct Graph* createGraph(int vertices) {
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    graph->adjLists = malloc(vertices * sizeof(struct Node*));
    graph->visited = malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

// Função para Adicionar Aresta
void addEdge(struct Graph* graph, int src, int dest) {
    // Adiciona aresta de src para dest
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Adiciona aresta de dest para src (se o grafo for não-direcionado)
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// Função auxiliar para DFS
void DFSUtil(struct Graph* graph, int vertex) {
    struct Node* adjList = graph->adjLists[vertex];
    struct Node* temp = adjList;

    graph->visited[vertex] = 1;
    printf("Visitando %d\n", vertex);

    while (temp != NULL) {
        int connectedVertex = temp->vertex;

        if (graph->visited[connectedVertex] == 0) {
            DFSUtil(graph, connectedVertex);
        }
        temp = temp->next;
    }
}

// Função de Busca em Profundidade (DFS)
void DFS(struct Graph* graph, int startVertex) {
    DFSUtil(graph, startVertex);
}

// Função Principal
int main() {
    struct Graph* graph = createGraph(6);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 3, 4);
    addEdge(graph, 4, 5);

    DFS(graph, 0);

    return 0;
}
