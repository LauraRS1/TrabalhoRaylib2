#include <stdio.h>
#include "raylib.h"
#include "mapa.h"
#include "desenha.h"
#include "gravidade.h"
#include "controle.h"

int main() {
    int n;
    int morte = 0;
    int vida_atual;
    int framecount = 0;
    n = 0;
    Mapa mapa;
    mapa_carrega(&mapa);
    vida_atual = 3;
    InitWindow(LARGURA, ALTURA, "Jogo");
    GameScreen currentScreen = MENU;
    //Quadros por segundo
    SetTargetFPS(60);

    //capa do jogo, deve abrir depois de iniciar a janela
    Texture2D capa= LoadTexture("capa.png");

    //Rodar enquanto nao aperta ESC
    morte = 0;
    while (!WindowShouldClose()) {

        switch(currentScreen){

            case MENU:
                controle_menu(&n, &currentScreen);
                //Desenhando a capa
                DrawTexture(capa, 0, 20, BLUE);
                break;

            case GAMEPLAY:
                    controle_gameplay_loop(&mapa, &morte, &framecount, &vida_atual);

                    if(framecount%10 == 0)
                        gravidade(&mapa);
                    if(framecount%60 == 0)
                        printf("VIDA JOGADOR: %d\n",mapa.jogador.vidas);
                    if(framecount%60 == 0)
                        printf("VIDA ATUAL %d\n",vida_atual);
                    if(framecount%60 == 0)
                        printf("MORTE %d\n",morte);
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

            case MENU:
                desenha_menu(n);
                break;

            case GAMEPLAY:
                desenha_nivel(&mapa);
                break;

            case ENDING:
                break;

        }

        EndDrawing();
        framecount++;

    }

    //Fecha a janela:
    CloseWindow();

    return 0;
}




