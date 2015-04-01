#include "man.h"

#include "playerprojectile.h"
#include "particle.h"

std::uniform_real_distribution<double> Defender::Man::positionDistribution =
        std::uniform_real_distribution<double>(0.0, Defender::worldWidth);

Defender::Man::Man(Defender::Room& room, std::shared_ptr<Defender::Texture> texture) :
    Entity(room, texture)
{
    // Set the position to be a random horizontal position and at the bottom of the world
    this->position = Vector2D(this->positionDistribution(engine), worldHeight -
                              this->getBoundingBox().h);

    // Set the turn distribution
    this->turnDistribution = pseudo_random_distribution(0.01);
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

    if (isAbducted())
    {
        // If the man is abducted, it should not move
        acceleration = Vector2D(0, 0);
        velocity = Vector2D();
    }
    else
    {
        // Accelerate downwards for gravity
        acceleration = Vector2D(0, manFallSpeed);
        // If at the bottom of the screen
        if (position.y() >= worldHeight - getBoundingBox().h)
        {
            // Random roll
            if (turnDistribution(engine))
            {
                // Set a new horizontal velocity
                std::uniform_int_distribution<> distribution(-6, 6);
                velocity = Vector2D(50 * distribution(engine), 0);
            }
            // Random roll
            if (turnDistribution(engine))
            {
                // Set the vertical velocity
                velocity.y() = -100;
            }
        }
    }
}

bool Defender::Man::isAbducted() const
{
    // Return whether an abductor is attached
    return abductor != nullptr;
}

void Defender::Man::onKill()
{
    // Change the score
    room.incrementScore(manScoreDeduction);

    // Create the particles
    std::uniform_real_distribution<double> particleDistribution(-15, 15);
    for (int i = 0; i < manParticleCount; ++i)
    {
        room.addEntity<Particle>("blood.png", getMiddle(), 5,
                                 Vector2D(particleDistribution(engine),
                                          particleDistribution(engine) * 2) +
                                 velocity + Vector2D(0, -50),
                                 Vector2D(0, 240));
    }

    // Create the replacment man
    room.addEntity<Man>("man.png");

    // Detach itself from the abductor
    if (abductor != nullptr)
    {
        abductor->detachMan();
    }

    Entity::onKill();
}
