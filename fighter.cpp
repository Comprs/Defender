#include "fighter.h"

Defender::Fighter::Fighter(std::vector<std::shared_ptr<Entity>> &newEntities,
                           Defender::Room &newRoom,
                           std::shared_ptr<Defender::Texture> newTexture) :
    Alien(newEntities, newRoom, newTexture)
{
    // Always accelerate upwards
    acceleration = Vector2D(0, -240);

    // 50/50 chance of facing each direction
    if (std::bernoulli_distribution(0.5)(engine))
    {
        velocity = Vector2D(600, 0);
        facingRight = true;
    }
    else
    {
        velocity = Vector2D(-600, 0);
        facingRight = false;
    }
    diveDistribution = std::bernoulli_distribution(0.002);
    swapDistrubution = std::bernoulli_distribution(0.001);
}

void Defender::Fighter::update(const double time, std::shared_ptr<Entity> self)
{
    // If at the top, randomly dive
    if (position.y() == 0 && diveDistribution(engine))
    {
        velocity.y() = 450;
    }

    // Randomly switch directions
    if(swapDistrubution(engine))
    {
        velocity.x() = -velocity.x();
        facingRight = !facingRight;
    }
    Alien::update(time, self);
}

void Defender::Fighter::onKill()
{
    room.score += 1;
}
