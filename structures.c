#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

int Altura (pNodoA *a)
{
    int Alt_Esq, Alt_Dir;
    if (a == NULL)
        return 0;
    else
    {
        Alt_Esq = Altura (a->leftNode);
        Alt_Dir = Altura (a->rightNode);
        if (Alt_Esq > Alt_Dir)
            return (1 + Alt_Esq);
        else
            return (1 + Alt_Dir);
    }
}

int Calcula_FB(pNodoA *a)
{
    return (Altura(a->leftNode) - Altura(a->rightNode));
}

void Desenha(pNodoA *a , int nivel)
{
    int x;

    if (a !=NULL)
    {
        for (x=1; x<=nivel; x++)
            printf("=");
        printf("%s balanceFactor= %d\n", a->info.word, Calcula_FB(a));
        if (a->leftNode != NULL) Desenha(a->leftNode, (nivel+1));
        if (a->rightNode != NULL) Desenha(a->rightNode, (nivel+1));
    }
}

int is_avl(pNodoA *a)
{
    int alt_esq, alt_dir;

    if (a!=NULL)
    {
        alt_esq = Altura(a->leftNode);
        alt_dir = Altura(a->rightNode);
        return ( (alt_esq - alt_dir <2) && (alt_dir - alt_esq <2) && (is_avl(a->leftNode)) && (is_avl(a->rightNode)) );
    }
    else
        return 1;
}


pNodoA* rotacao_direita(pNodoA *pt)
{
    pNodoA* ptu;

    ptu = pt->leftNode;
    pt->leftNode = ptu->rightNode;
    ptu->rightNode = pt;
    pt->balanceFactor = 0;
    pt = ptu;
    return pt;
}

pNodoA* rotacao_esquerda(pNodoA *pt)
{
    pNodoA* ptu;

    ptu = pt->rightNode;
    pt->rightNode = ptu->leftNode;
    ptu->leftNode = pt;
    pt->balanceFactor = 0;
    pt = ptu;
    return pt;
}

pNodoA* rotacao_dupla_direita (pNodoA* pt)
{
    pNodoA* ptu, *ptv;

    ptu = pt->leftNode;
    ptv = ptu->rightNode;
    ptu->rightNode = ptv->leftNode;
    ptv->leftNode = ptu;
    pt->leftNode = ptv->rightNode;
    ptv->rightNode = pt;
    if (ptv->balanceFactor == 1)   pt->balanceFactor = -1;
    else pt->balanceFactor = 0;
    if (ptv->balanceFactor == -1)  ptu->balanceFactor = 1;
    else ptu->balanceFactor = 0;
    pt = ptv;
    return pt;
}

pNodoA* rotacao_dupla_esquerda (pNodoA* pt)
{
    pNodoA *ptu, *ptv;

    ptu = pt->rightNode;
    ptv = ptu->leftNode;
    ptu->leftNode = ptv->rightNode;
    ptv->rightNode = ptu;
    pt->rightNode = ptv->leftNode;
    ptv->leftNode = pt;
    if (ptv->balanceFactor == -1) pt->balanceFactor = 1;
    else pt->balanceFactor = 0;
    if (ptv->balanceFactor == 1) ptu->balanceFactor = -1;
    else ptu->balanceFactor = 0;
    pt = ptv;
    return pt;
}


pNodoA* Caso1 (pNodoA* a , int *ok)
{
    pNodoA *ptu;

    ptu = a->leftNode;
    if (ptu->balanceFactor == 1)
    {
        //printf("fazendo rotacao direita em %d\n",a->info);
        a = rotacao_direita(a);
    }
    else
    {
        //printf("fazendo rotacao dupla direita em %d\n",a->info);
        a = rotacao_dupla_direita(a);
    }

    a->balanceFactor = 0;
    *ok = 0;
    return a;
}

pNodoA* Caso2 (pNodoA *a , int *ok)
{
    pNodoA *ptu;

    ptu = a->rightNode;
    if (ptu->balanceFactor == -1)
    {
        //Desenha(a,1);
        //printf("fazendo rotacao esquerda em %d\n",a->info);
        a=rotacao_esquerda(a);
    }
    else
    {
        //Desenha(a,1);
        //printf("fazendo rotacao dupla esquerda em %d\n",a->info);
        a=rotacao_dupla_esquerda(a);
    }
    a->balanceFactor = 0;
    *ok = 0;
    return a;
}

pNodoA* InsereAVL (pNodoA *a, TipoInfo x, int *ok)
{
    if (a == NULL)
    {
        a = (pNodoA*) malloc(sizeof(pNodoA));
        a->info = x;
        a->leftNode = NULL;
        a->rightNode = NULL;
        a->balanceFactor = 0;
        *ok = 1;
    }
    else
    {
        int comparacao = strcmp(x.word, a->info.word);
        if (comparacao < 0)
        {
            a->leftNode = InsereAVL(a->leftNode,x,ok);
            if (*ok)
            {
                switch (a->balanceFactor)
                {
                case -1:
                    a->balanceFactor = 0;
                    *ok = 0;
                    break;
                case  0:
                    a->balanceFactor = 1;
                    break;
                case  1:
                    a=Caso1(a,ok);
                    break;
                }
            }
        }
        else if (comparacao > 0)
        {
            a->rightNode = InsereAVL(a->rightNode,x,ok);
            if (*ok)
            {
                switch (a->balanceFactor)
                {
                case  1:
                    a->balanceFactor = 0;
                    *ok = 0;
                    break;
                case  0:
                    a->balanceFactor = -1;
                    break;
                case -1:
                    a = Caso2(a,ok);
                    break;
                }
            }
        }
        else if (comparacao == 0)
        {
            //printf("\nsao iguais");
        }
    }
    return a;
}

/* Linked list */

PtNo* cria_lista(void)
{
    return NULL;
}

PtNo* insere_ord (PtNo* l, InfoNo dados)
{
    PtNo *novo; //novo elemento
    PtNo *ant = NULL; //ponteiro auxiliar para a posição anterior
    PtNo *ptaux = l; //ponteiro auxiliar para percorrer a lista

    /*aloca um novo nodo */
    novo = (PtNo*) malloc(sizeof(PtNo));

    /*insere a informação no novo nodo*/
    novo->info = dados;


    /*procurando a posição de inserção*/
    while ((ptaux!=NULL) && (ptaux->info.page < dados.page)) //se info.titulo < dados.titulo então strcmp retorna um valor menor que zero
    {
        ant = ptaux;
        ptaux = ptaux->prox;
    }

    /*encaeia o elemento*/
    if (ant == NULL) /*o anterior não existe, logo o elemento será inserido na primeira posição*/
    {
        //  puts("inserindo primeiro");
        novo->prox = l;
        l = novo;
    }
    else /*elemento inserido no meio da lista*/
    {
        novo->prox = ant->prox;
        ant->prox = novo;
    }

    return l;
}
void imprime(PtNo* l)
{
    PtNo* ptaux;
    if (l == NULL)
        puts("lista vazia");
    else
        for (ptaux=l; ptaux!=NULL; ptaux=ptaux->prox)
            printf("\n%d", l->info.page);
}

PtNo* remover(PtNo* l, int page)
{
    PtNo *ant = NULL; //ponteiro auxiliar para a posição anterior
    PtNo *ptaux = l; //ponteiro auxiliar para percorrer a lista

    /*procura o elemento na lista*/
    //strcmp(ptaux->info.titulo, titulo)
    while (ptaux !=NULL && (ptaux->info.page != page))
    {
        ant = ptaux;
        ptaux = ptaux->prox;
    }

    /*verifica se achou*/
    if (ptaux == NULL)
        return l; /*retorna a lista original*/

    if (ant == NULL) /*vai remover o primeiro elemento*/
        l = ptaux->prox;
    else /*vai remover do meio ou do final*/
        ant->prox = ptaux->prox;

    free(ptaux); /*libera a memória alocada*/

    return l;
}

PtNo* destroi(PtNo* l)
{
    PtNo *ptaux; //ponteiro auxiliar para percorrer a lista
    while (l != NULL)
    {
        ptaux = l;
        l = l->prox;
        free(ptaux);
    }
    free(l);
    return NULL;
}
