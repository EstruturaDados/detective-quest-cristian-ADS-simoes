#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- ESTRUTURAS ---

// Árvore Binária do Mapa
typedef struct Sala {
    char nome[50];
    char pista[30]; // Pista que existe nesta sala
    struct Sala *esquerda, *direita;
} Sala;

// Árvore de Busca Binária (BST) para o Inventário de Pistas
typedef struct Pista {
    char descricao[30];
    struct Pista *esq, *dir;
} Pista;

// --- FUNÇÕES DE PISTAS (BST) ---

Pista* inserirPista(Pista* raiz, char* descricao) {
    if (raiz == NULL) {
        Pista* novo = (Pista*)malloc(sizeof(Pista));
        strcpy(novo->descricao, descricao);
        novo->esq = novo->dir = NULL;
        return novo;
    }
    if (strcmp(descricao, raiz->descricao) < 0)
        raiz->esq = inserirPista(raiz->esq, descricao);
    else if (strcmp(descricao, raiz->descricao) > 0)
        raiz->dir = inserirPista(raiz->dir, descricao);
    return raiz;
}

void exibirPistasEmOrdem(Pista* raiz) {
    if (raiz != NULL) {
        exibirPistasEmOrdem(raiz->esq);
        printf("- %s\n", raiz->descricao);
        exibirPistasEmOrdem(raiz->dir);
    }
}

// --- FUNÇÕES DO MAPA ---

Sala* criarSala(char* nome, char* pista) {
    Sala* nova = (Sala*)malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    strcpy(nova->pista, pista);
    nova->esquerda = nova->direita = NULL;
    return nova;
}

Sala* montarMansao() {
    Sala* hall = criarSala("Hall de Entrada", "Nenhuma");
    hall->esquerda = criarSala("Sala de Estar", "Chave Antiga");
    hall->direita = criarSala("Cozinha", "Faca de Pao");
    hall->esquerda->esquerda = criarSala("Biblioteca", "Diario Secreto");
    hall->direita->direita = criarSala("Adega", "Garrafa Quebrada");
    return hall;
}

void explorar(Sala* mapa) {
    Sala* atual = mapa;
    Pista* inventario = NULL;
    char escolha;

    while (atual != NULL) {
        printf("\n📍 Local atual: %s", atual->nome);
        
        // Coleta automática de pista se houver
        if (strcmp(atual->pista, "Nenhuma") != 0) {
            printf("\n🔍 Voce encontrou uma pista: %s!", atual->pista);
            inventario = inserirPista(inventario, atual->pista);
        }

        printf("\n\n1. Ir para Esquerda | 2. Ir para Direita | 3. Ver Inventario de Pistas | 0. Sair\nEscolha: ");
        scanf(" %c", &escolha);

        if (escolha == '0') break;
        else if (escolha == '1' && atual->esquerda) atual = atual->esquerda;
        else if (escolha == '2' && atual->direita) atual = atual->direita;
        else if (escolha == '3') {
            printf("\n--- 📂 INVENTARIO (ORDEM ALFABETICA) ---\n");
            if (inventario == NULL) printf("Vazio.\n");
            else exibirPistasEmOrdem(inventario);
        } else printf("\nCaminho sem saida ou opcao invalida!");
    }
}

int main() {
    srand(0);
    Sala* mansao = montarMansao();
    explorar(mansao);
    return 0;
}