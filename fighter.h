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

    Defender::pseudo_random_distribution diveDistribution;
    Defender::pseudo_random_distribution swapDistrubution;
};
}

#endif // FIGHTER

