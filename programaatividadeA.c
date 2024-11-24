#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int ID;      // ID ou RA do aluno
    float P1;    // Nota da Prova 1
    float P2;    // Nota da Prova 2
    float media; // Média do aluno
} cadastro;

// Função para criar o cadastro de alunos
cadastro* Criar_alunos(int n) {
    cadastro* alunos = (cadastro*)malloc(n * sizeof(cadastro)); // Alocação dinâmica

    for (int i = 0; i < n; i++) {
        alunos[i].ID = i + 1;  // ID começando a partir de 1
        alunos[i].P1 = 0.0;    // Inicializa nota P1 com 0
        alunos[i].P2 = 0.0;    // Inicializa nota P2 com 0
        alunos[i].media = 0.0; // Inicializa média com 0
    }

    return alunos;
}

// Função para inserir as notas P1 e P2 de cada aluno
void Inserir_notas(cadastro* alunos, int n) {
    for (int i = 0; i < n; i++) {
        printf("\nDigite as notas para o aluno %d\n", alunos[i].ID);
        printf("Nota da P1: ");
        scanf("%f", &alunos[i].P1);
        printf("Nota da P2: ");
        scanf("%f", &alunos[i].P2);

        // Calcula a média
        alunos[i].media = (alunos[i].P1 + alunos[i].P2) / 2.0;
        printf("Aluno %d - Média: %.2f\n", alunos[i].ID, alunos[i].media);
    }
}

// Função para modificar a nota de um aluno
void Modificar_nota(cadastro* alunos, int n, int ID, int P) {
    if (ID < 1 || ID > n) {
        printf("Aluno com ID %d não existe.\n", ID);
        return;
    }

    float novaNota;
    printf("Digite a nova nota para a P%d do aluno %d: ", P, ID);
    scanf("%f", &novaNota);

    if (P == 1) {
        alunos[ID - 1].P1 = novaNota;  // Atualiza P1
    } else if (P == 2) {
        alunos[ID - 1].P2 = novaNota;  // Atualiza P2
    } else {
        printf("Nota inválida (P deve ser 1 ou 2).\n");
    }

    // Após modificar a nota, recalcula a média
    alunos[ID - 1].media = (alunos[ID - 1].P1 + alunos[ID - 1].P2) / 2.0;
    printf("Aluno %d - Média: %.2f\n", ID, alunos[ID - 1].media);
}

// Função para calcular e atualizar a média do aluno
void Calcular_media(cadastro* alunos, int ID) {
    alunos[ID - 1].media = (alunos[ID - 1].P1 + alunos[ID - 1].P2) / 2.0;
}

// Função para determinar o aluno com maior média
void Determinar_maior_media(cadastro* alunos, int n) {
    int idMaior = 0;
    float maiorMedia = -1.0;

    for (int i = 0; i < n; i++) {
        if (alunos[i].media > maiorMedia) {
            maiorMedia = alunos[i].media;
            idMaior = alunos[i].ID;
        }
    }

    printf("Aluno com maior média: %d\n", idMaior);
}

// Função principal
int main() {
    int n;

    printf("Digite o número de alunos: ");
    scanf("%d", &n);

    // Criar alunos
    cadastro* alunos = Criar_alunos(n);

    // Inserir as notas P1 e P2 para todos os alunos cadastrados
    Inserir_notas(alunos, n);

    while (1) {
        int ID, P;

        printf("\nDigite o ID do aluno e o número da prova (1 para P1, 2 para P2) ou 0 para terminar: ");
        scanf("%d", &ID);

        if (ID == 0) {
            Determinar_maior_media(alunos, n); // Determina o aluno com maior média
            free(alunos); // Libera a memória alocada
            return 0;     // Finaliza o programa
        }

        printf("Digite o número da prova (1 para P1, 2 para P2): ");
        scanf("%d", &P);

        Modificar_nota(alunos, n, ID, P); // Modifica a nota conforme a entrada
    }

    return 0;
}
