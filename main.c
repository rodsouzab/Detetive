#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// Definições de cores ANSI
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN "\x1B[36m"
#define RESET "\x1B[0m"

void printColor(const char* color, const char* text) {
    printf("%s%s\033[0m", color, text); // Reseta a cor após a impressão
}

typedef struct Carta {
    int id;
    char nome[30];
} Carta;

typedef struct Espaco {
    int id;
    struct Espaco *ant;
    struct Espaco *prox;
    char local[35];
} Espaco;

typedef struct Jogador {
    int id;
    struct Jogador *prox;
    Espaco *espaco;
    Carta cartas[5];
} Jogador;

Espaco *iniciarTabuleiro();
void *iniciarJogadores(Jogador **head, Jogador **tail, Espaco *espaco);
void inserirEspaco(Espaco **espaco, int id);
void imprimirTabuleiroByLocal(Espaco *head);
void inserirJogador(Jogador **head, Jogador **tail, int id, Espaco *espaco);
void imprimirJogadoresbyLocal(Jogador *head, Jogador *tail);
void iniciarCartas(Jogador *jogadorHead, Jogador *jogadorTail);
void bubbleSort(Jogador *jogadorHead, Jogador *jogadorTail);
void mostrarMenuPrevio();
void clearScreen();
void lerRegras();
int jogarDado();
void moverJogador(Jogador *jogador, int resultadoDado);
Espaco *buscaEspaco(Espaco *espaco, int id);

int main() {
    srand(time(NULL));
    clearScreen();

    int comando = 0;

    while (comando != 1) {
        mostrarMenuPrevio();
        scanf("%d", &comando);
        switch (comando) {
            case 1:
                break;
            case 2:
                lerRegras();
                clearScreen();
                break;
            case 3:
                exit(0);
                break;
            default:
                clearScreen();
                printf("\n\nComando Inválido, tente novamente.\n\n");
                break;
        }
    }

    Espaco *tabuleiroHead = iniciarTabuleiro();
    Espaco *espacoInicial = buscaEspaco(tabuleiroHead, 18);
    Jogador *jogadorHead = NULL;
    Jogador *jogadorTail = NULL;
    iniciarJogadores(&jogadorHead,&jogadorTail,espacoInicial);
    iniciarCartas(jogadorHead, jogadorTail);

    clearScreen();

    printf("Jogando o dado... \n");
    int resultadoDado = jogarDado();
    printf("Resultado do dado: %d\n", resultadoDado);

    printf("Iniciando Jogo...\n");
    sleep(4);

    clearScreen();

    imprimirJogadoresbyLocal(jogadorHead,jogadorTail);

}

Espaco *buscaEspaco(Espaco *espaco, int id) {
    if (espaco != NULL) {
        while(espaco->id != id)
            espaco = espaco->prox;
        return espaco;
    }
    return NULL;
}

void iniciarCartas(Jogador *jogadorHead, Jogador *jogadorTail) {
    FILE* arquivo = fopen("cartas.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de cartas.\n");
        return;
    }

    char buffer[100];
    int id = 0;
    Carta cartas[20];

    while (fgets(buffer, 100, arquivo) != NULL && id < 20) {
        cartas[id].id = id;
        strcpy(cartas[id].nome, buffer);
        id++;
    }
    fclose(arquivo);

    Jogador *aux = jogadorHead;

    do {
        int countDeck = 0;
        while (countDeck < 5) {
            int random = rand() % 20;

            if (strlen(cartas[random].nome) != 0) {
                aux->cartas[countDeck] = cartas[random];
                strcpy(cartas[random].nome, "");
                countDeck++;
            }
        }
        aux = aux->prox; // Avançar para o próximo jogador usando o ponteiro auxiliar
    } while (aux != jogadorTail->prox);

    aux = jogadorHead;

    bubbleSort(aux, jogadorTail);
}

void bubbleSort(Jogador *jogadorHead, Jogador *jogadorTail) {
    do {
        for (int n = 1; n <= 5; n++) {
            for (int j = 0; j < 4; j++) {
                if (jogadorHead->cartas[j].id > jogadorHead->cartas[j+1].id) {
                    Carta aux = jogadorHead->cartas[j];
                    jogadorHead->cartas[j] = jogadorHead->cartas[j+1];
                    jogadorHead->cartas[j+1] = aux;
                }
            }
        }
        jogadorHead = jogadorHead->prox;
    } while (jogadorHead != jogadorTail->prox);
}

void *iniciarJogadores(Jogador **head, Jogador **tail, Espaco *espaco) {
    for (int i = 3; i >= 0; i--) {
        inserirJogador(&(*head), &(*tail), i, espaco);
    }
}

Espaco *iniciarTabuleiro() {
    Espaco *espaco = NULL;
    for (int i = 29; i >= 0; i--) {
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

void inserirJogador(Jogador **head, Jogador **tail, int id, Espaco *espaco) {
  Jogador *novo = (Jogador *) malloc(sizeof(Jogador));
  if (novo != NULL) {
    novo->id = id;
    novo->espaco = espaco;
    if (*head == NULL) {
      *head = *tail = novo;
    } else {
      novo->prox = *head;
      *head = novo;
    }
    (*tail)->prox = *head;
  }
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

void imprimirJogadoresbyLocal(Jogador *head, Jogador *tail) {
    Jogador *current = head;
    printf("\nJogadores no jogo:\n");
    printf("ID\tPosição\t\tCartas\n");
    do {
        printf("%d\t%s\t\t", current->id, current->espaco->local);
        for (int i = 0; i < 5; i++) {
            printColor(GREEN, current->cartas[i].nome);
            if (i < 4) printf(", ");
        }
        printf("\n");
        current = current->prox;
    } while (current != tail->prox);
    printf("\n");
}

void imprimirTabuleiroByLocal(Espaco *head) {
    Espaco *current = head;
    printf(CYAN "\n---------------------------------------------\n" RESET);
    while (current != NULL) {
        printf("| " YELLOW "%s" RESET " ", current->local);
        current = current->prox;
        if (current != NULL) {
            printf(" <=> ");
        }
    }
    printf("|\n---------------------------------------------\n");
}

void mostrarMenuPrevio() {
    printf(GREEN "\n=============================\n" RESET);
    printf(MAGENTA "        DETETIVE 🔍\n" RESET);
    printf(GREEN "=============================\n" RESET);
    printf("1. 🕵️ Iniciar Jogo\n");
    printf("2. 📜 Ver Regras\n");
    printf("3. 🚪 Sair\n");
    printf(GREEN "=============================\n" RESET);
    printf("Escolha uma opção: ");
}

void clearScreen() {
    printf("\033[2J\033[H"); // Limpa a tela e move o cursor para o topo
}

void lerRegras() {
    FILE *arquivo = fopen("regras.txt", "r");
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
    return rand() % 6 + 1; // Gera um número entre 1 e 6
}

void moverJogador(Jogador *jogador, int resultadoDado) {
    for (int i = 0; i < resultadoDado; i++) {
        jogador->espaco = jogador->espaco->prox;
    }
    printf("Jogador %d moveu para %s\n", jogador->id, jogador->espaco->local);
}
