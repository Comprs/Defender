#include "playerprojectile.h"

#include "globals.h"

Defender::PlayerProjectile::
PlayerProjectile(std::vector<std::shared_ptr<Entity> >& newEntities,
                 Room& newRoom,
                 std::shared_ptr<Defender::Texture> newTexture,
                 Vector2D startPosition, bool startOrientation) :
  Defender::Entity(newEntities, newRoom, newTexture)
{
    position = startPosition;
    facingRight = startOrientation;
    lifeTime = 0.2;

    if (facingRight) { velocity = Vector2D(shotSpeed, 0); }
    else { velocity = Vector2D(-shotSpeed, 0); }
}
