#ifndef TELAS_H
#define TELAS_H
/*
    Telas do jogos
    LOAD: Tela de carregamento inicial
    NOVO_JOGO: Tela de carregamento ao iniciar novo jogo ou carregar
    MENU: Menu do jogo
    PROXIMO: Tela de carregamento da proxima fase
    RANKING: Ranking de jogadores
    GAMEOVER: Tela de derrota(perder todas as vidas e morrer)
    ENDING: Tela de encerramento
    NJINGAME: Tela de escolha de iniciar um novo jogo no meio da partida
    RETORNAR_MENU: Tela de escolha para retornar ao menu
    CARREGAR: Tela que sinaliza o carregamento.
    ADDRANK: Tela para a inclusão do jogador no ranking.
*/
typedef enum GameScreen{
    LOAD = 0,
    NOVO_JOGO,
    MENU,
    CARREGAR,
    GAMEPLAY,
    PROXIMO,
    GAMEOVER,
    ENDING,
    RETORNAR_MENU,
    NJINGAME,
    ADDRANK
} GameScreen;
#endif // TELAS


