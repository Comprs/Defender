#include "alien.h"

#include "player.h"
#include "playerprojectile.h"
#include "alienprojectile.h"

Defender::Alien::Alien(std::vector<std::shared_ptr<Entity>>& newEntities,
                       Defender::Room& newRoom,
                       std::shared_ptr<Defender::Texture> newTexture) :
    Entity(newEntities, newRoom, newTexture)
{
    position = Vector2D(distribution(engine), 0);
    shotDistribution = std::bernoulli_distribution(0.02);
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

        // If the player is withing 512 pixels
        if ((p->getPosition() - getPosition()).magnitude() <= 512 &&
                shotDistribution(engine))
        {
            Vector2D relativeVelocity = (p->getMiddle() - getMiddle())
                    .normalised();

            Vector2D newVelocity = p->getVelocity() + (relativeVelocity * 500);
            Vector2D newPosition = getMiddle() + (relativeVelocity * 16);

            room.addEntity<AlienProjectile>("enemyShot.png", newPosition, newVelocity);
        }
    }
}
