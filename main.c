#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

typedef struct Carta{
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
void imprimirTabuleiroById(Espaco *head);
void imprimirTabuleiroByLocal(Espaco *head);
void inserirJogador(Jogador **head, Jogador **tail, int id, Espaco *espaaco);
void imprimirJogadoresbyLocal(Jogador *head, Jogador *tail);
void imprimirJogadoresbyId(Jogador *head, Jogador *tail);
void iniciarCartas(Jogador *jogadorHead, Jogador *jogadorTail);
void imprimirCartasTotal(Jogador *jogadorHead, Jogador *jogadorTail);
void bubbleSort(Jogador *jogadorHead, Jogador *jogadorTail);
void mostrarMenuPrevio();
void clearScreen();
void lerRegras();
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

    //Iniciando Jogo
    Espaco *tabuleiroHead = iniciarTabuleiro();
    Espaco *espacoInicial = buscaEspaco(tabuleiroHead, 18);
    Jogador *jogadorHead = NULL;
    Jogador *jogadorTail = NULL;
    iniciarJogadores(&jogadorHead,&jogadorTail,espacoInicial);
    iniciarCartas(jogadorHead, jogadorTail);
    
    clearScreen();

    printf("Iniciando Jogo...\n");
    sleep(4);

    clearScreen();

    //Teste de Impressão
    imprimirJogadoresbyLocal(jogadorHead,jogadorTail);
    imprimirJogadoresbyId(jogadorHead,jogadorTail);
        
    
}

Espaco *buscaEspaco(Espaco *espaco, int id) {
    if (espaco != NULL) {
        while(espaco->id != id)
            espaco = espaco->prox;
        return espaco;
    }
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
    
    // Inicializar as cartas
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
                    // Troca os elementos se estiverem fora de ordem
                    Carta aux = jogadorHead->cartas[j];
                    jogadorHead->cartas[j] = jogadorHead->cartas[j+1];
                    jogadorHead->cartas[j+1] = aux;
                }
            }
        }
        jogadorHead = jogadorHead->prox;
    } while (jogadorHead != jogadorTail->prox);
    

}



void imprimirCartasTotal(Jogador *jogadorHead, Jogador *jogadorTail) {
    Jogador *aux = jogadorHead;


    do  {
        printf("Jogador %d:\n",(aux->id) + 1);
        
        for (int i = 0; i < 5; i++) {
            printf("Carta %d: %s\n", i + 1, aux->cartas[i].nome);
        }
        
        printf("\n");
        
        aux = aux->prox;
    } while (aux != jogadorTail->prox);
}

void *iniciarJogadores(Jogador **head, Jogador **tail, Espaco *espaco) {
    for (int i = 3; i >= 0; i--) {
        inserirJogador(&(*head),&(*tail),i, espaco);
    }
}

Espaco *iniciarTabuleiro() {
    Espaco *espaco = NULL;
    for (int i = 29; i >= 0; i--) {
        inserirEspaco(&espaco,i);
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
  if(novo != NULL){
    novo->id = id;  
    novo->espaco = espaco;  
    if(*head==NULL){
      *head = *tail = novo;
    }else{
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
  if(head != NULL){  
    do{
      printf("-> %s ",head->espaco->local);
      head = head->prox;
    }while(head != tail->prox);
    printf("->");
  }
  printf("\n");
}

void imprimirJogadoresbyId(Jogador *head, Jogador *tail) { 
  if(head != NULL){  
    do{
      printf("-> %d ",head->id);
      head = head->prox;
    }while(head != tail->prox);
    printf("->");
  }
  printf("\n");
}

void imprimirTabuleiroById(Espaco *head) {
    while(head != NULL) {
      printf("%d",head->id);
      if (head->id != 29)
        printf(" <=>");
      head = head->prox;
    }
    printf("\n");
}

void imprimirTabuleiroByLocal(Espaco *head) {
    while(head != NULL) {
        if (strcmp(head->local,"\0") == 0) {
            printf("NULL");
        }
        else {
            printf("%s",head->local);
        }
        if (head->id != 29)
        printf(" <=> ");
        head = head->prox;
    }
    printf("\n");
}

void mostrarMenuPrevio() {
    printf("Menu Principal\n");
    printf("1. Iniciar Jogo\n");
    printf("2. Ver Regras\n");
    printf("3. Sair\n");
    printf("Escolha uma opção: ");
};

void clearScreen() {
    printf("\033[2J\033[H"); 
}

void lerRegras() {
    FILE* arquivo = fopen("regras.txt", "r");
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
        printf("\n");
        printf("Digite '1' para continuar:");
        printf("\n");
        scanf("%d", &c);
    }
    fclose(arquivo);
}