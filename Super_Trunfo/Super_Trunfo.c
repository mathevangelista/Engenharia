#include <stdio.h>

// Definindo a estrutura da Carta
struct Carta {
    char estado;              // Uma letra de A até H
    char codigo[4];           // Ex: "A01" (3 + '\0')
    char cidade[50];          // Nome da cidade
    int populacao;            // Habitantes
    float area;               // Área em km²
    float pib;                // PIB em bilhões
    int pontosTuristicos;     // Número de pontos turísticos
};

int main() {
    // Criando duas cartas
    struct Carta carta1, carta2;

    // --- Entrada de dados da Carta 1 ---
    printf("=== Cadastro da Carta 1 ===\n");
    printf("Digite o Estado (A-H): ");
    scanf(" %c", &carta1.estado);

    printf("Digite o Código da Carta (ex: A01): ");
    scanf("%s", carta1.codigo);

    printf("Digite o Nome da Cidade: ");
    scanf(" %[^\n]", carta1.cidade);

    printf("Digite a População: ");
    scanf("%d", &carta1.populacao);

    printf("Digite a Área (km²): ");
    scanf("%f", &carta1.area);

    printf("Digite o PIB (em bilhões): ");
    scanf("%f", &carta1.pib);

    printf("Digite o Número de Pontos Turísticos: ");
    scanf("%d", &carta1.pontosTuristicos);

    // --- Entrada de dados da Carta 2 ---
    printf("\n=== Cadastro da Carta 2 ===\n");
    printf("Digite o Estado (A-H): ");
    scanf(" %c", &carta2.estado);

    printf("Digite o Código da Carta (ex: B02): ");
    scanf("%s", carta2.codigo);

    printf("Digite o Nome da Cidade: ");
    scanf(" %[^\n]", carta2.cidade);

    printf("Digite a População: ");
    scanf("%d", &carta2.populacao);

    printf("Digite a Área (km²): ");
    scanf("%f", &carta2.area);

    printf("Digite o PIB (em bilhões): ");
    scanf("%f", &carta2.pib);

    printf("Digite o Número de Pontos Turísticos: ");
    scanf("%d", &carta2.pontosTuristicos);

    // --- Exibindo as cartas cadastradas ---
    printf("\n=== Carta 1 ===\n");
    printf("Estado: %c\n", carta1.estado);
    printf("Código: %s\n", carta1.codigo);
    printf("Nome da Cidade: %s\n", carta1.cidade);
    printf("População: %d\n", carta1.populacao);
    printf("Área: %.2f km²\n", carta1.area);
    printf("PIB: %.2f bilhões de reais\n", carta1.pib);
    printf("Número de Pontos Turísticos: %d\n", carta1.pontosTuristicos);

    printf("\n=== Carta 2 ===\n");
    printf("Estado: %c\n", carta2.estado);
    printf("Código: %s\n", carta2.codigo);
    printf("Nome da Cidade: %s\n", carta2.cidade);
    printf("População: %d\n", carta2.populacao);
    printf("Área: %.2f km²\n", carta2.area);
    printf("PIB: %.2f bilhões de reais\n", carta2.pib);
    printf("Número de Pontos Turísticos: %d\n", carta2.pontosTuristicos);

    return 0;
}
