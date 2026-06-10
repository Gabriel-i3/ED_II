#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó da árvore binária
typedef struct No {
    int dado;
    struct No *esq;
    struct No *dir;
} No;

// Função para criar um novo nó
No* criarNo(int valor) {
    No* novo = (No*) malloc(sizeof(No));

    if (novo != NULL) {
        novo->dado = valor;
        novo->esq = NULL;
        novo->dir = NULL;
    }

    return novo;
}

// Função para inserir nós manualmente
No* inserir(No* raiz, int valor) {
    if (raiz == NULL) {
        return criarNo(valor);
    }

    int opcao;

    printf("\nInserir %d:", valor);
    printf("\n1 - Esquerda de %d", raiz->dado);
    printf("\n2 - Direita de %d", raiz->dado);
    printf("\nOpcao: ");
    scanf("%d", &opcao);

    if (opcao == 1) {
        raiz->esq = inserir(raiz->esq, valor);
    } else {
        raiz->dir = inserir(raiz->dir, valor);
    }

    return raiz;
}

// Percurso em pré-ordem
void preOrdem(No* raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->dado);
        preOrdem(raiz->esq);
        preOrdem(raiz->dir);
    }
}

// Percurso em ordem
void emOrdem(No* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esq);
        printf("%d ", raiz->dado);
        emOrdem(raiz->dir);
    }
}

// Percurso em pós-ordem
void posOrdem(No* raiz) {
    if (raiz != NULL) {
        posOrdem(raiz->esq);
        posOrdem(raiz->dir);
        printf("%d ", raiz->dado);
    }
}

// Função que conta o número de nós
int contarNos(No* raiz) {
    if (raiz == NULL) {
        return 0;
    }

    return 1 + contarNos(raiz->esq) + contarNos(raiz->dir);
}

// Função que calcula a altura da árvore
int altura(No* raiz) {
    if (raiz == NULL) {
        return -1; // altura em arestas
    }

    int altEsq = altura(raiz->esq);
    int altDir = altura(raiz->dir);

    if (altEsq > altDir) {
        return altEsq + 1;
    }

    return altDir + 1;
}

// Função que conta os nós folhas
int contarFolhas(No* raiz) {
    if (raiz == NULL) {
        return 0;
    }

    if (raiz->esq == NULL && raiz->dir == NULL) {
        return 1;
    }

    return contarFolhas(raiz->esq) + contarFolhas(raiz->dir);
}

// Função que espelha a árvore
void espelhar(No* raiz) {
    if (raiz == NULL) {
        return;
    }

    No* temp = raiz->esq;
    raiz->esq = raiz->dir;
    raiz->dir = temp;

    espelhar(raiz->esq);
    espelhar(raiz->dir);
}

// Função que verifica se duas árvores são iguais
int saoIguais(No* a, No* b) {
    if (a == NULL && b == NULL) {
        return 1;
    }

    if (a == NULL || b == NULL) {
        return 0;
    }

    return (a->dado == b->dado) &&
           saoIguais(a->esq, b->esq) &&
           saoIguais(a->dir, b->dir);
}

// Função para liberar memória
void liberarArvore(No* raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esq);
        liberarArvore(raiz->dir);
        free(raiz);
    }
}

int main() {
    No* raiz = NULL;

    raiz = inserir(raiz, 10);
    inserir(raiz, 20);
    inserir(raiz, 30);
    inserir(raiz, 40);
    inserir(raiz, 50);

    printf("\nPre-ordem: ");
    preOrdem(raiz);

    printf("\nEm ordem: ");
    emOrdem(raiz);

    printf("\nPos-ordem: ");
    posOrdem(raiz);

    printf("\n\nQuantidade de nos: %d", contarNos(raiz));
    printf("\nAltura da arvore: %d", altura(raiz));
    printf("\nQuantidade de folhas: %d", contarFolhas(raiz));

    espelhar(raiz);

    printf("\n\nArvore espelhada (pre-ordem): ");
    preOrdem(raiz);

    liberarArvore(raiz);

    return 0;
}