#ifndef ALIENPROJECTILE_H
#define ALIENPROJECTILE_H

#include "entity.h"

namespace Defender
{
class AlienProjectile : public Entity
{
public:
    AlienProjectile(std::vector<std::shared_ptr<Entity>>& newEntities,
                    Defender::Room& newRoom,
                    std::shared_ptr<Defender::Texture> newTexture,
                    Vector2D startPosition, Vector2D startVelocity);
};
}

#endif // ALIENPROJECTILE_H
