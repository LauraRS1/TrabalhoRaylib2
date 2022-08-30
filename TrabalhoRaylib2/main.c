#include <stdio.h>
#include "raylib.h"
#include "mapa.h"
#include "desenha.h"
#include "gravidade.h"
#include "controle.h"

int main() {
    int n;
    int morte = 0;
    n = 0;
    Mapa mapa;
    mapa_carrega(&mapa);

    InitWindow(LARGURA, ALTURA, "Jogo");
    GameScreen currentScreen = MENU;
    //Quadros por segundo
    SetTargetFPS(60);

    //Rodar enquanto nao aperta ESC


    while (!WindowShouldClose()) {

        switch(currentScreen){

            case MENU:
                controle_menu(&n, &currentScreen);
                break;

            case GAMEPLAY:
                    controle_gameplay(&mapa);
                    gravidade(&mapa);
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

    }

    //Fecha a janela:
    CloseWindow();

    return 0;
}




