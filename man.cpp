#include "man.h"

#include "playerprojectile.h"
#include "particle.h"

std::uniform_real_distribution<double> Defender::Man::positionDistribution =
        std::uniform_real_distribution<double>(0.0, Defender::worldWidth);

Defender::Man::Man(Defender::Room& newRoom, std::shared_ptr<Defender::Texture> newTexture) :
    Entity(newRoom, newTexture)
{
    position = Vector2D(positionDistribution(engine), worldHeight - getBoundingBox().h);
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
        acceleration = Vector2D(0, manFallSpeed);
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
    room.incrementScore(manScoreDeduction);
    std::uniform_real_distribution<double> particleDistribution(-7, 7);
    for (int i = 0; i < manParticleCount; ++i)
    {
        room.addEntity<Particle>("blood.png", getMiddle(), 5,
                                 Vector2D(particleDistribution(engine),
                                          particleDistribution(engine) * 2) +
                                 velocity,
                                 Vector2D(0, 240));
    }
    Entity::onKill();
}
