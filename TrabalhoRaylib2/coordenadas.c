#include "coordenadas.h"

/*
    localizacao_cria:
    Gera uma inst�ncia de Localizacao
    @param int linha: a linha associada � localiza��o na matriz
    @param int coluna: a coluna associada � localiza��o na matriz
    @return Localizacao: estrutura representando localiza��o na matriz
*/
Localizacao localizacao_cria(int linha, int coluna){

    Localizacao coordenada;
    coordenada.linha = linha;
    coordenada.coluna = coluna;
    return coordenada;
}


