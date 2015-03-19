#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <queue>
#include "entity.h"
#include "textureregistry.h"
#include "game.h"

namespace Defender
{
class Game;
class Entity;
class Room
{
    friend class Entity;
public:
    Room(Game& game);
    Room(Game& game, int width, int height);

    ~Room();

    const int width;
    const int height;

    virtual void update(const double time);
    virtual void draw();
    virtual void incrementScore(int delta);
    int getScore() const;

    template<typename T, typename... Args>
    void addEntity(const std::string& textureName, Args... args)
    {
        entityQueue.push(std::make_shared<T>(*this,
                                             TextureRegistry::getTexture(textureName), args...));
    }

protected:
    int score = 0;
    Game& game;
    std::vector<std::shared_ptr<Entity>> entities;
    std::queue<std::shared_ptr<Entity>> entityQueue;

    virtual void updateEntity(const double time, std::shared_ptr<Entity> e);
};
}

#endif // ROOM_H
