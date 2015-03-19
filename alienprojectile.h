#ifndef ALIENPROJECTILE_H
#define ALIENPROJECTILE_H

#include "entity.h"

namespace Defender
{
class AlienProjectile : public Entity
{
public:
    AlienProjectile(Room& newRoom, std::shared_ptr<Texture> newTexture, Vector2D startPosition,
                    Vector2D startVelocity);

protected:
    void bound() override;
};
}

#endif // ALIENPROJECTILE_H
