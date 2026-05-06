#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura que representa uma sala (nó da árvore)
typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// Função para criar uma nova sala
Sala* criarSala(char* nome) {
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    strcpy(novaSala->nome, nome);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    return novaSala;
}

// Função para montar o mapa da mansão (Árvore Binária Estática)
Sala* montarMansao() {
    // Nível 0: Raiz
    Sala* hall = criarSala("Hall de Entrada");

    // Nível 1
    hall->esquerda = criarSala("Sala de Estar");
    hall->direita = criarSala("Cozinha");

    // Nível 2 (Folhas)
    hall->esquerda->esquerda = criarSala("Biblioteca (Fim)");
    hall->esquerda->direita = criarSala("Jardim de Inverno (Fim)");
    hall->direita->esquerda = criarSala("Despensa (Fim)");
    hall->direita->direita = criarSala("Adega (Fim)");

    return hall;
}

// Função de exploração interativa
void explorarMansao(Sala* atual) {
    char escolha;

    while (atual != NULL) {
        printf("\nVocê está no(a): %s", atual->nome);

        // Se for um nó-folha (sem saídas), a exploração termina
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("\nVocê chegou ao fim deste caminho.\n");
            break;
        }

        printf("\nPara onde deseja ir? (e - Esquerda / d - Direita / s - Sair): ");
        scanf(" %c", &escolha);

        if (escolha == 's') {
            printf("Saindo da investigação...\n");
            break;
        } else if (escolha == 'e') {
            if (atual->esquerda != NULL) atual = atual->esquerda;
            else printf("Caminho bloqueado!\n");
        } else if (escolha == 'd') {
            if (atual->direita != NULL) atual = atual->direita;
            else printf("Caminho bloqueado!\n");
        } else {
            printf("Opção inválida!\n");
        }
    }
}

int main() {
    printf("--- 🕵️ DETECTIVE QUEST: O MISTÉRIO DA MANSÃO ---\n");
    
    // Montagem da estrutura
    Sala* mansao = montarMansao();

    // Início do jogo
    explorarMansao(mansao);

    return 0;
}