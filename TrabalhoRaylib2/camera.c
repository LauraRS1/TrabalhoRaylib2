#include "coordenadas.h"
#include "raylib.h"
#include "desenha.h"

/*
    camera_atualiza:
    Atualiza a câmera do jogador.
    @param Camera2D *camera: ponteiro para a câmera do jogador.
    @param Localizacao localizacao: a localização a ser apontada pela câmera do jogador.
*/
void camera_atualiza(Camera2D *camera, Localizacao localizacao){
    camera->target.x = 0 + localizacao.coluna * QUADRADO_LARGURA;
    camera->target.y = 0 + localizacao.linha * QUADRADO_ALTURA;
    camera->offset = (Vector2){ LARGURA/2.0f, ALTURA/2.0f };
}
