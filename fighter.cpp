#include "fighter.h"

Defender::Fighter::Fighter(Defender::Room &room,
                           std::shared_ptr<Defender::Texture> texture) :
    Alien(room, texture)
{
    // Always accelerate upwards
    this->acceleration = Vector2D(0, -240);

    // 50/50 chance of facing each direction
    if (std::bernoulli_distribution(0.5)(engine))
    {
        this->velocity = Vector2D(fighterSpeed, 0);
        this->facingRight = true;
    }
    else
    {
        this->velocity = Vector2D(-fighterSpeed, 0);
        this->facingRight = false;
    }
    this->diveDistribution = Defender::pseudo_random_distribution(0.002);
    this->swapDistrubution = Defender::pseudo_random_distribution(0.001);
}

void Defender::Fighter::interact(Entity &entity)
{
    entity.interact(*this);
}

void Defender::Fighter::update(const double time)
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
    Alien::update(time);
}

void Defender::Fighter::onKill()
{
    room.incrementScore(fighterScore);
    Alien::onKill();
}
