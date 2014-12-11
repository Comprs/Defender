#include "playerprojectile.h"

Defender::PlayerProjectile::
    PlayerProjectile(std::vector<std::shared_ptr<Entity> > *newEntities,
                     Defender::Room *newRoom,
                     std::shared_ptr<Defender::Texture> newTexture,
                     Vector2D startPosition, bool startOrientation) :
  Defender::Entity(newEntities, newRoom, newTexture)
{
    position = startPosition;
    facingRight = startOrientation;
    lifeTime = 0.5;

    if (facingRight) { velocity = Vector2D(2000, 0); }
    else { velocity = Vector2D(-2000, 0); }
}
