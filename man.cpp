#include "man.h"

#include "playerprojectile.h"

Defender::Man::Man(std::vector<std::shared_ptr<Entity>>& newEntities,
    Defender::Room& newRoom,
    std::shared_ptr<Defender::Texture> newTexture) :
    Entity(newEntities, newRoom, newTexture)
{
    position = Vector2D(distribution(engine), worldHeight - getBoundingBox().h);
}

void Defender::Man::interact(std::shared_ptr<Entity> &e)
{
    if (auto p = std::dynamic_pointer_cast<PlayerProjectile>(e))
    {
        //if (intersect(*p))
        if (p->intersect(*this))
        {
            p->kill();
            kill();
        }
    }
}

void Defender::Man::update(const double time, std::shared_ptr<Entity> self)
{
    Entity::update(time, self);
    if (abducted)
    {
        acceleration = Vector2D(0, 0);
    }
    else
    {
        acceleration = Vector2D(0, 15);
    }
}
