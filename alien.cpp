#include "alien.h"

#include "player.h"
#include "playerprojectile.h"
#include "alienprojectile.h"
#include "particle.h"
#include "maingameroom.h"
#include "defenderutils.h"

Defender::Alien::Alien(Room& room, std::shared_ptr<Texture> texture) : Entity(room, texture)
{
    double playerPosition = static_cast<MainGameRoom&>(this->room).getPlayerPos().x();
    std::normal_distribution<> positionDistribution(playerPosition + worldWidth / 2, worldWidth / 5);
    this->position = Vector2D(positionDistribution(engine), 0);
    this->shotDistribution = pseudo_random_distribution(0.02);
}

void Defender::Alien::interact(PlayerProjectile &playerProjectile)
{
    if (intersect(playerProjectile))
    {
        playerProjectile.kill();
        kill();
    }
}

void Defender::Alien::interact(Player &player)
{
    if (intersect(player))
    {
        player.kill();
        kill();
    }

    Vector2D vectorTo = getSmallestVectorTo(getMiddle(), player.getMiddle());
    // If the player is within 512 pixels
    if (vectorTo.magnitude() <= 512 && shotDistribution(engine))
    {
        Vector2D relativeVelocity = vectorTo.normalised();
        Vector2D newVelocity = Vector2D(player.getVelocity().x(), 0) +
                (relativeVelocity * alienProjectileFireRange);
        Vector2D newPosition = getMiddle() + (relativeVelocity * alienProjectileSpeed);

        room.addEntity<AlienProjectile>("enemyShot.png", newPosition, newVelocity);
    }
}

void Defender::Alien::onKill()
{
    std::uniform_real_distribution<double> particleDistribution(-120, 120);
    for (int i = 0; i < 10; ++i)
    {
        room.addEntity<Particle>("shard.png", getMiddle(), 5,
                                 Vector2D(particleDistribution(engine),
                                          -120 + particleDistribution(engine)) + velocity,
                                 Vector2D(0, 240));
    }
}

void Defender::Alien::interactWithBomb()
{
    kill();
}
