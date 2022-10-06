#include "salva_estado_jogo.h"
#include "mapa.h"
#include "coordenadas.h"
#include "jogador.h"
#include "bau.h"
#include <stdio.h>
#define NOME_ARQUIVO "jogo.dat"

/*
    arq_salva_jogo:
    Salva o estado do mapa (jogo) em um arquivo binário.
    @param mapa: estrutura Mapa representando o mapa do jogo
*/

void arq_salva_jogo(Mapa mapa) {
    FILE *arq_jogo;
    int i, qtd_char; // qtd caracteres inseridos por linha da matriz

    // abre arquivo para escrita; apaga caso já exista (novo save)
    arq_jogo = fopen(NOME_ARQUIVO, "w");
    if(!arq_jogo) {
        printf("Erro ao abrir arquivo!\n");
    } else {
        // modifica o spaw do jogador para a posição onde ele salvou o jogo
        //mapa_set_spawn(&mapa); --> nao consigo fazer funcionar; quando descomenta aparece uma porta toda vez que carrega o mapa

        // salva estado jogador
        fwrite(&(mapa.jogador), sizeof(Jogador), 1, arq_jogo);
        // salva estado mapa
        fwrite(&(mapa.dimencao), sizeof(Localizacao), 1, arq_jogo);
        fwrite(&(mapa.spawn), sizeof(Localizacao), 1, arq_jogo);
        fwrite(&(mapa.escada), sizeof(int), 1, arq_jogo);
        fwrite(&(mapa.porta), sizeof(char), 1, arq_jogo);
        fwrite(&(mapa.bau), sizeof(int), 1, arq_jogo);
        fwrite(&(mapa.qtdBaus), sizeof(int), 1, arq_jogo);
        fwrite(&(mapa.chave), sizeof(int), 1, arq_jogo);
        fwrite(&(mapa.baus), sizeof(Bau), mapa.qtdBaus, arq_jogo);
        fwrite(&(mapa.deletado), sizeof(char), 1, arq_jogo);
        fwrite(&(mapa.nivel), sizeof(int), 1, arq_jogo);

        // salva matriz de caracteres
        qtd_char = mapa.dimencao.coluna;
        for(i = 0; i < mapa.dimencao.linha; i++) {
            fwrite(mapa.mapa[i], sizeof(char), qtd_char, arq_jogo);
        }

        fclose(arq_jogo);
    }
}

/*
    arq_recupera_jogo:
    Recupera o conteúdo do arquivo binário contendo o estado do jogo
    e o carrega em um ponteiro do tipo Mapa.
    @param *mapa: ponteiro para o mapa do jogo.
*/

void arq_recupera_jogo(Mapa *mapa) {
    FILE *arq_jogo;
    int i, qtd_char;

    // abre sem apagar
    arq_jogo = fopen(NOME_ARQUIVO, "r");
    if(!arq_jogo) {
        printf("Erro ao abrir arquivo!\n");
    } else {
       // recupera estado jogador
        fread(&(mapa->jogador), sizeof(Jogador), 1, arq_jogo);
        // recupera estado mapa
        fread(&(mapa->dimencao), sizeof(Localizacao), 1, arq_jogo);
        fread(&(mapa->spawn), sizeof(Localizacao), 1, arq_jogo);
        //fread(&(mapa->jogador.localizacao), sizeof(Localizacao), 1, arq_jogo); --> tentei ler o spawn direto para a localização do jogador, mas também não funcionou
        fread(&(mapa->escada), sizeof(int), 1, arq_jogo);
        fread(&(mapa->porta), sizeof(char), 1, arq_jogo);
        fread(&(mapa->bau), sizeof(int), 1, arq_jogo);
        fread(&(mapa->qtdBaus), sizeof(int), 1, arq_jogo);
        fread(&(mapa->chave), sizeof(int), 1, arq_jogo);
        fread(&(mapa->baus), sizeof(Bau), mapa->qtdBaus, arq_jogo);
        fread(&(mapa->deletado), sizeof(char), 1, arq_jogo);
        fread(&(mapa->nivel), sizeof(int), 1, arq_jogo);

        // recupera matriz de caracteres
        qtd_char = mapa->dimencao.coluna;
        for(i = 0; i < mapa->dimencao.linha; i++) {
            fread(mapa->mapa[i], sizeof(char), qtd_char, arq_jogo);
        }

        fclose(arq_jogo);
    }
}

