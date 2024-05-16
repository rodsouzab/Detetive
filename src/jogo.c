#include "../include/jogo.h"

void loopJogo() {
    Espaco *tabuleiroHead = iniciarTabuleiro();
    Espaco *espacoInicial = buscaEspaco(tabuleiroHead, 18);
    Jogador *jogadorHead = NULL;
    Jogador *jogadorTail = NULL;
    iniciarJogadores(&jogadorHead,&jogadorTail,espacoInicial);
    Carta final[3];
    iniciarCartas(jogadorHead, jogadorTail, final);

    //printf("%s %s %s", final[0].nome, final[1].nome, final[2].nome);
    //sleep(4);

    clearScreen();

    printf("Iniciando Jogo...\n");
    sleep(4);

    clearScreen();

    int comando = 0;
    Jogador *jogadorAtual = jogadorHead;
    int turnoConfirmed = 0;
    int fimJogo = 0;
    int idGanhador = 0;

    while(1) {
        comando = 0;
        printf("Turno do Jogador %d\n", jogadorAtual->id);
        //printf("Head: %d\nTail: %d\n", jogadorHead->id, jogadorTail->id);
        //printf("%s %s %s\n", final[0].nome, final[1].nome, final[2].nome);
        while (comando != 1) {
            printf("\nDigite '1' para começar:");
            printf("\n");
            scanf("%d", &comando);
        }
        clearScreen();

        mostrarMenu(jogadorAtual, tabuleiroHead);

        scanf("%d",&comando);
        clearScreen();
        int resultadoDado; 
        switch (comando) {
            case 1:
                resultadoDado = jogarDado();
                printf("\n\nO resultado do dado foi %d", resultadoDado);
                comando = 0;
                int qtdMovimentos = resultadoDado;
                while (comando != 1) {
                    printf("\n\nDigite '1' para se locomover:");
                    printf("\n");
                    scanf("%d", &comando);
                }
                clearScreen();
                while (qtdMovimentos > 0) {
                    mostrarMenuDeMovimento(jogadorAtual,tabuleiroHead,qtdMovimentos);
                    scanf("%d",&comando);
                    clearScreen();
                    qtdMovimentos = moverJogador(jogadorAtual,comando,qtdMovimentos);
                }
                turnoConfirmed = 1;
                break;
            case 2:
                if (strcmp(jogadorAtual->espaco->local, "/0") != 0 && jogadorAtual->ultimoPalpite != jogadorAtual->espaco) {
                    int palpiteAssassino, palpiteArma, palpiteLocal;
                    printf(RED"Faça seu Palpite.\n\n"RESET);
                    printAssassinos();
                    printf("\nDigite o assassino que você quer palpitar:\n");
                    scanf("%d",&palpiteAssassino);
                    palpiteAssassino -= 1; //Correção de id
                    clearScreen();

                    printf(RED"Faça seu Palpite.\n\n"RESET);
                    printArmas();
                    printf("\nDigite a arma que você quer palpitar:\n");
                    scanf("%d",&palpiteArma);
                    palpiteArma += 7; //Correção de id
                    clearScreen();

                    palpiteLocal = idPalpiteLocal(jogadorAtual->espaco);

                    conferirPalpite(jogadorAtual, palpiteAssassino, palpiteArma, palpiteLocal);

                    jogadorAtual->ultimoPalpite = jogadorAtual->espaco;

                    turnoConfirmed = 1;
                } else turnoConfirmed = 0;
                break;
            case 3:
                if (jogadorAtual->espaco->id == 0) {
                    Jogador *aux = jogadorAtual;
                    while (aux->espaco->prox != NULL)
                        aux->espaco = aux->espaco->prox;
                    jogadorAtual->espaco = aux->espaco;
                    turnoConfirmed = 1;
                } else {
                    while (comando != 1) {
                    printf("\nComando Inválido. Digite '1' para voltar ao menu:");
                    printf("\n");
                    scanf("%d", &comando);
                    }
                    turnoConfirmed = 0;
                }
                break;
            case 4:
                if (jogadorAtual->espaco->id == 34) {
                    Jogador *aux = jogadorAtual;
                    while (aux->espaco->ant != NULL)
                        aux->espaco = aux->espaco->ant;
                    jogadorAtual->espaco = aux->espaco;
                    turnoConfirmed = 1;
                } else {
                    while (comando != 1) {
                    printf("\nComando Inválido. Digite '1' para voltar ao menu:");
                    printf("\n");
                    scanf("%d", &comando);
                    }
                    turnoConfirmed = 0;
                }
                break;
            case 5:
                if (jogadorAtual->espaco->id == 18) {
                    int palpiteAssassino, palpiteArma, palpiteLocal;
                    printf(RED"Faça seu Palpite final.\n\n"RESET);
                    printAssassinos();
                    printf("\nDigite o assassino que você quer palpitar:\n");
                    scanf("%d",&palpiteAssassino);
                    palpiteAssassino -= 1; //Correção de id
                    clearScreen();

                    printf(RED"Faça seu Palpite Final.\n\n"RESET);
                    printArmas();
                    printf("\nDigite a arma que você quer palpitar:\n");
                    scanf("%d",&palpiteArma);
                    palpiteArma += 7; //Correção de id
                    clearScreen();

                    printf(RED"Faça seu Palpite Final.\n\n"RESET);
                    printLocais();
                    printf("\nDigite o local que você quer palpitar:\n");
                    scanf("%d",&palpiteLocal);
                    palpiteLocal += 14; //Correção de id
                    clearScreen();

                    fimJogo = conferirPalpiteFinal(jogadorAtual, palpiteAssassino, palpiteArma, palpiteLocal, final);

                    if (fimJogo == 0) {
                        removerJogador(&jogadorHead, &jogadorTail, jogadorAtual->id);
                        printf(RED"JOGADOR %d FOI ELIMINADO!\n\n"RESET, jogadorAtual->id);
                        printf(RED"SUAS CARTAS ERAM:\n"RESET);
                        imprimirCartasJogador(jogadorAtual);
                        comando = 0;
                        while (comando != 1) {
                            printf("\nDigite '1' para continuar:");
                            printf("\n");
                            scanf("%d", &comando);
                        }
                        clearScreen();
                    }

                    if (fimJogo == 1)
                        idGanhador = jogadorAtual->id;
                        
                    if (jogadorHead->id == jogadorTail->id) {
                        fimJogo = 1;
                        idGanhador = jogadorHead->id;
                    }
                    
                    turnoConfirmed = 1;
                } else turnoConfirmed = 0;
                break;
            case 6: 
                printCartas();
                turnoConfirmed = 0;
                break;
            default:
                while (comando != 1) {
                    printf("\nComando Inválido. Digite '1' para voltar ao menu:");
                    printf("\n");
                    scanf("%d", &comando);
                }
                turnoConfirmed = 0;
                break;
            }
        
        if (fimJogo ==  1) {
            printf(YELLOW"FIM DE JOGO.\n\nGANHADOR: JOGADOR %d"RESET, idGanhador);
            printf(YELLOW"\n\nO Crime foi cometido pelo %s, com um(a) %s no(a) %s\n\n"RESET, final[0].nome, final[1].nome, final[2].nome);
            comando = 0;
            while (comando != 1) {
                printf("\nDigite '1' para continuar:");
                printf("\n");
                scanf("%d", &comando);
            }
            clearScreen();
            break;
        }
        
        if (turnoConfirmed == 1) {
            jogadorAtual = jogadorAtual->prox;
            turnoConfirmed = 0;
        }
    }
}

void conferirPalpite(Jogador *jogadorAtual, int idAssassino, int idArma, int idLocal) {
    Jogador *aux = jogadorAtual->prox;  
    Carta palpitesEncontrados[3];  
    int c = 0;  

    while (aux != jogadorAtual) {
        for (int i = 0; i < 5; i++) {
            if (aux->cartas[i].id == idAssassino || aux->cartas[i].id == idArma || aux->cartas[i].id == idLocal) {
                palpitesEncontrados[c] = aux->cartas[i];
                c++;
                if (c == 3) {
                    break;
                }
            }
        }
        if (c > 0) {
            break;
        }
        aux = aux->prox;  
    }

    clearScreen();

    printf("Conferindo palpite...");
    sleep(2);

    clearScreen();

    if (c == 0) {
        printf("Nenhum palpite foi confirmado.\n");
        int comando = 0;
        while (comando != 1) {
                    printf("\nDigite '1' para continuar\n");
                    printf("\n");
                    scanf("%d", &comando);
                }
        clearScreen();
        return;
    } else {
        printf(RED"O palpite foi encontrado pelo jogador %d\n\n"RESET,aux->id);
        int comando = 0;
        while (comando != 1) {
                    printf("(Jogador %d) Digite '1' para selecionar a carta que vai ser mostrada ao Jogador %d\n",(aux->id), (jogadorAtual->id));
                    printf("\n");
                    scanf("%d", &comando);
                }
        clearScreen();
        

        for (int i = 0; i < c; i++) 
            printf(GREEN"%d. %s"RESET, i + 1, palpitesEncontrados[i].nome);
            

        int escolha = 0;
        while (escolha < 1 || escolha > c) {
            printf("\n\nSelecione que carta mostrar ao Jogador %d:\n",(jogadorAtual->id));
            scanf("%d",&escolha);
        }
        clearScreen();

        comando = 0;
        while (comando != 1) {
            printf(" (Jogador %d) Carta selecionada. Digite '1' para vizualizá-la:\n", (jogadorAtual->id));
            scanf("%d",&comando);
        }
        clearScreen();

        printf("Carta Selecionada: "GREEN"%s\n"RESET,palpitesEncontrados[escolha-1].nome);

        comando = 0;
        while (comando != 1) {
            printf("\nDigite '1' para encerrar o turno: \n");
            scanf("%d",&comando);
        }
        clearScreen();
    }
}

int conferirPalpiteFinal(Jogador *jogadorAtual, int idAssassino, int idArma, int idLocal, Carta final[]) {
    Jogador *aux = jogadorAtual->prox;  
    int c = 0;  


    for (int i = 0; i < 3; i++) {
        if (final[i].id == idAssassino || final[i].id == idArma || final[i].id == idLocal) {
            c++;
        }
    }

    clearScreen();

    printf("Conferindo palpite final...");
    sleep(7);

    clearScreen();

    if (c == 3) 
        return 1;
    else 
        return 0;
    
}