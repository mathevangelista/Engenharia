#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura da Carta
struct Carta {
    char estado;
    char codigo[4];
    char cidade[50];
    int populacao;
    float area;
    float pib;
    int pontosTuristicos;
};

// Função para exibir os dados de uma carta
void exibirCarta(struct Carta c) {
    printf("Estado: %c\n", c.estado);
    printf("Código: %s\n", c.codigo);
    printf("Cidade: %s\n", c.cidade);
    printf("População: %d\n", c.populacao);
    printf("Área: %.2f km²\n", c.area);
    printf("PIB: %.2f bilhões\n", c.pib);
    printf("Pontos Turísticos: %d\n", c.pontosTuristicos);
    printf("Densidade Demográfica: %.2f hab/km²\n", (c.area > 0) ? (c.populacao / c.area) : 0);
}

// Função de comparação (com ternário e exibição detalhada)
void comparar(struct Carta c1, struct Carta c2, int atributo) {
    float valor1, valor2;
    char nomeAtributo[50];
    int invertido = 0; // usado para densidade

    switch (atributo) {
        case 1:
            printf("\nComparando População...\n");
            valor1 = c1.populacao;
            valor2 = c2.populacao;
            strcpy(nomeAtributo, "População");
            break;
        case 2:
            printf("\nComparando Área...\n");
            valor1 = c1.area;
            valor2 = c2.area;
            strcpy(nomeAtributo, "Área (km²)");
            break;
        case 3:
            printf("\nComparando PIB...\n");
            valor1 = c1.pib;
            valor2 = c2.pib;
            strcpy(nomeAtributo, "PIB (bi)");
            break;
        case 4:
            printf("\nComparando Pontos Turísticos...\n");
            valor1 = c1.pontosTuristicos;
            valor2 = c2.pontosTuristicos;
            strcpy(nomeAtributo, "Pontos Turísticos");
            break;
        case 5:
            printf("\nComparando Densidade Demográfica...\n");
            valor1 = (c1.area > 0) ? (c1.populacao / c1.area) : 0;
            valor2 = (c2.area > 0) ? (c2.populacao / c2.area) : 0;
            strcpy(nomeAtributo, "Densidade (hab/km²)");
            invertido = 1; // aqui vence o menor
            break;
        default:
            printf("Opção inválida!\n");
            return;
    }

    // Mostrar valores antes do resultado
    printf("%s da %s: %.2f\n", nomeAtributo, c1.cidade, valor1);
    printf("%s da %s: %.2f\n", nomeAtributo, c2.cidade, valor2);

    // Comparação com regra de inversão para densidade
    const char *resultado =
        (valor1 == valor2) ? "Empate!" :
        (!invertido ? ((valor1 > valor2) ? "Carta 1 venceu!" : "Carta 2 venceu!") :
                       ((valor1 < valor2) ? "Carta 1 venceu!" : "Carta 2 venceu!"));

    printf("Resultado: %s\n", resultado);
}

// Função para cadastrar manualmente uma carta
struct Carta cadastrarCarta() {
    struct Carta c;
    printf("Estado (A-H): ");
    scanf(" %c", &c.estado);

    printf("Código (ex: A01): ");
    scanf("%s", c.codigo);

    printf("Cidade: ");
    scanf(" %[^\n]", c.cidade);

    printf("População: ");
    scanf("%d", &c.populacao);

    printf("Área (km²): ");
    scanf("%f", &c.area);

    printf("PIB (em bilhões): ");
    scanf("%f", &c.pib);

    printf("Pontos Turísticos: ");
    scanf("%d", &c.pontosTuristicos);

    return c;
}

// Função para gerar carta aleatória (computador)
struct Carta gerarCartaAleatoria() {
    struct Carta c;
    c.estado = 'X'; // computador
    strcpy(c.codigo, "CPU");
    strcpy(c.cidade, "Cidade Aleatória");
    c.populacao = rand() % 10000000 + 100000;   // entre 100 mil e 10 milhões
    c.area = (rand() % 5000) + 50;             // entre 50 e 5000 km²
    c.pib = (rand() % 1000) / 10.0 + 10;       // entre 10 e 100 bilhões
    c.pontosTuristicos = rand() % 50 + 1;      // entre 1 e 50 pontos
    return c;
}

int main() {
    srand(time(NULL));
    struct Carta carta1, carta2;
    int modo, opcao, continuar;

    printf("=== Super Trunfo Digital ===\n");
    printf("1 - Jogar contra Player 2\n");
    printf("2 - Jogar contra o Computador\n");
    printf("Escolha o modo: ");
    if (scanf("%d", &modo) != 1 || (modo != 1 && modo != 2)) {
        printf("Entrada inválida! Encerrando...\n");
        return 1;
    }

    printf("\n=== Cadastro da Carta 1 ===\n");
    carta1 = cadastrarCarta();

    if (modo == 1) {
        printf("\n=== Cadastro da Carta 2 (Player 2) ===\n");
        carta2 = cadastrarCarta();
    } else {
        printf("\nGerando carta do Computador...\n");
        carta2 = gerarCartaAleatoria();
    }

    printf("\n=== Carta 1 ===\n");
    exibirCarta(carta1);

    printf("\n=== Carta 2 ===\n");
    exibirCarta(carta2);

    // Loop do menu de comparação
    do {
        printf("\n=== Menu de Comparação ===\n");
        printf("1 - População\n");
        printf("2 - Área\n");
        printf("3 - PIB\n");
        printf("4 - Pontos Turísticos\n");
        printf("5 - Densidade Demográfica\n");
        printf("Escolha uma opção: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida! Encerrando...\n");
            return 1;
        }

        comparar(carta1, carta2, opcao);

        // Pergunta se deseja continuar
        printf("\nDeseja voltar ao menu de comparação? (1 = Sim, 0 = Não): ");
        if (scanf("%d", &continuar) != 1) {
            printf("Entrada inválida! Encerrando...\n");
            return 1;
        }

    } while (continuar == 1);

    printf("\nObrigado por jogar Super Trunfo Digital!\n");
    return 0;
}
