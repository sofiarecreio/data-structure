#include <stdio.h>
#include <stdlib.h>

typedef struct lista {
    int info;
    struct lista* prox;
} TLista;

typedef struct pilha{
    TLista *topo;
} TPilha;

TPilha *inicializa();
void libera(TPilha *p);
int pilha_vazia(TPilha *p);
void push(TPilha *pilha, int elem);
int pop(TPilha *pilha);
int peek(TPilha *pilha);
void imprime_pilha(TPilha *pilha);

TPilha *inicializa() {
    TPilha *pilha = (TPilha *)malloc(sizeof(TPilha));
    pilha->topo = NULL;
    return pilha;
}

void libera(TPilha *p) {
    TLista *q = p->topo;
    TLista *r;
    while(q != NULL){
        r = q;
        q=q->prox;
        free(r);
    }
    free(p);
}

int pilha_vazia(TPilha *pilha) {
      if (pilha->topo == NULL)
      	return 1; //pilha vazia
      else
      	return 0; //pilha tem pelo menos 1 elemento
}

/* *
 * Insere elem no topo da pilha
 * */
void push(TPilha *pilha, int elem) {
    TLista *novo = (TLista*) malloc(sizeof(TLista));
    novo->info = elem;
    novo->prox = pilha->topo;
    pilha->topo = novo;
}

/* *
 * Altera o elemento do topo da pilha
 * */
void altera_topo(TPilha *pilha, int elem) {
    if (pilha_vazia(pilha)) {
        printf("Erro: pilha vazia, não é possível alterar o topo.\n");
        return;
    }
    pilha->topo->info = elem;
}

/* *
 * Exclui o elemento do topo da pilha
 * retorna o info do elemento excluído
 */
int pop(TPilha *pilha) {
    if (pilha->topo == NULL) {
        printf("Pilha vazia! Não é possível remover.\n");
        return -1; // valor de erro, pode ser ajustado
    }
    if (pilha_vazia(pilha)) {
        printf("Pilha vazia! Não é possível remover.\n");
        return -1; // valor de erro, pode ser ajustado
    }
    TLista *removido_node = pilha->topo;
    int removido = removido_node->info;
    pilha->topo = removido_node->prox;
    free(removido_node);
    return removido;
}

/* *
 * Consulta o elemento do topo da pilha
 * retorna info do elemento do topo
 */
int peek(TPilha *pilha) {
    if (pilha_vazia(pilha)) {
        printf("Pilha vazia! Não há topo.\n");
        return -1; // valor de erro
    }
    return pilha->topo->info;
}

void imprime_pilha(TPilha *pilha) {
    if (pilha->topo == NULL) {
        printf("Pilha vazia!\n");
        return;
    }

    printf("Conteúdo da pilha (topo -> base):\n");
    for (TLista *node = pilha->topo; node != NULL; node = node->prox) {
        printf("%d\n", node->info);
    }
}

int main() {
    TPilha *pilha;
    pilha = inicializa();
    push(pilha, 5);
    printf("topo: %d\n", peek(pilha));
    push(pilha, 4);
    printf("topo: %d\n", peek(pilha));
    push(pilha, 3);
    printf("topo: %d\n", peek(pilha));

    imprime_pilha(pilha);

    int info = pop(pilha);
    printf("elemento removido: %d\n", info);

    imprime_pilha(pilha);
}