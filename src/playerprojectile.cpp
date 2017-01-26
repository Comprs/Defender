#include "playerprojectile.hpp"

#include "globals.hpp"

Defender::PlayerProjectile:: PlayerProjectile(Room& room,
                                              std::shared_ptr<Defender::Texture> texture,
                                              Vector2D position, bool orientation) :
    Entity(room, texture)
{
    this->position = position;
    this->facingRight = orientation;
    this->lifeTime = 0.2;

    // Set the facing orientation based on the velocity
    if (this->facingRight) { this->velocity = Vector2D(shotSpeed, 0); }
    else { this->velocity = Vector2D(-shotSpeed, 0); }
}

void Defender::PlayerProjectile::interact(Entity& entity)
{
    entity.interact(*this);
}

SDL_Rect Defender::PlayerProjectile::getBoundingBox() const
{
    SDL_Rect r = Entity::getBoundingBox();

    // Increase effective height
    r.y -= r.h * 2;
    r.h += r.h * 4;

    return r;
}
