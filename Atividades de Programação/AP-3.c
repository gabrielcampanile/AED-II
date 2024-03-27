// Gabriel Belchior Vieira Campanile - RA 168853
// AED II - Turma IA

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct TipoItem
{
    int num;
    struct TipoItem *prox;
} TipoItem;

typedef struct
{
    TipoItem *inicio, *fim;
} TipoLista;

void inicializaLista(TipoLista *lista)
{
    lista->inicio = NULL;
    lista->fim = NULL;
}

void insereNoFinal(TipoLista *lista, int valor)
{
    TipoItem *novoNo = malloc(sizeof(TipoItem));
    novoNo->num = valor;
    novoNo->prox = NULL;

    if (lista->fim == NULL)
    { // Lista vazia
        lista->inicio = novoNo;
        lista->fim = novoNo;
    }
    else
    {
        lista->fim->prox = novoNo;
        lista->fim = novoNo;
    }
}

void imprimeLista(TipoLista *lista)
{
    TipoItem *atual = lista->inicio;
    while (atual != NULL)
    {
        printf("%d ", atual->num);
        atual = atual->prox;
    }
    printf("\n");
}

void esvaziarLista(TipoLista *lista)
{
    TipoItem *aux = lista->inicio;
    while (aux->prox != NULL)
    {
        lista->inicio = aux->prox;
        free(aux);
        aux = lista->inicio;
    }

    free(aux);
}

TipoItem* merge(TipoItem *left, TipoItem *right) {
    TipoItem *result = NULL;

    if (left == NULL)
        return right;
    if (right == NULL)
        return left;

    if (left->num <= right->num) {
        result = left;
        result->prox = merge(left->prox, right);
    } else {
        result = right;
        result->prox = merge(left, right->prox);
    }

    return result;
}

TipoItem* merge_sort(TipoItem *head) {
    if (head == NULL || head->prox == NULL)
        return head;

    TipoItem *slow = head;
    TipoItem *fast = head->prox;

    while (fast != NULL && fast->prox != NULL) {
        slow = slow->prox;
        fast = fast->prox->prox;
    }

    TipoItem *middle = slow->prox;
    slow->prox = NULL;

    TipoItem *left = merge_sort(head);
    TipoItem *right = merge_sort(middle);

    return merge(left, right);
}

// void merge(TipoLista *lista, TipoItem *middle, int n) {
    
// }

// TipoItem *merge_sort(TipoItem *head) {
//     TipoItem *middle, *aux = lista->inicio;
//     int m = ceil(n/2);
//     if(n>1) {
//         for(int i=0; i<m; i++) {
//             middle = aux->prox;
//             aux = aux->prox;
//         }
//         merge_sort(lista, m);
//         merge_sort(&middle, n-m);
//         merge(lista, middle, n);
//     }
// }

int main()
{
    TipoLista lista;
    TipoItem novo;
    inicializaLista(&lista);

    int n, p;
    scanf("%i", &n);

    p = ceil(log2(n)); //profundidade

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &novo.num);
        insereNoFinal(&lista, novo.num);
    }

    lista.inicio = merge_sort(lista.inicio);

    // printf("Elementos na lista:\n");
    imprimeLista(&lista);
    printf("%i", p);

    esvaziarLista(&lista);

    return 0;
}