
#ifndef BAU_H

#define BAU_H

#include "coordenadas.h"

/*
    Bau:
    Representa um ba� no mapa do jogo.
    @param char item: caracter do item contido no ba�.
    @param int aberto: flag que indica se o ba� est� aberto.
    @param Localizacao localizacao: localiza��o do ba�.
*/

typedef struct{
    char item;
    int aberto;
    Localizacao localizacao;
}Bau;


#endif // BAU


