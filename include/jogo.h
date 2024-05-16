#ifndef JOGO_H
#define JOGO_H

#include "jogador.h"

void loopJogo();
void conferirPalpite(Jogador *jogadorAtual, int idAssassino, int idArma, int idLocal);
int conferirPalpiteFinal(Jogador *jogadorAtual, int idAssassino, int idArma, int idLocal, Carta final[]);


#endif