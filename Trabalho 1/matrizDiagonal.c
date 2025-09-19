#include <stdio.h>
#include <stdlib.h>

// definição da struct
struct diagonal {
    int ordem; // ordem da matriz
    int *v;    // vetor que guarda apenas os elementos da diagonal principal
};
typedef struct diagonal Diagonal;

// função para criar a matriz diagonal
Diagonal* criarDiagonal(int ordem) {
    Diagonal *d = (Diagonal*) malloc(sizeof(Diagonal));
    if (d == NULL) {
        printf("Erro ao alocar memória para a estrutura.\n");
        exit(1);
    }
    d->ordem = ordem;
    d->v = (int*) malloc(ordem * sizeof(int));
    if (d->v == NULL) {
        printf("Erro ao alocar memória para o vetor da diagonal.\n");
        free(d);
        exit(1);
    }
    return d;
}

// preencher a diagonal
void preencherDiagonal(Diagonal *d) {
    for (int i = 0; i < d->ordem; i++) {
        printf("Digite o valor da posição [%d][%d]: ", i, i);
        scanf("%d", &d->v[i]);
    }
}

// imprimir a matriz completa
void imprimirDiagonal(Diagonal *d) {
    printf("\nMatriz diagonal (%dx%d):\n", d->ordem, d->ordem);
    for (int i = 0; i < d->ordem; i++) {
        for (int j = 0; j < d->ordem; j++) {
            if (i == j)
                printf("%3d ", d->v[i]);
            else
                printf("%3d ", 0);
        }
        printf("\n");
    }
}

// consultar elemento
int consultarElemento(Diagonal *d, int linha, int coluna) {
    if (linha < 0 || linha >= d->ordem || coluna < 0 || coluna >= d->ordem) {
        printf("Índices fora dos limites da matriz!\n");
        return 0;
    }
    if (linha == coluna)
        return d->v[linha];
    else
        return 0; // fora da diagonal sempre é 0
}

// liberar memória
void liberarDiagonal(Diagonal *d) {
    free(d->v);
    free(d);
}

// programa principal
int main() {
    int ordem;
    printf("Digite a ordem da matriz diagonal: ");
    scanf("%d", &ordem);

    Diagonal *d = criarDiagonal(ordem);

    preencherDiagonal(d);
    imprimirDiagonal(d);

    // consulta
    int linha, coluna;
    printf("\nDigite linha e coluna para consultar: ");
    scanf("%d %d", &linha, &coluna);
    int valor = consultarElemento(d, linha, coluna);
    printf("Elemento na posição [%d][%d] = %d\n", linha, coluna, valor);

    liberarDiagonal(d);
    return 0;
}