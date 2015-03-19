#ifndef PLAYERPROJECTILE_H
#define PLAYERPROJECTILE_H

#include "entity.h"

namespace Defender
{
class PlayerProjectile : public Entity
{
public:
    PlayerProjectile(Room& newRoom, std::shared_ptr<Texture> newTexture, Vector2D startPosition,
                     bool startOrientation);

    SDL_Rect getBoundingBox() const override;
};
}

#endif // PLAYERPROJECTILE_H
