#ifndef ALIEN_H
#define ALIEN_H

#include "entity.h"

namespace Defender
{
class Alien : public Entity
{
public:
    Alien(std::vector<std::shared_ptr<Entity>>& newEntities,
          Defender::Room& newRoom,
          std::shared_ptr<Defender::Texture> newTexture) :
        Entity(newEntities, newRoom, newTexture)
    {
        position = Vector2D(500, 0);
    }

protected:
    void interact(std::shared_ptr<Entity> &e) override;
};
}

#endif // ALIEN_H
