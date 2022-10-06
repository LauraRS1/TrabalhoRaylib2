#ifndef RANKING_H
#define RANKING_H
#define TAM_MAX_RANK 5
#define TAM_NOME 50

#include "jogador.h"

/*
    Ranking:
    Representa o ranking do jogo.
    @param char nome[TAM_NOME]: nome do jogador associado.
    @param int pontuacao: quantidade de pontos associada.
*/

typedef struct{
    char nome[TAM_NOME];
    int pontuacao;
}Ranking;

Ranking inicia_ranking(char nome[], int pontuacao);
void salva_ranking(Ranking vetor[TAM_NOME], int ocupadas);
void recupera_ranking(Ranking vetor[], int *ocupadas, int *ultima_pos);
void imprime_ranking(Ranking vetor[], int ocupadas);
void ordenamento_bolha(Ranking v[], int tamanho);
void salvar_vetor(Ranking vetor[], int *posicoes_ocupadas);
void nova_entrada(Ranking vetor[], int *ocupadas, Ranking vetor_novo[], int ocupadas_novo);


#endif // RANKING_H
