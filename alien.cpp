#include "alien.h"

#include "player.h"
#include "playerprojectile.h"

void Defender::Alien::interact(std::shared_ptr<Entity> &e)
{
    if (auto p = std::dynamic_pointer_cast<PlayerProjectile>(e))
    {
        if (intersect(*p))
        {
            p->kill();
            kill();
        }
    }
    if (auto p = std::dynamic_pointer_cast<Player>(e))
    {
        if (intersect(*p))
        {
            p->kill();
            kill();
        }
    }
}
