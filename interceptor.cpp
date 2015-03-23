#include "interceptor.h"

#include "player.h"
#include "alienprojectile.h"

Defender::Interceptor::Interceptor(Room &room, std::shared_ptr<Texture> texture) :
    Alien(room, texture)
{
    this->moveDistribution = pseudo_random_distribution(0.005);
    this->horizontalDistribution = std::uniform_real_distribution<>(0, worldWidth);
    this->verticalDistribution = std::uniform_real_distribution<>(0, worldHeight);
    this->target = Vector2D(horizontalDistribution(engine), verticalDistribution(engine));
}

void Defender::Interceptor::interact(Entity& entity)
{
    entity.interact(*this);
}

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
    if (moveDistribution(engine))
    {
        target = Vector2D(horizontalDistribution(engine), verticalDistribution(engine));
    }
    Vector2D displacementVector = getSmallestVectorTo(position, target);
    if (displacementVector.magnitude() > 10)
    {
        velocity = displacementVector.normalised() * 800;
    }
    else
    {
        velocity = Vector2D();
    }
    Alien::update(time);
}

void Defender::Interceptor::onKill()
{
    room.incrementScore(1);
}
