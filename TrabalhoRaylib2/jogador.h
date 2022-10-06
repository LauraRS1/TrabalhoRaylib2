#ifndef JOGADOR_H
#define JOGADOR_H
#include "coordenadas.h"
#define TAM 15
#define MORTE -632
#define TAM_ITENS 5

/*
    Jogador:
    Representa um jogador no mapa do jogo.
    @param char nome[TAM]: string do nome do jogador.
    @param Localizacao localizacao: localizacao do jogador.
    @param int vidas: quantidade de vidas.
    @param int pontuacao: quantidade de pontos.
    @param int altura_relativa: distância em relação à posição inicial da queda.
    @param int itens[TAM_ITENS]: vetor que armazena os itens do jogador para o salvamento no binário.
        bens[0]: conta a qtde de '!'
        bens[1]: conta a qtde de '@'
        bens[2]: conta a qtde de '#'
        bens[3]: conta a qtde de '$'
        bens[4]: conta a qtde de '%'
    @param char ultimo_item[TAM]: caracter que representa o último item obtido.
*/
typedef struct{
    char nome[TAM];
    Localizacao localizacao;
    int vidas;
    int pontuacao;
    int altura_relativa;
    int itens[TAM_ITENS];
    char ultimo_item[TAM];
}Jogador;

Jogador jog_inicializa(int x, int y);
int jog_diminui_vida(Jogador *jogador);
void jog_aumenta_pontuacao(Jogador *jogador, int pontos);
void jog_le_nome(Jogador *jogador);
void jog_print_info(Jogador jogador);
void jog_guarda_item(Jogador *j, char item);
void jog_seta_entrou_ranking(Jogador *j);

#endif // COORDENADAS_H
