// Busca em Largura (BFS): BFS começa por marcar o nó inicial como visitado e o coloca na fila. Em seguida, exploramos todos os nós adjacentes ao nó atual, visitando-os na ordem em que foram enfileirados.

#include <stdio.h>
#include <stdlib.h>

#define SIZE 40

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

// Estrutura da Fila
struct Queue {
    int items[SIZE];
    int front;
    int rear;
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

// Função para Criar Fila
struct Queue* createQueue() {
    struct Queue* queue = malloc(sizeof(struct Queue));
    queue->front = -1;
    queue->rear = -1;
    return queue;
}

// Verifica se a Fila está Vazia
int isEmpty(struct Queue* queue) {
    if (queue->rear == -1)
        return 1;
    else
        return 0;
}

// Enfileira um elemento
void enqueue(struct Queue* queue, int value) {
    if (queue->rear == SIZE - 1)
        printf("\nFila Cheia");
    else {
        if (queue->front == -1)
            queue->front = 0;
        queue->rear++;
        queue->items[queue->rear] = value;
    }
}

// Desenfileira um elemento
int dequeue(struct Queue* queue) {
    int item;
    if (isEmpty(queue)) {
        printf("Fila Vazia");
        item = -1;
    } else {
        item = queue->items[queue->front];
        queue->front++;
        if (queue->front > queue->rear) {
            queue->front = queue->rear = -1;
        }
    }
    return item;
}

// Função de Busca em Largura (BFS)
void BFS(struct Graph* graph, int startVertex) {
    struct Queue* queue = createQueue();

    graph->visited[startVertex] = 1;
    enqueue(queue, startVertex);

    while (!isEmpty(queue)) {
        int currentVertex = dequeue(queue);
        printf("Visitando %d\n", currentVertex);

        struct Node* temp = graph->adjLists[currentVertex];

        while (temp) {
            int adjVertex = temp->vertex;

            if (graph->visited[adjVertex] == 0) {
                graph->visited[adjVertex] = 1;
                enqueue(queue, adjVertex);
            }
            temp = temp->next;
        }
    }
}

// Função Principal
int main() {
    struct Graph* graph = createGraph(6);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 4);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 5);

    BFS(graph, 0);

    return 0;
}
