#include <stdio.h>
#include <stdlib.h>

typedef struct sNoAVL {
	int chave;
	int fb;
	struct sNoAVL *esq;
	struct sNoAVL *dir;
} TNoAVL;

void imprime(TNoAVL *no, int tab) {
	for (int i = 0; i < tab; i++) {
		printf("-");
	}
	if (no != NULL) {
		printf("%d (fb = %d)\n", no->chave, no->fb);
		imprime(no->esq, tab + 2);
		printf("\n");
		imprime(no->dir, tab + 2);
	} else printf("vazio");
}

TNoAVL *rotacao_direita(TNoAVL *p) {
	TNoAVL *u = p->esq;
    p->esq = u->dir;
    u->dir = p;
    p->fb = 0;
    p = u;
    return p;
}

TNoAVL *rotacao_esquerda(TNoAVL *p) {
	TNoAVL *u = p->dir;
    p->dir = u->esq;
    u->esq = p;
    p->fb = 0;
    p = u;
    return p;
}

TNoAVL *rotacao_dupla_direita(TNoAVL *p) {
    p->esq = rotacao_esquerda(p->esq);
    p = rotacao_direita(p);
    return p;
}

TNoAVL *rotacao_dupla_esquerda(TNoAVL *p) {
    p->dir = rotacao_direita(p->dir);
    p = rotacao_esquerda(p);
    return p;
}

TNoAVL *caso1(TNoAVL *p) {
	//chave foi inserida à esquerda de p e causou fb = -2
	//verificar se a rotacao eh simples ou dupla

	/*FAZER CODIGO AQUI*/
    TNoAVL *u = p->esq;
    if (u->fb == -1) {
        p = rotacao_direita(p);
    } else {
        p = rotacao_dupla_direita(p);
    }
    p->fb = 0;
    return p;
}

TNoAVL *caso2(TNoAVL *p) {
	//chave foi inserida à direita de p e causou fb = 2
	//verificar se a rotacao eh simples ou dupla

	/*FAZER CODIGO AQUI*/
    TNoAVL *u = p->dir;
    if (u->fb == 1) {
        p = rotacao_esquerda(p);
    } else {
        p = rotacao_dupla_esquerda(p);
    }
    p->fb = 0;
    return p;
}

TNoAVL *insere(TNoAVL *p, int chave, int *flag) {
	/* Insere no em uma árvore AVL, onde p representa a raiz da árvore,
	chave, a chave a ser inserida e flag é um booleano que indica se é necessário propagar operação de cálculo de fb */
	if (p == NULL) {
		p = (TNoAVL *) malloc(sizeof(TNoAVL));
		p->chave = chave;
		p->esq = NULL;
		p->dir = NULL;
		p->fb = 0;
		*flag = 1;
		printf("\nInseriu %d", p->chave);

	} else if (chave < p->chave) { //recursão à esquerda
		p->esq = insere(p->esq, chave, flag);
		if (*flag) { //inseriu: verificar balanceamento
			switch (p->fb) {
				case -1: /* fb(pt) = -2 */
					p = caso1(p);
					*flag = 0; //não propaga mais
					break;
				case 0:
					p->fb = -1; //ficou maior à esquerda
					break;
				case 1:
					p->fb = 0; // balanceou com inserção
					*flag = 0; // não propaga mais
					break;
			}
		}
	} else if (chave > p->chave) { //recursão à direita
		p->dir = insere(p->dir, chave, flag);
		if (*flag) {
			switch (p->fb) {
				case 1: //fb(pt) = 2 e p retorna balanceado
					p = caso2(p);
					*flag = 0; //não propaga mais
					break;
				case 0:
					p->fb = 1;
					break;
				case -1: //era mais alto à esquerda, zera fb
					p->fb = 0;
					*flag = 0; //não propaga mais
					break;
			}
		}
	}
	//else if (chave == pt->chave) ==> nada a fazer!
	return p;
}

TNoAVL *maior_no_esquerda(TNoAVL *p) {
    while (p->dir != NULL) {
        p = p->dir;
    }
    return p;
}

int altura(TNoAVL *p) {
    if (p == NULL) return 0;
    int he = altura(p->esq);
    int hd = altura(p->dir);
    return (he > hd ? he : hd) + 1;
}

int fator_balanceamento(TNoAVL *p) {
    return altura(p->dir) - altura(p->esq);
}

TNoAVL* remove_no(TNoAVL *p, int chave, int *flag) {
    if (p == NULL) return p;
    if (chave < p->chave) {
        p->esq = remove_no(p->esq, chave, flag);
        if (*flag) {
            // Atualizar fb e balancear
            p->fb = fator_balanceamento(p);
            if (p->fb == 2) {
                if (fator_balanceamento(p->dir) < 0) p = rotacao_dupla_esquerda(p);
                else p = rotacao_esquerda(p);
            } else if (p->fb == -2) {
                if (fator_balanceamento(p->esq) > 0) p = rotacao_dupla_direita(p);
                else p = rotacao_direita(p);
            }
            *flag = (p->fb == 0);
        }
    } else if (chave > p->chave) {
        p->dir = remove_no(p->dir, chave, flag);
        if (*flag) {
            p->fb = fator_balanceamento(p);
            if (p->fb == 2) {
                if (fator_balanceamento(p->dir) < 0) p = rotacao_dupla_esquerda(p);
                else p = rotacao_esquerda(p);
            } else if (p->fb == -2) {
                if (fator_balanceamento(p->esq) > 0) p = rotacao_dupla_direita(p);
                else p = rotacao_direita(p);
            }
            *flag = (p->fb == 0);
        }
    } else {
        // Nó encontrado para remoção
        if (p->esq == NULL) {
            TNoAVL *temp = p->dir;
            free(p);
            *flag = 1;
            return temp;
        } else if (p->dir == NULL) {
            TNoAVL *temp = p->esq;
            free(p);
            *flag = 1;
            return temp;
        } else {
            TNoAVL *temp = maior_no_esquerda(p->esq);
            p->chave = temp->chave;
            p->esq = remove_no(p->esq, temp->chave, flag);
            if (*flag) {
                p->fb = fator_balanceamento(p);
                if (p->fb == 2) {
                    if (fator_balanceamento(p->dir) < 0) p = rotacao_dupla_esquerda(p);
                    else p = rotacao_esquerda(p);
                } else if (p->fb == -2) {
                    if (fator_balanceamento(p->esq) > 0) p = rotacao_dupla_direita(p);
                    else p = rotacao_direita(p);
                }
                *flag = (p->fb == 0);
            }
        }
    }
    return p;
}

TNoAVL *busca(TNoAVL *p, int chave) {
    if (p == NULL) return NULL;
    if (chave < p->chave) return busca(p->esq, chave);
    else if (chave > p->chave) return busca(p->dir, chave);
    else return p;
}

int main() {
	TNoAVL *raiz;
	raiz = NULL;
	int ok;
	//arvore do exercício de inserção feito em aula
	raiz = insere(raiz, 50, &ok);
	raiz = insere(raiz, 40, &ok);
	raiz = insere(raiz, 30, &ok);
	raiz = insere(raiz, 55, &ok);
	raiz = insere(raiz, 60, &ok);
	raiz = insere(raiz, 57, &ok);
	raiz = insere(raiz, 58, &ok);
	raiz = insere(raiz, 52, &ok);
	raiz = insere(raiz, 51, &ok);
	printf("\n");
	imprime(raiz, 0);
	printf("\n\n\n\n");

    raiz = remove_no(raiz, 30, &ok);
    raiz = remove_no(raiz, 40, &ok);
    raiz = remove_no(raiz, 58, &ok);
    imprime(raiz, 0);
    printf("\n\n\n\n");
}