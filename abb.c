//Etapa 1 — Cada nó da árvore precisa armazenar:
//um valor;
//ponteiro para filho da esquerda; 
//ponteiro para filho da direita.

//Em linguagem C:

#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No *esq;
    struct No *dir;
} No;

//Etapa 2 — Criando um novo nó
//Agora criamos uma função para alocar memória para um nó.
No* criarNo(int valor) {
    No *novo = (No*) malloc(sizeof(No));
    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;

    return novo;
}

//commit inserção de nós
//Etapa 3 — Inserção na ABB
//A inserção é o coração da árvore.
//Regras:
//se o valor for menor → vai para esquerda;
//se o valor for maior → vai para direita.
//Implementação
No* inserir(No *raiz, int valor) {
    // árvore vazia
    if (raiz == NULL) {
        return criarNo(valor);
    }
    // inserção à esquerda
    if (valor < raiz->valor) {
        raiz->esq = inserir(raiz->esq, valor);
    }
    // inserção à direita
    else if (valor > raiz->valor) {
        raiz->dir = inserir(raiz->dir, valor);
    }
    return raiz;
}