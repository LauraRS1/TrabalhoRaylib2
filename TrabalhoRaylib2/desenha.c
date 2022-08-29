#include "desenha.h"
void desenha_menu(int selecionada) {
    char menu[OPCOES][TAMANHO_TEXTO] = {"Novo Jogo", "Carregar Jogo","Ranking de Pontos", "Sair"};
    char mudado[TAMANHO_TEXTO];  // string para guardar o texto modificado
    // desenha o texto de acordo com o parametro dado
    switch (selecionada) {
        case 0:

            //Menu de opcoes Novo Jogo selecionado
            sprintf(mudado, "-> %s <-", menu[0]);
            DrawText(mudado, MEIO - MeasureText(mudado, TAMANHO_FONTE_MAIOR)/2, ESPACO, TAMANHO_FONTE_MAIOR, PURPLE);
            DrawText(menu[1], MEIO - MeasureText(menu[1], TAMANHO_FONTE)/2, ESPACO*2, TAMANHO_FONTE, GRAY);
            DrawText(menu[2], MEIO - MeasureText(menu[2], TAMANHO_FONTE)/2, ESPACO*3, TAMANHO_FONTE, GRAY);
            DrawText(menu[3], MEIO - MeasureText(menu[3], TAMANHO_FONTE)/2, ESPACO*4, TAMANHO_FONTE, GRAY);
            break;

        case 1:
            //Menu de opcoes Carregar o Jogo selecionado
            DrawText(menu[0], MEIO - MeasureText(menu[0], TAMANHO_FONTE)/2, ESPACO, TAMANHO_FONTE, GRAY);
            sprintf(mudado, "-> %s <-", menu[1]);
            DrawText(mudado, MEIO - MeasureText(mudado, TAMANHO_FONTE_MAIOR)/2, ESPACO*2, TAMANHO_FONTE_MAIOR, GREEN);
            DrawText(menu[2], MEIO - MeasureText(menu[2], TAMANHO_FONTE)/2, ESPACO*3, TAMANHO_FONTE, GRAY);
            DrawText(menu[3], MEIO - MeasureText(menu[3], TAMANHO_FONTE)/2, ESPACO*4, TAMANHO_FONTE, GRAY);
            break;

        case 2:
            //Menu de opcoes Ranking Pontos Selecionado
            DrawText(menu[0], MEIO - MeasureText(menu[0], TAMANHO_FONTE)/2, ESPACO, TAMANHO_FONTE, GRAY);
            DrawText(menu[1], MEIO - MeasureText(menu[1], TAMANHO_FONTE)/2, ESPACO*2, TAMANHO_FONTE, GRAY);
            sprintf(mudado, "-> %s <-", menu[2]);
            DrawText(mudado, MEIO - MeasureText(mudado, TAMANHO_FONTE_MAIOR)/2, ESPACO*3, TAMANHO_FONTE_MAIOR, BLUE);
            DrawText(menu[3], MEIO - MeasureText(menu[3], TAMANHO_FONTE)/2, ESPACO*4, TAMANHO_FONTE, GRAY);
            break;

       case 3:
            //Menu de opcoes Sair selecionado
            DrawText(menu[0], MEIO - MeasureText(menu[0], TAMANHO_FONTE)/2, ESPACO, TAMANHO_FONTE, GRAY);
            DrawText(menu[1], MEIO - MeasureText(menu[1], TAMANHO_FONTE)/2, ESPACO*2, TAMANHO_FONTE, GRAY);
            DrawText(menu[2], MEIO - MeasureText(menu[2], TAMANHO_FONTE)/2, ESPACO*3, TAMANHO_FONTE, GRAY);
            sprintf(mudado, "-> %s <-", menu[3]);
            DrawText(mudado, MEIO - MeasureText(mudado, TAMANHO_FONTE_MAIOR)/2, ESPACO*4, TAMANHO_FONTE_MAIOR, RED);
            break;

      }
}
void desenha_nivel(Mapa *mapa){

    int i, j;
    for(i = 0; i < mapa->dimencao.linha; i++){
        for(j = 0; j < mapa->dimencao.coluna; j++){
                //Parede
                if(mapa->mapa[i][j] == 'X')
                    DrawRectangle((0 + LADO_QUADRADO * j), (0 + LADO_QUADRADO * i), LADO_QUADRADO, LADO_QUADRADO, GRAY);
                //Jogador
                 if(mapa->mapa[i][j] == 'D')
                    DrawRectangle((0 + LADO_QUADRADO * j), (0 + LADO_QUADRADO * i), LADO_QUADRADO, LADO_QUADRADO, RED);
                //Jogador na escada
                if((mapa->mapa[i][j] == 'D') && (mapa->escada == 1))
                    DrawRectangle((0 + LADO_QUADRADO * j), (0 + LADO_QUADRADO * i), LADO_QUADRADO, LADO_QUADRADO, GREEN);
                //Jogador na porta
                if((mapa->mapa[i][j] == 'D') && (mapa->porta != ' '))
                    DrawRectangle((0 + LADO_QUADRADO * j), (0 + LADO_QUADRADO * i), LADO_QUADRADO, LADO_QUADRADO, ORANGE);
                //Jogador no baú
                if((mapa->mapa[i][j] == 'D') && (mapa->bau == 1))
                    DrawRectangle((0 + LADO_QUADRADO * j), (0 + LADO_QUADRADO * i), LADO_QUADRADO, LADO_QUADRADO, PURPLE);
                //Baú
                if(mapa->mapa[i][j] == 'C')
                    DrawRectangle((0 + LADO_QUADRADO * j), (0 + LADO_QUADRADO * i), LADO_QUADRADO, LADO_QUADRADO, PINK);
                //Escada
                if(mapa->mapa[i][j] == 'H')
                    DrawRectangle((0 + LADO_QUADRADO * j), (0 + LADO_QUADRADO * i), LADO_QUADRADO, LADO_QUADRADO, BROWN);
                //Portas
                if((mapa->mapa[i][j] == '1') || (mapa->mapa[i][j] == '2'))
                    DrawRectangle((0 + LADO_QUADRADO * j), (0 + LADO_QUADRADO * i), LADO_QUADRADO, LADO_QUADRADO, YELLOW);


                }
        }
 }
