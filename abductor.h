#ifndef ABDUCTOR_H
#define ABDUCTOR_H

#include "alien.h"
#include "man.h"

namespace Defender
{
class Abductor : public Alien
{
    friend class Man;
public:
    Abductor(Room& room, std::shared_ptr<Texture> texture);
    void interact(Entity& entity) override;
    void interact(Man& man) override;
    void afterInteraction() override;
    void update(const double time) override;
    void detachMan();

protected:
    void onKill() override;

private:
    Man* abducting = nullptr;
    Man* target = nullptr;
    double distanceToTarget;
};
}

#endif // ABDUCTOR_H
