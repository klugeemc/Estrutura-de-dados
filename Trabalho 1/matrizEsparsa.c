#include <stdio.h>
#include <stdlib.h>

// definição da lista para armazenar os elementos não nulos
struct lista {
    int linha;
    int coluna;
    int info;
    struct lista* prox;
};
typedef struct lista Lista;

// definição da matriz esparsa
struct esparsa {
    int linhas;
    int colunas;
    Lista* prim; // aponta para o primeiro elemento não nulo
};
typedef struct esparsa Esparsa;

// cria matriz esparsa
Esparsa* criarMatriz(int linhas, int colunas) {
    Esparsa* m = (Esparsa*) malloc(sizeof(Esparsa));
    if (m == NULL) {
        printf("Erro de alocação!\n");
        exit(1);
    }
    m->linhas = linhas;
    m->colunas = colunas;
    m->prim = NULL;
    return m;
}

// insere elemento não nulo na lista
void inserirElemento(Esparsa* m, int linha, int coluna, int valor) {
    if (valor == 0) return; // não insere zeros
    
    Lista* novo = (Lista*) malloc(sizeof(Lista));
    if (novo == NULL) {
        printf("Erro de alocação!\n");
        exit(1);
    }
    novo->linha = linha;
    novo->coluna = coluna;
    novo->info = valor;
    novo->prox = m->prim;
    m->prim = novo;
}

// preenchimento da matriz (lê só não nulos)
void preencherMatriz(Esparsa* m) {
    int qtd;
    printf("Quantos elementos nao nulos deseja inserir? ");
    scanf("%d", &qtd);

    for (int i = 0; i < qtd; i++) {
        int l, c, v;
        printf("Elemento %d:\n", i+1);
        printf("  Linha: "); scanf("%d", &l);
        printf("  Coluna: "); scanf("%d", &c);
        printf("  Valor: "); scanf("%d", &v);
        if (l >= 0 && l < m->linhas && c >= 0 && c < m->colunas)
            inserirElemento(m, l, c, v);
        else
            printf("Posição inválida!\n");
    }
}

// imprime a matriz completa
void imprimirMatriz(Esparsa* m) {
    printf("\nMatriz esparsa (%dx%d):\n", m->linhas, m->colunas);
    for (int i = 0; i < m->linhas; i++) {
        for (int j = 0; j < m->colunas; j++) {
            int valor = 0;
            for (Lista* p = m->prim; p != NULL; p = p->prox) {
                if (p->linha == i && p->coluna == j) {
                    valor = p->info;
                    break;
                }
            }
            printf("%3d ", valor);
        }
        printf("\n");
    }
}

// consulta elemento em linha,coluna
int consultarElemento(Esparsa* m, int linha, int coluna) {
    if (linha < 0 || linha >= m->linhas || coluna < 0 || coluna >= m->colunas) {
        printf("Índices inválidos!\n");
        return 0;
    }
    for (Lista* p = m->prim; p != NULL; p = p->prox) {
        if (p->linha == linha && p->coluna == coluna) {
            return p->info;
        }
    }
    return 0; // se não está na lista, é zero
}

// somatório de uma linha i
int somatorioLinha(Esparsa* m, int linha) {
    int soma = 0;
    for (Lista* p = m->prim; p != NULL; p = p->prox) {
        if (p->linha == linha) {
            soma += p->info;
        }
    }
    return soma;
}

// percentual de não nulos
float percentualNaoNulos(Esparsa* m) {
    int total = m->linhas * m->colunas;
    int qtd = 0;
    for (Lista* p = m->prim; p != NULL; p = p->prox)
        qtd++;
    return (qtd * 100.0) / total;
}

// liberar memória
void liberarMatriz(Esparsa* m) {
    Lista* p = m->prim;
    while (p != NULL) {
        Lista* aux = p;
        p = p->prox;
        free(aux);
    }
    free(m);
}

// programa principal
int main() {
    int linhas, colunas;
    printf("Digite numero de linhas e colunas da matriz: ");
    scanf("%d %d", &linhas, &colunas);

    Esparsa* m = criarMatriz(linhas, colunas);

    preencherMatriz(m);
    imprimirMatriz(m);

    // consulta de elemento
    int l, c;
    printf("\nConsultar elemento (linha coluna): ");
    scanf("%d %d", &l, &c);
    printf("Elemento [%d][%d] = %d\n", l, c, consultarElemento(m, l, c));

    // somatório da linha
    int linhaSomatorio;
    printf("\nDigite a linha para calcular o somatorio: ");
    scanf("%d", &linhaSomatorio);
    printf("Somatorio da linha %d = %d\n", linhaSomatorio, somatorioLinha(m, linhaSomatorio));

    // percentual não nulos
    printf("\nPercentual de elementos nao nulos: %.2f%%\n", percentualNaoNulos(m));

    liberarMatriz(m);
    return 0;
}
