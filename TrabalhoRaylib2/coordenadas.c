#include "coordenadas.h"

/*
    localizacao_cria:
    Gera uma instância de Localizacao
    @param int linha: a linha associada à localização na matriz
    @param int coluna: a coluna associada à localização na matriz
    @return Localizacao: estrutura representando localização na matriz
*/
Localizacao localizacao_cria(int linha, int coluna){

    Localizacao coordenada;
    coordenada.linha = linha;
    coordenada.coluna = coluna;
    return coordenada;
}


