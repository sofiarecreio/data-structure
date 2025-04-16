#include <stdio.h>  
#include <stdlib.h>

typedef struct lista {
    int info;
    struct lista* prox;
} TLista;

TLista* cria_lista (void);
TLista* insere_ordenado_recursivo(TLista* li, int i);
void imprime_lista (TLista* li);

int main(void) {
    TLista *l2;
    /* Insere elementos no inicio da lista */
    /* Insere elementos no final da lista*/
    l2 = cria_lista(); /* cria e inicializa lista como vazia */
    l2 = insere_ordenado_recursivo(l2, 2);
    l2 = insere_ordenado_recursivo(l2, 5);
    l2 = insere_ordenado_recursivo(l2, 3);
    l2 = insere_ordenado_recursivo(l2, 4);
    l2 = insere_ordenado_recursivo(l2, 1);
    printf("Lista:\n");
    imprime_lista(l2);

    return 0;
}

TLista* cria_lista (void) {
    return NULL;
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