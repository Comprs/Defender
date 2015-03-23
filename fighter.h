#ifndef FIGHTER
#define FIGHTER

#include "alien.h"

namespace Defender
{
class Fighter : public Alien
{
public:
    Fighter(Room& room, std::shared_ptr<Texture> texture);
    void interact(Entity& entity) override;
    void update(const double time) override;

protected:
    pseudo_random_distribution diveDistribution;
    pseudo_random_distribution swapDistrubution;

    void onKill() override;
};
}

#endif // FIGHTER

