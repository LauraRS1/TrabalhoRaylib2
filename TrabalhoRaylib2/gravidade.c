
#include "mapa.h"
#include "stdio.h"
#include "jogador.h"

/*  gravidade:
    Se o jogador não estiver em baixo de uma plataforma, faz ele avançar para baixo
    @param *mapa: Ponteiro para um mapa


*/
void gravidade(Mapa *mapa){
    mapa_localiza_jogador(mapa);
    char aux;
    aux = mapa->mapa[mapa->jogador.localizacao.linha + 1][mapa->jogador.localizacao.coluna];
    char chao = mapa->mapa[mapa->jogador.localizacao.linha + 1][mapa->jogador.localizacao.coluna]; // char do conteudo abaixo do jogador

    //Se o jogador não estiver uma plataforma
    if((aux == ' ') || (aux == 'C') || ((aux > '0') && (aux  <= '9'))){
        if(aux == 'C'){
            mapa->bau = 1;
        }
        if((aux > '0') && (aux  <='9')){
            mapa->porta = aux;
        }
        //Coloca o mais uma linha para baixo
        mapa->mapa[mapa->jogador.localizacao.linha + 1][mapa->jogador.localizacao.coluna] = 'D';
        mapa->mapa[mapa->jogador.localizacao.linha][mapa->jogador.localizacao.coluna] = mapa->deletado;
        mapa->deletado = aux;
        mapa->jogador.altura_relativa += 1; // altura do jog em relação ao chao aumenta em 1;; representa um bloco de altura de queda
        //printf("\n\naltura: %d     vidas: %d", mapa->jogador.altura_relativa, mapa->jogador.vidas);
    }

    //Se o jogador estiver em numa plataforma
    if((chao == 'X') || (chao == 'H')) { // se jogador alcancar o chao
        if(mapa->jogador.altura_relativa > 3) { // caso altura da queda maior que 3
            //printf("+++++++++++++++++++DANO=====================");

            jog_diminui_vida(&(mapa->jogador)); // diminui vida do jogador
        }

        mapa->jogador.altura_relativa = 0; // ao cair, reseta a altura relativa do jogador para 1
        //printf("\n\naltura: %d     vidas: %d", mapa->jogador.altura_relativa, mapa->jogador.vidas);
    }
}
