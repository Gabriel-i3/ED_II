#include <stdio.h>
#include <stdlib.h>

//Definição da estrutura do nó para a Árvore Binária de Busca
typedef struct No {
    int dado;
    struct No* esq;
    struct No* dir; 
} No;

//Função para inserir um valor na ABB usando recursão
No* inserir(No* raiz, int valor) {
    if (raiz == NULL) {
        No* novo = (No*)malloc(sizeof(No));
        if (novo != NULL) {
            novo->dado = valor;
            novo->esq = NULL;
            novo->dir = NULL;
        }
        return novo;
    }

    if (valor < raiz->dado) {
        raiz->esq = inserir(raiz->esq, valor);
    } else if (valor > raiz->dado) {
        raiz->dir = inserir(raiz->dir, valor);
    }
    return raiz;
}

//Função de busca na ABB
No* buscar(No* raiz, int valor) {
    if (raiz == NULL || raiz->dado == valor) {
        return raiz;
    }

    if (valor < raiz->dado) {
        return buscar(raiz->esq, valor);
    }
    return buscar(raiz->dir, valor);
}

//Percurso em ordem (imprime os valores ordenados)
void em_ordem(No* raiz) {
    if (raiz != NULL) {
        em_ordem(raiz->esq);
        printf("%d ", raiz->dado);
        em_ordem(raiz->dir);
    }
}

//Função auxiliar para encontrar o menor nó (mais à esquerda)
No* encontrar_menor(No* raiz) {
    No* atual = raiz;
    while (atual && atual->esq != NULL) {
        atual = atual->esq;
    }
    return atual;
}

//Função auxiliar para encontrar o maior nó (mais à direita)
No* encontrar_maior(No* raiz) {
    No* atual = raiz;
    while (atual && atual->dir != NULL) {
        atual = atual->dir;
    }
    return atual;
}

//Função para remover um nó da ABB (Trata nós folhas, 1 filho e 2 filhos)
No* remover(No* raiz, int valor) {
    if (raiz == NULL) return NULL;

    if (valor < raiz->dado) {
        raiz->esq = remover(raiz->esq, valor);
    } else if (valor > raiz->dado) {
        raiz->dir = remover(raiz->dir, valor);
    } else {
        //Caso 1: Nó folha (sem filhos)
        if (raiz->esq == NULL && raiz->dir == NULL) {
            free(raiz);
            return NULL;
        }
        //Caso 2: Apenas um filho na direita
        else if (raiz->esq == NULL) {
            No* aux = raiz->dir;
            free(raiz);
            return aux;
        } 
        //Caso 2: Apenas um filho na esquerda
        else if (raiz->dir == NULL) {
            No* aux = raiz->esq;
            free(raiz);
            return aux;
        }
        //Caso 3: Nó com dois filhos (usa o sucessor em ordem)
        else {
            No* aux = encontrar_menor(raiz->dir);
            raiz->dado = aux->dado;
            raiz->dir = remover(raiz->dir, aux->dado);
        }
    }
    return raiz;
}

//Função para verificar se a árvore é uma ABB válida
int eh_abb_valida(No* raiz, No* min, No* max) {
    if (raiz == NULL) return 1;

    if ((min != NULL && raiz->dado <= min->dado) || 
        (max != NULL && raiz->dado >= max->dado)) {
        return 0;
    }

    return eh_abb_valida(raiz->esq, min, raiz) && 
           eh_abb_valida(raiz->dir, raiz, max);
}

//Função para contar a quantidade de níveis da árvore
int contar_niveis(No* raiz) {
    if (raiz == NULL) return 0;

    int alt_esq = contar_niveis(raiz->esq);
    int alt_dir = contar_niveis(raiz->dir);

    return (alt_esq > alt_dir ? alt_esq : alt_dir) + 1;
}

//Função para liberar toda a memória alocada pela árvore
void destruir_arvore(No* raiz) {
    if (raiz != NULL) {
        destruir_arvore(raiz->esq);
        destruir_arvore(raiz->dir);
        free(raiz);
    }
}

//Programa principal com menu interativo
int main() {
    No* raiz = NULL;
    int opcao, valor;
    No* busca_resultado;

    do {
        printf("\n========= MENU ABB =========\n");
        printf("1. Inserir\n");
        printf("2. Buscar\n");
        printf("3. Remover\n");
        printf("4. Imprimir em ordem\n");
        printf("5. Mostrar altura / Niveis\n");
        printf("6. Mostrar Menor e Maior\n");
        printf("7. Validar se e ABB\n");
        printf("0. Encerrar\n");
        printf("============================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o valor para inserir: ");
                scanf("%d", &valor);
                raiz = inserir(raiz, valor);
                printf("Valor %d inserido.\n", valor);
                break;

            case 2:
                printf("Digite o valor para buscar: ");
                scanf("%d", &valor);
                busca_resultado = buscar(raiz, valor);
                if (busca_resultado != NULL) {
                    printf("Elemento %d encontrado!\n", busca_resultado->dado);
                } else {
                    printf("Elemento %d nao encontrado.\n", valor);
                }
                break;

            case 3:
                printf("Digite o valor para remover: ");
                scanf("%d", &valor);
                if (buscar(raiz, valor) != NULL) {
                    raiz = remover(raiz, valor);
                    printf("Valor %d removido.\n", valor);
                } else {
                    printf("Valor %d nao existe na arvore.\n", valor);
                }
                break;

            case 4:
                printf("Caminhamento em ordem: ");
                if (raiz == NULL) printf("Arvore vazia.");
                else em_ordem(raiz);
                printf("\n");
                break;

            case 5:
                printf("Quantidade de niveis: %d\n", contar_niveis(raiz));
                printf("Altura da arvore (arestas): %d\n", contar_niveis(raiz) - 1);
                break;

            case 6:
                if (raiz != NULL) {
                    printf("Menor valor: %d\n", encontrar_menor(raiz)->dado);
                    printf("Maior valor: %d\n", encontrar_maior(raiz)->dado);
                } else {
                    printf("Arvore vazia.\n");
                }
                break;

            case 7:
                if (eh_abb_valida(raiz, NULL, NULL)) {
                    printf("A arvore e uma ABB VALIDA.\n");
                } else {
                    printf("A arvore NAO E uma ABB valida.\n");
                }
                break;

            case 0:
                printf("Encerrando e liberando memoria...\n");
                destruir_arvore(raiz);
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}
