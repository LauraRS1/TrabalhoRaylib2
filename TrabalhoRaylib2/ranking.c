#include "ranking.h"
#include "jogador.h"
#include <stdio.h>
#include <stdlib.h>
#define TAM_NOME 30
#define TAM_VETOR 5

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define RANKING_TXT "ranking.txt"



// inicia o jogador
Ranking inicia_ranking(char nome[], int pontuacao){
    int i=0;
    Ranking jogador = {{0}, pontuacao};
    for(i=0; nome[i]!='\0';i++)
        jogador.nome[i]=nome[i];
    return jogador;
}

//salva o ranking no arquivo .txt
void salva_ranking(Ranking vetor[TAM_NOME], int ocupadas){
    int i=0;
    FILE *arquivo;
    arquivo=fopen("ranking.txt", "w");


    if(arquivo){
        fprintf(arquivo, "%d" ,ocupadas);
        for(i=0; i<ocupadas; i++){
            fprintf(arquivo,"%s %d\n",vetor[i].nome,vetor[i].pontuacao);
        }


    }else {
        printf("ERRO AO ABRIR O ARQUIVO;");
    }
    fclose(arquivo);
    printf("\nRanking salvo\n\n");
}

//recupera o arquivo txt e coloca no vetor
void recupera_ranking(Ranking vetor[], int *ocupadas, int *ultima_pos){
    int i;
    int pontuacao;
    char nome[TAM_NOME];
    FILE *arquivo;
    arquivo=fopen("ranking.txt", "r");


    if(arquivo){
    fscanf(arquivo, "%d", ocupadas);
    for(i=0; i<*ocupadas; i++){
            fscanf(arquivo, "%s %d",&nome, &pontuacao);
            vetor[i]= inicia_ranking(nome, pontuacao);
    }
    *ultima_pos= pontuacao;

    }else {
        printf("ERRO AO ABRIR O ARQUIVO;");
    }
    fclose(arquivo);

}
//imprime o ranking
void imprime_ranking(Ranking vetor[], int ocupadas){
    int i=0;

    printf("Ranking\n");
    for(i=0; i<ocupadas;i++){
        printf("-----------------\n"
               "%d Lugar\n"
               "\nNome:%s"
               "\nPontuacao:%d \n", i+1,vetor[i].nome, vetor[i].pontuacao);
    }
    printf("-----------------\n");

}

//ordena o vetor de jogadores de maior para menor
void ordenamento_bolha(Ranking v[], int tamanho) {
    int i, trocou;
    Ranking aux;
    do {
    trocou = 0;
    for (i = 0; i < tamanho - 1; i++) {
        if (v[i].pontuacao < v[i + 1].pontuacao) {
            aux = v[i];
            v[i] = v[i + 1];
            v[i + 1] = aux;
            trocou = 1;
            }
    }
    } while (trocou == 1);
}
//salva o vetor
void salvar_vetor(Ranking vetor[], int *posicoes_ocupadas){
    char nome[TAM_NOME]={0};
    int pontuacao=0;
    int i=0;

    for(i=0; i<TAM_VETOR; i++){
        fflush(stdin);
        printf("%d Nome:", i+1);
        fgets(nome, TAM_NOME, stdin);
        if(nome[0]=='@'){
            ordenamento_bolha(vetor, TAM_VETOR);
            break;
        }
        printf("Pontuacao:");
        scanf("%d", &pontuacao);
        vetor[i]=inicia_ranking(nome, pontuacao);
        }
    *posicoes_ocupadas=i;
    ordenamento_bolha(vetor, TAM_VETOR);
}
//acrescenta a nova entrada na ordem de maior pontuacao para menor
void nova_entrada(Ranking vetor[], int *ocupadas, Ranking vetor_novo[], int ocupadas_novo){
    int i, j;
    Ranking vetor_aux[TAM_VETOR*2+1]={0};

    for(i=0; i<=*ocupadas; i++){
        vetor_aux[i]=vetor[i];
    }
    for(j=0; j<=ocupadas_novo; j++, i++){
        vetor_aux[i-1]=vetor_novo[j];
    }

    ordenamento_bolha(vetor_aux, TAM_VETOR*2);

    for(j=0; j<TAM_VETOR; j++)
        vetor[j]=vetor_aux[j];

    *ocupadas=j;

}





