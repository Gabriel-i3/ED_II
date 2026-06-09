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

//função que conta quantos nós existe em uma árvore

int contar_nos(No* raiz) {
    if (raiz == NULL) return 0;
    return 1 + contar_nos(raiz->esq) + contar_nos(raiz->dir);
}


//função recursiva para calcular a altura de uma árvore.
int calcular_altura(No* raiz) {
    if (raiz == NULL) return -1;
    
    int max_altura_filhos = -1;
    No* filho = raiz->esq; 
    
   
    while (filho != NULL) {
        int alt_filho = calcular_altura(filho);
        if (alt_filho > max_altura_filhos) {
            max_altura_filhos = alt_filho;
        }
        filho = filho->dir;
    }
    
    return max_altura_filhos + 1;
}

//Contar quantas folhas existem

int contar_folhas(No* raiz) {
    if (raiz == NULL) return 0;
    
    if (raiz->esq == NULL) {
        return 1 + contar_folhas(raiz->dir);
    }
    
    return contar_folhas(raiz->esq) + contar_folhas(raiz->dir);
}

//Verificar se um valor existe na árvore

int buscar_valor(No* raiz, int valor) {
    if (raiz == NULL) return 0;
    if (raiz->dado == valor) return 1;
    
    return buscar_valor(raiz->esq, valor) || buscar_valor(raiz->dir, valor);
}

//imprime os nós por nível

void imprimir_nivel_especifico(No* raiz, int nivel_alvo, int nivel_atual) {
    if (raiz == NULL) return;
    
    if (nivel_atual == nivel_alvo) {
        printf("%d ", raiz->dado);
    }
    
    imprimir_nivel_especifico(raiz->esq, nivel_alvo, nivel_atual + 1); // Desce nível nos filhos
    imprimir_nivel_especifico(raiz->dir, nivel_alvo, nivel_atual);     // Mantém nível nos irmãos
}

void imprimir_por_nivel(No* raiz) {
    int h = calcular_altura(raiz);
    for (int i = 0; i <= h; i++) {
        printf("Nivel %d: ", i);
        imprimir_nivel_especifico(raiz, i, 0);
        printf("\n");
    }
}

//função para destruir/liberar toda a árvore da memória.

void destruir_arvore(No* raiz) {
    if (raiz == NULL) return;
    
    destruir_arvore(raiz->esq);
    destruir_arvore(raiz->dir);
    
    free(raiz);
}
