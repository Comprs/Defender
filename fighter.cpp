#include "fighter.h"

Defender::Fighter::Fighter(Defender::Room &newRoom, std::shared_ptr<Defender::Texture> newTexture) :
    Alien(newRoom, newTexture)
{
    // Always accelerate upwards
    acceleration = Vector2D(0, -240);

    // 50/50 chance of facing each direction
    if (std::bernoulli_distribution(0.5)(engine))
    {
        velocity = Vector2D(fighterSpeed, 0);
        facingRight = true;
    }
    else
    {
        velocity = Vector2D(-fighterSpeed, 0);
        facingRight = false;
    }
    diveDistribution = Defender::pseudo_random_distribution(0.002);
    swapDistrubution = Defender::pseudo_random_distribution(0.001);
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
    room.incrementScore(fighterScore);
    Alien::onKill();
}
