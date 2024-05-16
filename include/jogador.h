#ifndef JOGADOR_H
#define JOGADOR_H

#include "tabuleiro.h"
#include "carta.h"

typedef struct Jogador {
    int id;
    struct Jogador *prox;
    Espaco *espaco;
    Carta cartas[5];
    Espaco *ultimoPalpite;
} Jogador;

void *iniciarJogadores(Jogador **head, Jogador **tail, Espaco *espaco);
void inserirJogador(Jogador **head, Jogador **tail, int id, Espaco *espaco);
void imprimirJogadoresbyLocal(Jogador *head, Jogador *tail);
void bubbleSort(Jogador *jogadorHead, Jogador *jogadorTail);
int moverJogador(Jogador *jogador, int sentido, int qtdMovimentos);
void imprimirCartasJogador(Jogador *jogador);
void removerJogador(Jogador **jogadorHead, Jogador **jogadorTail, int id);
void mostrarMenu(Jogador *jogadorAtual, Espaco *tabuleiroHead);
void mostrarMenuDeMovimento(Jogador *jogadorAtual, Espaco *tabuleiroHead, int qtdMovimentos);
void iniciarCartas(Jogador *jogadorHead, Jogador *jogadorTail, Carta final[3]);


#endif