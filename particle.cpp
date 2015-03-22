#include "particle.h"

Defender::Particle::Particle(Defender::Room& room, std::shared_ptr<Defender::Texture> texture,
                             Vector2D position, int lifeTime, Vector2D velocity,
                             Vector2D acceleration) : Entity(room, texture)
{
    this->position = position;
    this->velocity = velocity;
    this->acceleration = acceleration;
    this->lifeTime = lifeTime;
}

void Defender::Particle::interact(Entity& entity)
{
    entity.interact(*this);
}

void Defender::Particle::interactAll() {}

void Defender::Particle::bound()
{
    // Do not bound to the room;
    return;
}
