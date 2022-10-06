#ifndef COORDENADAS_H
#define COORDENADAS_H

/*
    Localizacao:
    Representa uma localização.
    @param int linha: número da linha associada.
    @param int coluna: número da coluna associada.
*/
typedef struct{
    int linha;
    int coluna;
}Localizacao;

Localizacao localizacao_cria(int linha, int coluna);

#endif // COORDENADAS_H

