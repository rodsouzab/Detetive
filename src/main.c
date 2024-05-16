#include <locale.h>
#include "../include/jogo.h"
#include "../include/jogador.h"
#include "../include/base.h"
#include "../include/carta.h"
#include "../include/tabuleiro.h"

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");

    srand(time(NULL));
    clearScreen();

    int comando = 0;

    while (1) {
        mostrarMenuPrevio();
        scanf("%d", &comando);
        switch (comando) {
            case 1:
                loopJogo();
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
}