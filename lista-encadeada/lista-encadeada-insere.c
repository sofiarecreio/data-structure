#include <stdio.h>  
#include <stdlib.h>

typedef struct lista {
    int info;
    struct lista* prox;
} TLista;

TLista* cria_lista (void);
TLista* insere_inicio (TLista* li, int i);
TLista* insere_fim (TLista* li, int i);
TLista* insere_ordenado (TLista* li, int i);
void imprime_lista (TLista* li);

TLista* cria_lista (void) {
    return NULL;
}

TLista *insere_inicio (TLista *li, int i) {
    TLista *novo = (TLista*) malloc(sizeof(TLista));

    if (novo == NULL) {
        printf("Erro ao alocar memoria\n");
        return li;
    }

    novo->info = i;
    novo->prox = li;
    return novo;
}

TLista* insere_fim(TLista* li, int i) {
    TLista *novo = (TLista*) malloc(sizeof(TLista));

    novo->info = i;
    novo->prox = NULL;
    TLista *p = li;

    if (li == NULL) { // lista vazia
        return novo;
    } else {
        while (p->prox != NULL) { // percorre a lista
            p = p->prox;
        }
        p->prox = novo; // insere no final
    }

    return li;
}

TLista* insere_ordenado(TLista* li, int i) {
    TLista *novo = (TLista*) malloc(sizeof(TLista));
    novo->info = i;
    novo->prox = NULL;
    TLista *p = li;

    if(p == NULL) { //lista vazia
        novo->prox = NULL;
        li = novo;
    } else if ( p->info > i) { //insere início
        novo->prox = li;
        li = novo;
    } else {
        while (p->prox != NULL && p->prox->info < i) { //percorre a lista
            p = p->prox;
        }
        novo->prox = p->prox; //insere no meio ou no final
        p->prox = novo;
    }
}    

void imprime_lista(TLista* li) {
    while (li != NULL) {
        printf("%d ", li->info);
        li = li->prox;
    }
    printf("\n");
}