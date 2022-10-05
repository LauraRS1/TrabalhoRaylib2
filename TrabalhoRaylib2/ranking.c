#include "ranking.h"
#include "jogador.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define RANKING_TXT "ranking.txt"

Ranking insere_ranking(char nome[], int pontuacao) {
    Ranking r;
    strcpy(r.jog_nome, nome);
    r.jog_pontuacao = pontuacao;

    return r;
}

void arq_salva_vet_entradas(Ranking vet_entradas[], int pos_ocupadas) {
    FILE *arquivo;
    int i;
    arquivo = fopen(RANKING_TXT, "w");

    if(arquivo) {
        for(i = 0; i < pos_ocupadas; i++) {
            fprintf(arquivo, "%s %d\n", vet_entradas[i].jog_nome, vet_entradas[i].jog_pontuacao);
            //fflush(arquivo);
        }
        fclose(arquivo);
    } else {
        printf("Erro ao abrir o arquivo!\n");
    }
}

void arq_recupera_vet_entradas(Ranking vet_entradas[], int *pos_ocupadas) {
    FILE *arquivo;
    int pontuacao;
    char nome[TAM_NOME];
    int i;

    arquivo = fopen(RANKING_TXT, "r");
    *pos_ocupadas = 0;

    if(arquivo) {
        fflush(arquivo);
        for(i = 0; i < 5; i++) {
            // lê dados e remove "/n"
            if(fscanf(arquivo, "%s %d", nome, &pontuacao)) {
                fgetc(arquivo);
                // gera uma entrada e salva no vetor
                vet_entradas[*pos_ocupadas] = insere_ranking(nome, pontuacao);

                // incrementa tamanho
                (*pos_ocupadas)++;
            }
        }
        fclose(arquivo);
    } else {
        printf("Erro ao abrir o arquivo!\n");
    }
}

void imprime_ranking(Ranking vet_entradas[], int tamanho) {
    int i;

    for(i = 0; i < tamanho; i++) {
        printf("%s %d\n", vet_entradas[i].jog_nome, vet_entradas[i].jog_pontuacao);
    }
}

int jog_pode_entrar(Jogador j, Ranking vet_antigo[], int pos_ocupadas) {

   if(j.entrou_ranking) {
        return 0;   // se o jogador ja entrou, impedir que o ranking seja salvo novamente
   }

    if(pos_ocupadas < 5) {
        return 1;
    // se não tem espaço no vetor...
    } else {
        if(j.pontuacao > vet_antigo[pos_ocupadas - 1].jog_pontuacao) {
            return 1;
        }

        return 0;
    }
}

void adiciona_entrada_ranking(Ranking vet_antigo[], int *pos_ocupadas, Ranking entrada, Jogador *j) {
    int entrou = 0;

    // se tem espaço no vetor
    if(*pos_ocupadas < 5) {
        vet_antigo[*pos_ocupadas] = entrada;
        (*pos_ocupadas)++;
        entrou = 1;
        j->entrou_ranking = 1;

    // se não tem espaço no vetor...
    } else {
        if(entrada.jog_pontuacao > vet_antigo[*pos_ocupadas - 1].jog_pontuacao) {
            vet_antigo[*pos_ocupadas - 1] = entrada;
            entrou = 1;
            j->entrou_ranking = 1;
        }
    }

    if(entrou && (*pos_ocupadas > 1)) {
        ordena(vet_antigo, *pos_ocupadas);
    }

    arq_salva_vet_entradas(vet_antigo, *pos_ocupadas);
}

void ordena(Ranking vetor[], int pos_ocupadas) {
    Ranking aux; // variavel auxiliar p/ troca
    int i; //controle laço extermo
    int j; // controle laço interno

    for(i = 0; i < pos_ocupadas; i++) {
        for(j = i; j < pos_ocupadas; j++) {
            if(vetor[j].jog_pontuacao > vetor[i].jog_pontuacao) {
                aux = vetor[i];
                vetor[i] = vetor[j];
                vetor[j] = aux;
            }
        }
    }
}



