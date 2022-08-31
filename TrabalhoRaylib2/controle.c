#include <stdio.h>
#include "jogador.h"
#include "coordenadas.h"
#include "mapa.h"
#include "telas.h"
#include "raylib.h"

void controle_menu(int *n, GameScreen *tela){

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
        *tela = GAMEPLAY;
    } else if((*n) == 1 && IsKeyDown(KEY_ENTER)) {

    } else if((*n) == 2 && IsKeyDown(KEY_ENTER)) {

    } else if((*n) == 3 && IsKeyDown(KEY_ENTER)) {
        exit(0); //encerra o programa
    }
}

void controle_gameplay(Mapa *mapa){
    if(IsKeyPressed(KEY_UP)){
        mapa_movimenta(mapa, 'c');
        controle_proxima_fase(mapa);
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

}

void controle_abre_bau(Mapa *mapa){
        int i;
        mapa_localiza_jogador(mapa);
        for(i = 0; i < mapa->qtdBaus; i++){
            if((mapa->baus[i].localizacao.linha == mapa->jogador.localizacao.linha) && (mapa->baus[i].localizacao.coluna == mapa->jogador.localizacao.coluna) && (mapa->baus[i].aberto == 0)){

                mapa->baus[i].aberto = 1;
                switch(mapa->baus[i].item){
                    case '!':
                        jog_aumenta_pontuacao(&(mapa->jogador), 50);
                        break;

                    case '@':
                        jog_aumenta_pontuacao(&(mapa->jogador), 100);
                        break;

                    case '#':
                        jog_aumenta_pontuacao(&(mapa->jogador), 150);
                        break;

                    case '$':
                        jog_aumenta_pontuacao(&(mapa->jogador), 200);
                        break;

                    case '%':
                        jog_aumenta_pontuacao(&(mapa->jogador), 300);
                        break;
                    case 'P':
                        mapa->chave = 1;
                        break;

                }

            }

        }
        printf("\nPONTUACAO: %d", mapa->jogador.pontuacao);


}

void controle_proxima_fase(Mapa *mapa){
    if((mapa->deletado == 'P') && (mapa->chave == 1)){
        printf("+++++++++++++++++++++++\n\n FASE CONCLUIDA\n\n++++++++++++++++++");
    }
}

void controle_gameplay_loop(Mapa *mapa, int *morte, int *frames, int *vida_atual){
    char aux;

    //Caso o jogador esteja vivo, permitir que controle o personagaem
    if(*morte == 0){
        controle_gameplay(mapa);

    }else{
        //Senão, jogador perde vida e atualiza vida_atual com a vida do jogador
        printf("\nJogador morreu");
        *vida_atual = mapa->jogador.vidas;

    }

    //Caso o jogador tenha perdido uma vida, morre
    if(*vida_atual != mapa->jogador.vidas){
         *morte = *frames;
    }

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



 /*
void controla_jogo() {
    char mov;
    int pontos;
    Mapa mapa;
    mapa_carrega(&mapa);


    do {
        mapa_imprime(mapa);
        printf("\nInforme\n(c) para ir para cima\n(b) para ir para baixo\n(p) para adicionar pontos\n(-) para diminuir a vida ou \n(n) para ler o nome: \n(s) para voltar para o menu)");
        scanf(" %c", &mov);

        if (mov == 'c') {
            mapa_movimenta(&mapa, mov);
        }

        if (mov == 'b') {
            mapa_movimenta(&mapa, mov);
        }

        if (mov == 'e') {
            mapa_movimenta(&mapa, mov);
        }

        if (mov == 'd') {
            mapa_movimenta(&mapa, mov);
        }


        if (mov == 'p') {
            printf("\tQuantos pontos? ");
            scanf("%d", &pontos);
            jog_aumenta_pontuacao(&(mapa.jogador), pontos);
        }

        if (mov == '-')
            if(jog_diminui_vida(&(mapa.jogador)))

        if (mov == 'n'){
            jog_le_nome(&(mapa.jogador));
            jog_print_info(mapa.jogador);
        }

        printf("\n\n\n");
    } while (mov != 's');

}
*/
