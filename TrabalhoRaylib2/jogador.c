#include "jogador.h"
#include "coordenadas.h"
#include <string.h>
#include <stdio.h>

/*  jog_inicializa:
    Retorna um jogador com os dados iniciais de uma partida
    @param x: Linha que o jogador se encontra
    @param y: Coluna que o jogador se encontra

*/
Jogador jog_inicializa(int x, int y){
    Jogador jogador = {"---", {x, y}, 3, 0, 1};
    return jogador;
}


/*  jog_diminui_vida:

    Diminui a vida do jogador
    @param *jogador: Ponteiro para um jogador

*/
int jog_diminui_vida(Jogador *jogador){
    if(jogador->vidas > 0){
        jogador->vidas = jogador->vidas -1;
        return 1;
    }else{
        jogador->vidas = MORTE;

        return MORTE;
    }
}

/*  jog_guarda_item:
    Aumenta a quantidade de um determinado item que o jogador possui
    @param j: Ponteiro para um jogador
    @param item: Item que o jogador coletou

*/
void jog_guarda_item(Jogador *j, char item) {
    switch(item) {
        case '!':
            //Ametista 50 pontos
            (j->itens[0])++;
             j->colecao[0]='!';
            break;

        case '@':
            //Safira 100 pontos
            (j->itens[1])++;
            j->colecao[1]='@';
            break;

        case '#':
            //Rubi 150 pontos
            (j->itens[2])++;
            j->colecao[2]='#';
            break;

        case '$':
            //Anel 200 pontos
            (j->itens[3])++;
            j->colecao[3]='$';
            break;

        case '%':
            //Coroa 300 pontos
            (j->itens[4])++;
            j->colecao[4]='%';
            break;
    }
}

/*  jog_guarda_item:
    Aumenta a quantidade de pontos que um jogador possui
    @param *jogador: Ponteiro para um jogador
    @param  pontos: Pontos a serem adicionados

*/
void jog_aumenta_pontuacao(Jogador *jogador, int pontos){
    jogador->pontuacao += pontos;
    if(jogador->pontuacao < 0)
        jogador->pontuacao = 0;
}

void jog_seta_entrou_ranking(Jogador *j) {
    j->entrou_ranking = 0;
}

void jog_le_nome(Jogador *jogador){
    fflush(stdin); // limpa o buffer de entrada
    printf("\nDigite o nome do jogador: ");
    fgets(jogador->nome, TAM, stdin);
    jogador->nome[strlen(jogador->nome) - 1] = '\0';

}

void jog_print_info(Jogador jogador){
    printf("\n=======================\n"
           "JOGADOR: %s\n"
           "VIDAS:%d\n"
           "PONTUACAO:%d\n"
           "=======================\n",
           jogador.nome, jogador.vidas, jogador.pontuacao);
}


