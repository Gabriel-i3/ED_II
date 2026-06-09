#include <stdio.h>
#include <stdlib.h>

//estrura de um nó para uma árvore generica.

typedef struct No {
    int dado;
    struct No* esq;  
    struct No* dir;  
} No;

//função que inicializa uma árvore vazia 

No* inicializar_arvore() {
    return NULL; 
}

No* criar_no(int valor) {
    No* novo = (No*)malloc(sizeof(No));
    if (novo != NULL) {
        novo->dado = valor;
        novo->esq = NULL;
        novo->dir = NULL;
    }
    return novo;
}

//função para inserir filhos em um nó

void inserir_filho(No* pai, No* filho) {
    if (pai == NULL || filho == NULL) return;
    
    if (pai->esq == NULL) {
        pai->esq = filho;
    } else {
        
        No* atual = pai->esq;
        while (atual->dir != NULL) {
            atual = atual->dir;
        }
        atual->dir = filho; 
    }
}

