#ifndef MUTANT_H
#define MUTANT_H

#include "alien.h"

namespace Defender
{
class Mutant : public Alien
{
public:
    Mutant(std::vector<std::shared_ptr<Entity>>& newEntities,
           Defender::Room& newRoom,
           std::shared_ptr<Defender::Texture> newTexture,
           Vector2D startPosition);

protected:
    void interact(std::shared_ptr<Entity>& e) override;
};
}

#endif // MUTANT_H
