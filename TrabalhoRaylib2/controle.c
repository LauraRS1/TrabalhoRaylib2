#include <stdio.h>
#include "jogador.h"
#include "coordenadas.h"
#include "mapa.h"
#include "telas.h"
#include "raylib.h"
#include "ranking.h"
#include "salva_estado_jogo.h"


void controle_menu(int *n, GameScreen *tela, Mapa *mapa, int *vidas_atual){

    if(IsKeyPressed(KEY_UP))
        (*n)--;

    if((*n) < 0)
        (*n )= 3;

    if(IsKeyPressed(KEY_DOWN))
        (*n)++;
    if((*n)>3)

        (*n)=0;

    //Mensagens ao apertar enter em Novo Jogo, Carregar Jogo, Ranking de Pontos e Sair.

    if((*n)==0 && IsKeyDown(KEY_ENTER)) {
        *mapa = mapa_seleciona_fase(1, tela);
         mapa_carrega(mapa);
        *tela = NOVO_JOGO;
    } else if((*n) == 1 && IsKeyDown(KEY_ENTER)) {
        *vidas_atual=3;
        arq_recupera_jogo(mapa);
        *tela = GAMEPLAY;

    } else if((*n) == 2 && IsKeyDown(KEY_ENTER)) {
        *tela = RANKING;
    } else if((*n) == 3 && IsKeyDown(KEY_ENTER)) {
        exit(0); //encerra o programa
    }
}

void controle_gameplay(Mapa *mapa, GameScreen *tela, int *vidas_atual){
    if(IsKeyPressed(KEY_UP)){
        mapa_movimenta(mapa, 'c');
        controle_proxima_fase(mapa, tela);
        if(mapa->bau == 1)
            controle_abre_bau(mapa);
    }
    if(IsKeyPressed(KEY_DOWN)){
        mapa_movimenta(mapa, 'b');
    }


    if(IsKeyPressed(KEY_LEFT)){
        mapa_movimenta(mapa, 'e');
    }
    if(IsKeyPressed(KEY_RIGHT)){
        mapa_movimenta(mapa, 'd');
    }

    if(IsKeyPressed(KEY_ESCAPE)){
        printf("\nTECLA ESC APERTADA\n");
        char escolha=' ';
        printf("\nDeseja sair do jogo? [s]im ou [n]ao ");
        scanf(" %c", &escolha);
        if(escolha=='S'||escolha=='s'){
            WindowShouldClose();
        }else *tela=GAMEPLAY;
    }

    //controle estado jogo
    if(IsKeyPressed(KEY_S)) { // s para salvar estado
        printf("\nJOGO SALVO\n");
        desenha_msg_checkpoint();
        arq_salva_jogo(*mapa);
    }

    //voltar para o MENU
    if(IsKeyPressed(KEY_M)) {
        printf("\nTECLA M APERTADA\n");
        char escolha=' ';
        printf("\nDeseja retornar ao menu? [s]im ou [n]ao ");
        scanf(" %c", &escolha);
        if(escolha=='S'||escolha=='s'){
            *vidas_atual=3;
            *tela = MENU;
        }else *tela=GAMEPLAY;
    }

    //novo jogo
    if(IsKeyPressed(KEY_N)) {
        printf("\nTECLA N APERTADA\n");
        char escolha=' ';
        printf("\nDeseja inciar novo jogo? [s]im ou [n]ao ");
        scanf(" %c", &escolha);
        if(escolha=='S'||escolha=='s'){
            *vidas_atual=3;
            *mapa = mapa_seleciona_fase(1, tela);
             mapa_carrega(mapa);
            *tela = NOVO_JOGO;
        }else *tela = GAMEPLAY;
    }


}

void controle_abre_bau(Mapa *mapa){
        int i;
        mapa_localiza_jogador(mapa);
        for(i = 0; i < mapa->qtdBaus; i++){
            if((mapa->baus[i].localizacao.linha == mapa->jogador.localizacao.linha) && (mapa->baus[i].localizacao.coluna == mapa->jogador.localizacao.coluna) && (mapa->baus[i].aberto == 0)){

                mapa->baus[i].aberto = 1;
                switch(mapa->baus[i].item){
                    case '!':
                        printf("\n=+50A=\n");
                        jog_aumenta_pontuacao(&(mapa->jogador), 50);
                        jog_guarda_item(&(mapa->jogador), '!');
                        break;

                    case '@':
                        printf("\n=+100=\n");
                        jog_aumenta_pontuacao(&(mapa->jogador), 100);
                        jog_guarda_item(&(mapa->jogador), '@');
                        break;

                    case '#':
                        printf("\n=+150=\n");
                        jog_aumenta_pontuacao(&(mapa->jogador), 150);
                        jog_guarda_item(&(mapa->jogador), '#');
                        break;

                    case '$':
                        printf("\n=+200=\n");
                        jog_aumenta_pontuacao(&(mapa->jogador), 200);
                        jog_guarda_item(&(mapa->jogador), '$');
                        break;

                    case '%':
                        printf("\n=+300=\n");
                        jog_aumenta_pontuacao(&(mapa->jogador), 300);
                        jog_guarda_item(&(mapa->jogador), '%');
                        break;

                    case 'P':
                        printf("\n=CHAVE=\n");
                        jog_aumenta_pontuacao(&(mapa->jogador), 1000);
                        mapa->chave = 1;
                        break;

                        //Bomba
                    case 'B':
                        printf("\n=BOMBA=\n");
                        jog_diminui_vida(&(mapa->jogador));
                        jog_aumenta_pontuacao(&(mapa->jogador), -500);
                        break;

                }

            }

        }
        printf("\nPONTUACAO: %d\n", mapa->jogador.pontuacao);
}

void controle_ranking(Mapa *mapa) {
printf("\ncontrole_ranking\n");

}

void controle_proxima_fase(Mapa *mapa, GameScreen *tela){
    if((mapa->deletado == 'P') && (mapa->chave == 1)){
        Jogador jogador;
        jogador = mapa->jogador;
        *tela = PROXIMO;
        *mapa = mapa_seleciona_fase(mapa->nivel + 1, tela);
        mapa_carrega_proxima_fase_e_jogador(mapa, jogador);
        printf("\n+++++++++++++++++++++++\n\n FASE CONCLUIDA\n\n++++++++++++++++++\n");
    }
}

void controle_gameplay_loop(Mapa *mapa, int *morte, int *frames, int *vida_atual, GameScreen *tela){
    char aux;
    //Caso o jogador esteja vivo, permitir que controle o personagaem
    if(*morte == 0){
        controle_gameplay(mapa, tela, vida_atual);

    }else{
        //Senão, jogador perde vida e atualiza vida_atual com a vida do jogador
        *vida_atual = mapa->jogador.vidas;
    }

    //Caso o jogador tenha perdido uma vida, morre
    if(*vida_atual != mapa->jogador.vidas){
         *morte = *frames;
    }
    //printf("\n %d ", mapa->jogador.vidas);
    if(mapa->jogador.vidas == MORTE)
        *tela = GAMEOVER;

    //Depois de passar 1 segundo da morte do jogador
    if((*frames - *morte) == 60){
        //Coloca o jogador no local de spawn da fase.
        mapa_localiza_jogador(mapa);
        aux = mapa->mapa[mapa->spawn.linha][mapa->spawn.coluna];

        mapa->bau = 0;
        mapa->escada = 0;
        mapa->porta = ' ';

        if(aux == 'H'){
            mapa->escada = 1;

        }else if(aux == 'C'){
            mapa->bau = 1;
        }else{
            mapa->porta = aux;
            //condição da porta...
        }
        mapa->mapa[mapa->jogador.localizacao.linha][mapa->jogador.localizacao.coluna] = mapa->deletado;
        mapa->deletado = aux;
        mapa->mapa[mapa->spawn.linha][mapa->spawn.coluna] = 'D';

        *morte = 0;
    }

}
