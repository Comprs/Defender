#include "particle.h"

Defender::Particle::Particle(std::vector<std::shared_ptr<Entity>> &newEntities,
                             Defender::Room &newRoom,
                             std::shared_ptr<Defender::Texture> newTexture,
                             Vector2D newPosition, int newLifeTime,
                             Vector2D newVelocity, Vector2D newAcceleration) :
    Entity(newEntities, newRoom, newTexture)
{
    lifeTime = newLifeTime;
    position = newPosition;
    velocity = newVelocity;
    acceleration = newAcceleration;
}

void Defender::Particle::bound()
{
    // Do not bound to the room;
    return;
}
