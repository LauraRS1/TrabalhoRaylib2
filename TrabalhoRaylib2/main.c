#include <stdio.h>
#include "raylib.h"
#include <string.h>
#include "mapa.h"
#include "desenha.h"
#include "gravidade.h"
#include "controle.h"
#include "camera.h"
#include "ranking.h"
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#define IMAGENS 13
#define TAM 50
#define TAM_VETOR 5
#define TAM_CAPA 400


int main() {
    int n = 0;
    int i= 0;
    int morte = 0;
    int framecount = 0;
    int vida_atual;
    Camera2D camera = {0};
    camera.zoom = 1.5;
    Mapa mapa;

    //incialização das variáveis do ranking do jogo
    int ultimo_lugar=0, pontuacao_nova=0, posicoes_ocupadas=1, ocupadas_novo=0;
    Ranking vetor[TAM_VETOR]={0}, vetor_novo[1]={0};
    char nome_ranking[TAM];
    recupera_ranking(vetor, &posicoes_ocupadas, &ultimo_lugar);

    // nomes das imagens
    char nomes[IMAGENS][TAM] = {"imagens/parede.png", "imagens/jogador.png","imagens/jogador_escada.png","imagens/jogador_porta.png",
    "imagens/jogador_bau.png", "imagens/bau.png","imagens/escada.png", "imagens/porta_normal.png", "imagens/porta_fase.png",
    "imagens/parede_fundo.png","imagens/jogador_saida.png","imagens/jogador_transparente.png", "imagens/capa.png"};

    //seed do tempo
    srand(time(NULL));

    //inicialização da janela do jogo
    InitWindow(LARGURA, ALTURA, "Jogo");
    GameScreen currentScreen = LOAD;
    SetTargetFPS(60);

    //Arquivos das imagens do jogo, devem abrir depois de iniciar a janela
    //Nivel
    Texture2D imagens[IMAGENS];
    for (i=0; i<IMAGENS; i++){
        imagens[i]=LoadTexture(nomes[i]);
    }
    //inicialização da vida
    vida_atual = 3;

    //loop do jogo
    while (1) {
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
                DrawTexture(imagens[12], MEIO-TAM_CAPA, 20, BLUE);
                desenha_menu(n);
                //controles do menu
                controle_menu(&n, &currentScreen, &mapa, &vida_atual);
                break;

            case RANKING:
                //Desenhando o Ranking
                desenha_ranking(vetor, imagens);
                //aperta esc para retornar ao menu
                if(IsKeyPressed(KEY_ESCAPE)) {
                    printf("\nTECLA ESC APERTADA\n");
                        vida_atual=3;
                        currentScreen = MENU;
                }
                break;

            case CARREGAR:
                desenha_load();
                if(framecount%180 == 0){
                    morte = 0;
                    currentScreen = GAMEPLAY;}
                break;

            case GAMEPLAY:
                //chamada do controle da gameplay
                controle_gameplay_loop(&mapa, &morte, &framecount, &vida_atual, &currentScreen);
                // controle da câmera e gravidade
                camera_atualiza(&camera, mapa.jogador.localizacao);
                BeginMode2D(camera);
                if(framecount%10 == 0)
                    gravidade(&mapa);
                desenha_nivel(&mapa, imagens);
                EndMode2D();
                desenha_hud(&mapa);
                //salva a última pontuação do jogador
                pontuacao_nova=mapa.jogador.pontuacao;
                break;

            case PROXIMO:
                desenha_proximo();
                if(framecount%180 == 0)
                  currentScreen = GAMEPLAY;
                break;

            case NJINGAME:
                desenha_nvingame();
                controle_njingame(&currentScreen, &mapa, &vida_atual);
                break;

            case RETORNAR_MENU:
                desenha_retorna_menu();
                controle_retorna_menu(&currentScreen, &mapa);
                break;

            case GAMEOVER:
                //
                desenha_gameover(imagens, pontuacao_nova, ultimo_lugar, nome_ranking);
                if(framecount%60 == 0){
                    if(pontuacao_nova>ultimo_lugar){
                        printf("\nDigite o seu nome para o Ranking:\n");
                        fflush(stdin);
                        scanf(" %s", nome_ranking);
                        vetor_novo[0]=inicia_ranking(nome_ranking, pontuacao_nova);
                        nova_entrada(vetor, &posicoes_ocupadas, vetor_novo, ocupadas_novo);
                        salva_ranking(vetor, posicoes_ocupadas);
                        vida_atual=3;
                        currentScreen=RANKING;
                    }
                    else{
                        vida_atual=3;
                        currentScreen=MENU;
                        }
                }
                   break;
            case ENDING:
                desenha_fim(imagens, pontuacao_nova, ultimo_lugar, nome_ranking);
                if(framecount%60 == 0){
                    if(pontuacao_nova>ultimo_lugar){
                        printf("\nDigite o seu nome para o Ranking:\n");
                        fflush(stdin);
                        scanf(" %s", nome_ranking);
                        vetor_novo[0]=inicia_ranking(nome_ranking, pontuacao_nova);
                        nova_entrada(vetor, &posicoes_ocupadas, vetor_novo, ocupadas_novo);
                        salva_ranking(vetor, posicoes_ocupadas);
                        vida_atual=3;
                        currentScreen=RANKING;
                    }
                    else{
                        vida_atual=3;
                        currentScreen=MENU;
                        }
                }


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




