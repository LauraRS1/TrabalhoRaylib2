#ifndef MAPA_H
#define MAPA_H
#define MAPA_L 30
#define MAPA_C 120
#include "jogador.h"
#include "coordenadas.h"
#include "bau.h"



typedef struct{
    char mapa[MAPA_L][MAPA_C];
    Localizacao dimencao; //Valor real da dimensão do mapa, onde o jogo ocorre
    Localizacao spawn;//Coordenadas do spawn do jogador, onde ele começa e onde ele renasce ao morrer
    int escada;//Flag, determina se o jogador está numa escada
    char porta;//Determina se o jogador está numa porta
    int bau;//Flag, determina se o jogador está num baú
    int qtdBaus;//Quantidade de baús do mapa
    int chave;//Flag, determina se o jogador está com a chave
    Bau baus[50];//Baus do mapa
    Jogador jogador;//Jogador
    char deletado;// Caracter que o jogador deleta ao se mover
}Mapa;


void mapa_carrega(Mapa *mapa);
void mapa_movimenta(Mapa *mapa, char direcao);
void mapa_localiza_jogador(Mapa *mapa);
void mapa_busca_porta(Mapa mapa, char porta, Localizacao *local_porta);
void mapa_imprime(Mapa mapa);
void chama_mensagem_bau();
int mapa_bau_quantidade(Mapa *mapa);
void mapa_bau_cria(Mapa *mapa);
Localizacao mapa_set_dimencao(char mapa[MAPA_L][MAPA_C]);
void mapa_set_spawn(Mapa *mapa);
void mapa_gera_chave(Mapa *mapa);
void mapa_gera_bomba(Mapa *mapa, int fase);
void mapa_gera_outros(Mapa *mapa, int fase);
void mapa_bau_gera_itens(Mapa *mapa, int fase);


#endif // MAPA_H
