#ifndef PLAYERPROJECTILE_H
#define PLAYERPROJECTILE_H

#include "entity.h"

namespace Defender
{
class PlayerProjectile : public Entity
{
public:
    PlayerProjectile(Room& room, std::shared_ptr<Texture> texture, Vector2D position, bool orientation);

    SDL_Rect getBoundingBox() const override;
};
}

#endif // PLAYERPROJECTILE_H
