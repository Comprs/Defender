#include "man.h"

#include "playerprojectile.h"
#include "particle.h"

std::uniform_real_distribution<double> Defender::Man::positionDistribution =
        std::uniform_real_distribution<double>(0.0, Defender::worldWidth);

Defender::Man::Man(Defender::Room& room, std::shared_ptr<Defender::Texture> texture) :
    Entity(room, texture)
{
    this->position = Vector2D(this->positionDistribution(this->engine), worldHeight -
                              this->getBoundingBox().h);
}

void Defender::Man::interact(Entity& entity)
{
    entity.interact(*this);
}

void Defender::Man::interact(PlayerProjectile& playerProjectile)
{
    // Kill if it has collieded with a playerprojectile
    if (playerProjectile.intersect(*this))
    {
        playerProjectile.kill();
        kill();
    }
}

void Defender::Man::update(const double time)
{
    Entity::update(time);

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
    return abductor != nullptr;
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
    room.addEntity<Man>("man.png");
    if (abductor != nullptr)
    {
        abductor->abducting = nullptr;
        abductor = nullptr;
    }
    Entity::onKill();
}
