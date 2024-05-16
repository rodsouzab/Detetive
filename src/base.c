#include "../include/base.h"

void printColor(const char* color, const char* text) {
    printf("%s%s\033[0m", color, text); // Reseta a cor após a impressão
}

void mostrarMenuPrevio() {
    printf(GREEN "\n=============================\n" RESET);
    printf(MAGENTA "        DETETIVE\n" RESET);
    printf(GREEN "=============================\n" RESET);
    printf("1. Iniciar Jogo\n");
    printf("2. Ver Regras\n");
    printf("3. Sair\n");
    printf(GREEN "=============================\n" RESET);
    printf("Escolha uma opção: ");
}

void clearScreen() {
    printf("\033[2J\033[H"); // Limpa a tela e move o cursor para o topo
}

void lerRegras() {
    FILE *arquivo = fopen(PATH_REGRAS, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de regras.\n");
        return;
    }

    clearScreen();

    char buffer[500];
    while (fgets(buffer, 500, arquivo) != NULL) {
        printf("%s", buffer);
    }

    printf("\n");
    int c = 0;

    while (c != 1) {
        printf("\nDigite '1' para continuar:");
        printf("\n");
        scanf("%d", &c);
    }
    fclose(arquivo);
}

int jogarDado() {
    printf("Jogando o dado...");
    sleep(2);
    
    return rand() % 6 + 1; // Gera um número entre 1 e 6

    //return 20;
}



