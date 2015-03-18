#ifndef ALIEN_H
#define ALIEN_H

#include "entity.h"
#include "pseudorandomdistribution.h"

namespace Defender
{
class Alien : public Entity
{
public:
    Alien(std::vector<std::shared_ptr<Entity>>& newEntities, Room& newRoom,
          std::shared_ptr<Texture> newTexture);

protected:
    void interact(std::shared_ptr<Entity> &e) override;
    void onKill() override;

    std::normal_distribution<> positionDistribution;
    pseudo_random_distribution shotDistribution;
};
}

#endif // ALIEN_H
