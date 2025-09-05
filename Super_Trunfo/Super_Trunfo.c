#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

/* =========================
   Estruturas e Assinaturas
   ========================= */

struct Carta {
    char estado;
    char codigo[4];
    char pais[50];      // usaremos como "nome" para exibição
    int  populacao;
    float area;
    float pib;
    int  pontosTuristicos;
};

/* Utilidades de IO e validação */
static void limparBuffer(void);
static int  lerInteiro(const char *prompt, int *dest);
static int  lerInteiroFaixa(const char *prompt, int min, int max, int *dest);

/* Exibição e cadastro */
void exibirCarta(struct Carta c);
struct Carta cadastrarCarta(void);
struct Carta gerarCartaAleatoria(void);

/* Comparações (já existentes) */
void comparar(struct Carta c1, struct Carta c2, int atributo);

/* Nível mestre (NOVO) */
static float valorAtributo(const struct Carta *c, int atributo, int *inverte, char *nomeAttr, size_t n);
void compararDoisAtributosInteractivo(struct Carta c1, struct Carta c2);

/* =========================
   Implementação
   ========================= */

static void limparBuffer(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) { /* descarta */ }
}

/* Lê um inteiro com mensagem e valida se de fato veio um número */
static int lerInteiro(const char *prompt, int *dest) {
    if (prompt && *prompt) printf("%s", prompt);
    int ok = scanf("%d", dest);
    if (ok != 1) {
        printf("Entrada inválida.\n");
        limparBuffer();
        return 0;
    }
    limparBuffer();
    return 1;
}

/* Lê inteiro validando faixa [min, max] */
static int lerInteiroFaixa(const char *prompt, int min, int max, int *dest) {
    while (1) {
        if (!lerInteiro(prompt, dest)) return 0;
        if (*dest < min || *dest > max) {
            printf("Opção fora do intervalo permitido (%d a %d).\n", min, max);
            continue;
        }
        return 1;
    }
}

/* Exibe carta, com densidade calculada com proteção a área = 0 */
void exibirCarta(struct Carta c) {
    float dens = (c.area > 0.0f) ? (c.populacao / c.area) : 0.0f;
    printf("Estado: %c\n", c.estado);
    printf("Código: %s\n", c.codigo);
    printf("País: %s\n", c.pais);
    printf("População: %d\n", c.populacao);
    printf("Área: %.2f km²\n", c.area);
    printf("PIB: %.2f bilhões\n", c.pib);
    printf("Pontos Turísticos: %d\n", c.pontosTuristicos);
    printf("Densidade Demográfica: %.2f hab/km²\n", dens);
}

/* Comparação simples (mantida), com operador ternário e prints claros */
void comparar(struct Carta c1, struct Carta c2, int atributo) {
    float valor1 = 0, valor2 = 0;
    char  nomeAtributo[50] = "";
    int   invertido = 0;

    switch (atributo) {
        case 1:
            printf("\nComparando População...\n");
            valor1 = c1.populacao; valor2 = c2.populacao;
            strcpy(nomeAtributo, "População");
            break;
        case 2:
            printf("\nComparando Área...\n");
            valor1 = c1.area; valor2 = c2.area;
            strcpy(nomeAtributo, "Área (km²)");
            break;
        case 3:
            printf("\nComparando PIB...\n");
            valor1 = c1.pib; valor2 = c2.pib;
            strcpy(nomeAtributo, "PIB (bi)");
            break;
        case 4:
            printf("\nComparando Pontos Turísticos...\n");
            valor1 = c1.pontosTuristicos; valor2 = c2.pontosTuristicos;
            strcpy(nomeAtributo, "Pontos Turísticos");
            break;
        case 5:
            printf("\nComparando Densidade Demográfica...\n");
            valor1 = (c1.area > 0) ? (c1.populacao / c1.area) : 0;
            valor2 = (c2.area > 0) ? (c2.populacao / c2.area) : 0;
            strcpy(nomeAtributo, "Densidade (hab/km²)");
            invertido = 1; // vence o menor
            break;
        default:
            printf("Opção inválida!\n");
            return;
    }

    printf("%s de %s: %.2f\n", nomeAtributo, c1.pais, valor1);
    printf("%s de %s: %.2f\n", nomeAtributo, c2.pais, valor2);

    const char *res =
        (valor1 == valor2) ? "Empate!" :
        (!invertido ? ((valor1 > valor2) ? "Carta 1 venceu!" : "Carta 2 venceu!") :
                       ((valor1 < valor2) ? "Carta 1 venceu!" : "Carta 2 venceu!"));

    printf("Resultado: %s\n", res);
}

/* Cadastro manual (mantido) */
struct Carta cadastrarCarta() {
    struct Carta c;
    printf("Estado (A-H): ");
    scanf(" %c", &c.estado); limparBuffer();

    printf("Código (ex: A01): ");
    scanf("%3s", c.codigo); limparBuffer();

    printf("País: ");
    scanf(" %49[^\n]", c.pais); limparBuffer();

    lerInteiro("População: ", &c.populacao);

    printf("Área (km²): ");
    while (scanf("%f", &c.area) != 1 || c.area < 0) {
        printf("Valor inválido. Informe área >= 0: ");
        limparBuffer();
    }
    limparBuffer();

    printf("PIB (em bilhões): ");
    while (scanf("%f", &c.pib) != 1 || c.pib < 0) {
        printf("Valor inválido. Informe PIB >= 0: ");
        limparBuffer();
    }
    limparBuffer();

    lerInteiro("Pontos Turísticos: ", &c.pontosTuristicos);
    return c;
}

/* Geração aleatória (mantida) */
struct Carta gerarCartaAleatoria() {
    struct Carta c;
    c.estado = 'X';
    strcpy(c.codigo, "CPU");
    strcpy(c.pais, "Sérvia");
    c.populacao = rand() % 10000000 + 100000;   // 100 mil a 10 milhões
    c.area = (rand() % 5000) + 50;             // 50 a 5000 km²
    c.pib = (rand() % 1000) / 10.0f + 10.0f;   // 10 a 110 bilhões (aprox.)
    c.pontosTuristicos = rand() % 50 + 1;      // 1 a 50
    return c;
}

/* === NÍVEL MESTRE: apoio ===
   Retorna o valor do atributo escolhido, define se a regra é invertida (densidade)
   e escreve o nome legível do atributo. */
static float valorAtributo(const struct Carta *c, int atributo, int *inverte, char *nomeAttr, size_t n) {
    *inverte = 0;
    switch (atributo) {
        case 1:
            strncpy(nomeAttr, "População", n);
            return (float)c->populacao;
        case 2:
            strncpy(nomeAttr, "Área (km²)", n);
            return c->area;
        case 3:
            strncpy(nomeAttr, "PIB (bi)", n);
            return c->pib;
        case 4:
            strncpy(nomeAttr, "Pontos Turísticos", n);
            return (float)c->pontosTuristicos;
        case 5: {
            strncpy(nomeAttr, "Densidade (hab/km²)", n);
            *inverte = 1; // vence o menor
            return (c->area > 0.0f) ? (c->populacao / c->area) : 0.0f;
        }
        default:
            strncpy(nomeAttr, "Atributo inválido", n);
            return 0.0f;
    }
}

/* === NÍVEL MESTRE: comparação de DOIS atributos com menus dinâmicos === */
void compararDoisAtributosInteractivo(struct Carta c1, struct Carta c2) {
    int a1 = 0, a2 = 0;

    /* Primeiro menu */
    printf("\n=== Comparação Mestre: escolha DOIS atributos ===\n");
    printf("Atributos disponíveis:\n");
    printf("1 - População\n");
    printf("2 - Área (km²)\n");
    printf("3 - PIB (bi)\n");
    printf("4 - Pontos Turísticos\n");
    printf("5 - Densidade Demográfica (menor vence)\n");

    if (!lerInteiroFaixa("Escolha o 1º atributo (1-5): ", 1, 5, &a1)) {
        printf("Falha de entrada.\n");
        return;
    }

    /* Segundo menu dinâmico: oculta o atributo já escolhido */
    printf("\nAgora escolha o 2º atributo (diferente do 1º):\n");
    for (int i = 1; i <= 5; i++) {
        if (i == a1) continue; // não mostrar o já escolhido
        switch (i) {
            case 1: printf("1 - População\n"); break;
            case 2: printf("2 - Área (km²)\n"); break;
            case 3: printf("3 - PIB (bi)\n"); break;
            case 4: printf("4 - Pontos Turísticos\n"); break;
            case 5: printf("5 - Densidade Demográfica (menor vence)\n"); break;
        }
    }

    if (!lerInteiroFaixa("Escolha o 2º atributo: ", 1, 5, &a2)) {
        printf("Falha de entrada.\n");
        return;
    }
    if (a2 == a1) {
        printf("O 2º atributo não pode ser igual ao 1º. Operação cancelada.\n");
        return;
    }

    /* Obtém valores e nomes dos atributos */
    int inv1 = 0, inv2 = 0;
    char nome1[48], nome2[48];

    float c1v1 = valorAtributo(&c1, a1, &inv1, nome1, sizeof(nome1));
    float c2v1 = valorAtributo(&c2, a1, &inv1, nome1, sizeof(nome1)); // inv1 já setado pelo 1º call, reusa nome

    float c1v2 = valorAtributo(&c1, a2, &inv2, nome2, sizeof(nome2));
    float c2v2 = valorAtributo(&c2, a2, &inv2, nome2, sizeof(nome2));

    /* Exibição clara dos dados */
    printf("\n=== Resultado da Comparação Mestre ===\n");
    printf("Cartas: %s (Carta 1)  vs  %s (Carta 2)\n", c1.pais, c2.pais);

    printf("\nAtributo 1: %s%s\n", nome1, inv1 ? "  [menor vence]" : "");
    printf(" - %s: %.2f\n", c1.pais, c1v1);
    printf(" - %s: %.2f\n", c2.pais, c2v1);

    const char *vencedorA1 =
        (c1v1 == c2v1) ? "Empate" :
        (!inv1 ? ((c1v1 > c2v1) ? "Carta 1" : "Carta 2")
               : ((c1v1 < c2v1) ? "Carta 1" : "Carta 2"));
    printf("Vencedor no atributo 1: %s\n", vencedorA1);

    printf("\nAtributo 2: %s%s\n", nome2, inv2 ? "  [menor vence]" : "");
    printf(" - %s: %.2f\n", c1.pais, c1v2);
    printf(" - %s: %.2f\n", c2.pais, c2v2);

    const char *vencedorA2 =
        (c1v2 == c2v2) ? "Empate" :
        (!inv2 ? ((c1v2 > c2v2) ? "Carta 1" : "Carta 2")
               : ((c1v2 < c2v2) ? "Carta 1" : "Carta 2"));
    printf("Vencedor no atributo 2: %s\n", vencedorA2);

    /* Soma dos atributos (especificação pede soma direta dos valores) */
    float soma1 = c1v1 + c1v2;
    float soma2 = c2v1 + c2v2;

    printf("\nSoma dos atributos:\n");
    printf(" - %s: %.2f\n", c1.pais, soma1);
    printf(" - %s: %.2f\n", c2.pais, soma2);

    const char *vencedorFinal =
        (soma1 == soma2) ? "Empate!" :
        ((soma1 > soma2)  ? "Carta 1 venceu a rodada!" : "Carta 2 venceu a rodada!");

    printf("\nResultado Final: %s\n", vencedorFinal);
}

/* =========================
   MAIN (mantendo o fluxo prévio e adicionando a opção 6)
   ========================= */
int main() {
    srand((unsigned)time(NULL));

    struct Carta carta1, carta2;
    int modo = 0, opcao = 0, continuar = 0;

    printf("=== Super Trunfo Digital ===\n");
    printf("1 - Jogar contra Player 2\n");
    printf("2 - Jogar contra o Computador\n");
    if (!lerInteiroFaixa("Escolha o modo: ", 1, 2, &modo)) {
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

    /* Loop do menu de comparação (mantido) + opção mestre (novo item 6) */
    do {
        printf("\n=== Menu de Comparação ===\n");
        printf("1 - População\n");
        printf("2 - Área\n");
        printf("3 - PIB\n");
        printf("4 - Pontos Turísticos\n");
        printf("5 - Densidade Demográfica (menor vence)\n");
        printf("6 - Comparação Mestre (escolher 2 atributos)\n");

        if (!lerInteiroFaixa("Escolha uma opção: ", 1, 6, &opcao)) {
            printf("Entrada inválida! Encerrando...\n");
            return 1;
        }

        switch (opcao) {
            case 1: case 2: case 3: case 4: case 5:
                comparar(carta1, carta2, opcao);
                break;
            case 6:
                compararDoisAtributosInteractivo(carta1, carta2);
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }

        if (!lerInteiroFaixa("\nDeseja voltar ao menu de comparação? (1 = Sim, 0 = Não): ", 0, 1, &continuar)) {
            printf("Entrada inválida! Encerrando...\n");
            return 1;
        }
    } while (continuar == 1);

    printf("\nObrigado por jogar Super Trunfo Digital!\n");
    return 0;
}
