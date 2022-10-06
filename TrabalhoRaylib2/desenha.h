#ifndef DESENHA_MENU_H_INCLUDED
#define DESENHA_MENU_H_INCLUDED
#include "raylib.h"
#include "mapa.h"
#include "ranking.h"
#define OPCOES 4
#define TAMANHO_FONTE 20
#define TAMANHO_FONTE_MAIOR 60
#define TAMANHO_TEXTO 20
#define MEIO 440
#define ESPACO 160
#define ALTURA 660
#define LARGURA 880
#define QUADRADO_ALTURA 66
#define QUADRADO_LARGURA 80
#define TAMANHO_HUD 20
#define TAMANHO_CHECKPOINT 15
#define BASE_X 0
#define BASE_Y 0

void desenha_menu(int selecionada);
void desenha_nivel(Mapa *mapa, Texture2D imagens[]);
void desenha_proximo();
void desenha_load();
void desenha_hud(Mapa *mapa);
void desenha_gameover(Texture2D imagens[], int pontuacao, int ultimo_lugar, char nome_ranking[]);
void desenha_fim(Texture2D imagens[], int pontuacao, int ultimo_lugar, char nome_ranking[]);
void desenha_msg_checkpoint();
void desenha_msg_sair();
void desenha_ranking(Ranking vetor[], Texture2D imagens[]);
void desenha_nvingame();
void desenha_retorna_menu();
#endif // DESENHA_MENU_H_INCLUDED
