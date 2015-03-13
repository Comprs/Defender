#include "room.h"

#include <algorithm>

Defender::Room::Room(Game& newGame, int newWidth, int newHeight) :
    width(newWidth), height(newHeight), game(newGame) {}

Defender::Room::Room(Game& newGame) :
    Defender::Room::Room(newGame, 512, 512) {}

void Defender::Room::update(const double time)
{
    // Update the entities
    for (std::shared_ptr<Entity> e : entities)
    {
        if (e == nullptr) { continue; }
        updateEntity(time, e);
    }

    // Remove dead entities
    auto newEnd = std::remove_if(entities.begin(), entities.end(),
                                 [](auto e){return e->isDead();});
    entities.erase(newEnd, entities.end());

    if (score > game.highScore) { game.highScore = score; }
}

void Defender::Room::updateEntity(const double time, std::shared_ptr<Entity> e)
{
    e->update(time, e);
}

void Defender::Room::draw()
{
    // Draw the entities
    for (std::shared_ptr<Entity> e : entities)
    {
        e->draw();
    }
}
