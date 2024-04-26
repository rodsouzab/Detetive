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
void inserirEspaco(Espaco **espaco, int id);
void imprimirTabuleiro(Espaco *head);

int main() {

    Espaco *tabuleiro = iniciarTabuleiro();

    imprimirTabuleiro(tabuleiro);

}

Espaco *iniciarTabuleiro() {
    Espaco *espaco = NULL;
    for (int i = 29; i >= 0; i--) {
        inserirEspaco(&espaco,i);
    }
    
    return espaco;
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

void imprimirTabuleiro(Espaco *head) {
    while(head != NULL) {
      printf("%d <-> ",head->id);
      head = head->prox;
    }
    printf("NULL\n");
}