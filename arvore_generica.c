#include <stdio.h>
#include <stdlib.h>

//estrura de um nó para uma árvore generica.

typedef struct No {
    int dado;
    struct No* esq;  
    struct No* dir;  
} No;