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
    void interact(Player& player) override;
    void interact(PlayerProjectile& playerProjectile) override;
    void interactWithBomb() override;

protected:
    pseudo_random_distribution shotDistribution;
    void onKill() override;
};
}

#endif // ALIEN_H
