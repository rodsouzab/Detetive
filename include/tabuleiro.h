#ifndef TABULEIRO_H
#define TABULEIRO_H

#include "base.h"

typedef struct Espaco {
    int id;
    struct Espaco *ant;
    struct Espaco *prox;
    char local[35];
} Espaco;

Espaco *iniciarTabuleiro();
void inserirEspaco(Espaco **espaco, int id);
void imprimirTabuleiroByLocal(Espaco *head);
Espaco *buscaEspaco(Espaco *espaco, int id);
int idPalpiteLocal(Espaco *espaco);


#endif