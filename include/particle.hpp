#ifndef PARTICLE_H
#define PARTICLE_H

#include "entity.hpp"

namespace Defender
{
class Particle : public Entity
{
public:
    Particle(Room& room, std::shared_ptr<Texture> texture, Vector2D position,
             double lifeTime = -1, Vector2D velocity = Vector2D(),
             Vector2D acceleration = Vector2D());

    void interact(Entity& entity) override;
    void interactAll() override;

protected:
    void boundY() override;
};
}

#endif // PARTICLE_H
