#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar um nó na árvore AVL
typedef struct Node {
    int chave;
    struct Node* esquerda;
    struct Node* direita;
    int altura;
} Node;

// Função para obter a altura de um nó
int altura(Node* node) {
    if (node == NULL)
        return 0;
    return node->altura;
}

// Função para obter o máximo de dois inteiros
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Função para criar um novo nó
Node* novoNo(int chave) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->chave = chave;
    node->esquerda = NULL;
    node->direita = NULL;
    node->altura = 1; // novo nó é adicionado como folha
    return node;
}

// Função para rodar a subárvore para a direita
Node* rotacaoDireita(Node* y) {
    Node* x = y->esquerda;
    Node* T2 = x->direita;

    // Realiza a rotação
    x->direita = y;
    y->esquerda = T2;

    // Atualiza alturas
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;

    return x;
}

// Função para rodar a subárvore para a esquerda
Node* rotacaoEsquerda(Node* x) {
    Node* y = x->direita;
    Node* T2 = y->esquerda;

    // Realiza a rotação
    y->esquerda = x;
    x->direita = T2;

    // Atualiza alturas
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;

    return y;
}

// Função para balancear a árvore
int balanceamento(Node* node) {
    if (node == NULL)
        return 0;
    return altura(node->esquerda) - altura(node->direita);
}

// Função para inserir um nó na árvore AVL
Node* inserir(Node* node, int chave) {
    // Passo 1: inserção normal de um nó de BST
    if (node == NULL)
        return novoNo(chave);

    if (chave < node->chave)
        node->esquerda = inserir(node->esquerda, chave);
    else if (chave > node->chave)
        node->direita = inserir(node->direita, chave);
    else // chaves iguais não são permitidas na árvore AVL
        return node;

    // Passo 2: atualizar a altura deste nó ancestral
    node->altura = 1 + max(altura(node->esquerda), altura(node->direita));

    // Passo 3: obter o fator de balanceamento deste nó ancestral
    int bf = balanceamento(node);

    // Se o nó ficar desbalanceado, então haverá 4 casos possíveis

    // Caso da rotação simples à direita
    if (bf > 1 && chave < node->esquerda->chave)
        return rotacaoDireita(node);

    // Caso da rotação simples à esquerda
    if (bf < -1 && chave > node->direita->chave)
        return rotacaoEsquerda(node);

    // Caso da rotação dupla à direita
    if (bf > 1 && chave > node->esquerda->chave) {
        node->esquerda = rotacaoEsquerda(node->esquerda);
        return rotacaoDireita(node);
    }

    // Caso da rotação dupla à esquerda
    if (bf < -1 && chave < node->direita->chave) {
        node->direita = rotacaoDireita(node->direita);
        return rotacaoEsquerda(node);
    }

    // Se o nó não estiver desbalanceado, retorne o próprio nó
    return node;
}

// Função de utilidade para percorrer a árvore AVL em ordem
void emOrdem(Node* root) {
    if (root != NULL) {
        emOrdem(root->esquerda);
        printf("%d ", root->chave);
        emOrdem(root->direita);
    }
}

int main() {
    Node* root = NULL;
    int N, chave;

    printf("Digite o número de chaves a serem inseridas: ");
    scanf("%d", &N);

    // Inserindo chaves na árvore AVL
    for (int i = 0; i < N; i++) {
        printf("Digite a chave %d: ", i + 1);
        scanf("%d", &chave);
        root = inserir(root, chave);
    }

    printf("Árvore AVL em ordem:\n");
    emOrdem(root);
    printf("\n");

    return 0;
}
