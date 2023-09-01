/* 
   Curso: Sistemas de Informação
   Disciplina: Algoritmos e Estruturas de Dados
   Alunos: Francisco Araujo Loureiro Neto 2215310037
   Giulia Salles Feitosa 2215310010
   Juliene Witoria Viana Barros Araujo 2215310040
   Leonardo Castro Da Silva 2215310016
   Lucas Almeida Trovao 2215310018
   Rahilson Dias Costa 2215310025
   Selthon Noronha De Moura 2215310028
   Victor Emanuel Barros De Lima 2215310048   
*/

#include <stdio.h>
#include <stdlib.h>
#include "arvore_avl.h"

int main(int argc, char *argv[]) {
    No *raiz = NULL;

    raiz = inserir(raiz, 42);
    raiz = inserir(raiz, 15);
    raiz = inserir(raiz, 88);
    raiz = inserir(raiz, 6);
    raiz = inserir(raiz, 27);
    raiz = inserir(raiz, 63);
    raiz = inserir(raiz, 94);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 57);
    raiz = inserir(raiz, 71);

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
