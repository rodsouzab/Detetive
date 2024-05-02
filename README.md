# Especificação Detetive
## Introdução
O jogo é uma releitura do clássico jogo de tabuleiro "Detetive". Nele, os jogadores assumem o papel de detetives investigando um crime misterioso. Com elementos de estratégia e dedução, os participantes devem utilizar suas habilidades de raciocínio lógico para resolver o caso e identificar o culpado, a arma do crime e o local onde ocorreu.


## Objetivo do Jogo
O objetivo do jogo é usar a dedução para solucionar o crime daquela partida, descobrindo quem cometeu o crime, qual arma foi utilizada e onde ocorreu o crime.

Para chegar a tal conclusão, os detetives devem se locomover pelo tabuleiro até chegar nas localizações, na qual ele fará um palpite sobre o crime, contendo um assassino, uma arma e o local em que ele está. Será verificado, então, se os próximos jogadores possuem uma das cartas do palpite e o participante que tiver alguma, o mostra para o detetive em questão (se ele houver mais de uma, ele escolhe qual mostrar). O jogador não pode fazer um palpite no mesmo lugar duas vezes seguidas.

Assim que algum jogador chegar a uma conclusão final sobre o assassinato, ele pode se dirigir até um local específico no tabuleiro, onde ele fará seu palpite final e, se estiver certo, ganha o jogo. Todavia, se esse palpite estiver errado, ele é eliminado e o jogo segue normalmente.


## Estruturas de Dados utilizadas

Array: Para armazenar as cartas de cada jogador, permitindo acesso rápido e fácil manipulação durante a troca de informações e deduções.

Lista Duplamente Encadeada: Para gerenciar os jogadores e os espaços no tabuleiro. As listas encadeadas permitem inserções e deleções eficientes de elementos, o que é crucial em um jogo dinâmico onde os jogadores podem ser eliminados ou mover-se livremente pelo tabuleiro.

Lista Circular Simplesmente Encadeada: Será utilizada para “conectar” todos os jogadores, uma vez que o jogo exige constantemente a verificação das cartas de outros componentes (o que será feito através dos ponteiros de cada elemento), além disso, será utilizada para gerenciar os turnos de cada participante.


## Algoritmo de Ordenação Utilizado.

Bubble Sort: Utilizado para ordenar as cartas de suspeitos, locais ou armas durante a fase de preparação do jogo. Isso ajudará a organizar as cartas que cada jogador recebe, facilitando a verificação rápida e a estratégia durante o jogo. O Bubble Sort foi escolhido por sua simplicidade e por ser suficientemente eficiente para o conjunto limitado de cartas que cada jogador manuseia.


## Principais funções a serem utilizadas
Inicialização do Jogo: Criar funções para inicializar o jogo, distribuir cartas e preparar o tabuleiro.

Movimento: Implementar a lógica para mover os jogadores pelo tabuleiro. Isso pode envolver alterar o índice do espaço do jogador na lista do tabuleiro.

Palpites: Desenvolver o mecanismo para que os jogadores façam palpites sobre as cartas dos outros jogadores quando chegam em uma nova localização do tabuleiro.

Checagem de Palpite: Desenvolver lógica que percorra a lista de jogadores e verifique qual tem uma carta referente no palpite em questão, esse poderá selecionar qual carta quer mostrar para o detetive que fez o palpite (se houver mais de uma).

Checagem de Palpite Final: Implementar a verificação do palpite final de um jogador e determinar se ele ganhou ou foi eliminado.


## Referências Bibliográficas
Estrela S/A. (1988). Clue [Jogo de tabuleiro]. Brasil: Estrela.
