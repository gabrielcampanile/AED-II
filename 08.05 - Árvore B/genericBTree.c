#include <stdio.h>
#include <stdlib.h>

// Estrutura para um nó da árvore B
typedef struct BTreeNode {
    int n; // Número de chaves no nó
    int *keys; // Array de chaves (tamanho máximo de 2 * N)
    struct BTreeNode **children; // Array de ponteiros para os filhos (tamanho máximo de 2 * N + 1)
    int leaf; // Booleano que indica se o nó é folha (1) ou não (0)
} BTreeNode;

// Função para criar um novo nó
BTreeNode* createNode(int leaf, int N) {
    BTreeNode *newNode = (BTreeNode*)malloc(sizeof(BTreeNode));
    newNode->n = 0;
    newNode->leaf = leaf;
    newNode->keys = (int*)malloc((2 * N) * sizeof(int));
    newNode->children = (BTreeNode**)malloc((2 * N + 1) * sizeof(BTreeNode*));
    for (int i = 0; i < 2 * N + 1; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

// Função para dividir o filho y de um nó x
void splitChild(BTreeNode *x, int i, BTreeNode *y, int N) {
    BTreeNode *z = createNode(y->leaf, N);
    z->n = N;

    for (int j = 0; j < N; j++) {
        z->keys[j] = y->keys[j + N + 1];
    }

    if (!y->leaf) {
        for (int j = 0; j <= N; j++) {
            z->children[j] = y->children[j + N + 1];
        }
    }

    y->n = N;

    for (int j = x->n; j >= i + 1; j--) {
        x->children[j + 1] = x->children[j];
    }

    x->children[i + 1] = z;

    for (int j = x->n - 1; j >= i; j--) {
        x->keys[j + 1] = x->keys[j];
    }

    x->keys[i] = y->keys[N];
    x->n++;
}

// Função para inserir uma nova chave em um nó não cheio
void insertNonFull(BTreeNode *x, int k, int N) {
    int i = x->n - 1;

    if (x->leaf) {
        while (i >= 0 && k < x->keys[i]) {
            x->keys[i + 1] = x->keys[i];
            i--;
        }
        x->keys[i + 1] = k;
        x->n++;
    } else {
        while (i >= 0 && k < x->keys[i]) {
            i--;
        }
        i++;
        if (x->children[i]->n == 2 * N) {
            splitChild(x, i, x->children[i], N);
            if (k > x->keys[i]) {
                i++;
            }
        }
        insertNonFull(x->children[i], k, N);
    }
}

// Função para inserir uma nova chave na árvore B
void insert(BTreeNode **root, int k, int N) {
    BTreeNode *r = *root;

    if (r->n == 2 * N) {
        BTreeNode *s = createNode(0, N);
        *root = s;
        s->children[0] = r;
        splitChild(s, 0, r, N);
        insertNonFull(s, k, N);
    } else {
        insertNonFull(r, k, N);
    }
}

// Função para imprimir a árvore B em ordem (in order)
void printInOrder(BTreeNode *node) {
    int i;
    for (i = 0; i < node->n; i++) {
        // Recursivamente imprime os filhos à esquerda
        if (!node->leaf) {
            printInOrder(node->children[i]);
        }
        // Imprime a chave do nó
        printf("%d ", node->keys[i]);
    }
    // Imprime o último filho à direita
    if (!node->leaf) {
        printInOrder(node->children[i]);
    }
}

int main() {
    int m, n;

    printf("Digite o valor de N (tamanho mínimo de chaves em um nó): ");
    scanf("%d", &m);

    BTreeNode *root = createNode(1, m);

    while (n >= 0) {
        // printf("Digite um número para inserir na árvore (ou um número negativo para parar): ");
        scanf("%d", &n);
        if (n >= 0) {
            insert(&root, n, m);
        }
    }

    printf("Arvore B em ordem: ");
    printInOrder(root);
    printf("\n");

    return 0;
}
