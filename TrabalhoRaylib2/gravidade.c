
#include "mapa.h"
#include "stdio.h"
#include "jogador.h"

void gravidade(Mapa *mapa){
    mapa_localiza_jogador(mapa);
    char aux;
    aux = mapa->mapa[mapa->jogador.localizacao.linha + 1][mapa->jogador.localizacao.coluna];
    char chao = mapa->mapa[mapa->jogador.localizacao.linha - 1][mapa->jogador.localizacao.coluna]; // char do conteudo abaixo do jogador

    if((chao == 'X') || (chao == 'H')) { // se jogador alcancar o chao
        if(mapa->jogador.altura_relativa > 3) { // caso altura da queda maior que 3
            jog_diminui_vida(&(mapa->jogador)); // diminui vida do jogador
        }

        mapa->jogador.altura_relativa = 0; // ao cair, reseta a altura relativa do jogador para 1
    }

    if((aux == ' ') || (aux == 'C') || (aux == '1') || (aux == '2')){
        if(aux == 'C'){
            mapa->bau = 1;
        }
        if((aux == '1') || (aux == '2')){
            mapa->porta = aux;
        }
        mapa->mapa[mapa->jogador.localizacao.linha + 1][mapa->jogador.localizacao.coluna] = 'D';
        mapa->mapa[mapa->jogador.localizacao.linha][mapa->jogador.localizacao.coluna] = mapa->deletado;
        mapa->deletado = aux;

        //printf("\n\naltura: %d     vidas: %d", mapa->jogador.altura_relativa, mapa->jogador.vidas);
        mapa->jogador.altura_relativa += 1; // altura do jog em relação ao chao aumenta em 1;; representa um bloco de altura de queda
    }
}
