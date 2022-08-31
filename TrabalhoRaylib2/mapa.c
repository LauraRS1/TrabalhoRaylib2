
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "jogador.h"
#include "mapa.h"
#include "desenha.h"
#include "bau.h"

void mapa_carrega(Mapa *mapa) {
    int i;
    strcpy(mapa->mapa[0], "XXXXXXXXXX");
    strcpy(mapa->mapa[1], "X1 C  C2 X");
    strcpy(mapa->mapa[2], "XXHX  XX X");
    strcpy(mapa->mapa[3], "XCH    1 X");
    strcpy(mapa->mapa[4], "XXX HXHX X");
    strcpy(mapa->mapa[5], "X   H H  X");
    strcpy(mapa->mapa[6], "X  CH HC2X");
    strcpy(mapa->mapa[7], "X HXX XXXX");
    strcpy(mapa->mapa[8], "XDHCX   PX");
    strcpy(mapa->mapa[9], "XXXXXXXXXX");
    mapa->dimencao = mapa_set_dimencao(mapa->mapa);
    mapa_set_spawn(mapa);
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

    mapa->baus[0].item = 'B';
    mapa->baus[1].item = 'P';
    mapa->baus[2].item = '@';
    mapa->baus[3].item = '#';
    mapa->baus[4].item = '#';
    mapa->baus[5].item = '%';

    /*
    i = 0;
    while(i < mapa->qtdBaus){
        //Posteriormente função que faz isso sozinho
        printf("Item: ");
        scanf(" %c", &(mapa->baus[i].item));
        printf("\nITEM:%c", mapa->baus[i].item);
        /*printf("\nABERTO:%d", mapa->baus[i].aberto);
        printf("\nCOLUNA:%d", mapa->baus[i].localizacao.coluna);
        printf("\nINHA:%d", mapa->baus[i].localizacao.linha);*/
        //i++;
    //}


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
                //Caso próximo lugar seja uma porta(colocar intervalo de digitos no teste posteriormente)
                }else if((aux == '1') || (aux  == '2')){
                    mapa->porta = mapa->mapa[x_jog][y_jog + dir_int];
                    mapa->bau = 0;
                    mapa->escada = 0;
                }

                mapa->mapa[x_jog][y_jog + dir_int] = 'D';
                mapa->mapa[x_jog][y_jog] = mapa->deletado;
                mapa->deletado = aux;

                /*
                //queda(mapa); // faz o teste da queda
                .......
                .......
                ainda nao esta funcional, por isso o comentario na chamada da função

                */

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
//problema:
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
/*
void mapa_imprime(Mapa mapa) {
    int i, j;
    for(i = 0; i < mapa.dimencao.linha; i++){
        for(j = 0; j < mapa.dimencao.coluna; j++){
            printf("%c", mapa.mapa[i][j]);
        }
        printf("\n");
    }
    jog_print_info(mapa.jogador);
}
void chama_mensagem_bau() {
    char abrir;
    printf("\nVoce encontrou um bau. Deseja abri-lo? [s]im");
    scanf("%c", &abrir);

    if(toupper(abrir) == 'S') {
        // aqui a função que seleciona um item
    }
}
*/
// função recursiva da queda
// chamar apos movimento lateral movimento para os lados
// ainda não está funcional. A matriz na linha abaixo nao esta representando o char correto
/*
void queda(Mapa *mapa) {
    //variáveis para a localização do jogador
    mapa_localiza_jogador(mapa);//Atualiza a localização do jogador
    int x_jog = mapa->jogador.localizacao.linha;
    int y_jog = mapa->jogador.localizacao.coluna;
    char aux; // guarda o conteudo da matriz abaixo do jogador

    printf("\nchar abaixo: %c", mapa->mapa[x_jog - 1][y_jog]);
    if(mapa->mapa[x_jog - 1][y_jog] == ' ') { // se jogador esta flutuando
        mapa->mapa[x_jog][y_jog - 1] = 'D'; // // diminui linha do jogador na matriz
        mapa->mapa[x_jog][y_jog] = ' ';

        queda(mapa); // continua verificando proximas linhas
    } else if(mapa->mapa[x_jog - 1][y_jog] != 'X') { // se jogador sobre um objeto diferente de parede
        aux = mapa->mapa[x_jog - 1][y_jog]; // apenas atualiza jogador, mas nao chama função
        mapa->mapa[x_jog][y_jog - 1] = 'D';
        mapa->mapa[x_jog][y_jog] = aux;
    }

}
*/



