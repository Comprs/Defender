#include "alien.h"

#include "player.h"
#include "playerprojectile.h"
#include "alienprojectile.h"
#include "particle.h"
#include "maingameroom.h"
#include "defenderutils.h"

Defender::Alien::Alien(Room& room, std::shared_ptr<Texture> texture) :
    Entity(room, texture)
{
    // Get the horizontal position of the player
    double playerPosition = static_cast<MainGameRoom&>(this->room).getPlayerPos().x();
    // Set up a normal distribution so that the initial position is least likely to spawn
    // near the player
    std::normal_distribution<> positionDistribution(playerPosition + worldWidth / 2,
                                                    worldWidth / 5);
    // Set the intial position so that the alien spawns at the top of the screen and with
    // the conditions the previous statment was to address
    this->position = Vector2D(positionDistribution(engine), 0);

    // Set up the distribution used to randomly shoot
    this->shotDistribution = pseudo_random_distribution(0.02);
}

void Defender::Alien::interact(PlayerProjectile& playerProjectile)
{
    // If the alien has collided with a player's projectile
    if (intersect(playerProjectile))
    {
        // Kill them both
        playerProjectile.kill();
        kill();
    }
}

void Defender::Alien::interact(Player& player)
{
    // If the alien has collied with a player
    if (intersect(player))
    {
        // Kill them both
        player.kill();
        kill();
    }

    Vector2D vectorTo = getSmallestVectorTo(getMiddle(), player.getMiddle());
    // If the player is within range
    if (vectorTo.magnitude() <= alienProjectileFireRange && shotDistribution(engine))
    {
        // Set the velocity of the new projectile to be going directly towards the player
        // at a predetermained speed plus the current velocity of the player
        Vector2D newVelocity = Vector2D(player.getVelocity().x(), 0) +
                (vectorTo.normalised() * alienProjectileSpeed);

        // Set the position such that the projectile appears to have originated from the
        // side in the direction it will travel
        Vector2D newPosition = getMiddle() + (newVelocity.normalised() * 20);

        // Add the projectile using the previously calculated values
        room.addEntity<AlienProjectile>("enemyShot.png", newPosition, newVelocity);
    }
}

void Defender::Alien::onKill()
{
    // Create the particals
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
