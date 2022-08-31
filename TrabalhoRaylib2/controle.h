#ifndef CONTROLE_H
#define CONTROLE_H
#include "telas.h"
void controle_menu(int *n, GameScreen *tela);
void controle_gameplay(Mapa *mapa, GameScreen *tela);
void controle_abre_bau(Mapa *mapa);
void controle_proxima_fase(Mapa *mapa, GameScreen *tela);
void controle_gameplay_loop(Mapa *mapa, int *morte, int *frames, int *vida_atual, GameScreen *tela);
#endif // CONTROLE
