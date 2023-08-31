#include <stdio.h>
#include <stdlib.h>

typedef struct no* No;

struct no
{
    int info;
    int altura;
    struct no *esquerda;
    struct no *direita;
};

No* criar()
{
    No* raiz = (No*) malloc(sizeof(No));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void libera_NO(struct no* No)
{
    if(No == NULL)
        return;
    libera_NO(No->esquerda);
    libera_NO(No->direita);
    free(No);
    No = NULL;
}

void libera_ArvAVL(No* raiz)
{
    if(raiz == NULL)
        return;
    libera_NO(*raiz);
    free(raiz);
}

int altura_NO(struct no* No)
{
    if(No == NULL)
        return -1;
    else
    return No->altura;
}

int fatorBalanceamento(struct no* No)
{
    return labs(altura_NO(No->esquerda) - altura_NO(No->direita));
}

int maior(int x, int y)
{
    if(x > y)
        return x;
    else
        return y;
}

int estaVazia(No *raiz)
{
    if(raiz == NULL)
        return 1;
    if(*raiz == NULL)
        return 1;
    return 0;
}

int quantidade_no(No *raiz)
{
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int altura_esquerda = quantidade_no(&((*raiz)->esquerda));
    int altura_direita = quantidade_no(&((*raiz)->direita));
    int quantidade = altura_esquerda + altura_direita + 1;
    return quantidade;
}

int altura_ArvAVL(No *raiz)
{
    if (raiz == NULL || *raiz == NULL)
        return 0;
    int altura_esquerda = altura_ArvAVL(&((*raiz)->esquerda));
    int altura_direita = altura_ArvAVL(&((*raiz)->direita));
    if (altura_esquerda > altura_direita)
        return (altura_esquerda + 1);
    else
        return(altura_direita + 1);
}

void imprimir(No *raiz, int detalhe)
{
    if(raiz == NULL)
        return;
    if(*raiz != NULL)
    {
        imprimir(&((*raiz)->esquerda), detalhe);
        if (detalhe == 0)
            printf("%d\n",(*raiz)->info);
        if (detalhe == 1)
            printf("No %d: altura(%d) balaceamento(%d)\n",(*raiz)->info,altura_NO(*raiz),fatorBalanceamento(*raiz));
        imprimir(&((*raiz)->direita), detalhe);
    }
}

//=================================
void RotacaoLL(No *A)
{
    //printf("RotacaoLL\n");
    struct no *B;
    B = (*A)->esquerda;
    (*A)->esquerda = B->direita;
    B->direita = *A;
    (*A)->altura = maior(altura_NO((*A)->esquerda),altura_NO((*A)->direita)) + 1;
    B->altura = maior(altura_NO(B->esquerda),(*A)->altura) + 1;
    *A = B;
}

void RotacaoRR(No *A)
{
    //printf("RotacaoRR\n");
    struct no *B;
    B = (*A)->direita;
    (*A)->direita = B->esquerda;
    B->esquerda = (*A);
    (*A)->altura = maior(altura_NO((*A)->esquerda),altura_NO((*A)->direita)) + 1;
    B->altura = maior(altura_NO(B->direita),(*A)->altura) + 1;
    (*A) = B;
}

void RotacaoLR(No *A)
{
    RotacaoRR(&(*A)->esquerda);
    RotacaoLL(A);
}

void RotacaoRL(No *A)
{
    RotacaoLL(&(*A)->direita);
    RotacaoRR(A);
}

int inserir(No *raiz, int valor)
{
    int retorno;
    if(*raiz == NULL)
    {
        struct no *novo;
        novo = (struct no*)malloc(sizeof(struct no));
        if(novo == NULL)
            return 0;

        novo->info = valor;
        novo->altura = 0;
        novo->esquerda = NULL;
        novo->direita = NULL;
        *raiz = novo;
        return 1;
    }

    struct no *atual = *raiz;
    if(valor < atual->info)
    {
        if((retorno = inserir(&(atual->esquerda), valor)) == 1)
        {
            if(fatorBalanceamento(atual) >= 2)
            {
                if(valor < (*raiz)->esquerda->info )
                {
                    RotacaoLL(raiz);
                }else
                {
                    RotacaoLR(raiz);
                }
            }
        }
    }else
    {
        if(valor > atual->info)
        {
            if((retorno = inserir(&(atual->direita), valor)) == 1)
            {
                if(fatorBalanceamento(atual) >= 2)
                {
                    if((*raiz)->direita->info < valor)
                    {
                        RotacaoRR(raiz);
                    }else
                    {
                        RotacaoRL(raiz);
                    }
                }
            }
        }else
        {
            printf("Valor duplicado!!\n");
            return 0;
        }
    }

    atual->altura = maior(altura_NO(atual->esquerda),altura_NO(atual->direita)) + 1;

    return retorno;
}

struct no* procuraMenor(struct no* atual)
{
    struct no *no1 = atual;
    struct no *no2 = atual->esquerda;
    while(no2 != NULL)
    {
        no1 = no2;
        no2 = no2->esquerda;
    }
    return no1;
}

int remover(No *raiz, int valor)
{
	if(*raiz == NULL)
    {
	    printf("valor não existe!!\n");
	    return 0;
	}

    int retorno;
	if(valor < (*raiz)->info)
    {
	    if((retorno = remover(&(*raiz)->esquerda,valor)) == 1)
        {
            if(fatorBalanceamento(*raiz) >= 2)
            {
                if(altura_NO((*raiz)->direita->esquerda) <= altura_NO((*raiz)->direita->direita))
                    RotacaoRR(raiz);
                else
                    RotacaoRL(raiz);
            }
	    }
	}

	if((*raiz)->info < valor)
    {
	    if((retorno = remover(&(*raiz)->direita, valor)) == 1)
        {
            if(fatorBalanceamento(*raiz) >= 2)
            {
                if(altura_NO((*raiz)->esquerda->direita) <= altura_NO((*raiz)->esquerda->esquerda) )
                    RotacaoLL(raiz);
                else
                    RotacaoLR(raiz);
            }
	    }
	}

	if((*raiz)->info == valor)
    {
	    if(((*raiz)->esquerda == NULL || (*raiz)->direita == NULL))
        {// se o nó tiver 1 filho ou nenhum
			struct no *oldNode = (*raiz);
			if((*raiz)->esquerda != NULL)
                *raiz = (*raiz)->esquerda;
            else
                *raiz = (*raiz)->direita;
			free(oldNode);
		}else 
        { // se o no tiver 2 filhos
			struct no* temp = procuraMenor((*raiz)->direita);
			(*raiz)->info = temp->info;
			remover(&(*raiz)->direita, (*raiz)->info);
            if(fatorBalanceamento(*raiz) >= 2){
				if(altura_NO((*raiz)->esquerda->direita) <= altura_NO((*raiz)->esquerda->esquerda))
					RotacaoLL(raiz);
				else
					RotacaoLR(raiz);
			}
		}
		if (*raiz != NULL)
            (*raiz)->altura = maior(altura_NO((*raiz)->esquerda),altura_NO((*raiz)->direita)) + 1;
		return 1;
	}

	(*raiz)->altura = maior(altura_NO((*raiz)->esquerda),altura_NO((*raiz)->direita)) + 1;

	return retorno;
}