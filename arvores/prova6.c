#include <stdio.h>
#include <stdlib.h>

typedef struct noA{
	char info;
	struct noA *esq;
	struct noA *dir;
} TNoA;

void imprime(TNoA *nodo, int tab){
	for (int i = 0; i < tab; i++){
		printf("-");
	}
	if (nodo != NULL){
		printf("%c\n", nodo->info);
		imprime(nodo->esq, tab + 2);
		printf("\n");
		imprime(nodo->dir, tab + 2);
	} else printf("vazio");
}

TNoA *criaNo(char ch){
	TNoA *novo;
	novo = (TNoA *) malloc(sizeof(TNoA));
	novo->info = ch;
	novo->esq = NULL;
	novo->dir = NULL;
	return novo;
}

void profundidade(TNoA* a){
	if (a!= NULL){
		printf("%c ",a->info);
		profundidade(a->esq);
		profundidade(a->dir);
	}
}

void simetrica(TNoA* a){
	if (a!= NULL){
		simetrica(a->esq);
        printf("%c ",a->info);
		simetrica(a->dir);	
	}
}

void posOrdem(TNoA* a){
	if (a!= NULL){
		posOrdem(a->esq);
		posOrdem(a->dir);	
        printf("%c ",a->info);
	}
}

int main(void){
	TNoA *raiz;
	raiz = criaNo('A');
	raiz->esq = criaNo('B');
	raiz->dir = criaNo('C');
	raiz->dir->esq = criaNo('D');
	raiz->dir->dir = criaNo('E');
	imprime(raiz, 0);
	printf("\n");
	profundidade(raiz);
	printf("\n");
	simetrica(raiz);
	printf("\n");
	posOrdem(raiz);
};