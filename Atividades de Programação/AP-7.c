#include <stdio.h>
#include <stdlib.h>
 
// Estrutura para representar um nó na árvore AVL
typedef struct Node
{
    struct Node *esquerda;
    struct Node *direita;
    int chave;
    int altura;
} Node;
 
// Função para inicializar a árvore AVL
Node *inicializar(Node *root)
{
    root = NULL;
    return root;
}
 
// Função para obter a altura de um nó
int altura(Node *node)
{
    if (node == NULL)
        return 0;
    return node->altura;
}
 
// Função para obter o máximo de dois inteiros
int max(int x, int y)
{
    return (x > y) ? x : y;
}
 
// Função para criar um novo nó
Node *novoNo(int chave)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->chave = chave;
    node->esquerda = NULL;
    node->direita = NULL;
    node->altura = 1; // novo nó é adicionado como folha
    
    return node;
}
 
// Função para ratação simples à direita
Node *LLrotation(Node *n)
{
    Node *pA = n;
    Node *pB = pA->esquerda;
 
    // Realiza a rotação
    pA->esquerda = pB->direita;
    pB->direita = pA;
 
    // Atualiza alturas
    pA->altura = max(altura(pA->esquerda), altura(pA->direita)) + 1;
    pB->altura = max(altura(pB->esquerda), altura(pB->direita)) + 1;
 
    return pB;
}
 
// Função para rotação simples à esquerda
Node *RRrotation(Node *n)
{
    Node *pA = n;
    Node *pB = pA->direita;
 
    // Realiza a rotação
    pA->direita = pB->esquerda;
    pB->esquerda = pA;
 
    // Atualiza alturas
    pA->altura = max(altura(pA->esquerda), altura(pA->direita)) + 1;
    pB->altura = max(altura(pB->esquerda), altura(pB->direita)) + 1;
 
    return pB;
}

// Função para rotação dupla à direita
Node *LRrotation(Node *n) {
    Node *pA = n;
    pA->direita = LLrotation(pA->direita);

    return RRrotation(pA);
}

// Função para rotação dupla à esquerda
Node *RLrotation(Node *n) {
    Node *pA = n;
    pA->esquerda = RRrotation(pA->esquerda);

    return LLrotation(pA);
}
 
// Função para balancear a árvore
int balanceamento(Node *node)
{
    if (node == NULL)
        return 0;
    return altura(node->esquerda) - altura(node->direita);
}
 
// Função para inserir um nó na árvore AVL
Node *inserir(Node *node, int chave)
{
    // Passo 1: inserção normal de um nó
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
    int fb = balanceamento(node);
 
    // Se o nó ficar desbalanceado, então haverá 4 casos possíveis:
 
    // Caso da rotação simples à direita
    if (fb > 1 && chave < node->esquerda->chave)
        return LLrotation(node);
 
    // Caso da rotação simples à esquerda
    if (fb < -1 && chave > node->direita->chave)
        return RRrotation(node);
 
    // Caso da rotação dupla à direita
    if (fb > 1 && chave > node->esquerda->chave)
        return RLrotation(node);
 
    // Caso da rotação dupla à esquerda
    if (fb < -1 && chave < node->direita->chave)
        return LRrotation(node);
 
    // Se o nó não estiver desbalanceado, retorne o próprio nó
    return node;
}
 
// Função para remover um nó da árvore AVL
Node *remover(Node *node, int chave)
{
    // Passo 1: remoção normal de um nó
    if (node == NULL)
        return node;
 
    if (chave < node->chave)
        node->esquerda = remover(node->esquerda, chave);
    else if (chave > node->chave)
        node->direita = remover(node->direita, chave);
    else
    {
        if ((node->esquerda == NULL) || (node->direita == NULL))
        {
            Node *temp = node->esquerda ? node->esquerda : node->direita;
 
            // Caso sem filhos
            if (temp == NULL)
            {
                temp = node;
                node = NULL;
            }
            else               // Caso com um filho
                *node = *temp; // Copia o conteúdo do filho não vazio
            free(temp);
        }
        else
        {
            // Caso com dois filhos: obter o sucessor em ordem
            Node *temp = node->direita;
            while (temp->esquerda != NULL)
                temp = temp->esquerda;
 
            // Copiar o sucessor em ordem para este nó
            node->chave = temp->chave;
 
            // Remover o sucessor em ordem
            node->direita = remover(node->direita, temp->chave);
        }
    }
 
    // Se a árvore tinha apenas um nó, então retornar
    if (node == NULL)
        return node;
 
    // Passo 2: atualizar a altura deste nó ancestral
    node->altura = 1 + max(altura(node->esquerda), altura(node->direita));
 
    // Passo 3: obter o fator de balanceamento deste nó ancestral
    int fb = balanceamento(node);
 
    // Se o nó ficar desbalanceado, então haverá 4 casos possíveis:
 
    // Caso da rotação simples à direita
    if (fb > 1 && altura(node->esquerda) >= altura(node->direita))
        return LLrotation(node);
 
    // Caso da rotação simples à esquerda
    if (fb < -1 && altura(node->direita) >= altura(node->esquerda))
        return RRrotation(node);
 
    // Caso da rotação dupla à direita
    if (fb > 1 && altura(node->direita) >= altura(node->esquerda))
        return RLrotation(node);
 
    // Caso da rotação dupla à esquerda
    if (fb < -1 && altura(node->esquerda) >= altura(node->direita))
        return LRrotation(node);
 
    // Se o nó não estiver desbalanceado, retorne o próprio nó
    return node;
}
 
// Função de utilidade para percorrer a árvore AVL em ordem
void emOrdem(Node *root)
{
    if (root != NULL)
    {
        emOrdem(root->esquerda);
        printf("%d ", root->chave);
        emOrdem(root->direita);
    }
}
 
// Função para printar a altura de um nó
void printHeight(Node *root)
{
    if (root == NULL)
    {
        printf("0, 0, 0\n");
        return;
    }
 
    printf("%d, ", root->altura - 1);
 
    if (root->esquerda != NULL)
        printf("%d, ", root->esquerda->altura);
    else
        printf("0, ");
 
    if (root->direita != NULL)
        printf("%d\n", root->direita->altura);
    else
        printf("0\n");
}
 
// Função para buscar uma chave na árvore AVL
int busca(Node *root, int chave, int mode)
{
    if (root == NULL)
    {
        // printf("Chave %d não encontrada na árvore AVL\n", chave);
        if (mode == 0)
            return 1;
        else
        {
            printf("Valor nao encontrado\n");
            return 0;
        }
    }
    else if (root->chave == chave)
    {
        // printf("Chave %d encontrada na árvore AVL\n", chave);
        if (mode == 0)
            return 0;
        else
        {
            printHeight(root);
            return 0;
        }
    }
 
    if (chave < root->chave)
        return busca(root->esquerda, chave, mode);
    else
        return busca(root->direita, chave, mode);
}

int main()
{
    Node *root = NULL; // Initialize 'root' variable
 
    int chave;
 
    // Inserindo chaves na árvore AVL
    while (chave >= 0)
    {
        // printf("Digite a chave %d: ", i + 1);
        scanf("%d", &chave);
        if (chave < 0)
            break;
        root = inserir(root, chave);
    }
 
    // printf("Arvore AVL em ordem:\n");
    // emOrdem(root);
    // printf("\n");
 
    printHeight(root);
 
    int chave_busca;
 
    while (chave_busca >= 0)
    {
        // printf("Digite a chave %d: ", i + 1);
        scanf("%d", &chave_busca);
        if (chave_busca < 0)
            break;
        if (busca(root, chave_busca, 0))
            root = inserir(root, chave_busca);
        else
            root = remover(root, chave_busca);
    }
 
    // printf("Árvore AVL em ordem:\n");
    // emOrdem(root);
    // printf("\n");
 
    scanf("%d", &chave_busca);
    busca(root, chave_busca, 1);
 
    return 0;
}