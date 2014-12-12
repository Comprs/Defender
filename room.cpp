#include "room.h"

#include <algorithm>

Defender::Room::Room(Game& newGame, int newWidth, int newHeight) :
    width(newWidth), height(newHeight), game(newGame) {}

Defender::Room::Room(Game& newGame) :
    Defender::Room::Room(newGame, 512, 512) {}

void Defender::Room::update(const double time)
{
    for (std::shared_ptr<Entity> e : entities)
    {
        if (e == nullptr) { continue; }
        updateEntity(time, e);
    }

    auto newEnd = std::remove_if(entities.begin(), entities.end(),
                                 [](auto e){return e->isDead();});

    entities.erase(newEnd, entities.end());
}

void Defender::Room::updateEntity(const double time, std::shared_ptr<Entity> e)
{
    e->update(time, e);
}

void Defender::Room::draw()
{
    for (std::shared_ptr<Entity> e : entities)
    {
        e->draw();
    }
}
