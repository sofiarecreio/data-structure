#include <stdio.h>
#include <stdlib.h>

typedef struct lista {
    int info;
    struct lista* prox;
} TLista;


typedef struct fila {
    TLista *inicio;
    TLista *fim;
} TFila;

TFila *inicializa(void);
int fila_vazia(TFila *f);
void insere(TFila *f, int elem);
int retira(TFila *f);
void libera(TFila *f);
void imprime_fila(TFila *f);


TFila *inicializa(void){
    TFila *f = (TFila *)malloc(sizeof(TFila));
    f->inicio = NULL;
    f->fim = NULL;
    return f;
}

int fila_vazia(TFila *f){
    if (f->inicio == NULL) {
        return 1;
    }
    else return 0;
}

void insere(TFila *f, int elem){
    TLista *novo = (TLista *)malloc(sizeof(TLista));
    novo->info = elem;
    novo->prox = NULL; //inserção no fim da fila
    if (!fila_vazia(f)){
        f->fim->prox = novo;
    }
    else{
        f->inicio = novo;
    }
    f->fim = novo; //elemento inserido é o novo fim da fila
}

/*
 * Remove elemento da fila e retorna info do elemento excluído
 */
int retira(TFila *f){
    if (fila_vazia(f)){
        exit(1);
    }
    int info = f->inicio->info;

    TLista *aux = f->inicio;
    f->inicio=f->inicio->prox;
    //se elemento removido era o único da fila
    //faz fim apontar para NULL também
    if (f->inicio == NULL) {
        f->fim = NULL;
    }
    free(aux);
    return info;
}

void libera(TFila *f){
    TLista *q, *p = f->inicio;
    while(p != NULL){
        q = p;
        p = p->prox;
        free(q);
    }
    free(f);
}

void altera_inicio(TFila *f, int elem) {
    if (fila_vazia(f)) {
        printf("Erro: fila vazia\n");
    }
    
    f->inicio->info = elem;
}

void imprime_fila(TFila *f) {
    TLista *p;
    p = f->inicio;
    if (p == NULL) {
        printf("Fila vazia\n");
        return;
    }
    printf("Fila: ");
    while (p != NULL) {
        printf("%d ", p->info);
        p = p->prox;
    }
}

int main() {
    TFila *fila = inicializa();
    insere(fila, 5);
    insere(fila, 3);
    insere(fila, 2);
    imprime_fila(fila);
    int x = retira(fila);
    printf("\nelemento %d retirado da fila\n", x);
    imprime_fila(fila);
    libera(fila);
}