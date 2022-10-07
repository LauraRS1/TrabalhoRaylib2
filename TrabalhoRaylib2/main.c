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
#define IMAGENS 14
#define TAM 50
#define TAM_VETOR 5
#define TAM_CAPA 400
#define TAM_NOME2 9


int main() {
    int n = 0;
    int i= 0;
    int morte = 0;
    int framecount = 0;
    int vida_atual;
    Camera2D camera = {0};
    camera.zoom = 1.5;
    Mapa mapa;
    int i_vezes=10, j_vezes=20;
    int save = 0;

    //incialização das variáveis do ranking do jogo
    int ultimo_lugar=0, pontuacao_nova=0, posicoes_ocupadas=1, ocupadas_novo=0;
    Ranking vetor[TAM_VETOR]={0}, vetor_novo[1]={0};
    char nome_ranking[TAM_NOME2 + 1] = "\0";
    int letra = 0;
    Rectangle textBox = { LARGURA/2.0f - 100, 180, 225, 50 };
    recupera_ranking(vetor, &posicoes_ocupadas, &ultimo_lugar);

    // nomes das imagens
    char nomes[IMAGENS][TAM] = {"imagens/parede.png", "imagens/jogador.png","imagens/jogador_escada.png","imagens/jogador_porta.png",
    "imagens/jogador_bau.png", "imagens/bau.png","imagens/escada.png", "imagens/porta_normal.png", "imagens/porta_fase.png",
    "imagens/parede_fundo.png","imagens/jogador_saida.png","imagens/jogador_transparente.png", "imagens/capa.png", "imagens/fundo_hud.png"};

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
                if(IsKeyPressed(KEY_S))
                    save = framecount;





                //chamada do controle da gameplay
                controle_gameplay_loop(&mapa, &morte, &framecount, &vida_atual, &currentScreen);
                // controle da câmera e gravidade
                camera_atualiza(&camera, mapa.jogador.localizacao);
                BeginMode2D(camera);
                if(framecount%10 == 0)
                    gravidade(&mapa);
                desenha_nivel(&mapa, imagens);
                EndMode2D();
                desenha_hud(&mapa, imagens);
                //Se Jogador salvou então desenha mensagem
                if(save){
                    desenha_msg_checkpoint();
                    if(framecount - save == 60)
                        save = 0;
                }
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

            case ADDRANK:
                int key = GetCharPressed();

                for(int i = 0; i < i_vezes; i++)
                        for(int j = 0; j < j_vezes; j++)
                            DrawTexture(imagens[9], (0 + QUADRADO_LARGURA *j), (0 + QUADRADO_ALTURA * i), WHITE);
                DrawTexture(imagens[11], MEIO-200, ESPACO, WHITE);

                while (key > 0){

                    if ((key >= 32) && (key <= 125) && (letra < TAM_NOME2)){
                        nome_ranking[letra] = (char)key;
                        nome_ranking[letra+1] = '\0';
                        letra++;
                    }
                    key = GetCharPressed();
                }

                if (IsKeyPressed(KEY_BACKSPACE)){
                    letra--;
                    if (letra < 0)
                        letra = 0;
                    nome_ranking[letra] = '\0';
                }

                if(IsKeyPressed(KEY_ENTER)){
                    vetor_novo[0]=inicia_ranking(nome_ranking, pontuacao_nova);
                    nova_entrada(vetor, &posicoes_ocupadas, vetor_novo, ocupadas_novo);
                    salva_ranking(vetor, posicoes_ocupadas);
                    vida_atual=3;
                    currentScreen = RANKING;

                }
                DrawText("Otima pontuacao! digite seu nome:", (LARGURA-MeasureText("Ótima pontuação! digite seu nome:",TAMANHO_FONTE))/2, ESPACO-20, TAMANHO_FONTE, WHITE);

                DrawRectangleRec(textBox, DARKBLUE);
                DrawText(nome_ranking, (int)textBox.x + 5, (int)textBox.y + 8, 40, WHITE);
                break;

            case GAMEOVER:
                //
                desenha_gameover(imagens, pontuacao_nova, ultimo_lugar, nome_ranking);
                if(framecount%180 == 0){
                    if(pontuacao_nova>ultimo_lugar){
                        currentScreen=ADDRANK;
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
                       currentScreen=ADDRANK;
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




