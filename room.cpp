#include "room.h"

#include <algorithm>

Defender::Room::Room(Game& newGame, int newWidth, int newHeight) :
    width(newWidth), height(newHeight), game(newGame) {}

Defender::Room::Room(Game& newGame) :
    Defender::Room::Room(newGame, 512, 512) {}

Defender::Room::~Room()
{
    if (score > game.highScore) { game.highScore = score; }
}

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

    // Add new entities
    while (entityQueue.size() > 0)
    {
        entities.push_back(entityQueue.front());
        entityQueue.pop();
    }
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

void Defender::Room::incrementScore(int delta)
{
    score += delta;
}

int Defender::Room::getScore() const
{
    return score;
}
