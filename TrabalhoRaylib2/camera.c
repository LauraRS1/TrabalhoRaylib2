#include "coordenadas.h"
#include "raylib.h"
#include "desenha.h"
void camera_atualiza(Camera2D *camera, Localizacao localizacao){
    camera->target.x = 0 + localizacao.coluna * QUADRADO_LARGURA;
    camera->target.y = 0 + localizacao.linha * QUADRADO_ALTURA;
    camera->offset = (Vector2){ LARGURA/2.0f, ALTURA/2.0f };
}
