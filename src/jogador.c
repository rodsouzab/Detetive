#include "../include/jogador.h"

void *iniciarJogadores(Jogador **head, Jogador **tail, Espaco *espaco) {
    for (int i = 4; i >= 1; i--) {
        inserirJogador(&(*head), &(*tail), i, espaco);
    }
}

void inserirJogador(Jogador **head, Jogador **tail, int id, Espaco *espaco) {
  Jogador *novo = (Jogador *) malloc(sizeof(Jogador));
  if (novo != NULL) {
    novo->id = id;
    novo->espaco = espaco;
    novo->ultimoPalpite = espaco;
    if (*head == NULL) {
      *head = *tail = novo;
    } else {
      novo->prox = *head;
      *head = novo;
    }
    (*tail)->prox = *head;
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
            printf("\t\t\t");
        }
        printf("\n");
        current = current->prox;
    } while (current != tail->prox);
    printf("\n");
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

int moverJogador(Jogador *jogador, int sentido, int qtdMovimentos) {
    if (sentido == 1) {
        if (jogador->espaco->id != 0) {
            jogador->espaco = jogador->espaco->ant;
            qtdMovimentos--;
        }
    }
    if (sentido == 2) {
        if (jogador->espaco->id != 34) {
            jogador->espaco = jogador->espaco->prox;
            qtdMovimentos--;
        }
    }
    if (sentido == 3) {
        qtdMovimentos = 0;
    }
    return qtdMovimentos;
}

void imprimirCartasJogador(Jogador *jogador) {
    for (int i = 0; i < 5; i++) {
            printColor(GREEN, jogador->cartas[i].nome);
            printf("\n");
        }
        printf("\n");
};

void removerJogador(Jogador **jogadorHead, Jogador **jogadorTail, int id) {
    if (*jogadorHead != NULL) {
        Jogador *aux = *jogadorHead;
        while (aux->id != id)
            aux = aux->prox;
        if (aux == *jogadorHead) {
            *jogadorHead = (*jogadorHead)->prox;
            (*jogadorTail)->prox = *jogadorHead;
        } else {
            Jogador *aux2 = *jogadorHead;
            while (aux2->prox != aux)
                aux2 = aux2->prox;
            aux2->prox = aux->prox;
            if (aux2->prox == aux2) {
                *jogadorHead = *jogadorTail;
            }
        }
    }
}

void mostrarMenu(Jogador *jogadorAtual, Espaco *tabuleiroHead) {
    printf("Tabuleiro:");
    imprimirTabuleiroByLocal(tabuleiroHead);

    printf("\nSuas Cartas:\n");
    imprimirCartasJogador(jogadorAtual);

    if (strcmp(jogadorAtual->espaco->local,"\0") != 0)
        printf("Você está no(a) %s\n",jogadorAtual->espaco->local);
    else
        printf("Você está no espaço %d\n",jogadorAtual->espaco->id);

    printf("\nDigite o que você deseja fazer: \n");
    printf("1. Jogar Dado\n");
    if (strcmp(jogadorAtual->espaco->local,"\0") != 0 && jogadorAtual->ultimoPalpite != jogadorAtual->espaco)
        printf("2. Fazer Palpite\n");
    if (jogadorAtual->espaco->id == 0)
        printf("3. Ir para Ponto de Ônibus\n");
    if (jogadorAtual->espaco->id == 34)
        printf("4. Ir para Metrô\n");
    if (jogadorAtual->espaco->id == 18)
        printf("5. Fazer Palpite Final\n");
    printf("6. Ver Todas as Cartas\n");
}

void mostrarMenuDeMovimento(Jogador *jogadorAtual, Espaco *tabuleiroHead, int qtdMovimentos) {
    printf("Tabuleiro:");
    imprimirTabuleiroByLocal(tabuleiroHead);

    if (strcmp(jogadorAtual->espaco->local,"\0") != 0)
        printf("\nVocê está no(a) %s\n",jogadorAtual->espaco->local);
    else
        printf("\nVocê está no espaço %d\n",jogadorAtual->espaco->id);

    printf("\nMovimentos restantes: %d\n", qtdMovimentos);

    printf("\nDigite o que você deseja fazer: \n");
    printf("1. Mover para a esquerda\n");
    printf("2. Mover para a direita\n");
    printf("3. Parar\n");
}

void iniciarCartas(Jogador *jogadorHead, Jogador *jogadorTail, Carta final[3]) {
    FILE* arquivo = fopen(PATH_CARTAS, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de cartas.\n");
        return;
    }

    char buffer[100];
    int id = 0;
    Carta cartas[23];

    while (fgets(buffer, 100, arquivo) != NULL && id < 23) {
        buffer[strcspn(buffer, "\n")] = 0; 
        cartas[id].id = id;
        strcpy(cartas[id].nome, buffer);
        id++;
    }
    fclose(arquivo);

    int r1 = rand() % 8; // Assassino
    final[0] = cartas[r1];
    strcpy(cartas[r1].nome, "");

    int r2 = rand() % 7 + 8; // Arma
    final[1] = cartas[r2];
    strcpy(cartas[r2].nome, "");

    int r3 = (rand() % 8) + 15; // Local
    final[2] = cartas[r3];
    strcpy(cartas[r3].nome, "");




    Jogador *aux = jogadorHead;

    do {
        int countDeck = 0;
        while (countDeck < 5) {
            int random = rand() % 23;

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