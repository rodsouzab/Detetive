#include "../include/carta.h"

void printAssassinos() {
    FILE* arquivo = fopen(PATH_CARTAS, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de cartas.\n");
        return;
    }

    char buffer[100];
    int id = 0;
    int c = 1;
    Carta cartas[20];

    while (fgets(buffer, 100, arquivo) != NULL && id < 8) {
        printf(GREEN"%d. %s"RESET,c,buffer);
        id++; c++;
    }
    fclose(arquivo);
}

void printArmas() {
    FILE* arquivo = fopen(PATH_CARTAS, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de cartas.\n");
        return;
    }

    char buffer[100];
    int id = 0;
    int c = 1;
    Carta cartas[20];

    while (fgets(buffer, 100, arquivo) != NULL && id < 15) {
        if (id > 7) {
            printf(GREEN"%d. %s"RESET,c,buffer);
            c++;
        }
        id++; 
    }
    fclose(arquivo);
}

void printLocais() {
    FILE* arquivo = fopen(PATH_CARTAS, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de cartas.\n");
        return;
    }

    char buffer[100];
    int id = 0;
    int c = 1;
    Carta cartas[20];

    while (fgets(buffer, 100, arquivo) != NULL && id < 23) {
        if (id > 14) {
            printf(GREEN"%d. %s"RESET,c,buffer);
            c++;
        }
        id++; 
    }
    fclose(arquivo);
}

void printCartas() {
    printf("ASSASSINOS\n");
    printAssassinos();
    printf(GREEN"--------------------------\n"RESET);
    printf("ARMAS\n");
    printArmas();
    printf(GREEN"\n--------------------------\n"RESET);
    printf("LOCAIS\n");
    printLocais();
    printf("\n");
    int comando = 0;
    while (comando != 1) {
        printf("\nDigite '1' para continuar:");
        printf("\n");
        scanf("%d", &comando);
    }
    clearScreen();
}
