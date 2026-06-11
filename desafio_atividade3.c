#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct No {
    int dado;
    struct No* esq;
    struct No* dir;
} No;

//Função auxiliar de criação
No* criar_no(int valor) {
    No* novo = (No*)malloc(sizeof(No));
    if (novo != NULL) {
        novo->dado = valor;
        novo->esq = NULL;
        novo->dir = NULL;
    }
    return novo;
}

//Inserção Iterativa
No* inserir_iterativo(No* raiz, int valor) {
    No* novo = criar_no(valor);
    if (novo == NULL) return raiz;

    //Se a árvore estiver vazia, o novo nó se torna a raiz
    if (raiz == NULL) {
        return novo;
    }

    No* atual = raiz;
    No* pai = NULL;

    
    while (atual != NULL) {
        pai = atual;
        if (valor < atual->dado) {
            atual = atual->esq;
        } else if (valor > atual->dado) {
            atual = atual->dir;
        } else {
            
            free(novo);
            return raiz;
        }
    }

    
    if (valor < pai->dado) {
        pai->esq = novo;
    } else {
        pai->dir = novo;
    }

    return raiz;
}

// função que transforma uma árvore binária em espelho
void espelhar_arvore(No* raiz) {
    if (raiz == NULL) return;

    No* temp = raiz->esq;
    raiz->esq = raiz->dir;
    raiz->dir = temp;

  
    espelhar_arvore(raiz->esq);
    espelhar_arvore(raiz->dir);
}


int obter_altura(No* raiz) {
    if (raiz == NULL) return 0;
    
    int alt_esq = obter_altura(raiz->esq);
    int alt_dir = obter_altura(raiz->dir);
    
    return (alt_esq > alt_dir ? alt_esq : alt_dir) + 1;
}

//função que verifique se uma árvore é balanceada
int eh_balanceada(No* raiz) {
    if (raiz == NULL) return 1;

    int alt_esq = obter_altura(raiz->esq);
    int alt_dir = obter_altura(raiz->dir);

    int diferenca = abs(alt_esq - alt_dir);

    if (diferenca <= 1 && eh_balanceada(raiz->esq) && eh_balanceada(raiz->dir)) {
        return 1;
    }

    return 0;
}

// Função auxiliar para imprimir em ordem
void em_ordem(No* raiz) {
    if (raiz != NULL) {
        em_ordem(raiz->esq);
        printf("%d ", raiz->dado);
        em_ordem(raiz->dir);
    }
}

// Função auxiliar para liberar a memória
void destruir_arvore(No* raiz) {
    if (raiz != NULL) {
        destruir_arvore(raiz->esq);
        destruir_arvore(raiz->dir);
        free(raiz);
    }
}

int main() {
    No* raiz = NULL;

    
    raiz = inserir_iterativo(raiz, 50);
    raiz = inserir_iterativo(raiz, 30);
    raiz = inserir_iterativo(raiz, 70);
    raiz = inserir_iterativo(raiz, 20);
    raiz = inserir_iterativo(raiz, 40);

    printf("Arvore original (em ordem): ");
    em_ordem(raiz);
    printf("\n");

    
    if (eh_balanceada(raiz)) {
        printf("A arvore esta balanceada.\n");
    } else {
        printf("A arvore nao esta balanceada.\n");
    }

    
    printf("Espelhando a arvore\n");
    espelhar_arvore(raiz);

    printf("Arvore espelhada (em ordem): ");
    em_ordem(raiz);
    printf("\n");

    destruir_arvore(raiz);
    return 0;
}