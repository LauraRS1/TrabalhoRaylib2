#include <stdio.h>
#include "raylib.h"
#include "mapa.h"
#include "desenha.h"
#include "gravidade.h"
#include "controle.h"
#include <limits.h>
#include <time.h>
#define IMAGENS 10
#define TAM 50

int main() {
    int n =0;
    int i=0;
    int morte = 0;
    int framecount = 0;
    int vida_atual;
    char nomes[IMAGENS][TAM] = {"imagens/parede.png", "imagens/jogador.png","imagens/jogador_escada.png","imagens/jogador_porta.png", "imagens/jogador_bau.png", "imagens/bau.png","imagens/escada.png", "imagens/porta_normal.png", "imagens/porta_fase.png", "imagens/parede_fundo.png" };

    srand(time(NULL));
    Mapa mapa;
    mapa_carrega(&mapa);

    InitWindow(LARGURA, ALTURA, "Jogo");
    GameScreen currentScreen = LOAD;
    SetTargetFPS(60);

    //Arquivos das imagens do jogo, devem abrir depois de iniciar a janela
    //Capa
    Texture2D capa= LoadTexture("capa.png");
    //Nivel
    Texture2D imagens[10];
    for (i=0; i<IMAGENS; i++){
        imagens[i]=LoadTexture(nomes[i]);
    }

    vida_atual = mapa.jogador.vidas;

    //Rodar enquanto nao aperta ESC
    while (!WindowShouldClose()) {

        //Comeca a desenhar a tela
        BeginDrawing();
        // Tela preta
        ClearBackground(BLACK);

        //switch de controle do jogo
        switch(currentScreen){

            case LOAD:
                desenha_load();
                if(framecount == 60)
                    currentScreen = MENU;
                break;

            case MENU:
                //Desenhando a capa e o menu
                DrawTexture(capa, 0, 20, BLUE);
                desenha_menu(n);
                //controles do menu
                controle_menu(&n, &currentScreen);
                break;

            case GAMEPLAY:
                desenha_nivel(&mapa, imagens);
                controle_gameplay_loop(&mapa, &morte, &framecount, &vida_atual, &currentScreen);
                if(framecount%10 == 0)
                    gravidade(&mapa);
                if(framecount%240 == 0)
                    jog_print_info(mapa.jogador);
                break;

            case PROXIMO:
                desenha_proximo();
                break;

            case ENDING:
                break;

        }

        EndDrawing();
        framecount++;
        if(framecount == INT_MAX)
            framecount = 61;

    }

    //Fecha a janela:
    CloseWindow();

    return 0;
}




