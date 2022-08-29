#ifndef MAPA_H
#define MAPA_H
#define MAPA_L 120
#define MAPA_C 120
#include "jogador.h"
#include "coordenadas.h"

typedef struct{
    char mapa[MAPA_L][MAPA_C];
    Localizacao dimencao;
    int escada;
    char porta;
    int bau;
    Jogador jogador;
    char deletado;
}Mapa;


void mapa_carrega(Mapa *mapa);
void mapa_movimenta(Mapa *mapa, char direcao);
void queda(Mapa *mapa);
void mapa_localiza_jogador(Mapa *mapa);
void mapa_busca_porta(Mapa mapa, char porta, Localizacao *local_porta);
void mapa_imprime(Mapa mapa);
void chama_mensagem_bau();

#endif // MAPA_H
