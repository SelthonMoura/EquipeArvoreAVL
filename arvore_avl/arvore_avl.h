#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó da árvore AVL
typedef struct No
{
    int chave;
    struct No *esquerda;
    struct No *direita;
    int altura;
} No;

// Função para criar um novo nó
No *criar_no(int chave)
{
    No *novo_no = (No *)malloc(sizeof(No));
    novo_no->chave = chave;
    novo_no->esquerda = NULL;
    novo_no->direita = NULL;
    novo_no->altura = 1;

    return novo_no;
}

// Função para calcular a altura de um nó
int altura(No *no)
{

    if (no == NULL)
        return 0;

    return no->altura;
}

// Função para calcular o fator de balanceamento de um nó
int fator_balanceamento(No *no)
{

    if (no == NULL)
        return 0;

    return altura(no->esquerda) - altura(no->direita);
}

// Função para atualizar a altura de um nó
void atualizar_altura(No *no)
{
    int altura_esquerda = altura(no->esquerda);
    int altura_direita = altura(no->direita);
    no->altura = (altura_esquerda > altura_direita ? altura_esquerda : altura_direita) + 1;
}

// Função para fazer uma rotação simples à esquerda
No *rotacao_esquerda(No *raiz)
{
    No *nova_raiz = raiz->direita;
    raiz->direita = nova_raiz->esquerda;
    nova_raiz->esquerda = raiz;
    atualizar_altura(raiz);
    atualizar_altura(nova_raiz);

    return nova_raiz;
}

// Função para fazer uma rotação simples à direita
No *rotacao_direita(No *raiz)
{
    No *nova_raiz = raiz->esquerda;
    raiz->esquerda = nova_raiz->direita;
    nova_raiz->direita = raiz;
    atualizar_altura(raiz);
    atualizar_altura(nova_raiz);

    return nova_raiz;
}

// Função para balancear um nó
No *balancear_no(No *no)
{
    atualizar_altura(no);

    int fb = fator_balanceamento(no);

    if (fb > 1)
    {
        if (fator_balanceamento(no->esquerda) < 0)
            no->esquerda = rotacao_esquerda(no->esquerda);

        return rotacao_direita(no);
    }

    if (fb < -1)
    {
        if (fator_balanceamento(no->direita) > 0)
            no->direita = rotacao_direita(no->direita);

        return rotacao_esquerda(no);
    }

    return no;
}

// Função para inserir uma chave na árvore AVL
No *inserir(No *raiz, int chave)
{
    if (raiz == NULL)
        return criar_no(chave);

    if (chave < raiz->chave)
        raiz->esquerda = inserir(raiz->esquerda, chave);

    else if (chave > raiz->chave)
        raiz->direita = inserir(raiz->direita, chave);

    else
        return raiz;  // Não permite chaves duplicadas

    return balancear_no(raiz);
}

// Função para percorrer a árvore em ordem
void percorrer_em_ordem(No *raiz)
{
    if (raiz != NULL)
    {
        percorrer_em_ordem(raiz->esquerda);
        printf("\n\t%d ", raiz->chave);
        percorrer_em_ordem(raiz->direita);
    }
}

// Função para encontrar o nó com a menor chave
No *encontra_menor(No *raiz)
{
    No *atual = raiz;

    while (atual->esquerda != NULL)
        atual = atual->esquerda;

    return atual;
}

// Função para excluir um nó na árvore AVL
No *excluir(No *raiz, int chave)
{
    if (raiz == NULL)
        return raiz;

    if (chave < raiz->chave)
        raiz->esquerda = excluir(raiz->esquerda, chave);

    else if (chave > raiz->chave)
        raiz->direita = excluir(raiz->direita, chave);

    else {
        if (raiz->esquerda == NULL || raiz->direita == NULL)
        {
            No *temp = raiz->esquerda ? raiz->esquerda : raiz->direita;

            if (temp == NULL)
            {
                temp = raiz;
                raiz = NULL;

            } else
                *raiz = *temp;

            free(temp);
        } else {
            No *temp = encontra_menor(raiz->direita);
            raiz->chave = temp->chave;
            raiz->direita = excluir(raiz->direita, temp->chave);
        }
    }

    if (raiz == NULL)
        return raiz;

    return balancear_no(raiz);
}

// Função para buscar uma chave na árvore AVL
No *buscar(No *raiz, int chave)
{
    if (raiz == NULL || raiz->chave == chave)
        return raiz;

    if (chave < raiz->chave)
        return buscar(raiz->esquerda, chave);

    return buscar(raiz->direita, chave);
}
