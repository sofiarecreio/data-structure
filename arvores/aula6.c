#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct noA {
    char info;
    struct noA *esq;
    struct noA *dir;
} TNoA;

// Funções da Árvore Binária
TNoA *inicializa(void);
void imprime(TNoA *nodo, int tab);
TNoA *criaNo(char ch);
void profundidade(TNoA* a);
void simetrico(TNoA* a);
void posOrdem(TNoA* a);
int contaNos(TNoA *a);

// Funções da Fila
typedef struct lista {
    TNoA *info;
    struct lista* prox;
} TLista;

typedef struct fila {
    TLista *inicio;
    TLista *fim;
} TFila;

TFila *inicializaFila(void);
void insere(TFila *f, TNoA *elem);
TNoA* retira(TFila *f);
int fila_vazia(TFila *f);
void liberaFila(TFila *f);

// Funções da Pilha
typedef struct pilha{
    TLista *topo;
} TPilha;

TPilha *inicializaPilha(void);
void push(TPilha *pilha, TNoA *elem);
TNoA* pop(TPilha *pilha);
int pilha_vazia(TPilha *pilha);
void liberaPilha(TPilha *pilha);

// Funções para percursos da árvore
void caminho_largura(TNoA* raiz);
void caminho_profundidade(TNoA* raiz);

TNoA *inicializa(void) {
    return NULL;
}

void imprime(TNoA *nodo, int tab) {
    for (int i = 0; i < tab; i++) {
        printf("-");
    }
    if (nodo != NULL) {
        printf("%c\n", nodo->info);
        imprime(nodo->esq, tab + 2);
        imprime(nodo->dir, tab + 2);
    } else {
        printf("vazio\n");
    }
}

TNoA *criaNo(char ch) {
    TNoA *novo = (TNoA *)malloc(sizeof(TNoA));
    novo->info = ch;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

void profundidade(TNoA* a) {
    if (a != NULL) {
        printf("%c ", a->info);
        profundidade(a->esq);
        profundidade(a->dir);
    }
}

void simetrico(TNoA* a) {
    if (a != NULL) {
        simetrico(a->esq);
        printf("%c ", a->info);
        simetrico(a->dir);
    }
}

void posOrdem(TNoA* a) {
    if (a != NULL) {
        posOrdem(a->esq);
        posOrdem(a->dir);
        printf("%c ", a->info);
    }
}

int contaNos(TNoA *a) {
    if (a == NULL) {
        return 0;
    }
    return 1 + contaNos(a->esq) + contaNos(a->dir);
}

// Funções da Fila
TFila *inicializaFila(void) {
    TFila *f = (TFila *)malloc(sizeof(TFila));
    f->inicio = NULL;
    f->fim = NULL;
    return f;
}

void insere(TFila *f, TNoA *elem) {
    TLista *novo = (TLista *)malloc(sizeof(TLista));
    novo->info = elem;
    novo->prox = NULL;
    if (f->fim != NULL) {
        f->fim->prox = novo;
    } else {
        f->inicio = novo;
    }
    f->fim = novo;
}

TNoA* retira(TFila *f) {
    if (fila_vazia(f)) {
        return NULL;
    }
    TNoA *valor = f->inicio->info;
    TLista *aux = f->inicio;
    f->inicio = f->inicio->prox;
    if (f->inicio == NULL) {
        f->fim = NULL;
    }
    free(aux);
    return valor;
}

int fila_vazia(TFila *f) {
    return f->inicio == NULL;
}

void liberaFila(TFila *f) {
    TLista *temp;
    while (f->inicio != NULL) {
        temp = f->inicio;
        f->inicio = f->inicio->prox;
        free(temp);
    }
    free(f);
}

// Funções da Pilha
TPilha *inicializaPilha(void) {
    TPilha *pilha = (TPilha *)malloc(sizeof(TPilha));
    pilha->topo = NULL;
    return pilha;
}

void push(TPilha *pilha, TNoA *elem) {
    TLista *novo = (TLista *)malloc(sizeof(TLista));
    novo->info = elem;
    novo->prox = pilha->topo;
    pilha->topo = novo;
}

TNoA* pop(TPilha *pilha) {
    if (pilha_vazia(pilha)) {
        return NULL;
    }
    TNoA *valor = pilha->topo->info;
    TLista *aux = pilha->topo;
    pilha->topo = pilha->topo->prox;
    free(aux);
    return valor;
}

int pilha_vazia(TPilha *pilha) {
    return pilha->topo == NULL;
}

void liberaPilha(TPilha *pilha) {
    TLista *temp;
    while (pilha->topo != NULL) {
        temp = pilha->topo;
        pilha->topo = pilha->topo->prox;
        free(temp);
    }
    free(pilha);
}

// Funções para percursos da árvore
void caminho_largura(TNoA* raiz) {
    if (raiz == NULL) return;

    TFila *fila = inicializaFila();
    insere(fila, raiz); // Inserir a raiz na fila

    while (!fila_vazia(fila)) {
        TNoA *nodo = retira(fila);
        printf("%c ", nodo->info);

        // Inserir filhos na fila (navegar sem alterar a árvore)
        if (nodo->esq != NULL)
            insere(fila, nodo->esq);
        if (nodo->dir != NULL)
            insere(fila, nodo->dir);
    }
    liberaFila(fila);
}

void caminho_profundidade(TNoA* raiz) {
    if (raiz == NULL) return;

    TPilha *pilha = inicializaPilha();
    push(pilha, raiz); // Inserir a raiz na pilha

    while (!pilha_vazia(pilha)) {
        TNoA *nodo = pop(pilha);
        printf("%c ", nodo->info);

        // Inserir filhos na pilha (último a ser inserido será o primeiro a ser visitado)
        if (nodo->dir != NULL)
            push(pilha, nodo->dir);
        if (nodo->esq != NULL)
            push(pilha, nodo->esq);
    }
    liberaPilha(pilha);
}

int main(void) {
    TNoA *raiz;
    raiz = criaNo('A');
    raiz->esq = criaNo('B');
    raiz->dir = criaNo('C');
    raiz->dir->esq = criaNo('D');
    raiz->dir->dir = criaNo('E');
    raiz->esq->esq = criaNo('F');
    
    printf("Impressao da Arvore:\n");
    imprime(raiz, 0);
    printf("\n");

    printf("Profundidade (Pre Ordem): ");
    profundidade(raiz);
    printf("\n");

    printf("Simetrico (In Ordem): ");
    simetrico(raiz);
    printf("\n");

    printf("Pos Ordem: ");
    posOrdem(raiz);
    printf("\n");

    printf("Total de Nos: %d\n", contaNos(raiz));

    printf("Caminho em Largura: ");
    caminho_largura(raiz);
    printf("\n");

    printf("Caminho em Profundidade: ");
    caminho_profundidade(raiz);
    printf("\n");

    return 0;
}
