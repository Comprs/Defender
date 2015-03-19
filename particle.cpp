#include "particle.h"

Defender::Particle::Particle(Defender::Room &newRoom, std::shared_ptr<Defender::Texture> newTexture,
                             Vector2D newPosition, int newLifeTime, Vector2D newVelocity,
                             Vector2D newAcceleration) :
    Entity(newRoom, newTexture)
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
