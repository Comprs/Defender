#include "alienprojectile.h"

Defender::AlienProjectile::
AlienProjectile(std::vector<std::shared_ptr<Entity>>& newEntities,
                Defender::Room& newRoom,
                std::shared_ptr<Defender::Texture> newTexture,
                Vector2D startPosition, Vector2D startVelocity) :
    Entity(newEntities, newRoom, newTexture)
{
    lifeTime = 2;
    position = startPosition;
    velocity = startVelocity;
}

