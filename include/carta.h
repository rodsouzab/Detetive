#ifndef CARTA_H
#define CARTA_H

#include "base.h"

typedef struct Carta {
    int id;
    char nome[30];
} Carta;

void printAssassinos();
void printArmas();
void printLocais();
void printCartas();

#endif