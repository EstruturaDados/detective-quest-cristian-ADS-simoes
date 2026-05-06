#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_HASH 10

// --- ESTRUTURAS ---

typedef struct Sala {
    char nome[50];
    char pista[30];
    struct Sala *esquerda, *direita;
} Sala;

typedef struct {
    char pista[30];
    char suspeito[30];
} HashEntry;

HashEntry tabelaHash[TAM_HASH];

// --- FUNÇÕES DE HASH (Mestre) ---

// Função simples: soma os valores ASCII e tira o módulo
int calcularHash(char* str) {
    int soma = 0;
    for (int i = 0; str[i] != '\0'; i++) soma += str[i];
    return soma % TAM_HASH;
}

void inserirNaHash(char* pista, char* suspeito) {
    int indice = calcularHash(pista);
    // Tratamento de colisão linear simples
    while (strlen(tabelaHash[indice].pista) > 0) {
        indice = (indice + 1) % TAM_HASH;
    }
    strcpy(tabelaHash[indice].pista, pista);
    strcpy(tabelaHash[indice].suspeito, suspeito);
}

char* buscarSuspeito(char* pista) {
    int indice = calcularHash(pista);
    int inicial = indice;
    do {
        if (strcmp(tabelaHash[indice].pista, pista) == 0)
            return tabelaHash[indice].suspeito;
        indice = (indice + 1) % TAM_HASH;
    } while (indice != inicial);
    return "Desconhecido";
}

// --- FUNÇÕES DE JOGO ---

Sala* criarSala(char* nome, char* pista) {
    Sala* nova = (Sala*)malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    strcpy(nova->pista, pista);
    nova->esquerda = nova->direita = NULL;
    return nova;
}

void inicializarCaso() {
    for (int i = 0; i < TAM_HASH; i++) strcpy(tabelaHash[i].pista, "");
    
    // Relacionando Pistas a Suspeitos na Hash
    inserirNaHash("Chave Antiga", "Mordomo");
    inserirNaHash("Faca de Pao", "Cozinheiro");
    inserirNaHash("Diario Secreto", "Mordomo");
    inserirNaHash("Garrafa Quebrada", "Jardineiro");
}

void finalizarInvestigacao(char pistasEncontradas[][30], int total) {
    printf("\n--- ⚖️ RELATÓRIO FINAL DA ENIGMA STUDIOS ---\n");
    int contMordomo = 0, contCozinheiro = 0, contJardineiro = 0;

    for (int i = 0; i < total; i++) {
        char* suspeito = buscarSuspeito(pistasEncontradas[i]);
        printf("Pista: %-15s -> Suspeito: %s\n", pistasEncontradas[i], suspeito);
        
        if (strcmp(suspeito, "Mordomo") == 0) contMordomo++;
        else if (strcmp(suspeito, "Cozinheiro") == 0) contCozinheiro++;
        else if (strcmp(suspeito, "Jardineiro") == 0) contJardineiro++;
    }

    printf("\n--- CONCLUSÃO ---");
    if (contMordomo > contCozinheiro && contMordomo > contJardineiro)
        printf("\nO CULPADO É: O MORDOMO (Mais evidências encontradas)!\n");
    else
        printf("\nEvidências insuficientes para uma acusação direta.\n");
}

int main() {
    inicializarCaso();
    
    // Montagem do Mapa
    Sala* hall = criarSala("Hall", "Nenhuma");
    hall->esquerda = criarSala("Sala de Estar", "Chave Antiga");
    hall->direita = criarSala("Cozinha", "Faca de Pao");
    hall->esquerda->esquerda = criarSala("Biblioteca", "Diario Secreto");
    
    Sala* atual = hall;
    char pistasAchadas[10][30];
    int nPistas = 0;
    char escolha;

    printf("🕵️ Detective Quest: Resolva o Crime!\n");

    while (atual != NULL) {
        printf("\n📍 Local: %s", atual->nome);
        if (strcmp(atual->pista, "Nenhuma") != 0) {
            printf("\n🔍 Pista coletada: %s", atual->pista);
            strcpy(pistasAchadas[nPistas++], atual->pista);
        }

        printf("\n1. Esquerda | 2. Direita | 0. Encerrar e Acusar\nEscolha: ");
        scanf(" %c", &escolha);

        if (escolha == '0') break;
        if (escolha == '1' && atual->esquerda) atual = atual->esquerda;
        else if (escolha == '2' && atual->direita) atual = atual->direita;
        else printf("\nCaminho bloqueado!");
    }

    finalizarInvestigacao(pistasAchadas, nPistas);
    return 0;
}