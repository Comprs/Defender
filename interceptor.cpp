#include "interceptor.h"

#include "player.h"
#include "alienprojectile.h"

Defender::Interceptor::Interceptor(Room &room, std::shared_ptr<Texture> texture) :
    Alien(room, texture)
{
    // Set the random distributions
    this->moveDistribution = pseudo_random_distribution(0.005);
    this->horizontalDistribution = std::uniform_real_distribution<>(0, worldWidth);
    this->verticalDistribution = std::uniform_real_distribution<>(0, worldHeight);

    // Set the target position to a random position in the world
    this->target = Vector2D(horizontalDistribution(engine), verticalDistribution(engine));
}

void Defender::Interceptor::interact(Entity& entity)
{
    entity.interact(*this);
}

// See Defender::Alien::interact(Player& player)
// This varies from it override as it has a larger projectile range and speed
void Defender::Interceptor::interact(Player& player)
{
    if (intersect(player))
    {
        player.kill();
        kill();
    }

    Vector2D vectorTo = getSmallestVectorTo(getMiddle(), player.getMiddle());
    if (vectorTo.magnitude() <= alienProjectileFireRange * 1.5 && shotDistribution(engine))
    {
        Vector2D relativeVelocity = vectorTo.normalised();
        Vector2D newVelocity = Vector2D(player.getVelocity().x(), 0) +
                (relativeVelocity * alienProjectileSpeed * 2);
        Vector2D newPosition = getMiddle() + (newVelocity.normalised() * 20);

        room.addEntity<AlienProjectile>("enemyShot.png", newPosition, newVelocity);
    }
}

void Defender::Interceptor::update(const double time)
{
    // On random chance
    if (moveDistribution(engine))
    {
        // Set a new targer
        target = Vector2D(horizontalDistribution(engine), verticalDistribution(engine));
    }

    // If far away from the target
    Vector2D displacementVector = getSmallestVectorTo(position, target);
    if (displacementVector.magnitude() > 10)
    {
        // Goto the target
        velocity = displacementVector.normalised() * 800;
    }
    else
    {
        // Stay still
        velocity = Vector2D();
    }
    Alien::update(time);
}

void Defender::Interceptor::onKill()
{
    // Increase the score on death
    room.incrementScore(1);
}
