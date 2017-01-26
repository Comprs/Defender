#ifndef ALIENPROJECTILE_H
#define ALIENPROJECTILE_H

#include "entity.hpp"

namespace Defender
{
class AlienProjectile : public Entity
{
public:
    AlienProjectile(Room& room, std::shared_ptr<Texture> texture, Vector2D position,
                    Vector2D velocity);
    void interact(Entity& entity) override;
    void interactWithBomb() override;

protected:
    void boundY() override;
};
}

#endif // ALIENPROJECTILE_H
