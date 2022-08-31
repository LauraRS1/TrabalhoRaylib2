#ifndef DESENHA_MENU_H_INCLUDED
#define DESENHA_MENU_H_INCLUDED
#include "raylib.h"
#include "mapa.h"
#define OPCOES 4
#define TAMANHO_FONTE 20
#define TAMANHO_FONTE_MAIOR 60
#define TAMANHO_TEXTO 20
#define MEIO 400
#define ESPACO 160
#define ALTURA 660
#define LARGURA 800
#define QUADRADO_ALTURA 66
#define QUADRADO_LARGURA 80

void desenha_menu(int selecionada);
void desenha_nivel(Mapa *mapa);
void desenha_proximo();
void desenha_load();

#endif // DESENHA_MENU_H_INCLUDED