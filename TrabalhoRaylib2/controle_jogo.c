#include <stdio.h>
#include "jogador.h"
#include "coordenadas.h"
#include "mapa.h"

void controla_jogo() {
    char mov;
    int pontos;
    Mapa mapa;
    mapa_carrega(&mapa);


    do {
        mapa_imprime(mapa);
        printf("\nInforme\n(c) para ir para cima\n(b) para ir para baixo\n(p) para adicionar pontos\n(-) para diminuir a vida ou \n(n) para ler o nome: \n(s) para voltar para o menu)");
        scanf(" %c", &mov);

        if (mov == 'c') {
            mapa_movimenta(&mapa, mov);
        }

        if (mov == 'b') {
            mapa_movimenta(&mapa, mov);
        }

        if (mov == 'e') {
            mapa_movimenta(&mapa, mov);
        }

        if (mov == 'd') {
            mapa_movimenta(&mapa, mov);
        }


        if (mov == 'p') {
            printf("\tQuantos pontos? ");
            scanf("%d", &pontos);
            jog_aumenta_pontuacao(&(mapa.jogador), pontos);
        }

        if (mov == '-')
            if(jog_diminui_vida(&(mapa.jogador)))

        if (mov == 'n'){
            jog_le_nome(&(mapa.jogador));
            jog_print_info(mapa.jogador);
        }

        printf("\n\n\n");
    } while (mov != 's');

}

