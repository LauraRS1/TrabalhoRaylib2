#include "desenha.h"
#include <string.h>
#define ESP 90
#define TAM_VETOR 5


void desenha_ranking(Ranking vetor[], Texture2D imagens[]){
    int i, j;
    int i_vezes=10, j_vezes=20;
    char numeros[TAM_VETOR][TAM_NOME]={0};
    char posicoes[TAM_VETOR][TAM_NOME]={0};

    for(i=0; i<TAM_VETOR; i++)
        itoa(vetor[i].pontuacao, numeros[i], 10);

    for(i=0; i<TAM_VETOR; i++)
        sprintf(posicoes[i], "%d Lugar: %s %s", i+1, vetor[i].nome, numeros[i]);

    DrawText("*RANKING MUNDIAL*", MEIO - MeasureText("*RANKING MUNDIAL*", TAMANHO_FONTE_MAIOR)/2, ESPACO-100, TAMANHO_FONTE_MAIOR, DARKBLUE);
    DrawText("_________________________________________________________", MEIO - MeasureText("_________________________________________________________", TAMANHO_FONTE)/2, ESPACO-40, TAMANHO_FONTE, DARKBLUE);

    for(i=0; i<TAM_VETOR; i++)
        DrawText(posicoes[i], MEIO - MeasureText(posicoes[i], TAMANHO_FONTE)/2, ESPACO+ESP*i, TAMANHO_FONTE, WHITE);
        DrawText("Pressione esc para retornar ao menu", MEIO + 200, ESPACO+ESP*i, TAMANHO_FONTE/2, WHITE);



    for(i = 0; i < i_vezes; i++)
        for(j = 0; j < j_vezes; j++)
            DrawTexture(imagens[9], (0 + QUADRADO_LARGURA *j), (0 + QUADRADO_ALTURA * i), WHITE);

    DrawTexture(imagens[11], MEIO-250, ESPACO-30, WHITE);



}
void desenha_nvingame(){
    DrawText("Deseja iniciar um novo Jogo?", (LARGURA-MeasureText("Deseja iniciar um novo jogo?",TAMANHO_FONTE*3))/2, ALTURA/2 - 50, TAMANHO_FONTE*3, WHITE);
    DrawText("[S]", (LARGURA-MeasureText("[S]",TAMANHO_FONTE*3))/2 - 50, ALTURA/2 + 50, TAMANHO_FONTE*3, GREEN);
    DrawText("[N]", (LARGURA-MeasureText("[N]",TAMANHO_FONTE*3))/2 + 50, ALTURA/2 + 50, TAMANHO_FONTE*3, RED);
}
void desenha_retorna_menu(){
    DrawText("Deseja retornar ao Menu?", (LARGURA-MeasureText("Deseja retornar ao Menu?",TAMANHO_FONTE*3))/2, ALTURA/2 - 50, TAMANHO_FONTE*3, WHITE);
    DrawText("[S]", (LARGURA-MeasureText("[S]",TAMANHO_FONTE*3))/2 - 50, ALTURA/2 + 50, TAMANHO_FONTE*3, GREEN);
    DrawText("[N]", (LARGURA-MeasureText("[N]",TAMANHO_FONTE*3))/2 + 50, ALTURA/2 + 50, TAMANHO_FONTE*3, RED);
}

void desenha_load(){
    DrawText("Carregando...", (LARGURA-MeasureText("Carregando...",TAMANHO_FONTE*3))/2, ALTURA/2 - 50, TAMANHO_FONTE*3, WHITE);

}

void desenha_gameover(Texture2D imagens[], int pontuacao, int ultimo_lugar, char nome_ranking[]){
    DrawText("GAME OVER", (LARGURA-MeasureText("GAME OVER",TAMANHO_FONTE*3))/2, ALTURA/2 - 50, TAMANHO_FONTE*3, WHITE);

    int i, j;
    int i_vezes=10, j_vezes=20;
    for(i = 0; i < i_vezes; i++)
        for(j = 0; j < j_vezes; j++)
            DrawTexture(imagens[9], (0 + QUADRADO_LARGURA *j), (0 + QUADRADO_ALTURA * i), WHITE);


    DrawTexture(imagens[11], MEIO-33, 330, WHITE);

    if(pontuacao > ultimo_lugar){
        DrawText("Otima pontuacao! digite seu nome:", (LARGURA-MeasureText("Ótima pontuação! digite seu nome:",TAMANHO_FONTE))/2, ALTURA/2 + 100, TAMANHO_FONTE, WHITE);
    }


}
void desenha_fim(Texture2D imagens[], int pontuacao, int ultimo_lugar, char nome_ranking[]){
    DrawText("FIM", (LARGURA-MeasureText("FIM!",TAMANHO_FONTE*3))/2, ALTURA/2 - 50, TAMANHO_FONTE*3, WHITE);

    int i, j;
    int i_vezes=10, j_vezes=20;
    for(i = 0; i < i_vezes; i++)
        for(j = 0; j < j_vezes; j++)
            DrawTexture(imagens[9], (0 + QUADRADO_LARGURA *j), (0 + QUADRADO_ALTURA * i), WHITE);

    DrawTexture(imagens[11], MEIO-33, 330, WHITE);

    if(pontuacao > ultimo_lugar){
        DrawText("Otima pontuacao! digite seu nome:", (LARGURA-MeasureText("Ótima pontuação! digite seu nome:",TAMANHO_FONTE))/2, ALTURA/2 + 100, TAMANHO_FONTE, WHITE);
    }

}

void desenha_proximo(){
    DrawText("Passou de Nivel", (LARGURA-MeasureText("Passou de Nivel",TAMANHO_FONTE*3))/2, ALTURA/2 - 50, TAMANHO_FONTE*3, WHITE);

}

void desenha_msg_checkpoint(){
    DrawText("Checkpoint...", BASE_X + (TAMANHO_CHECKPOINT / 2), ALTURA - (TAMANHO_CHECKPOINT * 1.625), TAMANHO_FONTE, WHITE);

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

    DrawText("SCORE:", x, y, TAMANHO_HUD, WHITE);
    x += MeasureText("SCORE: ", TAMANHO_HUD);

    sprintf(saida_pontos, "%d pontos", mapa->jogador.pontuacao);
    DrawText(saida_pontos, x, y, TAMANHO_HUD, DARKBLUE);
    x += MeasureText("2500 pontos", TAMANHO_HUD);

    x += 30;
    DrawText("VIDAS:", x, y, TAMANHO_HUD, WHITE);
    x += MeasureText("VIDAS: ", TAMANHO_HUD);

    sprintf(saida_vida, "%d", mapa->jogador.vidas);
    DrawText(saida_vida, x, y, TAMANHO_HUD, DARKBLUE);

    x += QUADRADO_LARGURA;
    DrawText("CHAVE:", x, y, TAMANHO_HUD, WHITE);
    x += MeasureText("CHAVE: ", TAMANHO_HUD);

    sprintf(saida_chave, "%d", mapa->chave);
    DrawText(saida_chave, x, y, TAMANHO_HUD, DARKBLUE);

    x += QUADRADO_LARGURA;
    DrawText("FASE:", x, y, TAMANHO_HUD, WHITE);
    x += MeasureText("FASE: ", TAMANHO_HUD);

    sprintf(saida_fase, "%d", mapa->nivel);
    DrawText(saida_fase, x, y, TAMANHO_HUD, DARKBLUE);


}

void desenha_nivel(Mapa *mapa, Texture2D imagens[]){
    // coloca na tela o score, vidas, fase e chave
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
                 if(mapa->mapa[i][j] == 'D'&& (mapa->bau != 1)&& (mapa->escada != 1) && (mapa->deletado == ' '))
                    DrawTexture(imagens[1], (0 + QUADRADO_LARGURA *j), (0 + QUADRADO_ALTURA * i), WHITE);
                if((mapa->mapa[i][j] == 'D') && (mapa->chave != 1) && (mapa->deletado == 'P'))
                    DrawTexture(imagens[1], (0 + QUADRADO_LARGURA *j), (0 + QUADRADO_ALTURA * i), WHITE);
                //Jogador na escada
                if((mapa->mapa[i][j] == 'D') && (mapa->escada == 1))
                    DrawTexture(imagens[2], (0 + QUADRADO_LARGURA *j), (0 + QUADRADO_ALTURA * i), WHITE);
                //Jogador na porta
                if((mapa->mapa[i][j] == 'D') && (mapa->porta != ' ') )
                    DrawTexture(imagens[3], (0 + QUADRADO_LARGURA *j), (0 + QUADRADO_ALTURA * i), WHITE);
                //Jogador no baú
                if((mapa->mapa[i][j] == 'D') && (mapa->bau == 1)&& (mapa->deletado != 'P'))
                    DrawTexture(imagens[4], (0 + QUADRADO_LARGURA *j), (0 + QUADRADO_ALTURA * i), WHITE);
                //Baú
                if(mapa->mapa[i][j] == 'C')
                    DrawTexture(imagens[5], (0 + QUADRADO_LARGURA *j), (0 + QUADRADO_ALTURA * i), WHITE);
                //Escada
                if(mapa->mapa[i][j] == 'H')
                    DrawTexture(imagens[6], (0 + QUADRADO_LARGURA *j), (0 + QUADRADO_ALTURA * i), WHITE);
                //Porta normal
                if((mapa->mapa[i][j] == '1') || (mapa->mapa[i][j] == '2') || (mapa->mapa[i][j] == '3') || (mapa->mapa[i][j] == '4'))
                    DrawTexture(imagens[7], (0 + QUADRADO_LARGURA *j), (0 + QUADRADO_ALTURA * i), WHITE);
                //Porta fase
                if((mapa->mapa[i][j] == 'P') && (mapa->chave == 1))
                    DrawTexture(imagens[8], (0 + QUADRADO_LARGURA *j), (0 + QUADRADO_ALTURA * i), WHITE);
                // jogador na porta de saída
                if((mapa->mapa[i][j] == 'D') && (mapa->deletado == 'P') && (mapa->chave == 1))
                    DrawTexture(imagens[10], (0 + QUADRADO_LARGURA *j), (0 + QUADRADO_ALTURA * i), WHITE);
                //parede do fundo
                if(mapa->mapa[i][j] == ' ')
                    DrawTexture(imagens[9], (0 + QUADRADO_LARGURA *j), (0 + QUADRADO_ALTURA * i), WHITE);

                }


        }
 }
