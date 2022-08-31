#include "desenha.h"
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
void desenha_nivel(Mapa *mapa){

    int i, j;
    for(i = 0; i < mapa->dimencao.linha; i++){
        for(j = 0; j < mapa->dimencao.coluna; j++){
                //Parede
                if(mapa->mapa[i][j] == 'X')
                    DrawRectangle((0 + QUADRADO_LARGURA *j), (0 + QUADRADO_ALTURA * i), QUADRADO_LARGURA, QUADRADO_ALTURA, GRAY);
                //Jogador
                 if(mapa->mapa[i][j] == 'D')
                    DrawRectangle((0 + QUADRADO_LARGURA *j), (0 + QUADRADO_ALTURA * i), QUADRADO_LARGURA, QUADRADO_ALTURA, RED);
                //Jogador na escada
                if((mapa->mapa[i][j] == 'D') && (mapa->escada == 1))
                    DrawRectangle((0 + QUADRADO_LARGURA *j), (0 + QUADRADO_ALTURA * i), QUADRADO_LARGURA, QUADRADO_ALTURA, GREEN);
                //Jogador na porta
                if((mapa->mapa[i][j] == 'D') && (mapa->porta != ' '))
                    DrawRectangle((0 + QUADRADO_LARGURA *j), (0 + QUADRADO_ALTURA * i), QUADRADO_LARGURA, QUADRADO_ALTURA, ORANGE);
                //Jogador no baú
                if((mapa->mapa[i][j] == 'D') && (mapa->bau == 1))
                    DrawRectangle((0 + QUADRADO_LARGURA *j), (0 + QUADRADO_ALTURA * i), QUADRADO_LARGURA, QUADRADO_ALTURA, PURPLE);
                //Baú
                if(mapa->mapa[i][j] == 'C')
                    DrawRectangle((0 + QUADRADO_LARGURA *j), (0 + QUADRADO_ALTURA * i), QUADRADO_LARGURA, QUADRADO_ALTURA, PINK);
                //Escada
                if(mapa->mapa[i][j] == 'H')
                    DrawRectangle((0 + QUADRADO_LARGURA *j), (0 + QUADRADO_ALTURA * i), QUADRADO_LARGURA, QUADRADO_ALTURA, BROWN);
                //Portas
                if((mapa->mapa[i][j] == '1') || (mapa->mapa[i][j] == '2'))
                    DrawRectangle((0 + QUADRADO_LARGURA *j), (0 + QUADRADO_ALTURA * i), QUADRADO_LARGURA, QUADRADO_ALTURA, YELLOW);

                if((mapa->mapa[i][j] == 'P') && (mapa->chave == 1))
                    DrawRectangle((0 + QUADRADO_LARGURA *j), (0 + QUADRADO_ALTURA * i), QUADRADO_LARGURA, QUADRADO_ALTURA, GREEN);
                }


        }
 }
