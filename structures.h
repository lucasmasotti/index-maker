/* LINKED LIST */
typedef struct TipoInfoNo InfoNo;
typedef struct TipoPtNo PtNo;

struct TipoInfoNo
{
    int page;
};

struct TipoPtNo
{
    InfoNo info;
    PtNo *prox;
};

PtNo* cria_lista(void);
PtNo* insere_ord (PtNo *l, InfoNo dados);
void imprime(PtNo* l);
PtNo* remover(PtNo* l, int page);
PtNo* destroi(PtNo* l);

/* AVL */

#define WORD_MAX_SIZE 50

struct TInfoArvore
{
    char word[WORD_MAX_SIZE];
    PtNo* occurrencesList;
};

struct TNodoA
{
    struct TInfoArvore info;
    int balanceFactor;
    struct TNodoA *leftNode;
    struct TNodoA *rightNode;
};

typedef struct TInfoArvore TipoInfo;
typedef struct TNodoA pNodoA;

pNodoA * InsereArvore(pNodoA * a, TipoInfo ch);
int Altura (pNodoA * a);
int Calcula_FB(pNodoA * a);
void Desenha(pNodoA * a , int nivel);
int is_avl(pNodoA * a);
pNodoA * rotacao_direita(pNodoA * pt);
pNodoA * rotacao_esquerda(pNodoA * pt);
pNodoA * rotacao_dupla_direita (pNodoA * pt);
pNodoA * rotacao_dupla_esquerda (pNodoA * pt);
pNodoA * Caso1 (pNodoA * a , int *ok);
pNodoA * Caso2 (pNodoA * a , int *ok);
pNodoA * InsereAVL (pNodoA * a, TipoInfo x, int *ok);
