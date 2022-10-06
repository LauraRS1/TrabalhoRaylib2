#ifndef COORDENADAS_H
#define COORDENADAS_H

/*
    Localizacao:
    Representa uma localiza��o.
    @param int linha: n�mero da linha associada.
    @param int coluna: n�mero da coluna associada.
*/
typedef struct{
    int linha;
    int coluna;
}Localizacao;

Localizacao localizacao_cria(int linha, int coluna);

#endif // COORDENADAS_H

