#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

typedef struct Carta{
    int id;
    char nome[];
} Carta;

typedef struct Espaco {
    int id;
    struct Espaco *ant;
    struct Espaco *prox;
    char local[];
} Espaco;

typedef struct Jogador{
    int id;
    struct Jogador *prox;
    Espaco espaco;
    Carta cartas[];
} Jogador;

Espaco *iniciarTabuleiro();
Jogador *iniciarJogadores(Jogador **head, Jogador **tail);
void inserirEspaco(Espaco **espaco, int id);
void imprimirTabuleiroById(Espaco *head);
void imprimirTabuleiroByLocal(Espaco *head);
void inserirJogador(Jogador **head, Jogador **tail, int id);
void imprimirJogadores(Jogador *head, Jogador *tail);

int main() {
    //Iniciando Tabuleiro
    Espaco *tabuleiroHead = iniciarTabuleiro();

    printf("Tabuleiro: ");
    imprimirTabuleiroByLocal(tabuleiroHead);

    printf("\n");

    //Iniciando Jogadores
    Jogador *jogadorHead = NULL;
    Jogador *jogadorTail = NULL;

    
    iniciarJogadores(&jogadorHead,&jogadorTail);

    printf("Jogadores: ");
    imprimirJogadores(jogadorHead,jogadorTail);
    

}

Jogador *iniciarJogadores(Jogador **head, Jogador **tail) {
    for (int i = 3; i >= 0; i--) {
        inserirJogador(&(*head),&(*tail),i);
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
            case 13:
                strcpy(espaco->local, "Prefeitura");
                break;
            case 18:
                strcpy(espaco->local, "Parque");
                break;
            case 22:
                strcpy(espaco->local, "Praia");
                break;
            case 26:
                strcpy(espaco->local, "Ponte");
                break;
            case 29:
                strcpy(espaco->local, "Ponto de Ônibus");
                break;
            default:
                strcpy(espaco->local, "\0");
                break;
        }
    }

    return espaco;
}

void inserirJogador(Jogador **head, Jogador **tail, int id) {
  Jogador *novo = (Jogador *) malloc(sizeof(Jogador));
  if(novo != NULL){
    novo->id = id;    
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
    if (novo != NULL){
        novo->id = id;    
        novo->prox = *espaco;
        novo->ant = NULL;
        
        if(*espaco!=NULL){
        (*espaco)->ant = novo;
        }    
        *espaco = novo;
    } 
}

void imprimirJogadores(Jogador *head, Jogador *tail) { 
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

