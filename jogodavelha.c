#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARQUIVO "jogo_da_velha.txt"

// Função para imprimir o tabuleiro
void imprimirTabuleiro(char tabuleiro[3][3]) {
    printf("\nTabuleiro atual:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%c ", tabuleiro[i][j]);  // Imprime cada célula do tabuleiro
        }
        printf("\n");
    }
    printf("\n");  // Linha em branco após o tabuleiro para melhorar a legibilidade
}

// Função para verificar se há um vencedor
int verificarVitoria(char tabuleiro[3][3]) {
    // Verificar linhas
    for (int i = 0; i < 3; i++) {
        if (tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][1] == tabuleiro[i][2] && tabuleiro[i][0] != '-') {
            return tabuleiro[i][0] == 'X' ? 1 : 2;
        }
    }

    // Verificar colunas
    for (int i = 0; i < 3; i++) {
        if (tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[1][i] == tabuleiro[2][i] && tabuleiro[0][i] != '-') {
            return tabuleiro[0][i] == 'X' ? 1 : 2;
        }
    }

    // Verificar diagonais
    if (tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2] && tabuleiro[0][0] != '-') {
        return tabuleiro[0][0] == 'X' ? 1 : 2;
    }
    if (tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0] && tabuleiro[0][2] != '-') {
        return tabuleiro[0][2] == 'X' ? 1 : 2;
    }

    return 0;  // Sem vencedor
}

// Função para ler o estado atual do jogo do arquivo
void lerArquivo(char tabuleiro[3][3], char *vezJogador) {
    FILE *arquivo = fopen(ARQUIVO, "r");

    if (arquivo == NULL) {
        // Se o arquivo não existir, inicializamos um novo jogo
        *vezJogador = 'X'; // Jogador 1 começa
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                tabuleiro[i][j] = '-';
            }
        }
        return;
    }

    // Lê a primeira linha para saber de quem é a vez
    fscanf(arquivo, "%c\n", vezJogador);

    // Lê o tabuleiro
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            fscanf(arquivo, "%c", &tabuleiro[i][j]);
        }
        fgetc(arquivo); // Lê o caractere de nova linha após cada linha do tabuleiro
    }

    fclose(arquivo);
}

// Função para escrever o estado atual do jogo no arquivo
void escreverArquivo(char tabuleiro[3][3], char vezJogador, int vencedor) {
    FILE *arquivo = fopen(ARQUIVO, "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    // Se o jogo terminou, escrevemos o vencedor
    if (vencedor != 0) {
        fprintf(arquivo, "%d\n", vencedor);
    } else {
        fprintf(arquivo, "%c\n", vezJogador);
    }

    // Escreve o tabuleiro
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            fprintf(arquivo, "%c", tabuleiro[i][j]);
        }
        fprintf(arquivo, "\n");  // Após cada linha do tabuleiro, adiciona uma quebra de linha
    }

    fclose(arquivo);
}

// Função para verificar se a jogada é válida
int jogadaValida(char tabuleiro[3][3], int linha, int coluna) {
    if (linha < 0 || linha > 2 || coluna < 0 || coluna > 2 || tabuleiro[linha][coluna] != '-') {
        return 0;  // Jogada inválida
    }
    return 1;  // Jogada válida
}

// Função principal do programa
int main() {
    char tabuleiro[3][3];
    char vezJogador;
    int linha, coluna;
    int vencedor = 0;

    // Ler o estado atual do jogo
    lerArquivo(tabuleiro, &vezJogador);

    // Verifica se alguém já ganhou
    vencedor = verificarVitoria(tabuleiro);

    if (vencedor != 0) {
        printf("Jogador %d venceu!\n", vencedor);
        imprimirTabuleiro(tabuleiro);
        
        // Perguntar se o jogador quer iniciar um novo jogo
        char resposta;
        printf("Deseja iniciar um novo jogo? (s/n): ");
        scanf(" %c", &resposta);

        if (resposta == 's' || resposta == 'S') {
            remove(ARQUIVO);  // Deleta o arquivo
            return 0;  // Encerra o programa
        } else {
            return 0;
        }
    }

    // Se o jogo não acabou, continuar o jogo
    printf("É a vez de %c jogar.\n", vezJogador);
    imprimirTabuleiro(tabuleiro);

    // Solicitar a jogada do jogador
    printf("Informe a linha (0-2) e a coluna (0-2) para a jogada: ");
    scanf("%d %d", &linha, &coluna);

    // Verificar se a jogada é válida
    if (!jogadaValida(tabuleiro, linha, coluna)) {
        printf("Jogada inválida, tente novamente.\n");
        return 0;
    }

    // Atualiza o tabuleiro
    tabuleiro[linha][coluna] = vezJogador;

    // Verificar se há vencedor após a jogada
    vencedor = verificarVitoria(tabuleiro);

    // Escrever o estado atualizado no arquivo
    escreverArquivo(tabuleiro, vezJogador == 'X' ? 'O' : 'X', vencedor);

    // Imprimir o tabuleiro atualizado
    imprimirTabuleiro(tabuleiro);

    if (vencedor != 0) {
        printf("Jogador %d venceu!\n", vencedor);
    }

    return 0;
}
