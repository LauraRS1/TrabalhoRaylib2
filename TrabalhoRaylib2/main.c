#include <stdio.h>
#include "raylib.h"
#include <string.h>
#include "mapa.h"
#include "desenha.h"
#include "gravidade.h"
#include "controle.h"
#include "camera.h"
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#define IMAGENS 12
#define TAM 50


int main() {
    int n = 0;
    int i= 0;
    int morte = 0;
    int framecount = 0;
    int vida_atual;
    Camera2D camera = {0};
    camera.zoom = 1.5;
    int ultimo_lugar=-65;
    int pontuacao_nova=0;

    char nome_ranking[TAM];

    char nomes[IMAGENS][TAM] = {"imagens/parede.png", "imagens/jogador.png","imagens/jogador_escada.png","imagens/jogador_porta.png",
    "imagens/jogador_bau.png", "imagens/bau.png","imagens/escada.png", "imagens/porta_normal.png", "imagens/porta_fase.png",
    "imagens/parede_fundo.png","imagens/jogador_saida.png","imagens/jogador_transparente.png"};

    srand(time(NULL));
    printf("TESTES");
    Mapa mapa; //mapa = mapa_seleciona_fase(1);; //numero da fase como parametro
    jog_seta_entrou_ranking(&(mapa.jogador)); // coloca entrou_ranking para 0
    printf("TESTES");

    //mapa_carrega(&mapa);

    InitWindow(LARGURA, ALTURA, "Jogo");
    GameScreen currentScreen = LOAD;
    SetTargetFPS(60);

    //Arquivos das imagens do jogo, devem abrir depois de iniciar a janela
    //Capa
    Texture2D capa= LoadTexture("imagens/capa.png");
    //Nivel
    Texture2D imagens[IMAGENS];
    for (i=0; i<IMAGENS; i++){
        imagens[i]=LoadTexture(nomes[i]);
    }

    vida_atual = 3;



    //Rodar enquanto nao aperta ESC
    while (!WindowShouldClose()) {
        int fim_ou_gameover = 0; // flag p fim ou gameover

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

            case NOVO_JOGO:
                desenha_load();

                if(framecount%180 == 0){
                    morte = 0;
                    currentScreen = GAMEPLAY;}
                break;

            case MENU:
                //Desenhando a capa e o menu
                DrawTexture(capa, MEIO-400, 20, BLUE);
                desenha_menu(n);
                //controles do menu
                controle_menu(&n, &currentScreen, &mapa);
                break;

            case GAMEPLAY:
                camera_atualiza(&camera, mapa.jogador.localizacao);
                BeginMode2D(camera);
                    controle_gameplay_loop(&mapa, &morte, &framecount, &vida_atual, &currentScreen);
                    if(framecount%10 == 0)
                        gravidade(&mapa);
                    desenha_nivel(&mapa, imagens);
                    //desenha_nivel(&mapa, imagens);
                    /*if(framecount%240 == 0)
                        jog_print_info(mapa.jogador);*/
                EndMode2D();
                //desenha_nivel(&mapa, imagens);
                pontuacao_nova=mapa.jogador.pontuacao;
                break;

            case PROXIMO:
                desenha_proximo();
                if(framecount%180 == 0)
                  currentScreen = GAMEPLAY;
                break;

            case GAMEOVER:
                desenha_gameover(imagens, pontuacao_nova, ultimo_lugar, nome_ranking);
                if(framecount%30 == 0)
                    if(pontuacao_nova>ultimo_lugar){
                    printf("Digite o seu nome para o Ranking:");
                    fflush(stdin);
                    scanf(" %s", nome_ranking);
                    currentScreen=MENU;
                    }
                break;
            case ENDING:
                desenha_fim(imagens, pontuacao_nova, ultimo_lugar, nome_ranking);

                //desenha o ranking
                //desenha_ranking(imagens);

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




