#ifndef PARTICLE
#define PARTICLE

#include "entity.h"

namespace Defender
{
class Particle : public Entity
{
public:
    Particle(Room& newRoom, std::shared_ptr<Texture> newTexture, Vector2D newPosition,
             int newLifeTime = -1, Vector2D newVelocity = Vector2D(),
             Vector2D newAcceleration = Vector2D());

protected:
    void bound() override;
};
}

#endif // PARTICLE
