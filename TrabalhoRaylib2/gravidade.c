
#include "mapa.h"

void gravidade(Mapa *mapa){
    mapa_localiza_jogador(mapa);
    char aux;
    aux = mapa->mapa[mapa->jogador.localizacao.linha + 1][mapa->jogador.localizacao.coluna];
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
    }

}
