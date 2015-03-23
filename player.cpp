#include "player.h"

#include "globals.h"
#include "inputmanager.h"
#include "playerprojectile.h"
#include "alienprojectile.h"
#include "particle.h"
#include "maingameroom.h"

Defender::Player::Player(Room& room, std::shared_ptr<Texture> texture) : Entity(room, texture) {}

void Defender::Player::update(const double time)
{
    Entity::update(time);

    double leftXAxis =
            Defender::GameControllerManager::getAxis(SDL_CONTROLLER_AXIS_LEFTX);
    double leftYAxis =
            Defender::GameControllerManager::getAxis(SDL_CONTROLLER_AXIS_LEFTY);
    double rightXAxis =
            Defender::GameControllerManager::getAxis(SDL_CONTROLLER_AXIS_RIGHTX);

    // If D is down and A is not, accelerate to the right
    if (Defender::KeyboardManager::isDown(SDL_SCANCODE_D) &&
            !Defender::KeyboardManager::isDown(SDL_SCANCODE_A))
    {
        // If acceleration will be opposite to the current velocity
        // Provide a larger acceleration
        if (velocity.x() < 0)
        {
            acceleration.x() = resistiveAcceleration;
        }
        // Provide a normal acceleration
        else
        {
            acceleration.x() = normalAcceleration;
        }
        facingRight = true;

    }
    // If A is down and D is not, accelerate to the left
    else if (Defender::KeyboardManager::isDown(SDL_SCANCODE_A) &&
             !Defender::KeyboardManager::isDown(SDL_SCANCODE_D))
    {
        if (velocity.x() > 0)
        {
            acceleration.x() = -resistiveAcceleration;
        }
        else
        {
            acceleration.x() = -normalAcceleration;
        }
        facingRight = false;
    }
    // Perform acceleration based on game controller input
    else if (leftXAxis != 0)
    {
        if (leftXAxis > 0)
        {
            facingRight = true;
            if (velocity.x() < 0)
            {
                acceleration.x() = resistiveAcceleration * leftXAxis;
            }
            else
            {
                acceleration.x() = normalAcceleration * leftXAxis;
            }
        }
        else if (leftXAxis < 0)
        {
            facingRight = false;
            if (velocity.x() > 0)
            {
                acceleration.x() = resistiveAcceleration * leftXAxis;
            }
            else
            {
                acceleration.x() = normalAcceleration * leftXAxis;
            }
        }
    }
    // Else perfom slow down
    else
    {
        // Slow down by accelerating oppositely to movement
        if (velocity.x() > 1)
        {
            acceleration.x() = -passiveSlowdown;
        }
        else if (velocity.x() < 1)
        {
            acceleration.x() = passiveSlowdown;
        }
        // If the velocity is low, make it zero
        else
        {
            velocity.x() = 0;
        }
    }

    if (rightXAxis != 0)
    {
        facingRight = rightXAxis > 0;
    }

    // Keep the horizontal velocity within certain bounds
    if (std::abs(velocity.x()) > terminalVelocity)
    {
        if (velocity.x() < 0)
        {
            velocity.x() = -terminalVelocity;
        }
        else
        {
            velocity.x() = terminalVelocity;
        }
    }

    // If W is pressed and S is not, move up the screen
    if (Defender::KeyboardManager::isDown(SDL_SCANCODE_W) &&
            !Defender::KeyboardManager::isDown(SDL_SCANCODE_S))
    {
        velocity.y() = -verticalSpeed;
    }
    // If S is pressed and W is not, move down the screen
    else if (Defender::KeyboardManager::isDown(SDL_SCANCODE_S) &&
             !Defender::KeyboardManager::isDown(SDL_SCANCODE_W))
    {
        velocity.y() = verticalSpeed;
    }
    else if (leftYAxis != 0)
    {
        velocity.y() = verticalSpeed * leftYAxis;
    }
    // Else stay still
    else
    {
        velocity.y() = 0;
    }

    // Fire a projectile if the return key was pressed
    if (ifOneWasPressed(SDL_SCANCODE_RETURN, SDL_CONTROLLER_BUTTON_A,
                        SDL_CONTROLLER_BUTTON_RIGHTSHOULDER))
    {
        Vector2D startPosition = position;
        // Set the x position based on direction of the player so that the
        // projectile won't appear to collide with the  player
        if (facingRight)
        {
            startPosition.x() += texture->getRect().w;
        }
        else
        {
            startPosition.x() -= TextureRegistry::getTexture("shot.png")->
                    getRect().w;
        }

        // Set the y position so that the projectile is centred
        startPosition.y() += (texture->getRect().h -
                TextureRegistry::getTexture("shot.png")->getRect().h) / 2;

        // Add the entity to the room
        room.addEntity<PlayerProjectile>("shot.png", startPosition, facingRight);
    }

    if (MainGameRoom* mainGameRoom = dynamic_cast<MainGameRoom*>(&room))
    {
        mainGameRoom->playerAlive = true;
        mainGameRoom->playerPos = position;

        mainGameRoom->cameraPos.x() = position.x() - windowWidth / 2 +
                texture->getRect().w / 2;

        mainGameRoom->radarPos.x() = position.x() / worldWidth * windowWidth - radarWidth / 2;
    }
}

void Defender::Player::interact(Entity& entity)
{
    entity.interact(*this);
}

void Defender::Player::interact(AlienProjectile& alienProjectile)
{
    if (intersect(alienProjectile))
    {
        alienProjectile.kill();
        kill();
    }
}

void Defender::Player::onKill()
{
    std::uniform_real_distribution<double> particleDistribution(-480, 480);
    for (int i = 0; i < playerParticleCount; ++i)
    {
        room.addEntity<Particle>("playerShard.png", getMiddle(), 30,
                                 Vector2D(particleDistribution(engine),
                                          -120 + particleDistribution(engine)) +
                                 velocity / 4,
                                 Vector2D(0, 240));
    }
    if (MainGameRoom* mainGameRoom = dynamic_cast<MainGameRoom*>(&room))
    {
        mainGameRoom->playerAlive = false;
    }
    Entity::onKill();
}
