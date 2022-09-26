#ifndef JOGADOR_H
#define JOGADOR_H
#include "coordenadas.h"
#define TAM 15
#define MORTE -632
typedef struct{
    char nome[TAM];
    Localizacao localizacao;
    int vidas;
    int pontuacao;
    int altura_relativa;
}Jogador;

Jogador jog_inicializa(int x, int y);
int jog_diminui_vida(Jogador *jogador);
void jog_aumenta_pontuacao(Jogador *jogador, int pontos);
void jog_le_nome(Jogador *jogador);
void jog_print_info(Jogador jogador);
#endif // COORDENADAS_H
