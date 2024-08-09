// Gabriel Belchior Vieira Campanile - RA 168853
// AED II - Turma IA

#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar um nó na árvore AVL
typedef struct AVL
{
    struct AVL *esquerda;
    struct AVL *direita;
    int chave;
} AVL;

// Estrutura para representar um nó na árvore Rubro Negra
typedef struct AVP
{
    struct AVP *esquerda;
    struct AVP *direita;
    struct AVP *pai;
    int chave;
    int cor; // 0 = vermelho, 1 = preto
} AVP;

// Função para inicializar a árvore
AVL *inicializarAVL(AVL *root)
{
    root = NULL;
    return root;
}
AVP *inicializarAVP(AVP *root)
{
    root = NULL;
    return root;
}

// Função para criar um novo nó
AVL *novoNoAVL(int chave)
{
    AVL *node = (AVL *)malloc(sizeof(AVL));
    node->chave = chave;
    node->esquerda = NULL;
    node->direita = NULL;

    return node;
}
AVP *novoNoAVP(int chave)
{
    AVP *node = (AVP *)malloc(sizeof(AVP));
    node->chave = chave;
    node->esquerda = NULL;
    node->direita = NULL;
    node->pai = NULL;
    node->cor = 0; // novo nó é adicionado como vermelho

    return node;
}

// Função para obter a altura de um nó
int alturaAVL(AVL *node)
{
    if (node == NULL)
        return 0;
    else
    {
        int alt_esq = alturaAVL(node->esquerda);
        int alt_dir = alturaAVL(node->direita);
        // Seleciona a maior altura entre as subarvores da direita e esquerda
        if (alt_esq > alt_dir)
            return (alt_esq + 1);
        else
            return (alt_dir + 1);
    }
}
int alturaAVP(AVP *node)
{
    if (node == NULL)
        return 0;
    else
    {
        int alt_esq = alturaAVP(node->esquerda);
        int alt_dir = alturaAVP(node->direita);
        // Seleciona a maior altura entre as subarvores da direita e esquerda
        if (alt_esq > alt_dir)
            return (alt_esq + 1);
        else
            return (alt_dir + 1);
    }
}

// Função para obter a altura negra
int alturaNegra(AVP *node)
{
    if (node == NULL)
        return 0;
    else
    {
        int alt_esq = alturaNegra(node->esquerda);
        int alt_dir = alturaNegra(node->direita);
        // Seleciona a maior altura entre as subarvores da direita e esquerda
        if (alt_esq > alt_dir)
        {
            if ((node->esquerda == NULL) || (node->esquerda->cor == 0))
                return alt_esq;
            else
                return alt_esq + 1;
        }
        else
        {
            if ((node->direita == NULL) || (node->direita->cor == 0))
                return alt_dir;
            else
                return alt_dir + 1;
        }
    }
}

// Função para obter o máximo de dois inteiros
int max(int x, int y)
{
    return (x > y) ? x : y;
}

// Função para ratação simples à direita
AVL *LLrotationAVL(AVL *n, int *rotacao)
{
    AVL *pA = n;
    AVL *pB = pA->esquerda;

    // Realiza a rotação
    pA->esquerda = pB->direita;
    pB->direita = pA;

    *rotacao = *rotacao + 1;

    return pB;
}
AVP *LLrotationAVP(AVP *n, int *rotacao)
{
    AVP *pA = n;
    AVP *pB = pA->esquerda;
    int Lado;            // 0 = Esquerda, 1 = Direita
    if (pA->pai != NULL) // Verifica de qual lado o nó está
    {
        if (pA->pai->esquerda == pA)
            Lado = 0;
        else
            Lado = 1;
    }
    // Realiza a rotação
    pA->esquerda = pB->direita;
    pB->direita = pA;
    pB->pai = pA->pai;
    pA = pB;
    // Atualiza o pai do nó
    if (pA->esquerda != NULL)
        pA->esquerda->pai = pA;
    if (pA->direita != NULL)
        pA->direita->pai = pA;
    if (pA->direita->esquerda != NULL)
        pA->direita->esquerda->pai = pA->direita;
    if (pA->pai != NULL)
    {
        if (Lado == 0)
            pA->pai->esquerda = pA;
        else
            pA->pai->direita = pA;
    }

    *rotacao = *rotacao + 1;

    return pA;
}

// Função para rotação simples à esquerda
AVL *RRrotationAVL(AVL *n, int *rotacao)
{
    AVL *pA = n;
    AVL *pB = pA->direita;

    // Realiza a rotação
    pA->direita = pB->esquerda;
    pB->esquerda = pA;

    *rotacao = *rotacao + 1;

    return pB;
}
AVP *RRrotationAVP(AVP *n, int *rotacao)
{
    AVP *pA = n;
    AVP *pB = pA->direita;
    int Lado;
    if (pA->pai != NULL) // Verifica de qual lado o nó está
    {
        if (pA->pai->esquerda == pA)
            Lado = 0;
        else
            Lado = 1;
    }
    // Realiza a rotação
    pA->direita = pB->esquerda;
    pB->esquerda = pA;
    pB->pai = pA->pai;
    pA = pB;
    // Atualiza o pai do nó
    if (pA->esquerda != NULL)
        pA->esquerda->pai = pA;
    if (pA->direita != NULL)
        pA->direita->pai = pA;
    if (pA->esquerda->direita != NULL)
        pA->esquerda->direita->pai = pA->esquerda;
    if (pA->pai != NULL)
    {
        if (Lado == 0)
            pA->pai->esquerda = pA;
        else
            pA->pai->direita = pA;
    }

    *rotacao = *rotacao + 1;

    return pA;
}

// Função para rotação dupla à direita
AVL *LRrotationAVL(AVL *n, int *rotacao)
{
    AVL *pA = n;
    pA->direita = LLrotationAVL(pA->direita, rotacao);

    *rotacao = *rotacao - 1;

    return RRrotationAVL(pA, rotacao);
}

// Função para rotação dupla à esquerda
AVL *RLrotationAVL(AVL *n, int *rotacao)
{
    AVL *pA = n;
    pA->esquerda = RRrotationAVL(pA->esquerda, rotacao);

    *rotacao = *rotacao - 1;

    return LLrotationAVL(pA, rotacao);
}

// Função para balancear a árvore AVL
int balanceamento(AVL *node)
{
    if (node == NULL)
        return 0;
    return alturaAVL(node->esquerda) - alturaAVL(node->direita);
}

// Função para inserir um nó na árvore AVL
AVL *inserirAVL(AVL *node, int chave, int *rotacao)
{
    // Passo 1: inserção normal de um nó
    if (node == NULL)
        return novoNoAVL(chave);

    if (chave < node->chave)
        node->esquerda = inserirAVL(node->esquerda, chave, rotacao);
    else if (chave > node->chave)
        node->direita = inserirAVL(node->direita, chave, rotacao);
    else // chaves iguais não são permitidas na árvore AVL
        return node;

    // Passo 2: atualizar a altura deste nó ancestral
    // node->altura = 1 + max(alturaAVL(node->esquerda), alturaAVL(node->direita));

    // Passo 3: obter o fator de balanceamento deste nó ancestral
    int fb = balanceamento(node);

    // Se o nó ficar desbalanceado, então haverá 4 casos possíveis:

    // Caso da rotação simples à direita
    if (fb > 1 && chave < node->esquerda->chave)
        return LLrotationAVL(node, rotacao);

    // Caso da rotação simples à esquerda
    if (fb < -1 && chave > node->direita->chave)
        return RRrotationAVL(node, rotacao);

    // Caso da rotação dupla à direita
    if (fb > 1 && chave > node->esquerda->chave)
        return RLrotationAVL(node, rotacao);

    // Caso da rotação dupla à esquerda
    if (fb < -1 && chave < node->direita->chave)
        return LRrotationAVL(node, rotacao);

    // Se o nó não estiver desbalanceado, retorne o próprio nó
    return node;
}

// Função para buscar uma chave na árvore Rubro Negra
AVP *pesquisa(AVP *root, int chave)
{
    if (root == NULL)
        return NULL;
    if (root->chave == chave)
        return root;
    else
    {
        if (chave > root->chave)
            return pesquisa(root->direita, chave);
        if (chave < root->chave)
            return pesquisa(root->esquerda, chave);
    }
    return NULL;
}

// Função para inserir um nó na árvore Rubro Negra
AVP *inserirAVP(AVP *root, int chave)
{
    AVP *node;
    if (root == NULL)
    {
        node = novoNoAVP(chave);
        return node;
    }
    if (chave > root->chave)
    {
        root->direita = inserirAVP(root->direita, chave);
        root->direita->pai = root;
    }
    else
    {
        root->esquerda = inserirAVP(root->esquerda, chave);
        root->esquerda->pai = root;
    }
    return root;
}

// Função para corrigir a árvore Rubro Negra de acordo com as propriedades
AVP *corrigirAVP(AVP *root, AVP *inserido, int *rotacao, int *mudancaCor)
{
    AVP *pai, *avo, *tio;
    // Condições para a correção da Árvore Rubro Negra
    while ((inserido != root) && (inserido->cor == 0) && (inserido->pai->cor == 0))
    {
        pai = inserido->pai;
        if (pai->pai == root)
            avo = root;
        else
            avo = pai->pai;
        // Caso A
        if (pai == avo->esquerda)
        {
            tio = avo->direita;
            if ((tio != NULL) && (tio->cor == 0)) // Caso 1
            {
                pai->cor = 1;
                tio->cor = 1;
                avo->cor = 0;
                inserido = avo;
                *mudancaCor = *mudancaCor + 3;
            }
            else
            {
                if (inserido == pai->direita) // Caso 2
                {
                    inserido = pai;
                    pai = RRrotationAVP(pai, rotacao);
                }
                else // Caso 3
                {
                    pai = LLrotationAVP(avo, rotacao);
                    if (pai->pai == NULL)
                        root = pai;
                    pai->cor = 1;
                    pai->esquerda->cor = 0;
                    pai->direita->cor = 0;
                    inserido = pai;
                    *mudancaCor = *mudancaCor + 2;
                }
            }
        }
        else // Caso B
        {
            tio = avo->esquerda;
            if ((tio != NULL) && (tio->cor == 0)) // Caso 1
            {
                pai->cor = 1;
                tio->cor = 1;
                avo->cor = 0;
                inserido = avo;
                *mudancaCor = *mudancaCor + 3;
            }
            else
            {
                if (inserido == pai->esquerda) // Caso 2
                {
                    inserido = pai;
                    pai = LLrotationAVP(pai, rotacao);
                }
                else // Caso 3
                {
                    pai = RRrotationAVP(avo, rotacao);
                    if (pai->pai == NULL)
                        root = pai;
                    pai->cor = 1;
                    pai->esquerda->cor = 0;
                    pai->direita->cor = 0;
                    inserido = pai;
                    *mudancaCor = *mudancaCor + 2;
                }
            }
        }
    }
    root->cor = 1;
    if (root->cor == 0)
    {
        root->cor = 1;
        *mudancaCor = *mudancaCor + 1;
    }

    return root;
}

// Libera memória da Árvore
void PosOrdem_FreeAVL(AVL *root)
{
    if (root != NULL)
    {
        PosOrdem_FreeAVL(root->esquerda);
        PosOrdem_FreeAVL(root->direita);
        free(root);
    }
}
void PosOrdem_FreeAVP(AVP *root)
{
    if (root != NULL)
    {
        PosOrdem_FreeAVP(root->esquerda);
        PosOrdem_FreeAVP(root->direita);
        free(root);
    }
}

int main()
{
    AVL *rootAVL = NULL;
    inicializarAVL(rootAVL);
    AVP *rootAVP = NULL;
    inicializarAVP(rootAVP);
    AVP *inserido;

    int chave;
    int blackHeight;
    int mudancaCor = 0;
    int rotacaoAVP = 0;
    int rotacaoAVL = 0;

    // Insere as chaves nas árvores AVL e Rubro Negra
    scanf("%d", &chave);
    while (chave > 0)
    {
        rootAVL = inserirAVL(rootAVL, chave, &rotacaoAVL);
        rootAVP = inserirAVP(rootAVP, chave);
        inserido = pesquisa(rootAVP, chave);
        rootAVP = corrigirAVP(rootAVP, inserido, &rotacaoAVP, &mudancaCor);
        scanf("%d", &chave);
    }

    // Imprime a altura máxima da árvore AVL e a altura das subárvores
    printf("%d, %d, %d\n", alturaAVL(rootAVL) - 1, alturaAVL(rootAVL->esquerda), alturaAVL(rootAVL->direita));

    // Imprime a altura máxima da árvore Rubro Negra e a altura das subárvores
    printf("%d, %d, %d\n", alturaAVP(rootAVP) - 1, alturaAVP(rootAVP->esquerda), alturaAVP(rootAVP->direita));

    // Imprime a altura negra da árvore Rubro Negra
    blackHeight = alturaNegra(rootAVP);
    if (rootAVP->cor == 1)
        blackHeight = blackHeight + 1;
    printf("%d\n", blackHeight);

    // Imprime o número de mudanças de cor e de rotações realizadas nas árvores
    printf("%d, %d, %d\n", mudancaCor, rotacaoAVP, rotacaoAVL);

    PosOrdem_FreeAVP(rootAVP);
    PosOrdem_FreeAVL(rootAVL);

    return 0;
}