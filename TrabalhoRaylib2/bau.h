
#ifndef BAU_H

#define BAU_H

#include "coordenadas.h"

/*
    Bau:
    Representa um baú no mapa do jogo.
    @param char item: caracter do item contido no baú.
    @param int aberto: flag que indica se o baú está aberto.
    @param Localizacao localizacao: localização do baú.
*/

typedef struct{
    char item;
    int aberto;
    Localizacao localizacao;
}Bau;


#endif // BAU


