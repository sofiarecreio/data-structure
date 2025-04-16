#include <stdio.h>  
#include <stdlib.h>

typedef struct lista {
    int info;
    struct lista* prox;
} TLista;

TLista* cria_lista (void);
TLista* insere_fim_recursivo(TLista* li, int i);
TLista* insere_ordenado_recursivo(TLista* li, int i);
void imprime_lista (TLista* li);

TLista* cria_lista (void) {
    return NULL;
}

TLista* insere_fim_recursivo(TLista* li, int i) {
    if( li == NULL || li->prox == NULL) {
        TLista* novo = (TLista*) malloc(sizeof(TLista));
        novo->info = i;
        novo->prox = NULL;

        if(li == NULL) {
            li = novo;
        } else li->prox = novo;
    } else {
        insere_fim_recursivo(li->prox, i); //chamada recursiva
    }

    return li;
}

TLista *insere_ordenado_recursivo(TLista* li, int i) {
    if(li == NULL || li->prox == NULL) {
        TLista* novo = (TLista*) malloc(sizeof(TLista));
        novo->info = i;
        novo->prox = NULL;

        if(li == NULL) {
            li = novo;
        } else {
            if(li->info > i) {
                novo->prox = li;
                li = novo;
            } else li->prox = novo;
        }
    } else {
        if(li->info > i) {
            TLista* novo = (TLista*) malloc(sizeof(TLista));
            novo->info = i;
            novo->prox = li;
            li = novo;
        } else {
            li->prox = insere_ordenado_recursivo(li->prox, i);
        }
    }

    return li;
}

void imprime_lista(TLista* li) {
    while (li != NULL) {
        printf("%d ", li->info);
        li = li->prox;
    }
    printf("\n");
}