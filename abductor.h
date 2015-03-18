#ifndef ABDUCTOR_H
#define ABDUCTOR_H

#include "alien.h"
#include "man.h"

namespace Defender
{
class Man;
class Abductor : public Alien
{
public:
    Abductor(std::vector<std::shared_ptr<Entity>>& newEntities, Room& newRoom,
             std::shared_ptr<Texture> newTexture);

protected:
    void interact(std::shared_ptr<Entity> &e) override;
    void update(const double time, std::shared_ptr<Entity> self) override;
    void onKill() override;

private:
    std::weak_ptr<Man> target;
    std::weak_ptr<Entity> self_ptr;
};
}

#endif // ABDUCTOR_H
