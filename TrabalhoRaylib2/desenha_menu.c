
#include "raylib.h"
#define OPCOES 4
#define TAMANHO_FONTE 20
#define TAMANHO_FONTE_MAIOR 60
#define TAMANHO_TEXTO 20
#define MEIO 400
#define ESPACO 100


void DesenhaMenu(int selecionada) {
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
