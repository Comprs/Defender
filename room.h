#ifndef ROOM_H
#define ROOM_H

#include <string>
#include "entity.h"
#include "textureregistry.h"
#include "game.h"

namespace Defender
{
class Game;
class Entity;
class Room
{
public:
    Room(Game& newGame);
    Room(Game& newGame, int newWidth, int newHeight);

    const int width;
    const int height;

    virtual void update(const double time);
    virtual void draw();

    template<typename T, typename... Args>
    void addEntity(const std::string& textureName, Args... args)
    {
        entities.push_back(std::make_shared<T>
                           (entities, *this,
                            TextureRegistry::getTexture(textureName),
                            args...));
    }

protected:
    Game& game;
    std::vector<std::shared_ptr<Entity>> entities;

    virtual void updateEntity(const double time, std::shared_ptr<Entity> e);
};
}

#endif // ROOM_H
