#include <stdio.h>
#include "jogador.h"
#include "coordenadas.h"
#include "mapa.h"
#include "telas.h"
#include "raylib.h"
#include "ranking.h"
#include "desenha.h"
#include "salva_estado_jogo.h"


/*  controle_menu:
    Manipula??o das op??es do menu do jogo
    @param *n: Ponteiro para um inteiro, respons?vel por dizer qual op??o est? sendo selecionada
    @param  *tela: Ponteiro para a tela atual do jogo
    @param *mapa: Ponteiro para o mapa do jogo
*/
void controle_menu(int *n, GameScreen *tela, Mapa *mapa, int *vida_atual){

    if(IsKeyPressed(KEY_UP))
        (*n)--;

    if((*n) < 0)
        (*n )= 3;

    if(IsKeyPressed(KEY_DOWN))
        (*n)++;
    if((*n)>3)
        (*n)=0;

    //A??es ao apertar enter em Novo Jogo, Carregar Jogo, Ranking de Pontos e Sair.

    if((*n)==0 && IsKeyDown(KEY_ENTER)) {
        //Inicia o n?vel 1 com o jogador zerado
        *mapa = mapa_seleciona_fase(1, tela);
         mapa_carrega(mapa);
        *tela = NOVO_JOGO;
    } else if((*n) == 1 && IsKeyDown(KEY_ENTER)) {
        //Inicia no ponto de salvamento
        arq_recupera_jogo(mapa);
        *vida_atual = mapa->jogador.vidas;
        *tela = NOVO_JOGO;

    } else if((*n) == 2 && IsKeyDown(KEY_ENTER)) {
        *tela = RANKING;

    } else if((*n) == 3 && IsKeyDown(KEY_ENTER)) {
        exit(0); //encerra o programa
    }
}


/*  controle_gameplay:
    Controla o jogador no jogo
    @param *mapa: Ponteiro para o Mapa do jogo
    @param  *tela: Ponteiro para a tela atual do jogo
*/
void controle_gameplay(Mapa *mapa, GameScreen *tela){


    if(IsKeyPressed(KEY_UP)){
        mapa_movimenta(mapa, 'c');
        controle_proxima_fase(mapa, tela);
        if(mapa->bau == 1)
            controle_abre_bau(mapa);//Se o jogador estiver em cima do ba?, abre o ba?
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
        *tela = RETORNAR_MENU;
    }

    //Salva o jogo
    if(IsKeyPressed(KEY_S)) { // s para salvar estado
        desenha_msg_checkpoint();
        arq_salva_jogo(*mapa);
    }
    //Iniciar novo jogo

    if(IsKeyPressed(KEY_N)) { // s para salvar estado
        *tela = NJINGAME;
    }
}


/*  controle_abre_bau:
    Se o jogador estiver na sa?da da fase e com a chave, conclui a fase e carrega a proxima fase
    @param *mapa: Ponteiro para o Mapa do jogo
    @param *tela: Tela atual do jogo
*/

void controle_abre_bau(Mapa *mapa){
        int i;
        mapa_localiza_jogador(mapa);
        for(i = 0; i < mapa->qtdBaus; i++){
            if((mapa->baus[i].localizacao.linha == mapa->jogador.localizacao.linha) && (mapa->baus[i].localizacao.coluna == mapa->jogador.localizacao.coluna) && (mapa->baus[i].aberto == 0)){

                mapa->baus[i].aberto = 1;
                switch(mapa->baus[i].item){
                    case '!':
                        //printf("\n=+50A=\n");
                        jog_aumenta_pontuacao(&(mapa->jogador), 50);
                        jog_guarda_item(&(mapa->jogador), '!');
                        break;

                    case '@':
                        //printf("\n=+100=\n");
                        jog_aumenta_pontuacao(&(mapa->jogador), 100);
                        jog_guarda_item(&(mapa->jogador), '@');
                        break;

                    case '#':
                        //printf("\n=+150=\n");
                        jog_aumenta_pontuacao(&(mapa->jogador), 150);
                        jog_guarda_item(&(mapa->jogador), '#');
                        break;

                    case '$':
                        //printf("\n=+200=\n");
                        jog_aumenta_pontuacao(&(mapa->jogador), 200);
                        jog_guarda_item(&(mapa->jogador), '$');
                        break;

                    case '%':
                        //printf("\n=+300=\n");
                        jog_aumenta_pontuacao(&(mapa->jogador), 300);
                        jog_guarda_item(&(mapa->jogador), '%');
                        break;

                    case 'P':
                        //printf("\n=CHAVE=\n");
                        jog_aumenta_pontuacao(&(mapa->jogador), 1000);
                        mapa->chave = 1;
                        jog_guarda_item(&(mapa->jogador), 'P');
                        break;

                        //Bomba
                    case 'B':
                        //printf("\n=BOMBA=\n");
                        jog_diminui_vida(&(mapa->jogador));
                        jog_aumenta_pontuacao(&(mapa->jogador), -500);
                        jog_guarda_item(&(mapa->jogador), 'B');
                        break;
                }
            }
        }
}


/*  controle_proxima_fase:
    Se o jogador estiver na sa?da da fase e com a chave, conclui a fase e carrega a proxima fase
    @param *mapa: Ponteiro para o Mapa do jogo
    @param *tela: Tela atual do jogo
*/
void controle_proxima_fase(Mapa *mapa, GameScreen *tela){
    if((mapa->deletado == 'P') && (mapa->chave == 1)){
        Jogador jogador;
        jogador = mapa->jogador;
        *tela = PROXIMO;
        *mapa = mapa_seleciona_fase(mapa->nivel + 1, tela);
        mapa_carrega_proxima_fase_e_jogador(mapa, jogador);
        //printf("+++++++++++++++++++++++\n\n FASE CONCLUIDA\n\n++++++++++++++++++");
    }
}


/*  controle_gameplay_loop:
    A??es gerais do jogador e do ambiente no jogo
    @param *mapa: Ponteiro para o Mapa do jogo
    @param *morte: Var?avel que determina se o jogador morreu(tomou dano)
    @param *vida_atual: Vida atual do jogador na partida, atualiza ap?s algum tempo depois de tomar dano
    @param *tela: Tela atual do jogo
*/
void controle_gameplay_loop(Mapa *mapa, int *morte, int *frames, int *vida_atual, GameScreen *tela){
    char aux;
    //printf("\n(*frames - *morte): %d\t MORTES: %d\t FRAMES: %d ", (*frames - *morte), *morte, *frames);
    //Caso o jogador esteja vivo, permitir que controle o personagaem
    if(*morte == 0){
        controle_gameplay(mapa, tela);

    }else{
        //Sen?o, jogador perde vida e atualiza vida_atual com a vida do jogador
        *vida_atual = mapa->jogador.vidas;

    }


    //Caso o jogador tenha perdido uma vida, morre
    if(*vida_atual != mapa->jogador.vidas){
         *morte = *frames;
    }
    //printf("\n %d ", mapa->jogador.vidas);
    //Se o jogador morreu de fato(tomou dano com 0 de vida), gameover
    if(mapa->jogador.vidas == MORTE){
        *tela = GAMEOVER;
        *morte = *frames - 1;
    }


    //Depois de passar 1 segundo da morte do jogador
    if((*frames - *morte) == 60){
        //printf("\n=MORTE POR QUEDA=\n");
        //Coloca o jogador no local de spawn da fase.
        mapa_localiza_jogador(mapa);
        aux = mapa->mapa[mapa->spawn.linha][mapa->spawn.coluna];

        //Zera as flags
        mapa->bau = 0;
        mapa->escada = 0;
        mapa->porta = ' ';

        if(aux == 'H'){
            mapa->escada = 1;

        }else if(aux == 'C'){
            mapa->bau = 1;
        }else{
            mapa->porta = aux;
            //condi??o da porta...
        }
        mapa->mapa[mapa->jogador.localizacao.linha][mapa->jogador.localizacao.coluna] = mapa->deletado;
        mapa->deletado = aux;
        mapa->mapa[mapa->spawn.linha][mapa->spawn.coluna] = 'D';

        *morte = 0;
    }
}


/*  controle_njingame:
    Controle da decis?o de iniciar um novo jogo no meio de uma partida
    @param *mapa: Ponteiro para o Mapa do jogo
    @param  *tela: Ponteiro para a tela atual do jogo
    @param *vida_atual: Vida atual do jogador na partida
*/
void controle_njingame(GameScreen *tela, Mapa *mapa, int *vida_atual){
    //Se N?o, volta pro gameplay
    if(IsKeyPressed(KEY_N)){
        *tela = GAMEPLAY;
    }
    //Se sim, inicia novo jogo
    if(IsKeyPressed(KEY_S)){
        *vida_atual = 3;
        *mapa = mapa_seleciona_fase(1, tela);
         mapa_carrega(mapa);
        *tela = NOVO_JOGO;
    }

}


/*  controle_retorna_menu:
    Controle da decis?o de retornar ao menu
    @param *mapa: Ponteiro para o Mapa do jogo
    @param  *tela: Ponteiro para a tela atual do jogo
    @param *vida_atual: Vida atual do jogador na partida
*/
void controle_retorna_menu(GameScreen *tela, Mapa *mapa){
    //Se N?o, volta pro gameplay
    if(IsKeyPressed(KEY_N)){
        *tela = GAMEPLAY;
    }
    //Se sim, inicia novo jogo
    if(IsKeyPressed(KEY_S)){
        //*vida_atual = 3;
        //*mapa = mapa_seleciona_fase(1, tela);
        //mapa_carrega(mapa);
        *tela = MENU;
    }
}
