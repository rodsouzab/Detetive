#ifndef BASE_H
#define BASE_H

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

#define PATH_CARTAS "cartas.txt" //Endereço do arquivo cartas.txt
#define PATH_REGRAS "regras.txt" //Endereço do arquivo regras.txt

void printColor(const char* color, const char* text);
void mostrarMenuPrevio();
void clearScreen();
void lerRegras();
int jogarDado();


#endif