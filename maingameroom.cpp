#include "maingameroom.h"

#include <typeinfo>
#include "globals.h"
#include "player.h"

Defender::MainGameRoom::MainGameRoom(Game *newGame) :
    Room(newGame, Defender::worldWidth, Defender::windowHeight)
{
    addEntity<Player>("player.png");
}

void Defender::MainGameRoom::draw()
{
    Texture target  = Texture(game->getRenderer(), width, height);
    target.setRenderTarget();
    SDL_RenderClear(game->getRenderer());

    Renderer r = Renderer(*TextureRegistry::getTexture("background.png"));
    for (int i = 0; i < width;
         i += TextureRegistry::getTexture("background.png")->getRect().w)
    {
        r.addOffset(i, 0);
    }
    r();

    Room::draw();

    SDL_SetRenderTarget(game->getRenderer(), nullptr);

    Renderer(target).addOffset(width, 0).addOffset(-width, 0)
            .setPosition(-cameraPos).commit();
}

void Defender::MainGameRoom::updateEntity(const double time,
                                          std::shared_ptr<Entity> e)
{
    Room::updateEntity(time, e);
    if (typeid(*e) == typeid(Player))
    {
        cameraPos = e->getPosition();
    }
}
