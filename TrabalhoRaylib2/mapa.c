
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "jogador.h"
#include "raylib.h"
#include "mapa.h"
#include "desenha.h"
#include "bau.h"

void mapa_carrega(Mapa *mapa) {
    mapa->dimencao = mapa_set_dimencao(mapa->mapa);
    printf("\nDIMENCAO: %d %d\n", mapa->dimencao.linha, mapa->dimencao.coluna);
    mapa_set_spawn(mapa);
    printf("\nSPAWN: %d %d\n", mapa->spawn.linha, mapa->spawn.coluna);
    mapa->porta = ' ';
    mapa->deletado = ' ';
    mapa->escada = 0;
    mapa->bau = 0;
    mapa->chave = 0;
    mapa->jogador = jog_inicializa(mapa->spawn.linha, mapa->spawn.coluna);

    //Váriavél deletado, guarda o char da matriz em que o char 'D' começou a ocupar
    if(mapa->escada == 1){
        mapa->deletado = 'H';
    }
    if(mapa->porta != ' '){
        mapa->deletado = mapa->porta;
    }
    if(mapa->bau == 1){
        mapa->deletado = 'C';
    }

    mapa->qtdBaus = mapa_bau_quantidade(mapa);
    mapa_bau_cria(mapa);
    mapa_bau_gera_itens(mapa);




}
void mapa_movimenta(Mapa *mapa, char direcao) {
    Localizacao local_porta;//Váriavel da localização da porta
    mapa_localiza_jogador(mapa);//Atualiza a localização do jogador
    //variáveis para a localização do jogador
    int x_jog = mapa->jogador.localizacao.linha;
    int y_jog = mapa->jogador.localizacao.coluna;

    char aux;//váriavel de auxilio para trocar os char da matriz de lugar
    int dir_int;//váriavel para somar no indice da matriz

    if((direcao == 'e') || (direcao == 'c')){
        dir_int = -1;
        } else{
            dir_int = 1;
            }
    //Caso for para cima
    if(direcao == 'c'){
        aux = mapa->mapa[x_jog + dir_int][y_jog];

        //Se o jogador estiver numa porta
        if(mapa->porta != ' '){
            mapa_busca_porta(*mapa, mapa->porta, &local_porta);
            mapa->mapa[x_jog][y_jog] = mapa->porta;
            mapa->mapa[local_porta.linha][local_porta.coluna] = 'D';
        }
        //Se o jogador estiver numa escada
        if(mapa->escada == 1){

            //Caso não haja escada acima do jogador
            if(aux == ' ')
                mapa->escada = 0;

            mapa->mapa[x_jog + dir_int][y_jog] = 'D';
            mapa->mapa[x_jog][y_jog] = mapa->deletado;
            mapa->deletado = aux;
        }
    }
    //Caso for para baixo
     if(direcao == 'b'){
        aux = mapa->mapa[x_jog + dir_int][y_jog];

        //Se o jogador estiver num lugar com uma escada embaixo
        if((aux == 'H') && (mapa->escada == 0)){


            mapa->escada = 1;//Jogador agora está numa escada
            mapa->mapa[x_jog][y_jog] = mapa->deletado;
            mapa->mapa[x_jog + dir_int][y_jog] = 'D';
            mapa->deletado = aux;

        //Caso o jogador for descer e estiver numa escada.
        } else if((mapa->escada == 1)  && (aux == 'H')){
            mapa->mapa[x_jog][y_jog] = mapa->deletado;
            mapa->mapa[x_jog + dir_int][y_jog] = 'D';
            mapa->deletado = aux;
        }


    }

    //Caso for para esquerda ou para a direita
    if(((direcao == 'e') || (direcao == 'd')) && ((mapa->mapa[x_jog + 1][y_jog] == 'X') || (mapa->mapa[x_jog + 1][y_jog] == 'H'))){
        aux = mapa->mapa[x_jog][y_jog + dir_int];

            //Caso não for uma parede
            if(aux != 'X'){
                //Se o próximo lugar não for um objeto especial
                if(aux == ' '){
                        //o lugar do jogador que o jogador estará não será um báu
                        mapa->bau = 0;
                        //nem uma escada
                        mapa->escada = 0;
                        //nem uma porta
                        mapa->porta = ' ';



                //Caso próximo lugar seja uma escada...
                }else if(aux == 'H'){
                    mapa->escada = 1;
                    mapa->bau = 0;
                    mapa->porta = ' ';
                //Caso próximo lugar seja um baú...
                }else if(aux == 'C'){
                    mapa->bau = 1;
                    mapa->escada = 0;
                    mapa->porta = ' ';

                    //chama_mensagem_bau();
                //Caso próximo lugar seja uma porta(colocar intervalo de digitos posteriormente)
                }else if((aux > '0') && (aux  <='9')){
                     mapa->porta = mapa->mapa[x_jog][y_jog + dir_int];
                    mapa->bau = 0;
                    mapa->escada = 0;
                }

                mapa->mapa[x_jog][y_jog + dir_int] = 'D';
                mapa->mapa[x_jog][y_jog] = mapa->deletado;
                mapa->deletado = aux;

            }
    }

}

void mapa_localiza_jogador(Mapa *mapa) {
    int i, j;
    for(i = 0; i < mapa->dimencao.linha; i++){
        for(j = 0; j < mapa->dimencao.coluna; j++){
            if(mapa->mapa[i][j] == 'D'){
                mapa->jogador.localizacao.linha = i;
                mapa->jogador.localizacao.coluna = j;
            }
        }
    }
}

void mapa_busca_porta(Mapa mapa, char porta, Localizacao *local_porta) {
    int i, j;
    for(i = 0; i < mapa.dimencao.linha; i++){
        for(j = 0; j < mapa.dimencao.coluna; j++){
            if(mapa.mapa[i][j] == porta){
                *local_porta = localizacao_cria(i,j);
            }
        }
    }
}

int mapa_bau_quantidade(Mapa *mapa){
    int i, j, b;
    b = 0;
    for(i = 0; i < mapa->dimencao.linha; i++){
        for(j = 0; j < mapa->dimencao.coluna; j++){
            if((mapa->mapa[i][j] == 'C') || ((mapa->mapa[i][j] == 'D') && (mapa->bau == 1)))
                b++;
        }
    }
    return b;
}


void mapa_bau_cria(Mapa *mapa){

    int i, j, b;
    b = 0;
        for(i = 0; i < mapa->dimencao.linha; i++){
            for(j = 0; j < mapa->dimencao.coluna; j++){

                if((mapa->mapa[i][j] == 'C') || ((mapa->mapa[i][j] == 'D') && (mapa->bau == 1))){

                    mapa->baus[b].localizacao.linha = i;
                    mapa->baus[b].localizacao.coluna = j;
                    mapa->baus[b].aberto = 0;
                    mapa->baus[b].item = ' ';
                    b++;
                }
            }

        }
}


Localizacao mapa_set_dimencao(char mapa[MAPA_L][MAPA_C]){
    int i, j;
    Localizacao dimencao;
    i = 0;
    j = 0;
    while(mapa[0][i] == 'X')
        i++;
    while(mapa[j][0] == 'X')
        j++;

    dimencao = localizacao_cria(j, i);
    return dimencao;
}

void mapa_set_spawn(Mapa *mapa){
    int i, j;
    for(i = 0; i < mapa->dimencao.linha; i++){
        for(j = 0; j < mapa->dimencao.coluna; j++){
            if(mapa->mapa[i][j] == 'D'){
                mapa->spawn.linha = i;
                mapa->spawn.coluna = j;
            }
        }
    }


}

void mapa_gera_chave(Mapa *mapa){
    int rand;
    rand = GetRandomValue(0, mapa->qtdBaus - 1);
    mapa->baus[rand].item = 'P';
}

void mapa_gera_bomba(Mapa *mapa, int fase){
    int rand;
    while(fase > 0){
        rand = GetRandomValue(0, mapa->qtdBaus - 1);

        //Atribui a bomba ao báu caso esteja vazio(sem a chave)
        if(mapa->baus[rand].item == ' '){
            mapa->baus[rand].item = 'B';
            fase--;
        }
    }
}

void mapa_gera_outros(Mapa *mapa, int fase){
    //Variável limite: Número de Báus do mapa - Quantidade de bombas(fase) - número de chaves(1)
    int limite = mapa->qtdBaus - fase - 1;
    int rand, rand2;//Váriaveis para guardar números aleatórios
    char itens[5] = {'!','@','#','$','%'}; //Vetor com os tipos de bens

     while(limite > 0){
        rand = GetRandomValue(0, mapa->qtdBaus - 1);//Gera um número aleatório entre 0, número referente da primeira posição e o número referente a última posição do vetor de Baús
        rand2 = GetRandomValue(0, 4);//
        //Atribui o item ao baú caso ele esteja sem itens;
        if(mapa->baus[rand].item == ' '){
            mapa->baus[rand].item = itens[rand2];
            limite--;
        }
    }

}
void mapa_bau_gera_itens(Mapa *mapa){
    mapa_gera_chave(mapa);
    mapa_gera_bomba(mapa, mapa->nivel);
    mapa_gera_outros(mapa, mapa->nivel);
}


Mapa mapa_seleciona_fase(int num, GameScreen *tela){
    Mapa mapa;
    char nome_fase[50];
    char linha[MAPA_C];
    mapa.nivel = num;
    int i = 0;
    sprintf(nome_fase, "fase%d.txt", num);
    //printf("%s\n", nome_fase);
    FILE *arquivo;
    if((arquivo = fopen(nome_fase, "r"))){
        while(fgets(linha, MAPA_C, arquivo) != NULL){
            printf("mapa[%d]%s", i, linha);
            strcpy(mapa.mapa[i], linha);


            i++;
        }
    fclose(arquivo);
    //Se não tiver arquivos para ler, pula para tela de encerramento
    }else{
        *tela = ENDING;
    }

    return mapa;
}

void mapa_carrega_proxima_fase_e_jogador(Mapa *mapa, Jogador jogador) {
    mapa->dimencao = mapa_set_dimencao(mapa->mapa);
    printf("\nDIEMNCAO: %d %d", mapa->dimencao.linha, mapa->dimencao.coluna);
    mapa_set_spawn(mapa);
    printf("\nSPAWN: %d %d", mapa->spawn.linha, mapa->spawn.coluna);
    mapa->porta = ' ';
    mapa->deletado = ' ';
    mapa->escada = 0;
    mapa->bau = 0;
    mapa->chave = 0;
    mapa->jogador = jogador;
    mapa->jogador.localizacao.linha = mapa->spawn.linha;
    mapa->jogador.localizacao.coluna = mapa->spawn.coluna;

    //Váriavél deletado, guarda o char da matriz em que o char 'D' começou a ocupar
    if(mapa->escada == 1){
        mapa->deletado = 'H';
    }
    if(mapa->porta != ' '){
        mapa->deletado = mapa->porta;
    }
    if(mapa->bau == 1){
        mapa->deletado = 'C';
    }

    mapa->qtdBaus = mapa_bau_quantidade(mapa);
    mapa_bau_cria(mapa);
    mapa_bau_gera_itens(mapa);




}

