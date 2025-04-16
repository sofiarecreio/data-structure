#include <stdio.h>  
#include <stdlib.h>

typedef struct lista {
    int info;
    struct lista* prox;
} TLista;

TLista* cria_lista (void);
TLista* remove_inicio (TLista* li);
TLista* remove_fim (TLista* li);
TLista* remove_ordenado (TLista* li, int i);
void imprime_lista (TLista* li);

TLista* cria_lista (void) {
    return NULL;
}

TLista* remove_inicio (TLista* li) {
    if(li == NULL) {
        printf("Lista vazia");
        exit(1);
    } else {
        TLista* p = li;
        li = li->prox;
        free(p);
    }

    return li;
}

TLista* remove_fim(TLista* li) {
    if(li == NULL) {
        printf("Lista vazia");
        exit(1);
    } else {
        TLista* p = li;
        TLista* ant = NULL;

        while(p->prox != NULL) {
            ant = p;
            p = p->prox;
        }

        if(ant == NULL) {
            free(li);
            li = NULL;
        } else {
            free(p);
            ant->prox = NULL;
        }
    }

    return li;
}

TLista* remove_ordenado(TLista* li, int i) {
    if(li == NULL) {
        printf("Lista vazia");
        exit(1);
    } else {
        TLista* p = li;
        TLista* ant = NULL;

        while(p != NULL && p->info < i) {
            ant = p;
            p = p->prox;
        }

        if(p != NULL && p->info == i) {
            if(ant == NULL) {
                li = li->prox;
                free(p);
            } else {
                ant->prox = p->prox;
                free(p);
            }
        } else {
            printf("Elemento não encontrado");
            exit(1);
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