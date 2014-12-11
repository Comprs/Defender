#ifndef PLAYERPROJECTILE_H
#define PLAYERPROJECTILE_H

#include "entity.h"

namespace Defender
{
class PlayerProjectile : public Entity
{
public:
    PlayerProjectile(std::vector<std::shared_ptr<Entity>>* newEntities,
                     Defender::Room* newRoom,
                     std::shared_ptr<Defender::Texture> newTexture,
                     Vector2D startPosition, bool startOrientation);
};
}

#endif // PLAYERPROJECTILE_H
