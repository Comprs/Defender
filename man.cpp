#include "man.h"

#include "playerprojectile.h"
#include "particle.h"

Defender::Man::Man(std::vector<std::shared_ptr<Entity>>& newEntities,
    Defender::Room& newRoom,
    std::shared_ptr<Defender::Texture> newTexture) :
    Entity(newEntities, newRoom, newTexture)
{
    position = Vector2D(distribution(engine), worldHeight - getBoundingBox().h);
}

void Defender::Man::interact(std::shared_ptr<Entity>& e)
{
    // Kill if it has collieded with a playerprojectile
    if (auto p = std::dynamic_pointer_cast<PlayerProjectile>(e))
    {
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

    // If the man is abducted, it should not fall
    if (isAbducted())
    {
        acceleration = Vector2D(0, 0);
    }
    else
    {
        acceleration = Vector2D(0, 15);
    }
}

bool Defender::Man::isAbducted() const
{
    // The man is considered abducted if the weak pointer to its abductor has
    // expired
    return !abductor.expired();
}

void Defender::Man::abduct(std::weak_ptr<Entity> a)
{
    // Set the weak pointer to its abductor to the pointer passed
    abductor = a;
}

void Defender::Man::drop()
{
    // Null the weak pointer to its abductor. This means that it is no longer
    // abducted
    abductor = std::weak_ptr<Entity>();
}

void Defender::Man::onKill()
{
    room.score -= 5;
    std::uniform_real_distribution<double> particleDistribution(-15, 15);
    for (int i = 0; i < 50; ++i)
    {
        room.addEntity<Particle>("blood.png", getMiddle(), 5,
                                 Vector2D(particleDistribution(engine),
                                          -60 + particleDistribution(engine)) +
                                 velocity,
                                 Vector2D(0, 240));
    }
    Entity::onKill();
}
