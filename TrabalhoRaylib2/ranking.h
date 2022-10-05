#ifndef RANKING_H
#define RANKING_H
#define TAM_MAX_RANK 5
#define TAM_NOME 50

#include "jogador.h"

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

/*
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
*/



#endif // RANKING_H
