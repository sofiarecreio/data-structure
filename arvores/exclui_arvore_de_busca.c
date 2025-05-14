#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct sNoA {
    int chave;
    struct sNoA *esq;
    struct sNoA *dir;
} TNoA;

void imprime(TNoA *nodo, int tab) {
    for (int i = 0; i < tab; i++) {
        printf("-");
    }
    if (nodo != NULL) {
        printf("%d\n", nodo->chave);
        imprime(nodo->esq, tab + 2);
        printf("\n");
        imprime(nodo->dir, tab + 2);
    } else printf("vazio");
}

TNoA *insere(TNoA *no, int chave) {
    if (no == NULL) {
        no = (TNoA *) malloc(sizeof(TNoA));
        no->chave = chave;
        no->esq = NULL;
        no->dir = NULL;
    } else if (chave < (no->chave))
        no->esq = insere(no->esq, chave);
    else if (chave > (no->chave)) {
        no->dir = insere(no->dir, chave);
    }
    else {
        printf("Inserção inválida! ");
        exit(1);
    }
    return no;
}

TNoA *criaArvoreBalanceada(TNoA *raiz, int *v, int inicio, int fim) {
    if (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        if (raiz == NULL) { // se for primeiro nó a ser inserido tem que atualizar a raiz da arvore
            raiz = (TNoA *)malloc(sizeof(TNoA));
            raiz->chave = v[meio];
            raiz->esq = NULL;
            raiz->dir = NULL;
        } else {
            insere(raiz, v[meio]);
        }
        // constroi subárvores esquerda e direita
        raiz = criaArvoreBalanceada(raiz, v, inicio, meio - 1);
        raiz = criaArvoreBalanceada(raiz, v, meio + 1, fim);
    }
    return raiz;
}

TNoA *excluir(TNoA *raiz, int chave) {
    if(raiz == NULL) {
        return raiz;
    }
    else {
        if(chave < raiz->chave) {
            raiz->esq = excluir(raiz->esq, chave);
        } else if(chave > raiz->chave) {
            raiz->dir = excluir(raiz->dir, chave);
        } else {
            // Caso 1: No sem filhos (folha)
            if(raiz->esq == NULL && raiz->dir == NULL) {
                free(raiz);
                raiz = NULL;
            }
            // Caso 2: No com um filho
            else if(raiz->esq == NULL) {
                TNoA *temp = raiz;
                raiz = raiz->dir;
                free(temp);
            } else if(raiz->dir == NULL) {
                TNoA *temp = raiz;
                raiz = raiz->esq;
                free(temp);
            }
            // Caso 3: No com dois filhos
            else {
                TNoA *temp = raiz->dir;
                while(temp->esq != NULL) {
                    temp = temp->esq;
                }
                raiz->chave = temp->chave;
                raiz->dir = excluir(raiz->dir, temp->chave);
            }
        }
    }

    return raiz;
}

int main(void) {
    int tam = 10;
    int v[10] = {150, 300, 400, 500, 600, 800, 900, 1000, 1200, 1500};
    TNoA *raiz = NULL;
    raiz = criaArvoreBalanceada(raiz,v,0,tam-1);
    imprime(raiz, 0);   
    excluir(raiz, 500);
    printf("\n\nArvore depois da exclusao:\n"); 
    imprime(raiz, 0);
}
