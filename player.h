#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

namespace Defender
{
class Player : public Entity
{
public:
    Player(Room& newRoom, std::shared_ptr<Texture> newTexture) : Entity(newRoom, newTexture) {}

    void update(const double time, std::shared_ptr<Entity> self) override;
    void interact(std::shared_ptr<Entity>& e) override;
    void onKill() override;
};
}

#endif // PLAYER_H
