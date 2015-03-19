#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

namespace Defender
{
class Player : public Entity
{
public:
    Player(Room& room, std::shared_ptr<Texture> texture);

    void update(const double time, std::shared_ptr<Entity> self) override;
    void interact(std::shared_ptr<Entity>& e) override;
    void onKill() override;
};
}

#endif // PLAYER_H
