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