#ifndef ABDUCTOR_H
#define ABDUCTOR_H

#include "alien.h"
#include "man.h"

namespace Defender
{
class Man;
class Abductor : public Alien
{
    friend class Man;
public:
    Abductor(Room& room, std::shared_ptr<Texture> texture);
    void interact(Entity& entity) override;
    void interact(Man& man) override;
    void afterInteraction() override;

protected:
    void update(const double time) override;
    void onKill() override;

private:
    Man* abducting = nullptr;
    Man* target = nullptr;
    double distanceToTarget;
};
}

#endif // ABDUCTOR_H
