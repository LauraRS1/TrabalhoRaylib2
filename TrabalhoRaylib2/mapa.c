
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
    printf("\nDIEMNCAO: %d %d", mapa->dimencao.linha, mapa->dimencao.coluna);
    mapa_set_spawn(mapa);
    printf("\nSPAWN: %d %d", mapa->spawn.linha, mapa->spawn.coluna);
    mapa->porta = ' ';
    mapa->deletado = ' ';
    mapa->escada = 0;
    mapa->bau = 0;
    mapa->chave = 0;
    mapa->jogador = jog_inicializa(mapa->spawn.linha, mapa->spawn.coluna);

    //V�riav�l deletado, guarda o char da matriz em que o char 'D' come�ou a ocupar
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
    Localizacao local_porta;//V�riavel da localiza��o da porta
    mapa_localiza_jogador(mapa);//Atualiza a localiza��o do jogador
    //vari�veis para a localiza��o do jogador
    int x_jog = mapa->jogador.localizacao.linha;
    int y_jog = mapa->jogador.localizacao.coluna;

    char aux;//v�riavel de auxilio para trocar os char da matriz de lugar
    int dir_int;//v�riavel para somar no indice da matriz

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

            //Caso n�o haja escada acima do jogador
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


            mapa->escada = 1;//Jogador agora est� numa escada
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

            //Caso n�o for uma parede
            if(aux != 'X'){
                //Se o pr�ximo lugar n�o for um objeto especial
                if(aux == ' '){
                        //o lugar do jogador que o jogador estar� n�o ser� um b�u
                        mapa->bau = 0;
                        //nem uma escada
                        mapa->escada = 0;
                        //nem uma porta
                        mapa->porta = ' ';



                //Caso pr�ximo lugar seja uma escada...
                }else if(aux == 'H'){
                    mapa->escada = 1;
                    mapa->bau = 0;
                    mapa->porta = ' ';
                //Caso pr�ximo lugar seja um ba�...
                }else if(aux == 'C'){
                    mapa->bau = 1;
                    mapa->escada = 0;
                    mapa->porta = ' ';

                    //chama_mensagem_bau();
                //Caso pr�ximo lugar seja uma porta(colocar intervalo de digitos posteriormente)
                }else if((aux > '0') && (aux  <='9')){
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
                ainda nao esta funcional, por isso o comentario na chamada da fun��o

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

/*
    mapa_busca_porta
    Retorna a quantidades de ba�s que um mapa possui.
    @param mapa: um Mapa
    @param porta: um char referentea porta que o jogador est� ocupando
    @param *local_porta: ponteiro para a Localizacao da porta

*/
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

/*
    mapa_bau_quantidade
    Retorna a quantidades de ba�s que um mapa possui.
    @param *mapa: ponteiro para um Mapa;

*/
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
/*
    mapa_bau_cria
    Inicializa o vetor de b�us com os dados padr�es
    @param *mapa: ponteiro para um Mapa;

*/

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
/*
    mapa_set_dimencao
    Retorna a Localiza��o da �ltima posi��o ocupada da matriz do mapa
    @param mapa: Um mapa;
*/

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
/*
    Fun��o respons�vel por atribuir o valor correto para o spawn do mapa, localiza��o em que o jogador come�a e retorna ao morrer.
    @param *mapa: ponteiro para um Mapa;
*/
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
    Fun��o que gera o item da chave em um ba� aleat�rio
    @param *mapa: ponteiro para um Mapa;
*/
void mapa_gera_chave(Mapa *mapa){
    int rand;
    rand = GetRandomValue(0, mapa->qtdBaus - 1);
    mapa->baus[rand].item = 'P';
}

/*
    Fun��o que gera as bombas de uma determinada fase, n�mero de bombas na fase � igual o n�mero da fase.
    @param *mapa: Ponteiro para um Mapa;
    @param fase: N�mero da fase
*/
void mapa_gera_bomba(Mapa *mapa, int fase){
    int rand;
    while(fase > 0){
        rand = GetRandomValue(0, mapa->qtdBaus - 1);

        //Atribui a bomba ao b�u caso esteja vazio(sem a chave)
        if(mapa->baus[rand].item == ' '){
            mapa->baus[rand].item = 'B';
            fase--;
        }
    }
}
/*  mapa_gera_outros:
    Fun��o que gera o restante dos itens, que apenas somam pontos
    @param *mapa: Ponteiro para um Mapa
    @param fase: N�mero da fase
*/
void mapa_gera_outros(Mapa *mapa, int fase){
    //Vari�vel limite: N�mero de B�us do mapa - Quantidade de bombas(fase) - n�mero de chaves(1)
    int limite = mapa->qtdBaus - fase - 1;
    int rand, rand2;//V�riaveis para guardar n�meros aleat�rios
    char itens[5] = {'!','@','#','$','%'}; //Vetor com os tipos de bens

     while(limite > 0){
        rand = GetRandomValue(0, mapa->qtdBaus - 1);//Gera um n�mero aleat�rio entre 0, n�mero referente da primeira posi��o e o n�mero referente a �ltima posi��o do vetor de Ba�s
        rand2 = GetRandomValue(0, 4);//
        //Atribui o item ao ba� caso ele esteja sem itens;
        if(mapa->baus[rand].item == ' '){
            mapa->baus[rand].item = itens[rand2];
            limite--;
        }
    }

}
/*  mapa_bau_gera_itens(Mapa *mapa):
    Fun��o que chama as fun��es que geram os itens dos ba�s dado o endere�o de um mapa
    @param *mapa: Ponteiro para um Mapa

*/
void mapa_bau_gera_itens(Mapa *mapa){
    mapa_gera_chave(mapa);
    mapa_gera_bomba(mapa, mapa->nivel);
    mapa_gera_outros(mapa, mapa->nivel);
}

/*  mapa_seleciona_fase:
    Retorna um Mapa com um mapa atribuido atrav�s de um arquivo texto referente a fase da partida
    @param num: interio referente a fase da partida
    @param *tela: ponteiro para a variav�l do tipo GameScreen

*/

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
    //Se n�o tiver arquivos para ler, pula para tela de encerramento
    }else{
        *tela = ENDING;
    }

    return mapa;
}
/*
    mapa_carrega_proxima_fase_e_jogador:
    Dado um ponteiro para um mapa e um jogador, inicia as vari�veis restantes do mapa e atribui asinforma��es do jogador dado.
    @param *mapa: ponteiro para um mapa
    @param jogador: ponteiro para a variav�l do tipo GameScreen

*/
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

    //V�riav�l deletado, guarda o char da matriz em que o char 'D' come�ou a ocupar
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
*/
/*
void chama_mensagem_bau() {
    char abrir;
    printf("\nVoce encontrou um bau. Deseja abri-lo? [s]im");
    scanf("%c", &abrir);

    if(toupper(abrir) == 'S') {
        // aqui a fun��o que seleciona um item
    }
}
*/
// fun��o recursiva da queda
// chamar apos movimento lateral movimento para os lados
// ainda n�o est� funcional. A matriz na linha abaixo nao esta representando o char correto
/*
void queda(Mapa *mapa) {
    //vari�veis para a localiza��o do jogador
    mapa_localiza_jogador(mapa);//Atualiza a localiza��o do jogador
    int x_jog = mapa->jogador.localizacao.linha;
    int y_jog = mapa->jogador.localizacao.coluna;
    char aux; // guarda o conteudo da matriz abaixo do jogador

    printf("\nchar abaixo: %c", mapa->mapa[x_jog - 1][y_jog]);
    if(mapa->mapa[x_jog - 1][y_jog] == ' ') { // se jogador esta flutuando
        mapa->mapa[x_jog][y_jog - 1] = 'D'; // // diminui linha do jogador na matriz
        mapa->mapa[x_jog][y_jog] = ' ';

        queda(mapa); // continua verificando proximas linhas
    } else if(mapa->mapa[x_jog - 1][y_jog] != 'X') { // se jogador sobre um objeto diferente de parede
        aux = mapa->mapa[x_jog - 1][y_jog]; // apenas atualiza jogador, mas nao chama fun��o
        mapa->mapa[x_jog][y_jog - 1] = 'D';
        mapa->mapa[x_jog][y_jog] = aux;
    }

}
*/



