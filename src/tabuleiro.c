#include "../include/tabuleiro.h"
#include "../include/jogador.h"

Espaco *iniciarTabuleiro() {
    Espaco *espaco = NULL;
    for (int i = 34; i >= 0; i--) {
        inserirEspaco(&espaco, i);
        switch (espaco->id){
            case 0:
                strcpy(espaco->local, "Metrô");
                break;
            case 7:
                strcpy(espaco->local, "Mansão");
                break;
            case 12:
                strcpy(espaco->local, "Prefeitura");
                break;
            case 18:
                strcpy(espaco->local, "Parque");
                break;
            case 22:
                strcpy(espaco->local, "Praia");
                break;
            case 25:
                strcpy(espaco->local, "Escola");
                break;
            case 29:
                strcpy(espaco->local, "Ponte");
                break;
            case 34:
                strcpy(espaco->local, "Ponto de Ônibus");
                break;
            default:
                strcpy(espaco->local, "\0");
                break;
        }
    }
    return espaco;
}

void inserirEspaco(Espaco **espaco, int id) {
    Espaco *novo = (Espaco*)malloc(sizeof(Espaco));
    if (novo != NULL) {
        novo->id = id;
        novo->prox = *espaco;
        novo->ant = NULL;

        if (*espaco != NULL) {
            (*espaco)->ant = novo;
        }
        *espaco = novo;
    }
}

void imprimirTabuleiroByLocal(Espaco *head) {
    Espaco *current = head;
    printf(CYAN "\n---------------------------------------------\n" RESET);
    while (current != NULL) {
        if (strcmp(current->local,"\0") != 0)
            printf(YELLOW "%s" RESET, current->local);
        else
            printf("%d", current->id);
        current = current->prox;
        if (current != NULL) {
            printf(" <=> ");
        }
    }
    printf(CYAN "\n---------------------------------------------\n" RESET);
}

Espaco *buscaEspaco(Espaco *espaco, int id) {
    if (espaco != NULL) {
        while(espaco->id != id)
            espaco = espaco->prox;
        return espaco;
    }
    return NULL;
}

int idPalpiteLocal(Espaco *espaco) {
    FILE* arquivo = fopen(PATH_CARTAS, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de cartas.\n");
        exit(0);
    }

    char buffer[100];
    int id = 0;

    while (fgets(buffer, 100, arquivo) != NULL && id < 23) {
        if (id > 15) {
             buffer[strcspn(buffer, "\n")] = 0;
            
            if (strcmp(espaco->local,buffer) == 0) {
                break;
            }
        }
        id++; 
    }
    fclose(arquivo);
    
    return id;
}