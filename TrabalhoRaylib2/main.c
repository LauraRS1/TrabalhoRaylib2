#include <stdio.h>
#include "raylib.h"
#include "mapa.h"
#include "desenha.h"
#include "gravidade.h"
#include "controle.h"
#include <limits.h>
#include <time.h>

int main() {
    int n;
    int morte = 0;
    int vida_atual;
    int framecount = 0;
    srand(time(NULL));
    n = 0;
    Mapa mapa;
    mapa_carrega(&mapa);
    InitWindow(LARGURA, ALTURA, "Jogo");
    GameScreen currentScreen = LOAD;
    //Quadros por segundo
    SetTargetFPS(60);

    //capa do jogo, deve abrir depois de iniciar a janela
    Texture2D capa= LoadTexture("capa.png");

    //Rodar enquanto nao aperta ESC
    morte = 0;
    vida_atual = mapa.jogador.vidas;
    while (!WindowShouldClose()) {

        switch(currentScreen){

            case LOAD:
                if(framecount == 60)
                    currentScreen = MENU;

                break;
            case MENU:
                controle_menu(&n, &currentScreen);
                //Desenhando a capa
                DrawTexture(capa, 0, 20, BLUE);
                break;

            case GAMEPLAY:
                    controle_gameplay_loop(&mapa, &morte, &framecount, &vida_atual, &currentScreen);

                    if(framecount%10 == 0)
                        gravidade(&mapa);
                    if(framecount%240 == 0)
                        jog_print_info(mapa.jogador);

                break;

            case PROXIMO:
                break;

            case ENDING:
                break;

    }

        //Comeca a desenhar a tela
        BeginDrawing();
        // Tela preta
        ClearBackground(BLACK);

        //Chama a funcao DesenhaMenu
        switch(currentScreen){
            case LOAD:
                desenha_load();
                break;

            case MENU:
                desenha_menu(n);
                break;

            case GAMEPLAY:
                desenha_nivel(&mapa);
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




