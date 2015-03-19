#ifndef FIGHTER
#define FIGHTER

#include "alien.h"

namespace Defender
{
class Fighter : public Alien
{
public:
    Fighter(Room& newRoom, std::shared_ptr<Texture> newTexture);

protected:
    void update(const double time, std::shared_ptr<Entity> self) override;
    void onKill() override;

    pseudo_random_distribution diveDistribution;
    pseudo_random_distribution swapDistrubution;
};
}

#endif // FIGHTER

