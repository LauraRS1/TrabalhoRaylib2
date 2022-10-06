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
    char itens[TAM][TAM]={"Ametista","Safira","Rubi","Anel","Coroa","Bomba","Chave"};

    switch(item) {
        case '!':
            //Ametista 50 pontos
            (j->itens[0])++;
             strcpy(j->ultimo_item, itens[0]);
            break;

        case '@':
            //Safira 100 pontos
            (j->itens[1])++;
            strcpy(j->ultimo_item, itens[1]);
            break;

        case '#':
            //Rubi 150 pontos
            (j->itens[2])++;
            strcpy(j->ultimo_item, itens[2]);
            break;

        case '$':
            //Anel 200 pontos
            (j->itens[3])++;
            strcpy(j->ultimo_item, itens[3]);
            break;

        case '%':
            //Coroa 300 pontos
            (j->itens[4])++;
            strcpy(j->ultimo_item, itens[4]);
            break;
         case 'B':
            //Bomba
            strcpy(j->ultimo_item, itens[5]);
            break;
        case 'P':
            //Chave
            strcpy(j->ultimo_item, itens[6]);
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

/*
    jog_print_info:
    Imprime as informações do jogador na tela.
    @param Jogador jogador: um jogador
*/
void jog_print_info(Jogador jogador){
    printf("\n=======================\n"
           "JOGADOR: %s\n"
           "VIDAS:%d\n"
           "PONTUACAO:%d\n"
           "=======================\n",
           jogador.nome, jogador.vidas, jogador.pontuacao);
}

