#include "alienprojectile.h"

Defender::AlienProjectile:: AlienProjectile(Defender::Room& room,
                                            std::shared_ptr<Defender::Texture> texture,
                                            Vector2D position, Vector2D velocity) :
    Entity(room, texture)
{
    this->position = position;
    this->velocity = velocity;
    this->lifeTime = 2;
}

void Defender::AlienProjectile::interact(Entity &entity)
{
    entity.interact(*this);
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

void Defender::AlienProjectile::interactWithBomb()
{
    kill();
}
