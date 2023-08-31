#include <stdio.h>
#include <stdlib.h>
#include "arvore_avl.h"

int main(int argc, char *argv[]) {
    No *raiz = NULL;

    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 30);

    printf("Arvore AVL em ordem: ");
    percorrer_em_ordem(raiz);
    printf("\n");

    int chave_busca = 20;
    No *no_encontrado = buscar(raiz, chave_busca);
    if (no_encontrado)
        printf("Chave %d encontrada!\n", chave_busca);
    else
        printf("Chave %d nao encontrada.\n", chave_busca);

    int chave_exclusao = 20;
    raiz = excluir(raiz, chave_exclusao);
    printf("Arvore AVL apos exclusao: ");
    percorrer_em_ordem(raiz);
    printf("\n");

    return 0;
}
