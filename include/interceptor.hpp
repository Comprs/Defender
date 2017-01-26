#ifndef INTERCEPTOR_H
#define INTERCEPTOR_H

#include "alien.hpp"

namespace Defender
{
class Interceptor : public Alien
{
public:
    Interceptor(Room& room, std::shared_ptr<Texture> texture);
    void interact(Entity& entity) override;
    void update(const double time) override;
    void interact(Player& player) override;

protected:
    void onKill() override;

private:
    pseudo_random_distribution moveDistribution;
    pseudo_random_distribution interceptorShotDist;
    std::uniform_real_distribution<> horizontalDistribution;
    std::uniform_real_distribution<> verticalDistribution;
    Vector2D target;
};
}

#endif // INTERCEPTOR_H

