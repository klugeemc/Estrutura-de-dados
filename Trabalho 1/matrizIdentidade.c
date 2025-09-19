#include <stdio.h>
#include <stdlib.h>

// nó da lista de violações
struct noh {
    int linha;
    int coluna;
    int valor;
    struct noh* prox;
};
typedef struct noh Noh;

// struct da matriz identidade
struct identidade {
    int ordem;
    Noh* violacoes; // elementos que violam a identidade
};
typedef struct identidade Identidade;

// cria a estrutura
Identidade* criarMatriz(int ordem) {
    Identidade* m = (Identidade*) malloc(sizeof(Identidade));
    if (m == NULL) {
        printf("Erro de alocacao!\n");
        exit(1);
    }
    m->ordem = ordem;
    m->violacoes = NULL;
    return m;
}

// insere violação na lista
void inserirViolacao(Identidade* m, int linha, int coluna, int valor) {
    Noh* novo = (Noh*) malloc(sizeof(Noh));
    if (novo == NULL) {
        printf("Erro de alocacao!\n");
        exit(1);
    }
    novo->linha = linha;
    novo->coluna = coluna;
    novo->valor = valor;
    novo->prox = m->violacoes;
    m->violacoes = novo;
}

// preenchimento da matriz + verificação
void preencherMatriz(Identidade* m) {
    int valor;
    for (int i = 0; i < m->ordem; i++) {
        for (int j = 0; j < m->ordem; j++) {
            printf("Elemento [%d][%d]: ", i, j);
            scanf("%d", &valor);

            // condição de identidade
            if ((i == j && valor != 1) || (i != j && valor != 0)) {
                inserirViolacao(m, i, j, valor);
            }
        }
    }
}

// imprime resultado
void verificarIdentidade(Identidade* m) {
    if (m->violacoes == NULL) {
        printf("\nA matriz E identidade.\n");
    } else {
        printf("\nA matriz NAO e identidade.\n");
        printf("Elementos que violam a propriedade:\n");
        for (Noh* p = m->violacoes; p != NULL; p = p->prox) {
            printf("  Posicao [%d][%d] = %d\n", p->linha, p->coluna, p->valor);
        }
    }
}

// liberar memória
void liberarMatriz(Identidade* m) {
    Noh* p = m->violacoes;
    while (p != NULL) {
        Noh* aux = p;
        p = p->prox;
        free(aux);
    }
    free(m);
}

// programa principal
int main() {
    int ordem;
    printf("Digite a ordem da matriz: ");
    scanf("%d", &ordem);

    Identidade* m = criarMatriz(ordem);

    preencherMatriz(m);
    verificarIdentidade(m);

    liberarMatriz(m);
    return 0;
}
