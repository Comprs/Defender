#include "alien.h"

#include "player.h"
#include "playerprojectile.h"
#include "alienprojectile.h"
#include "particle.h"
#include "maingameroom.h"
#include "defenderutils.h"

Defender::Alien::Alien(std::vector<std::shared_ptr<Entity>>& newEntities, Room& newRoom,
                       std::shared_ptr<Texture> newTexture) :
    Entity(newEntities, newRoom, newTexture)
{
    std::normal_distribution<> positionDistribution(static_cast<MainGameRoom&>(room).getPlayerPos().x() + worldWidth / 2,
                                                    worldWidth / 5);
    position = Vector2D(positionDistribution(engine), 0);
    shotDistribution = pseudo_random_distribution(0.02);
}

void Defender::Alien::interact(std::shared_ptr<Entity> &e)
{
    // Check for collisions with the player projectile
    if (auto p = std::dynamic_pointer_cast<PlayerProjectile>(e))
    {
        if (intersect(*p))
        {
            p->kill();
            kill();
        }
    }
    // Check for collisions with the player
    if (auto p = std::dynamic_pointer_cast<Player>(e))
    {
        if (intersect(*p))
        {
            p->kill();
            kill();
        }

        Vector2D vectorTo = getSmallestVectorTo(getMiddle(), p->getMiddle());
        // If the player is within 512 pixels
        if (vectorTo.magnitude() <= 512 && shotDistribution(engine))
        {
            Vector2D relativeVelocity = vectorTo.normalised();
            Vector2D newVelocity = Vector2D(p->getVelocity().x(), 0) +
                    (relativeVelocity * alienProjectileFireRange);
            Vector2D newPosition = getMiddle() + (relativeVelocity * alienProjectileSpeed);

            room.addEntity<AlienProjectile>("enemyShot.png", newPosition, newVelocity);
        }
    }
}

void Defender::Alien::onKill()
{
    std::uniform_real_distribution<double> particleDistribution(-120, 120);
    for (int i = 0; i < 10; ++i)
    {
        room.addEntity<Particle>("shard.png", getMiddle(), 5,
                                 Vector2D(particleDistribution(engine), -120 + particleDistribution(engine)) + velocity,
                                 Vector2D(0, 240));
    }
}
