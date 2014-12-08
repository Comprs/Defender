#include "room.h"

#include <algorithm>

Defender::Room::Room()
{
    addEntity<Defender::Entity>("alien1.png");
}

void Defender::Room::update(const double time)
{
    for (std::shared_ptr<Entity> e : entities)
    {
        e->update(time);
    }

    auto newEnd = std::remove_if(entities.begin(), entities.end(),
                                 [](auto e){return e->isDead();});

    entities.erase(newEnd, entities.end());
}

void Defender::Room::draw()
{
    for (std::shared_ptr<Entity> e : entities)
    {
        e->draw();
    }
}
