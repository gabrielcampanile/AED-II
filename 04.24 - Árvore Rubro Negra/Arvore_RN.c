// Programa de Árvore Rubro-Negra
#include <stdio.h>
#include <stdlib.h>

// Estrutura dos nós
typedef struct SCelula
{
    int Cor; // Rubro = 0, Negro = 1
    int Value;
    struct SCelula *Direita, *Esquerda, *Pai;
} Celula;

// Função que cria nós
Celula *Cria_Node(int Value)
{
    Celula *Node;
    Node = malloc(sizeof(Celula));
    Node->Direita = NULL;
    Node->Esquerda = NULL;
    Node->Pai = NULL;
    Node->Value = Value;
    Node->Cor = 0;
    return (Node);
}

// Inicia Arvore como NULL
Celula *Arvore_Inicia(Celula *Arvore)
{
    Arvore = NULL;
    return Arvore;
}

// Verifica se o nó é um nó folha
int Verifica_Folha(Celula *Node)
{
    if (Node->Direita == NULL && Node->Esquerda == NULL)
    {
        return 1;
    }

    return 0;
}

// Encontra a Altura do nó
int Altura_Node(Celula *Node)
{
    if (Node == NULL)
    {
        return 0;
    }
    else
    {
        int Alt_Esq;
        Alt_Esq = Altura_Node(Node->Esquerda);
        int Alt_Dir;
        Alt_Dir = Altura_Node(Node->Direita);

        if (Alt_Esq > Alt_Dir)
        {
            return (Alt_Esq + 1);
        }
        else
        {
            return (Alt_Dir + 1);
        }
    }
}

// Encontra a Altura Negra
int Altura_Negra(Celula *Node)
{
    if (Node == NULL)
    {
        return 0;
    }
    else
    {
        int Alt_Esq;
        Alt_Esq = Altura_Negra(Node->Esquerda);
        int Alt_Dir;
        Alt_Dir = Altura_Negra(Node->Direita);
        // Seleciona a maior altura entre as subarvores da direita e esquerda
        if (Alt_Esq > Alt_Dir)
        {
            if ((Node->Esquerda == NULL) || (Node->Esquerda->Cor == 0))
            {
                return (Alt_Esq);
            }
            else
            {
                return (Alt_Esq + 1);
            }
        }
        else
        {
            if ((Node->Direita == NULL) || (Node->Direita->Cor == 0))
            {
                return (Alt_Dir);
            }
            else
            {
                return (Alt_Dir + 1);
            }
        }
    }
}

// Encontra a Altura Rubra
int Altura_Rubra(Celula *Node)
{
    if (Node == NULL)
    {
        return 0;
    }
    else
    {
        int Alt_Esq;
        Alt_Esq = Altura_Rubra(Node->Esquerda);
        int Alt_Dir;
        Alt_Dir = Altura_Rubra(Node->Direita);
        // Seleciona a maior altura entre as subarvores da direita e esquerda
        if (Alt_Esq > Alt_Dir)
        {
            if ((Node->Esquerda == NULL) || (Node->Esquerda->Cor == 1))
            {
                return (Alt_Esq);
            }
            else
            {
                return (Alt_Esq + 1);
            }
        }
        else
        {
            if ((Node->Direita == NULL) || (Node->Direita->Cor == 1))
            {
                return (Alt_Dir);
            }
            else
            {
                return (Alt_Dir + 1);
            }
        }
    }
}

// Realiza pesquisa binária
Celula *Pesquisa_ArvBin(Celula *Arvore, int Key)
{
    if (Arvore == NULL)
    {
        return NULL;
    }
    if (Key == Arvore->Value)
    {
        return Arvore;
    }
    else
    {
        if (Key > Arvore->Value)
        {
            return (Pesquisa_ArvBin(Arvore->Direita, Key));
        }
        if (Key < Arvore->Value)
        {
            return (Pesquisa_ArvBin(Arvore->Esquerda, Key));
        }
    }
    return NULL;
}

// Libera memória da Árvore
void PosOrdem_Free(Celula *Raiz)
{
    if (Raiz != NULL)
    {
        PosOrdem_Free(Raiz->Esquerda);
        PosOrdem_Free(Raiz->Direita);
        free(Raiz);
    }
}

/*
Rotação LL
pB = pA->Esq;
pA->Esq = pB->Dir;
pB->Dir = pA;
pA = pB;
*/
Celula *Rotate_LL(Celula *Raiz)
{
    Celula *AuxB;
    int Lado;              // 0 = Esquerda, 1 = Direita
    if (Raiz->Pai != NULL) // Verifica de qual lado o nó está
    {
        if (Raiz->Pai->Direita == Raiz)
        {
            Lado = 1;
        }
        else
        {
            Lado = 0;
        }
    }
    AuxB = Raiz->Esquerda;
    Raiz->Esquerda = AuxB->Direita;
    AuxB->Direita = Raiz;
    AuxB->Pai = Raiz->Pai;
    Raiz = AuxB;
    if (Raiz->Esquerda != NULL)
    {
        Raiz->Esquerda->Pai = Raiz;
    }
    if (Raiz->Direita != NULL)
    {
        Raiz->Direita->Pai = Raiz;
    }
    if (Raiz->Direita->Esquerda != NULL)
    {
        Raiz->Direita->Esquerda->Pai = Raiz->Direita;
    }
    if (Raiz->Pai != NULL)
    {
        // Com base no lado inicial, atualiza o pai do nó
        if (Lado == 1)
        {
            Raiz->Pai->Direita = Raiz;
        }
        else
        {
            Raiz->Pai->Esquerda = Raiz;
        }
    }
    return Raiz;
}

/*
Rotação RR
pB = pA->Dir;
pA->Dir = pB->Esq;
pB->Esq = pA;
pA = pB;
*/
Celula *Rotate_RR(Celula *Raiz)
{
    Celula *AuxB;
    int Lado;              // 0 = Esquerda, 1 = Direita
    if (Raiz->Pai != NULL) // Verifica de qual lado o nó está
    {
        if (Raiz->Pai->Direita == Raiz)
        {
            Lado = 1;
        }
        else
        {
            Lado = 0;
        }
    }
    AuxB = Raiz->Direita;
    Raiz->Direita = AuxB->Esquerda;
    AuxB->Esquerda = Raiz;
    AuxB->Pai = Raiz->Pai;
    Raiz = AuxB;

    if (Raiz->Esquerda != NULL)
    {
        Raiz->Esquerda->Pai = Raiz;
    }
    if (Raiz->Direita != NULL)
    {
        Raiz->Direita->Pai = Raiz;
    }
    if (Raiz->Esquerda->Direita != NULL)
    {
        Raiz->Esquerda->Direita->Pai = Raiz->Esquerda;
    }
    if (Raiz->Pai != NULL)
    {
        // Com base no lado inicial, atualiza o pai do nó
        if (Lado == 1)
        {
            Raiz->Pai->Direita = Raiz;
        }
        else
        {
            Raiz->Pai->Esquerda = Raiz;
        }
    }
    return Raiz;
}

// Encontra o sucessor do nó
Celula *Sucessor(Celula *Raiz)
{
    Celula *Aux;
    if (Raiz->Direita != NULL)
    {
        Aux = Raiz->Direita;
        while (Aux->Esquerda != NULL)
        {
            Aux = Aux->Esquerda;
        }
    }
    return Aux;
}

// Função que corrige a Arvore conforme as propriedades
Celula *Corrige_Arvore_Insere(Celula *Raiz, Celula *Inserido)
{
    Celula *Pai, *Avo, *Tio;
    int Color;
    // Condições para a correção da Árvore
    while ((Inserido != Raiz) && (Inserido->Cor == 0) && (Inserido->Pai->Cor == 0))
    {
        Pai = Inserido->Pai;
        if (Pai->Pai == Raiz)
        {
            Avo = Raiz;
        }
        else
        {
            Avo = Pai->Pai;
        }
        if (Pai == Avo->Esquerda) // Caso A
        {
            Tio = Avo->Direita;
            if ((Tio != NULL) && (Tio->Cor == 0)) // Caso 1
            {
                Pai->Cor = 1;
                Tio->Cor = 1;
                Avo->Cor = 0;
                Inserido = Avo;
            }
            else
            {
                if (Inserido == Pai->Direita) // Caso 2
                {
                    Inserido = Pai;
                    Pai = Rotate_RR(Pai);
                }
                else // Caso 3
                {
                    Pai = Rotate_LL(Avo);
                    if (Pai->Pai == NULL)
                    {
                        Raiz = Pai;
                    }
                    Pai->Cor = 1;
                    Pai->Esquerda->Cor = 0;
                    Pai->Direita->Cor = 0;
                    Inserido = Pai;
                }
            }
        }
        else // Caso B
        {
            Tio = Avo->Esquerda;
            if ((Tio != NULL) && (Tio->Cor == 0)) // Caso 1
            {
                Pai->Cor = 1;
                Tio->Cor = 1;
                Avo->Cor = 0;
                Inserido = Avo;
            }
            else
            {
                if (Inserido == Pai->Esquerda) // Caso 2
                {
                    Inserido = Pai;
                    Pai = Rotate_LL(Pai);
                }
                else // Caso 3
                {
                    Pai = Rotate_RR(Avo);
                    if (Pai->Pai == NULL)
                    {
                        Raiz = Pai;
                    }
                    Pai->Cor = 1;
                    Pai->Esquerda->Cor = 0;
                    Pai->Direita->Cor = 0;
                    Inserido = Pai;
                }
            }
        }
    }
    Raiz->Cor = 1;
    return Raiz;
}

// Função de inserção
Celula *Insere_Arvore_RN(Celula *Raiz, int Value)
{
    Celula *Node;
    if (Raiz == NULL)
    {
        Node = Cria_Node(Value);
        return Node;
    }

    if (Value > Raiz->Value)
    {
        Raiz->Direita = Insere_Arvore_RN(Raiz->Direita, Value);
        Raiz->Direita->Pai = Raiz; // Atualiza o Pai do nó
    }
    if (Value < Raiz->Value)
    {
        Raiz->Esquerda = Insere_Arvore_RN(Raiz->Esquerda, Value);
        Raiz->Esquerda->Pai = Raiz; // Atualiza o Pai do nó
    }
    return Raiz;
}

Celula *Corrige_Arvore_Remove(Celula *Substituto)
{
    Celula *Pai, *Irmao, *Raiz;
    Raiz = Substituto;
    while (Raiz->Pai != NULL)
    {
        Raiz = Raiz->Pai;
    }
    while ((Substituto->Pai != NULL && (Substituto->Cor == 1)))
    {
        Pai = Substituto->Pai;
        if (Substituto == Pai->Esquerda)
        {
            Irmao = Pai->Direita;
            if (Irmao == NULL)
            {
                return Raiz;
            }
            if ((Irmao != NULL) && (Irmao->Cor == 0))
            {
                Irmao->Cor = 1;
                Pai->Cor = 0;
                Pai = Rotate_RR(Pai);
                Irmao = Pai->Direita;
            }
            else
            {
                if (((Irmao->Direita == NULL) || (Irmao->Direita->Cor == 1)) && ((Irmao->Esquerda == NULL) || (Irmao->Esquerda->Cor == 1)))
                {
                    Irmao->Cor = 0;
                    Substituto = Pai;
                }
                else
                {
                    if ((Irmao->Direita == NULL) || (Irmao->Direita->Cor == 1))
                    {
                        Irmao->Esquerda->Cor = 1;
                        Irmao->Cor = 0;
                        Irmao = Rotate_LL(Irmao);
                    }
                    Irmao = Pai->Direita;
                    Irmao->Cor = Pai->Cor;
                    Pai->Cor = 1;
                    Irmao->Direita->Cor = 1;
                    Pai = Rotate_RR(Pai);
                    Substituto = Raiz;
                }
            }
        }
        else
        {
            Irmao = Pai->Esquerda;
            if (Irmao == NULL)
            {
                return Raiz;
            }
            if ((Irmao != NULL) && (Irmao->Cor == 0))
            {
                Irmao->Cor = 1;
                Pai->Cor = 0;
                Pai = Rotate_LL(Pai);
                Irmao = Pai->Esquerda;
            }
            else
            {
                if (((Irmao->Direita == NULL) || (Irmao->Direita->Cor == 1)) && ((Irmao->Esquerda == NULL) || (Irmao->Esquerda->Cor == 1)))
                {
                    Irmao->Cor = 0;
                    Substituto = Pai;
                }
                else
                {
                    if ((Irmao->Esquerda == NULL) || (Irmao->Esquerda->Cor == 1))
                    {
                        Irmao->Direita->Cor = 1;
                        Irmao->Cor = 0;
                        Irmao = Rotate_RR(Irmao);
                    }
                    Irmao = Pai->Esquerda;
                    Irmao->Cor = Pai->Cor;
                    Pai->Cor = 1;
                    Irmao->Esquerda->Cor = 1;
                    Pai = Rotate_LL(Pai);
                    Substituto = Raiz;
                }
            }
        }
    }
    Raiz->Cor = 1;
    Substituto->Cor = 1;
    return Raiz;
}

/*
Celula *Remove_Arvore_RN(Celula *Raiz, int Key)
{
    Celula *Removido;
    Removido = Pesquisa_ArvBin(Raiz, Key);
    if((Removido->Esquerda == NULL) || (Removido->Direita == NULL))
        {
            if(Verifica_Folha(Removido))
                {
                    if(Removido->Pai->Esquerda == Removido)
                        {
                            Removido->Pai->Esquerda = NULL;
                        }
                    else
                        {
                            Removido->Pai->Direita = NULL;
                        }
                }
            else
                {
                    if(Removido->Esquerda != NULL)
                        {
                            Removido->Pai->Direita = Removido->Esquerda;
                            Removido->Esquerda->Pai = Removido->Pai;
                        }
                    else
                        {
                            Removido->Pai->Esquerda = Removido->Direita;
                            Removido->Direita->Pai = Removido->Pai;
                        }
                }
        }
    else
        {
            Celula *Substituto = Sucessor(Removido);
            Removido->Value = Substituto->Value;
            Removido = Substituto;
        }
    Removido->Cor = 0;
    return Corrige_Arvore_Remove(Removido);
}*/

Celula *Remove_Arvore_RN(Celula *Raiz, int Key)
{
    int Correcao;
    Correcao = 0;

    if (Raiz == NULL)
    {
        return Raiz;
    }
    if (Raiz->Cor == 1)
    {
        Correcao = 1;
    }
    if (Key > Raiz->Value)
    {
        Raiz->Direita = Remove_Arvore_RN(Raiz->Direita, Key);
        Corrige_Arvore_Remove(Raiz);
    }

    if (Key < Raiz->Value)
    {
        Raiz->Esquerda = Remove_Arvore_RN(Raiz->Esquerda, Key);
        Corrige_Arvore_Remove(Raiz);
    }

    Celula *Aux;
    if (Raiz->Value == Key)
    {
        if ((Raiz->Direita == NULL) || (Raiz->Esquerda == NULL))
        {
            if (Verifica_Folha(Raiz))
            {
                Aux = Raiz;
                Raiz = NULL;
                free(Aux);
                return Raiz;
            }
            else
            {
                if (Raiz->Direita == NULL)
                {
                    Aux = Raiz;
                    Raiz = Aux->Esquerda;
                    free(Aux);
                    return Raiz;
                }
                else
                {
                    Aux = Raiz;
                    Raiz = Aux->Direita;
                    free(Aux);
                    return Raiz;
                }
            }
        }
        if (Raiz->Direita != NULL && Raiz->Esquerda != NULL)
        {
            Celula *Prox;
            Prox = Sucessor(Raiz);
            Raiz->Value = Prox->Value;
            Raiz->Direita = Remove_Arvore_RN(Raiz->Direita, Prox->Value);
            return Raiz;
        }
    }
    return Raiz;
}

// Cadeia Principal
int main()
{
    int k, Red_Height;
    Celula *Arvore, *Pesquisado;
    Arvore = Arvore_Inicia(Arvore);
    Arvore = NULL;
    // Insere a primeira linha de entrada
    scanf("%d", &k);
    while (k > 0)
    {
        Arvore = Insere_Arvore_RN(Arvore, k);
        Pesquisado = Pesquisa_ArvBin(Arvore, k);
        Arvore = Corrige_Arvore_Insere(Arvore, Pesquisado);
        scanf("%d", &k);
    }
    // Imprime a altura maxima da árvore e a altura das subarvores
    printf("%d, %d, %d\n", Altura_Node(Arvore) - 1, Altura_Node(Arvore->Esquerda), Altura_Node(Arvore->Direita));
    // Verifica se o elemento está na árvore e insere caso não esteja
    scanf("%d", &k);
    while (k > 0)
    {
        Pesquisado = Pesquisa_ArvBin(Arvore, k);
        if (Pesquisado == NULL)
        {
            Arvore = Insere_Arvore_RN(Arvore, k);
            Pesquisado = Pesquisa_ArvBin(Arvore, k);
            Arvore = Corrige_Arvore_Insere(Arvore, Pesquisado);
        }
        else
        {
            // Caso esteja na árvore, imprime a altura do nó e das subarvores e remove o nó
            printf("%d, %d, %d\n", Altura_Node(Pesquisado) - 1, Altura_Node(Pesquisado->Esquerda), Altura_Node(Pesquisado->Direita));
            Arvore = Remove_Arvore_RN(Arvore, k);
        }

        scanf("%d", &k);
    }
    // Pesquisa o elemento na árvore
    scanf("%d", &k);
    Pesquisado = Pesquisa_ArvBin(Arvore, k);
    if (Pesquisado == NULL)
    {
        // Caso não esteja na árvore, informa que não está na árvore
        printf("Valor nao encontrado\n");
    }
    else
    {
        // Caso esteja na árvore, imprime a altura rubra
        Red_Height = Altura_Rubra(Pesquisado);
        if (Pesquisado->Cor == 1)
        {
            Red_Height = Red_Height + 1;
        }
        printf("%d", Red_Height);
    }

    PosOrdem_Free(Arvore);

    return 0;
}

/*
6 4 3 2 1 5 7 8 -1
6 4 9 11 10 8 4 -1
9


*/