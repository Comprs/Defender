#include "player.h"

#include "keyboardmanager.h"
#include "playerprojectile.h"

void Defender::Player::update(const double time, std::shared_ptr<Entity> self)
{
    Entity::update(time, self);

    // If D is down and A is not, accelerate to the right
    if (Defender::KeyboardManager::isDown(SDL_SCANCODE_D) &&
            !Defender::KeyboardManager::isDown(SDL_SCANCODE_A))
    {
        // If acceleration will be opposite to the current velocity
        // Provide a larger acceleration
        if (velocity.x() < 0)
        {
            acceleration.x() = 1500;
        }
        // Provide a normal acceleration
        else
        {
            acceleration.x() = 500;
        }
        facingRight = true;

    }
    // If A is down and D is not, accelerate to the left
    else if (Defender::KeyboardManager::isDown(SDL_SCANCODE_A) &&
             !Defender::KeyboardManager::isDown(SDL_SCANCODE_D))
    {
        if (velocity.x() > 0)
        {
            acceleration.x() = -1500;
        }
        else
        {
            acceleration.x() = -500;
        }
        facingRight = false;
    }
    // Else perfom slow down
    else
    {
        // Slow down by accelerating oppositely to movement
        if (velocity.x() > 1)
        {
            acceleration.x() = -100;
        }
        else if (velocity.x() < 1)
        {
            acceleration.x() = 100;
        }
        // If the velocity is low, make it zero
        else
        {
            velocity.x() = 0;
        }
    }

    // If W is pressed and S is not, move up the screen
    if (Defender::KeyboardManager::isDown(SDL_SCANCODE_W) &&
            !Defender::KeyboardManager::isDown(SDL_SCANCODE_S))
    {
        velocity.y() = -500;
    }
    // If S is pressed and W is not, move down the screen
    else if (Defender::KeyboardManager::isDown(SDL_SCANCODE_S) &&
             !Defender::KeyboardManager::isDown(SDL_SCANCODE_W))
    {
        velocity.y() = 500;
    }
    // Else stay still
    else
    {
        velocity.y() = 0;
    }

    if (KeyboardManager::wasPressed(SDL_SCANCODE_RETURN))
    {
        Vector2D startPosition = position;
        if (facingRight)
        {
            startPosition.x() += texture->getRect().w;
        }
        else
        {
            startPosition.x() -= TextureRegistry::getTexture("shot.png")->
                    getRect().w;
        }

        startPosition.y() += (texture->getRect().h -
                TextureRegistry::getTexture("shot.png")->getRect().h) / 2;

        room->addEntity<PlayerProjectile>("shot.png", startPosition,
                                          facingRight);
    }
}
