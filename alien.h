#ifndef ALIEN_H
#define ALIEN_H

#include "entity.h"
#include "pseudorandomdistribution.h"

namespace Defender
{
class Alien : public Entity
{
public:
    Alien(Room& room, std::shared_ptr<Texture> texture);

protected:
    void interact(std::shared_ptr<Entity> &e) override;
    void onKill() override;

    pseudo_random_distribution shotDistribution;
};
}

#endif // ALIEN_H
