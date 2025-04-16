#include <stdio.h>  
#include <stdlib.h>

typedef struct lista {
    int info;
    struct lista* prox;
} TLista;

TLista* cria_lista (void);
TLista* remove_fim_recursivo(TLista* li, int i);
TLista* remove_ordenado_recursivo(TLista* li, int i);
void imprime_lista (TLista* li);

TLista* cria_lista (void) {
    return NULL;
}

TLista* remove_fim_recursivo(TLista* li, int i) {
    if(li == NULL) {
        printf("Lista vazia");
        exit(1);
    } else {
        if(li->prox == NULL) {
            free(li);
            li == NULL;
        } else {
            li->prox = remove_fim_recursivo(li->prox, i);
        }
    }

    
    if (li == NULL) {
        printf("Elemento %d não encontrado na lista", i);
    }

    return li;
}

TLista* remove_ordenado_recursivo(TLista* li, int i) {
    if(li == NULL) {
        printf("Lista vazia");
        exit(1);
    } else {
        if(li->info == i) {
            TLista* p = li;
            li = li->prox;
            free(p);
        } else {
            li->prox = remove_ordenado_recursivo(li->prox, i);
        }
    }

    
    if (li == NULL) {
        printf("Elemento %d não encontrado na lista", i);
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