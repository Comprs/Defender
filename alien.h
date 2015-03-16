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
          std::shared_ptr<Defender::Texture> newTexture);

protected:
    void interact(std::shared_ptr<Entity> &e) override;
    void onKill() override;

    std::bernoulli_distribution shotDistribution;
};
}

#endif // ALIEN_H
