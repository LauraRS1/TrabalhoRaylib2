#ifndef JOGADOR_H
#define JOGADOR_H
#include "coordenadas.h"
#define TAM 15
#define MORTE -632
#define TAM_ITENS 5

/*
bens[0]: conta a qtde de '!'
bens[1]: conta a qtde de '@'
bens[2]: conta a qtde de '#'
bens[3]: conta a qtde de '$'
bens[4]: conta a qtde de '%'
*/
typedef struct{
    char nome[TAM];
    Localizacao localizacao;
    int vidas;
    int pontuacao;
    int altura_relativa;
    int itens[TAM_ITENS];
}Jogador;

Jogador jog_inicializa(int x, int y);
int jog_diminui_vida(Jogador *jogador);
void jog_aumenta_pontuacao(Jogador *jogador, int pontos);
void jog_le_nome(Jogador *jogador);
void jog_print_info(Jogador jogador);
void jog_guarda_item(Jogador *j, char item);
#endif // COORDENADAS_H
