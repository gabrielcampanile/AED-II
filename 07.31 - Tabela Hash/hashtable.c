#include <stdio.h>
#include <stdlib.h>

typedef struct Item
{
    int chave;
    struct Item *prox;
} Item;

int hash(int chave, int m)
{
    return chave % m;
}

void inicializa(Item **tabela, int m)
{
    for (int i = 0; i < m; i++)
    {
        tabela[i] = NULL;
    }
}

Item *criaItem(int chave)
{
    Item *novo = (Item *)malloc(sizeof(Item));
    novo->chave = chave;
    novo->prox = NULL;
    return novo;
}

void insereItem(Item **tabela, int chave, int m)
{
    int h = hash(chave, m);
    Item *novo = criaItem(chave);

    if (tabela[h] == NULL)
    {
        tabela[h] = novo;
        return;
    }
    else
    {
        Item *aux = tabela[h];
        while (aux->prox != NULL)
        {
            aux = aux->prox;
        }
        aux->prox = novo;
    }
}

void removeItem(Item **tabela, int chave, int m)
{
    int h = hash(chave, m);
    Item *aux = tabela[h];
    Item *ant = NULL;

    while (aux != NULL && aux->chave != chave)
    {
        ant = aux;
        aux = aux->prox;
    }

    if (aux == NULL)
    {
        return;
    }

    if (ant == NULL)
    {
        tabela[h] = aux->prox;
    }
    else
    {
        ant->prox = aux->prox;
    }

    free(aux);
}

int busca(Item **tabela, int chave, int m)
{
    int h = hash(chave, m);
    Item *aux = tabela[h];

    while (aux != NULL && aux->chave != chave)
    {
        aux = aux->prox;
    }

    if (aux == NULL)
    {
        return 0;
    }
    else
    {
        removeItem(tabela, chave, m);
        return 1;
    }
}

void imprime(Item **tabela, int m)
{
    for (int i = 0; i < m; i++)
    {
        printf("%d: ", i);
        Item *aux = tabela[i];
        while (aux != NULL)
        {
            printf("%d ", aux->chave);
            aux = aux->prox;
        }
        printf("\n");
    }
}

void imprimeLinha(Item **tabela, int m, int i)
{
    printf("[%d] ", i);
    Item *aux = tabela[i];
    while (aux != NULL)
    {
        printf("%d ", aux->chave);
        aux = aux->prox;
    }
    printf("\n");
}

int main()
{
    int m, n, b, l;

    // inicializa a tabela hash
    scanf("%d", &m);
    Item **tabela = (Item **)malloc(m * sizeof(Item *));
    inicializa(tabela, m);

    // insere os elementos na tabela hash
    while (n >= 0)
    {
        scanf("%d", &n);
        if (n >= 0)
        {
            insereItem(tabela, n, m);
        }
    }

    // imprime a tabela hash
    // imprime(tabela, m);

    // busca e remove chave na tabela hash
    scanf("%d", &b);
    if (!busca(tabela, b, m))
    {
        printf("Valor nao encontrado\n");
    }

    // imprime a linha da tabela hash
    scanf("%d", &l);
    imprimeLinha(tabela, m, l);

    return 0;
}