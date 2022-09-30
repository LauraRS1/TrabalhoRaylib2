#ifndef DESENHA_MENU_H_INCLUDED
#define DESENHA_MENU_H_INCLUDED
#include "raylib.h"
#include "mapa.h"
#define OPCOES 4
#define TAMANHO_FONTE 20
#define TAMANHO_FONTE_MAIOR 60
#define TAMANHO_TEXTO 20
#define MEIO 620
#define ESPACO 160
#define ALTURA 720
#define LARGURA 1280
#define QUADRADO_ALTURA 66
#define QUADRADO_LARGURA 80
#define TAMANHO_HUD 50
#define TAMANHO_CHECKPOINT 15
#define BASE_X 0
#define BASE_Y 0

void desenha_menu(int selecionada);
void desenha_nivel(Mapa *mapa, Texture2D imagens[]);
void desenha_proximo();
void desenha_load();
void desenha_hud(Mapa *mapa);
void desenha_gameover();
void desenha_fim();
void desenha_msg_checkpoint();
void desenha_msg_sair();
#endif // DESENHA_MENU_H_INCLUDED
