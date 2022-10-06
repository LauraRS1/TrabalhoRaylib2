#ifndef CONTROLE_H
#define CONTROLE_H
#include "telas.h"
void controle_menu(int *n, GameScreen *tela, Mapa *mapa, int *vida_atual);
void controle_gameplay(Mapa *mapa, GameScreen *tela);
void controle_abre_bau(Mapa *mapa);
void controle_proxima_fase(Mapa *mapa, GameScreen *tela);
void controle_gameplay_loop(Mapa *mapa, int *morte, int *frames, int *vida_atual, GameScreen *tela);
void controle_njingame(GameScreen *tela, Mapa *mapa, int *vida_atual);
void controle_retorna_menu(GameScreen *tela, Mapa *mapa);
#endif // CONTROLE
