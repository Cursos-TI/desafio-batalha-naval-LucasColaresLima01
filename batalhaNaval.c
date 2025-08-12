#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_HABILIDADE 5
#define VALOR_AGUA 0
#define VALOR_NAVIO 3
#define VALOR_HABILIDADE 5

void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = VALOR_AGUA;
        }
    }
}

void posicionarNavio(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linhaInicial, int colunaInicial, int tamanho, char orientacao) {
    // orientacao: 'H' para horizontal, 'V' para vertical
    for (int i = 0; i < tamanho; i++) {
        if (orientacao == 'H') {
            tabuleiro[linhaInicial][colunaInicial + i] = VALOR_NAVIO;
        } else if (orientacao == 'V') {
            tabuleiro[linhaInicial + i][colunaInicial] = VALOR_NAVIO;
        }
    }
}

void criarHabilidadeCone(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (i >= j && i >= (TAM_HABILIDADE - 1 - j)) habilidade[i][j] = 1;
            else habilidade[i][j] = 0;
        }
    }
}

void criarHabilidadeCruz(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (i == centro || j == centro) habilidade[i][j] = 1;
            else habilidade[i][j] = 0;
        }
    }
}

void criarHabilidadeOctaedro(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int dist = abs(i - centro) + abs(j - centro);
            if (dist <= centro) habilidade[i][j] = 1;
            else habilidade[i][j] = 0;
        }
    }
}

void sobreporHabilidade(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], int origemLinha, int origemColuna) {
    int meio = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int linhaTab = origemLinha - meio + i;
            int colTab = origemColuna - meio + j;
            if (linhaTab >= 0 && linhaTab < TAM_TABULEIRO && colTab >= 0 && colTab < TAM_TABULEIRO) {
                if (habilidade[i][j] == 1 && tabuleiro[linhaTab][colTab] == VALOR_AGUA) {
                    tabuleiro[linhaTab][colTab] = VALOR_HABILIDADE;
                }
            }
        }
    }
}

void imprimirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            if (tabuleiro[i][j] == VALOR_AGUA) printf("~ ");
            else if (tabuleiro[i][j] == VALOR_NAVIO) printf("N ");
            else if (tabuleiro[i][j] == VALOR_HABILIDADE) printf("X ");
            else printf("? ");
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];

    inicializarTabuleiro(tabuleiro);

    posicionarNavio(tabuleiro, 2, 3, 3, 'H');
    posicionarNavio(tabuleiro, 5, 6, 3, 'V');

    criarHabilidadeCone(cone);
    criarHabilidadeCruz(cruz);
    criarHabilidadeOctaedro(octaedro);

    sobreporHabilidade(tabuleiro, cone, 1, 3);
    sobreporHabilidade(tabuleiro, cruz, 5, 6);
    sobreporHabilidade(tabuleiro, octaedro, 7, 7);

    imprimirTabuleiro(tabuleiro);

    return 0;