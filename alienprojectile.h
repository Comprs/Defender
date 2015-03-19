#ifndef ALIENPROJECTILE_H
#define ALIENPROJECTILE_H

#include "entity.h"

namespace Defender
{
class AlienProjectile : public Entity
{
public:
    AlienProjectile(Room& room, std::shared_ptr<Texture> texture, Vector2D position, Vector2D velocity);

protected:
    void bound() override;
};
}

#endif // ALIENPROJECTILE_H
