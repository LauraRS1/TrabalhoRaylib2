#include <stdio.h>
#include "raylib.h"
#include "mapa.h"
#include "desenha_menu.h"
#include "gravidade.h"

#define ALTURA 660
#define LARGURA 800

#define Q 60

void desenha_nivel(Mapa *mapa);
void gravidade(Mapa *mapa);

typedef enum GameScreen { TITLE = 0, GAMEPLAY, ENDING } GameScreen;


int main() {
    int n;
    n=0;
    Mapa mapa;
    InitWindow(LARGURA, ALTURA, "Jogo");
    GameScreen currentScreen = TITLE;
    //Quadros por segundo
    SetTargetFPS(60);
    mapa_carrega(&mapa);
    //Rodar enquanto nao aperta ESC


    while (!WindowShouldClose()) {

        switch(currentScreen){
        case TITLE:
            if(IsKeyPressed(KEY_UP))
                    n--;
                if(n<0)
                    n=3;
                if(IsKeyPressed(KEY_DOWN))
                    n++;
                if(n>3)
                    n=0;

                //Mensagens ao apertar enter em Novo Jogo, Carregar Jogo, Ranking de Pontos e Sair.
                if(n==0 && IsKeyDown(KEY_ENTER)) {
                    currentScreen = GAMEPLAY;
                } else if(n==1 && IsKeyDown(KEY_ENTER)) {

                } else if(n==2 && IsKeyDown(KEY_ENTER)) {

                } else if(n==3 && IsKeyDown(KEY_ENTER)) {
                    exit(0); //encerra o programa
                }
            break;
        case GAMEPLAY:
                if(IsKeyPressed(KEY_UP)){
                    mapa_movimenta(&mapa, 'c');
                }
                if(IsKeyPressed(KEY_DOWN)){
                    mapa_movimenta(&mapa, 'b');
                }
                if(IsKeyPressed(KEY_LEFT)){
                    mapa_movimenta(&mapa, 'e');
                }
                if(IsKeyPressed(KEY_RIGHT)){
                    mapa_movimenta(&mapa, 'd');
                }

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

            case TITLE:
                DesenhaMenu(n);
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

void desenha_nivel(Mapa *mapa){


    int i, j;
    for(i = 0; i < mapa->dimencao.linha; i++){
        for(j = 0; j < mapa->dimencao.coluna; j++){

                if(mapa->mapa[i][j] == 'X')
                    DrawRectangle((0 + Q * j), (0 + Q * i), Q, Q, GRAY);

                 if(mapa->mapa[i][j] == 'D')
                    DrawRectangle((0 + Q * j), (0 + Q * i), Q, Q, RED);

                if((mapa->mapa[i][j] == 'D') && (mapa->escada == 1))
                    DrawRectangle((0 + Q * j), (0 + Q * i), Q, Q, GREEN);

                if((mapa->mapa[i][j] == 'D') && (mapa->porta != ' '))
                    DrawRectangle((0 + Q * j), (0 + Q * i), Q, Q, ORANGE);

                if((mapa->mapa[i][j] == 'D') && (mapa->bau == 1))
                    DrawRectangle((0 + Q * j), (0 + Q * i), Q, Q, PURPLE);

                if(mapa->mapa[i][j] == 'C')
                    DrawRectangle((0 + Q * j), (0 + Q * i), Q, Q, PINK);

                if(mapa->mapa[i][j] == 'H')
                    DrawRectangle((0 + Q * j), (0 + Q * i), Q, Q, BROWN);

                if((mapa->mapa[i][j] == '1') || (mapa->mapa[i][j] == '2'))
                    DrawRectangle((0 + Q * j), (0 + Q * i), Q, Q, YELLOW);


                }
        }
 }


