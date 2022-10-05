#ifndef RANKING_H
#define RANKING_H
#define TAM_MAX_RANK 5
#define TAM_NOME 50

#include "jogador.h"


typedef struct {
    char jog_nome[TAM_NOME];
    int jog_pontuacao;
} Ranking;

Ranking insere_ranking(char nome[], int pontuacao);
void arq_salva_vet_entradas(Ranking vet_entradas[], int pos_ocupadas);
void arq_recupera_vet_entradas(Ranking vet_entradas[], int *pos_ocupadas);
void imprime_ranking(Ranking vet_entradas[], int tamanho);
void adiciona_entrada_ranking(Ranking vet_antigo[], int *pos_ocupadas, Ranking entrada, Jogador *j);
void ordena(Ranking vetor[], int pos_ocupadas);
int jog_pode_entrar(Jogador j, Ranking vet_antigo[], int pos_ocupadas);

#endif // RANKING_H
