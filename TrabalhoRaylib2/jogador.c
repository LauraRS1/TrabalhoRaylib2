#include "jogador.h"
#include "coordenadas.h"
#include <string.h>
#include <stdio.h>
Jogador jog_inicializa(int x, int y){
    Jogador jogador = {"Sem Nome", {x, y}, 3, 0};
    return jogador;
}

int jog_diminui_vida(Jogador *jogador){
    if(jogador->vidas > 0){
        jogador->vidas = jogador->vidas -1;
        return 1;
    }else{
        return 0;
    }

}

void jog_aumenta_pontuacao(Jogador *jogador, int pontos){
    jogador->pontuacao += pontos;
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


