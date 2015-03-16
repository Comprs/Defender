#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

namespace Defender
{
class Player : public Entity
{
public:
    Player(std::vector<std::shared_ptr<Entity>>& newEntities,
           Defender::Room& newRoom,
           std::shared_ptr<Defender::Texture> newTexture) :
        Entity(newEntities, newRoom, newTexture) {}

    void update(const double time, std::shared_ptr<Entity> self) override;
    void interact(std::shared_ptr<Entity>& e) override;
    void onKill() override;
};
}

#endif // PLAYER_H
