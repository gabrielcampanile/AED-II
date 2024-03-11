#include <stdio.h>
#include <math.h>

int cashback(int d, int v, int l)
{
    int credito = d;
    credito = d % v;
    d = d / v;
    l += d;
    // printf("%i credito\n", credito);
    // printf("%i dinheiro\n", d);
    // printf("%i livros\n", l);
    
    int cash;
    cash = d + credito;

    if (cash >= v)
        return cashback(cash, v, l);
    else
        return l;
}

int main()
{
    int N, d, p, v, livros;

    scanf("%d", &N);

    for (int i = 0; i < N; i++)
    {
        livros = 0;
        scanf("%d %d %d", &d, &p, &v);
        livros = d / p;
        d = livros;
        // printf("%i dinheiro\n", d);
        // printf("%i livros\n", livros);
        livros = cashback(d, v, livros);

        printf("%i\n", livros);
    }

    return 0;
}
