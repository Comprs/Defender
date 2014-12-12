#ifndef MAN_H
#define MAN_H

#include "entity.h"

namespace Defender
{
class Man : public Entity
{
public:
    Man(std::vector<std::shared_ptr<Entity>>& newEntities,
        Defender::Room& newRoom,
        std::shared_ptr<Defender::Texture> newTexture) :
        Entity(newEntities, newRoom, newTexture) {}

    void update(const double time, std::shared_ptr<Entity> self) override;

protected:
    void interact(std::shared_ptr<Entity> &e) override;

private:
    bool abducted = false;
};
}

#endif // MAN_H
