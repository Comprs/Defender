#include "room.hpp"

#include <algorithm>

Defender::Room::Room(Game& game, int width, int height) : width(width), height(height),
    game(game) {}

Defender::Room::Room(Game& game) : Defender::Room::Room(game, 512, 512) {}

Defender::Room::~Room()
{
    if (score > game.highScore) { game.highScore = score; }
}

void Defender::Room::update(const double time)
{
    // Update the entities
    for (std::shared_ptr<Entity> entity : entities)
    {
        entity->update(time);
    }

    for (std::shared_ptr<Entity> entity : entities)
    {
        entity->afterInteraction();
    }

    // Remove dead entities
    auto newEnd = std::remove_if(entities.begin(), entities.end(),
                                 [](auto e){return e->isDead();});
    entities.erase(newEnd, entities.end());

    // Add new entities
    while (entityQueue.size() > 0)
    {
        entities.push_back(std::move(entityQueue.front()));
        entityQueue.pop();
    }
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
