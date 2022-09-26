#include "desenha.h"

void desenha_load(){
    DrawText("Carregando...", (LARGURA-MeasureText("Carregando...",TAMANHO_FONTE*3))/2, ALTURA/2 - 50, TAMANHO_FONTE*3, WHITE);

}

void desenha_proximo(){
    DrawText("Passou de Nivel", (LARGURA-MeasureText("Passou de Nivel",TAMANHO_FONTE*3))/2, ALTURA/2 - 50, TAMANHO_FONTE*3, WHITE);

}
void desenha_menu(int selecionada) {
    char menu[OPCOES][TAMANHO_TEXTO] = {"Novo Jogo", "Carregar Jogo","Ranking de Pontos", "Sair"};
    char mudado[TAMANHO_TEXTO];  // string para guardar o texto modificado
    // desenha o texto de acordo com o parametro dado
    switch (selecionada) {
        case 0:

            //Menu de opcoes Novo Jogo selecionado
            sprintf(mudado, "-> %s <-", menu[0]);
            DrawText(mudado, MEIO - MeasureText(mudado, TAMANHO_FONTE_MAIOR)/2, ESPACO, TAMANHO_FONTE_MAIOR, WHITE);
            DrawText(menu[1], MEIO - MeasureText(menu[1], TAMANHO_FONTE)/2, ESPACO*1.625, TAMANHO_FONTE, GRAY);
            DrawText(menu[2], MEIO - MeasureText(menu[2], TAMANHO_FONTE)/2, ESPACO*2.25, TAMANHO_FONTE, GRAY);
            DrawText(menu[3], MEIO - MeasureText(menu[3], TAMANHO_FONTE)/2, ESPACO*2.875, TAMANHO_FONTE, GRAY);
            break;

        case 1:
            //Menu de opcoes Carregar o Jogo selecionado
            DrawText(menu[0], MEIO - MeasureText(menu[0], TAMANHO_FONTE)/2, ESPACO, TAMANHO_FONTE, GRAY);
            sprintf(mudado, "-> %s <-", menu[1]);
            DrawText(mudado, MEIO - MeasureText(mudado, TAMANHO_FONTE_MAIOR)/2, ESPACO*1.625, TAMANHO_FONTE_MAIOR, WHITE);
            DrawText(menu[2], MEIO - MeasureText(menu[2], TAMANHO_FONTE)/2, ESPACO*2.25, TAMANHO_FONTE, GRAY);
            DrawText(menu[3], MEIO - MeasureText(menu[3], TAMANHO_FONTE)/2, ESPACO*2.875, TAMANHO_FONTE, GRAY);
            break;

        case 2:
            //Menu de opcoes Ranking Pontos Selecionado
            DrawText(menu[0], MEIO - MeasureText(menu[0], TAMANHO_FONTE)/2, ESPACO, TAMANHO_FONTE, GRAY);
            DrawText(menu[1], MEIO - MeasureText(menu[1], TAMANHO_FONTE)/2, ESPACO*1.625, TAMANHO_FONTE, GRAY);
            sprintf(mudado, "-> %s <-", menu[2]);
            DrawText(mudado, MEIO - MeasureText(mudado, TAMANHO_FONTE_MAIOR)/2, ESPACO*2.25, TAMANHO_FONTE_MAIOR, WHITE);
            DrawText(menu[3], MEIO - MeasureText(menu[3], TAMANHO_FONTE)/2, ESPACO*2.875, TAMANHO_FONTE, GRAY);
            break;

       case 3:
            //Menu de opcoes Sair selecionado
            DrawText(menu[0], MEIO - MeasureText(menu[0], TAMANHO_FONTE)/2, ESPACO, TAMANHO_FONTE, GRAY);
            DrawText(menu[1], MEIO - MeasureText(menu[1], TAMANHO_FONTE)/2, ESPACO*1.625, TAMANHO_FONTE, GRAY);
            DrawText(menu[2], MEIO - MeasureText(menu[2], TAMANHO_FONTE)/2, ESPACO*2.25, TAMANHO_FONTE, GRAY);
            sprintf(mudado, "-> %s <-", menu[3]);
            DrawText(mudado, MEIO - MeasureText(mudado, TAMANHO_FONTE_MAIOR)/2, ESPACO*2.875, TAMANHO_FONTE_MAIOR, WHITE);
            break;

      }
}

void desenha_hud(Mapa *mapa) {
    char saida_pontos[TAMANHO_TEXTO], saida_vida[TAMANHO_TEXTO], saida_fase[TAMANHO_TEXTO], saida_chave[TAMANHO_TEXTO];
    int x=0, y=0;

    DrawText("SCORE:", x, y, TAMANHO_FONTE, WHITE);
    x += MeasureText("SCORE: ", TAMANHO_FONTE);

    sprintf(saida_pontos, "%d pontos", mapa->jogador.pontuacao);
    DrawText(saida_pontos, x, y, TAMANHO_FONTE, DARKBLUE);
    x += MeasureText("2500 pontos", TAMANHO_FONTE);

    x += 30;
    DrawText("VIDAS:", x, y, TAMANHO_FONTE, WHITE);
    x += MeasureText("VIDAS: ", TAMANHO_FONTE);

    sprintf(saida_vida, "%d", mapa->jogador.vidas);
    DrawText(saida_vida, x, y, TAMANHO_FONTE, DARKBLUE);

    x += QUADRADO_LARGURA;
    DrawText("FASE:", x, y, TAMANHO_FONTE, WHITE);
    x += MeasureText("FASE: ", TAMANHO_FONTE);

    sprintf(saida_fase, "%d", mapa->nivel);
    DrawText(saida_fase, x, y, TAMANHO_FONTE, DARKBLUE);

    x += QUADRADO_LARGURA;
    DrawText("CHAVE:", x, y, TAMANHO_FONTE, WHITE);
    x += MeasureText("CHAVE: ", TAMANHO_FONTE);

    sprintf(saida_chave, "%d", mapa->chave);
    DrawText(saida_chave, x, y, TAMANHO_FONTE, DARKBLUE);


}

void desenha_nivel(Mapa *mapa, Texture2D imagens[]){

    desenha_hud(mapa);

    int i, j;
    for(i = 0; i < mapa->dimencao.linha; i++){
        for(j = 0; j < mapa->dimencao.coluna; j++){
                //Parede
                if(mapa->mapa[i][j] == 'X')
                    if(i==0)
                        DrawTexture(imagens[9], (0 + QUADRADO_LARGURA *j), (0 + QUADRADO_ALTURA * i), WHITE);
                    else
                        DrawTexture(imagens[0], (0 + QUADRADO_LARGURA *j), (0 + QUADRADO_ALTURA * i), WHITE);
                if((mapa->mapa[i][j] == 'P') && (mapa->chave == 0))
                    DrawTexture(imagens[9], (0 + QUADRADO_LARGURA *j), (0 + QUADRADO_ALTURA * i), WHITE);
                //Jogador
                 if(mapa->mapa[i][j] == 'D'&& (mapa->bau != 1)&& (mapa->escada != 1))
                    DrawTexture(imagens[1], (0 + QUADRADO_LARGURA *j), (0 + QUADRADO_ALTURA * i), WHITE);
                //Jogador na escada
                if((mapa->mapa[i][j] == 'D') && (mapa->escada == 1))
                    DrawTexture(imagens[2], (0 + QUADRADO_LARGURA *j), (0 + QUADRADO_ALTURA * i), WHITE);
                //Jogador na porta
                if((mapa->mapa[i][j] == 'D') && (mapa->porta != ' ') )
                    DrawTexture(imagens[3], (0 + QUADRADO_LARGURA *j), (0 + QUADRADO_ALTURA * i), WHITE);
                //Jogador no baú
                if((mapa->mapa[i][j] == 'D') && (mapa->bau == 1))
                    DrawTexture(imagens[4], (0 + QUADRADO_LARGURA *j), (0 + QUADRADO_ALTURA * i), WHITE);
                //Baú
                if(mapa->mapa[i][j] == 'C')
                    DrawTexture(imagens[5], (0 + QUADRADO_LARGURA *j), (0 + QUADRADO_ALTURA * i), WHITE);
                //Escada
                if(mapa->mapa[i][j] == 'H')
                    DrawTexture(imagens[6], (0 + QUADRADO_LARGURA *j), (0 + QUADRADO_ALTURA * i), WHITE);
                //Porta normal
                if((mapa->mapa[i][j] == '1') || (mapa->mapa[i][j] == '2'))
                    DrawTexture(imagens[7], (0 + QUADRADO_LARGURA *j), (0 + QUADRADO_ALTURA * i), WHITE);
                //Porta fase
                if((mapa->mapa[i][j] == 'P') && (mapa->chave == 1))
                    DrawTexture(imagens[8], (0 + QUADRADO_LARGURA *j), (0 + QUADRADO_ALTURA * i), WHITE);
                //parede do fundo
                if((mapa->mapa[i][j] == ' '))
                    DrawTexture(imagens[9], (0 + QUADRADO_LARGURA *j), (0 + QUADRADO_ALTURA * i), WHITE);
                }


        }
 }
