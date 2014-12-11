#include "maingameroom.h"

#include "player.h"

Defender::MainGameRoom::MainGameRoom(Game *newGame) : Room(newGame)
{
    addEntity<Player>("player.png");
}

void Defender::MainGameRoom::draw()
{
    Texture target  = Texture(game->getRenderer(), width, height);
    target.setRenderTarget();
    SDL_RenderClear(game->getRenderer());

    Room::draw();

    SDL_SetRenderTarget(game->getRenderer(), nullptr);

    Renderer(target).commit();
}
