#ifndef FIGHTER
#define FIGHTER

#include "alien.h"

namespace Defender
{
class Fighter : public Alien
{
public:
    Fighter(std::vector<std::shared_ptr<Entity>>& newEntities,
            Defender::Room& newRoom,
            std::shared_ptr<Defender::Texture> newTexture);

protected:
    void update(const double time, std::shared_ptr<Entity> self) override;
    void onKill() override;

    std::bernoulli_distribution diveDistribution;
    std::bernoulli_distribution swapDistrubution;
};
}

#endif // FIGHTER

