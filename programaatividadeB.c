#include <stdio.h>
#include <stdlib.h>

// Definição do tipo do nó da lista
typedef struct No {
    int dado;            // Dado armazenado no nó
    struct No* prox;     // Ponteiro para o próximo nó
} No;

// Função para criar um novo nó
No* criarNo(int dado) {
    No* novoNo = (No*)malloc(sizeof(No));  // Alocação de memória
    if (novoNo == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);  // Se não alocar memória, encerra o programa
    }
    novoNo->dado = dado;  // Atribui o dado
    novoNo->prox = NULL;   // Inicializa o próximo ponteiro como NULL
    return novoNo;
}

// Função para inserir um nó no início da lista
void inserirInicio(No** inicio, No** fim, int dado) {
    No* novoNo = criarNo(dado);
    
    if (*inicio == NULL) {
        // Se a lista estiver vazia, o início e o fim são o mesmo nó
        *inicio = novoNo;
        *fim = novoNo;
    } else {
        novoNo->prox = *inicio;  // Aponta o novo nó para o antigo início
        *inicio = novoNo;        // Atualiza o início para o novo nó
    }
}

// Função para inserir um nó no final da lista
void inserirFim(No** inicio, No** fim, int dado) {
    No* novoNo = criarNo(dado);
    
    if (*fim == NULL) {
        // Se a lista estiver vazia, o início e o fim são o mesmo nó
        *inicio = novoNo;
        *fim = novoNo;
    } else {
        (*fim)->prox = novoNo;  // Aponta o antigo fim para o novo nó
        *fim = novoNo;          // Atualiza o fim para o novo nó
    }
}

// Função para imprimir a lista do início para o fim
void imprimirLista(No* inicio) {
    No* temp = inicio;
    printf("Lista: ");
    while (temp != NULL) {
        printf("%d ", temp->dado);
        temp = temp->prox;
    }
    printf("\n");
}

// Função para imprimir a lista do fim para o início (usando recursão)
void imprimirListaFim(No* inicio) {
    if (inicio == NULL) {
        return;  // Se a lista estiver vazia, não faz nada
    }

    // Chamada recursiva para percorrer até o final da lista
    imprimirListaFim(inicio->prox);

    // Agora imprime o dado do nó atual após percorrer a lista
    printf("%d ", inicio->dado);
}

// Função para liberar a memória da lista
void liberarLista(No* inicio) {
    No* temp;
    while (inicio != NULL) {
        temp = inicio;
        inicio = inicio->prox;
        free(temp);  // Libera cada nó
    }
}

// Função principal
int main() {
    No* inicio = NULL;  // Inicializa o início da lista como NULL
    No* fim = NULL;     // Inicializa o fim da lista como NULL
    int opcao, dado;

    // Loop principal
    while (1) {
        printf("\nEscolha uma opção:\n");
        printf("1 - Inserir no início\n");
        printf("2 - Inserir no fim\n");
        printf("3 - Imprimir lista (início para fim)\n");
        printf("4 - Imprimir lista (fim para início)\n");
        printf("5 - Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o dado para inserir no início: ");
                scanf("%d", &dado);
                inserirInicio(&inicio, &fim, dado);
                break;
            case 2:
                printf("Digite o dado para inserir no fim: ");
                scanf("%d", &dado);
                inserirFim(&inicio, &fim, dado);
                break;
            case 3:
                imprimirLista(inicio);
                break;
            case 4:
                printf("Lista (do fim para o início): ");
                imprimirListaFim(inicio);  // Chama a função corrigida
                printf("\n");
                break;
            case 5:
                liberarLista(inicio);
                return 0;
            default:
                printf("Opção inválida.\n");
                break;
        }
    }

    return 0;
}
