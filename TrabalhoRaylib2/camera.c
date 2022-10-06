#include "coordenadas.h"
#include "raylib.h"
#include "desenha.h"

/*
    camera_atualiza:
    Atualiza a c�mera do jogador.
    @param Camera2D *camera: ponteiro para a c�mera do jogador.
    @param Localizacao localizacao: a localiza��o a ser apontada pela c�mera do jogador.
*/
void camera_atualiza(Camera2D *camera, Localizacao localizacao){
    camera->target.x = 0 + localizacao.coluna * QUADRADO_LARGURA;
    camera->target.y = 0 + localizacao.linha * QUADRADO_ALTURA;
    camera->offset = (Vector2){ LARGURA/2.0f, ALTURA/2.0f };
}
