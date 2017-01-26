#ifndef PLAYER_H
#define PLAYER_H

#include "entity.hpp"

namespace Defender
{
class Player : public Entity
{
public:
    Player(Room& room, std::shared_ptr<Texture> texture);

    void update(const double time) override;
    void interact(Entity& entity);
    void interact(AlienProjectile& alienProjectile) override;
    void onKill() override;
};
}

#endif // PLAYER_H
