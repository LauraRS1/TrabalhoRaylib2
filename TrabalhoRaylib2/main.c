#include <stdio.h>
#include "raylib.h"
#include "mapa.h"
#include "desenha.h"
#include "gravidade.h"
#include "controle.h"
#include <limits.h>
#include <time.h>

int main() {
    int n =0;
    int morte = 0;
    int framecount = 0;
    int vida_atual;

    srand(time(NULL));
    Mapa mapa;
    mapa_carrega(&mapa);

    InitWindow(LARGURA, ALTURA, "Jogo");
    GameScreen currentScreen = LOAD;
    SetTargetFPS(60);

    //capa do jogo, deve abrir depois de iniciar a janela
    Texture2D capa= LoadTexture("capa.png");
    //vetor de imagens
    Texture2D imagens = LoadTexture("imagens/parede.png");


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
                //Desenhando a capa
                DrawTexture(imagens, 0, 0, BLUE);
                DrawTexture(capa, 0, 20, BLUE);
                desenha_menu(n);
                controle_menu(&n, &currentScreen);
                break;

            case GAMEPLAY:
                desenha_nivel(&mapa);
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




