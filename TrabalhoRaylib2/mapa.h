#ifndef MAPA_H
#define MAPA_H
#define MAPA_L 30
#define MAPA_C 120
#include "jogador.h"
#include "coordenadas.h"
#include "bau.h"
#include "telas.h"

/*
    Mapa:
    Representa o mapa do jogo.
    @param char mapa[MAPA_L][MAPA_C]: matriz de caracteres do mapa do jogo.
    @param Localizacao dimencao: valor real da dimensão do mapa, onde o jogo ocorre.
    @param Localizacao spawn: Coordenadas do spawn do jogador, onde ele começa e onde ele renasce ao morrer.
    @param int escada: flag, determina se o jogador está numa escada.
    @param char porta: determina se o jogador está numa porta.
    @param int bau: flag, determina se o jogador está num baú.
    @param int qtdBaus: quantidade de baús do mapa.
    @param int chave: flag, determina se o jogador está com a chave.
    @param Bau baus[50]: vetor de baus do mapa.
    @param Jogador jogador: o jogador associado ao mapa.
    @param char deletado: o caracter que o jogador deleta ao se mover.
    @param int nivel: bivel do jogador.
*/
typedef struct{
    char mapa[MAPA_L][MAPA_C];
    Localizacao dimencao;
    Localizacao spawn;
    int escada;
    char porta;
    int bau;
    int qtdBaus;
    int chave;
    Bau baus[50];
    Jogador jogador;
    char deletado;
    int nivel;
}Mapa;


void mapa_carrega(Mapa *mapa);
void mapa_movimenta(Mapa *mapa, char direcao);
void mapa_localiza_jogador(Mapa *mapa);
void mapa_busca_porta(Mapa mapa, char porta, Localizacao *local_porta);
void mapa_imprime(Mapa mapa);
int mapa_bau_quantidade(Mapa *mapa);
void mapa_bau_cria(Mapa *mapa);
Localizacao mapa_set_dimencao(char mapa[MAPA_L][MAPA_C]);
void mapa_set_spawn(Mapa *mapa);
void mapa_gera_chave(Mapa *mapa);
void mapa_gera_bomba(Mapa *mapa, int fase);
void mapa_gera_outros(Mapa *mapa, int fase);
void mapa_bau_gera_itens(Mapa *mapa);
Mapa mapa_seleciona_fase(int num, GameScreen *tela);
void mapa_carrega_proxima_fase_e_jogador(Mapa *mapa, Jogador jogador);


#endif // MAPA_H
