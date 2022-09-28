#include "jogador.h"
#include "coordenadas.h"
#include <string.h>
#include <stdio.h>

Jogador jog_inicializa(int x, int y){
    Jogador jogador = {"Sem Nome", {x, y}, 3, 0, 1};
    return jogador;
}

int jog_diminui_vida(Jogador *jogador){
    if(jogador->vidas > 0){
        jogador->vidas = jogador->vidas -1;
        return 1;
    }else{
        jogador->vidas = MORTE;

        return MORTE;
    }
}

void jog_guarda_item(Jogador *j, char item) {
    switch(item) {
        case '!':
            (j->itens[0])++;
            break;

        case '@':
            (j->itens[1])++;
            break;

        case '#':
            (j->itens[2])++;
            break;

        case '$':
            (j->itens[3])++;
            break;

        case '%':
            (j->itens[4])++;
            break;
    }
}

void jog_aumenta_pontuacao(Jogador *jogador, int pontos){
    jogador->pontuacao += pontos;
    if(jogador->pontuacao < 0)
        jogador->pontuacao = 0;
}

void jog_le_nome(Jogador *jogador){
    fflush(stdin);
    char aux[TAM];
    printf("Nome do Jogador: ");
    fgets(aux, TAM, stdin);

}

void jog_print_info(Jogador jogador){
    printf("\n=======================\n"
           "JOGADOR: %s\n"
           "VIDAS:%d\n"
           "PONTUACAO:%d\n"
           "=======================\n",
           jogador.nome, jogador.vidas, jogador.pontuacao);
}


