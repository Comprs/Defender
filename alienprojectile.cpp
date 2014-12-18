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

void Defender::AlienProjectile::bound()
{
    // Wrap around horizontaly
    while (position.x() >= room.width)
    {
        position.x() -= room.width;
    }
    while (position.x() < 0)
    {
        position.x() += room.width;
    }

    // Kill if the projectile goes out of the room verticaly
    if (position.y() >= room.height)
    {
        kill();
    }
    else if (position.y() <= -getBoundingBox().h)
    {
        kill();
    }
}
