#include <stdio.h>
#include "arvore_AVL.h"

int main(int argc, char* argv[])
{
    int vetor[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    No* raiz = criar();

    for(int i=0;i<10;i++)
    {
        inserir(raiz, vetor[i]);
    }

    imprimir(raiz, 1);
}